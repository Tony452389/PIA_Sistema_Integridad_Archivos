# Notas de Ingeniería Inversa - Proyecto SIA

## Herramienta utilizada
**Ghidra** — Se cargó el binario ELF de 64 bits compilado para Linux x86-64. Se utilizaron las vistas de **Decompiler**, **Symbol Tree** y **Defined Strings** para identificar funciones, lógica de control y datos embebidos.

---

## 1. Identificación de Funciones en el Symbol Tree

Al importar el binario en Ghidra, el **Symbol Tree** lista automáticamente los símbolos presentes. Se identificaron las siguientes funciones principales:

| Función | Dirección (Entry Point) |
| :--- | :--- |
| `main` | `00108f20` |
| `processFile` | `0010915a` |
| `generateHash` | `00108890` |
| `initializeDatabase` | `00104f4a` |
| `insertBaseline` | `00105370` |
| `displayLatestBaselines` | `00105020` |

**Observación:** El binario **no fue despojado** (`non-stripped`). Los nombres originales de las funciones se conservan en la tabla de símbolos, lo que facilita el reversing directamente. En un binario despojado (`stripped`), estas funciones aparecerían como `FUN_00108f20`, `FUN_0010915a`, etc., y habría que inferir su propósito desde el comportamiento del código.

---

## 2. Strings Identificados con "Defined Strings"

La vista **Defined Strings** de Ghidra lista todas las cadenas de texto embebidas en el segmento `.rodata` del binario. Se encontraron los siguientes strings relevantes:

**Interfaz de usuario:**
```
===== File Integrity Monitor =====
1. Run Monitor
2. Restore Test Environment
3. Exit
Select an option:
```

**Mensajes de operación:**
```
Processing:
Event:
File not found.
Error opening file.
Exiting program.
Invalid option.
```

**Mensajes de base de datos:**
```
Database initialized successfully!
Files table created successfully!
Baselines table created successfully!
Error creating Files table:
Error creating Baselines table:
Error opening database.
Error displaying baselines:
```

**Sentencias SQL completas (embebidas en `.rodata`):**
```sql
CREATE TABLE IF NOT EXISTS Files (
    FileID   INTEGER PRIMARY KEY AUTOINCREMENT,
    Name     TEXT NOT NULL,
    FilePath TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Baselines (
    BaselineID INTEGER PRIMARY KEY AUTOINCREMENT,
    FileID     INTEGER,
    Hash       TEXT NOT NULL,
    Timestamp  TEXT NOT NULL,
    EventType  TEXT NOT NULL,
    FOREIGN KEY(FileID) REFERENCES Files(FileID)
);

SELECT Files.FilePath, Baselines.EventType, Baselines.Timestamp
FROM Baselines
INNER JOIN Files ON Files.FileID = Baselines.FileID
WHERE BaselineID IN (
    SELECT MAX(BaselineID) FROM Baselines GROUP BY FileID
)
ORDER BY Files.FileID;
```

**Rutas de archivo hardcodeadas:**
```
data/baseline.db
data/targets.txt
```

**Observación:** La presencia de strings SQL en texto plano permite reconstruir el schema completo de la base de datos y entender la lógica de consulta sin necesidad de analizar el flujo de control. Un analista puede obtener esta información ejecutando únicamente `strings ./binario | grep -i "CREATE\|SELECT"` desde la terminal, sin correr el programa.

---

## 3. Comprensión del Binario por Función

### 3.1 `main` — Punto de entrada y control del flujo

El decompilador muestra que `main` presenta un menú de tres opciones leído desde `stdin`. La lógica es un bloque `if/else` sobre la variable `option`:

- **Opción 1 (Run Monitor):** Llama a `initializeDatabase()`, carga rutas desde `data/targets.txt` en un `std::vector`, itera sobre el vector llamando a `processFile()` para cada archivo, y finaliza con `displayLatestBaselines()`.
- **Opción 2 (Restore Test Environment):** Llama a `restoreTestEnvironment()`.
- **Opción 3 / inválida:** Imprime mensaje de salida o de error y termina.

El bucle de iteración es visible en el decompilador como llamadas a `__gnu_cxx::__normal_iterator`, que es la representación interna de un range-based for loop de C++ (`for (auto& filePath : targets)`).

### 3.2 `generateHash` — Motor de hashing

El decompilador revela el algoritmo central:

```c
hash = (ulong)(byte)buffer[i] + hash * 0x1f;
```

- `0x1f` equivale a 31 en decimal. Es un **rolling hash polinomial**, el mismo multiplicador utilizado por `java.lang.String.hashCode()`.
- El archivo se lee en bloques de **4096 bytes** (`char buffer[4096]`, visible en el stack frame). Esto evita cargar archivos completos en RAM y cumple el requerimiento de procesamiento por bloques de la Entrega 2.
- El resultado se retorna como `std::string` para almacenarse en SQLite.

### 3.3 `initializeDatabase` — Inicialización de la base de datos

La función abre `data/baseline.db` con `sqlite3_open` y ejecuta dos sentencias DDL con `sqlite3_exec`. Si alguna falla, imprime el error retornado por SQLite y libera la memoria con `sqlite3_free`. Las dos tablas creadas son:

- **Files:** almacena la ruta y nombre de cada archivo monitoreado.
- **Baselines:** almacena hash, timestamp y tipo de evento por cada captura, vinculada a `Files` por `FileID` (clave foránea).

### 3.4 `processFile` — Núcleo del monitor

Esta función integra la lógica de escaneo y clasificación. El decompilador muestra dos flags booleanos: `existsOnSystem` y `existsInDatabase`. A partir de ellos se derivan tres comportamientos:

| Escenario | `existsOnSystem` | `existsInDatabase` | Acción |
| :--- | :---: | :---: | :--- |
| Archivo nuevo | ✓ | ✗ | Registra en BD, calcula hash, inserta baseline |
| Archivo existente (modificado o sin cambios) | ✓ | ✓ | Calcula hash, inserta baseline |
| Archivo eliminado | ✗ | ✓ | Inserta baseline con `EventType = "DELETED"` |

El string `"DELETED"` aparece directamente en Defined Strings, confirmando que es un valor fijo hardcodeado y no calculado en tiempo de ejecución.

### 3.5 `displayLatestBaselines` — Visualización del estado actual

El decompilador muestra una consulta con `INNER JOIN` y un subquery `MAX(BaselineID) GROUP BY FileID`. Esto garantiza mostrar únicamente el evento más reciente por cada archivo. La salida se formatea en columnas de ancho fijo utilizando `std::setw`.

---

## 4. Hallazgos de Seguridad del Binario

### Stack Canary
Todas las funciones analizadas presentan el siguiente patrón al inicio y al final:

```c
// Prólogo — guarda el valor del canary
local_N = *(long *)(in_FS_OFFSET + 0x28);

// Epílogo — verifica que no fue modificado
if (local_N != *(long *)(in_FS_OFFSET + 0x28)) {
    __stack_chk_fail();   // termina el proceso
}
```

Esto indica que el binario fue compilado con **protección contra buffer overflow** (`-fstack-protector`). Si un atacante sobrescribiera el stack entre prólogo y epílogo, el valor del canary cambiaría y el proceso terminaría de forma controlada antes de ejecutar código arbitrario.

### Strings SQL sin ofuscación
Las sentencias SQL están en texto plano dentro de `.rodata`. El schema completo de la base de datos es recuperable sin ejecutar el binario, simplemente inspeccionando sus strings.

### Rutas hardcodeadas
Las rutas `data/baseline.db` y `data/targets.txt` están fijas. El programa siempre opera sobre esas rutas relativas al directorio de trabajo, sin posibilidad de configuración externa.
