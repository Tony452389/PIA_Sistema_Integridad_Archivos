# Pruebas Técnicas — Sistema de Integridad de Archivos (SIA)

## Entorno de pruebas

- Sistema operativo: Ubuntu 24.04 LTS
- Arquitectura: x86-64
- Compilador: GCC 13.3.0
- Base de datos: SQLite3

---

# 1. Compilación

## Compilación Debug

```bash
g++ -g -std=c++17 src/*.cpp -Iinclude -lsqlite3 -o bin/file_monitor_debug
```

## Compilación Release

```bash
g++ -O2 -std=c++17 src/*.cpp -Iinclude -lsqlite3 -o bin/file_monitor_release
strip bin/file_monitor_release
```

---

# 2. Ejecución

La ejecución debe realizarse desde la raíz del proyecto.

## Ejecución de la versión Debug

```bash
./bin/file_monitor_debug
```

## Ejecución de la versión Release

```bash
./bin/file_monitor_release
```

---

# 3. Escenarios de Prueba

## Escenario 1 — Inicialización del entorno y generación de baseline

### Objetivo

Verificar:

- Creación de la base de datos SQLite
- Creación de tablas `Files` y `Baselines`
- Carga de archivos desde `targets.txt`
- Inserción inicial de baselines

### Procedimiento

1. Ejecutar el programa
2. Seleccionar la opción `2` (Restore Test Environment)
3. Ejecutar nuevamente el programa
4. Seleccionar la opción `1` (Run Monitor)

### Resultado esperado

- Creación correcta de `data/baseline.db`
- Creación de tablas SQLite
- Inserción inicial de archivos monitoreados
- Registro de eventos iniciales en `Baselines`

### Salida relevante

```text
===== File Integrity Monitor =====

1. Run Monitor
2. Restore Test Environment
3. Exit

Select an option: 1

Database initialized successfully!
Files table created successfully!
Baselines table created successfully!

Processing: data/config.txt
Event: NEW

Processing: data/notes.txt
Event: NEW
```

---

## Escenario 2 — Detección de modificación de archivo

### Objetivo

Verificar que el sistema detecta cambios en el contenido de un archivo mediante comparación de hashes.

### Procedimiento

1. Modificar manualmente el archivo:

```bash
nano data/config.txt
```

2. Agregar o modificar contenido
3. Guardar cambios
4. Ejecutar nuevamente el monitor

```bash
./bin/file_monitor_debug
```

5. Seleccionar opción `1`

### Resultado esperado

- El sistema recalcula el hash
- Se detecta diferencia respecto al baseline anterior
- Se registra un evento `MODIFIED`

### Salida relevante

```text
Processing: data/config.txt
Event: MODIFIED
```

---

## Escenario 3 — Detección de eliminación de archivo

### Objetivo

Verificar que el sistema detecta archivos previamente registrados que ya no existen en el sistema.

### Procedimiento

1. Eliminar un archivo monitoreado:

```bash
rm data/temp.log
```

2. Ejecutar nuevamente el monitor

```bash
./bin/file_monitor_debug
```

3. Seleccionar opción `1`

### Resultado esperado

- El sistema detecta que el archivo ya no existe físicamente
- Se conserva referencia previa en SQLite
- Se registra un evento `DELETED`

### Salida relevante

```text
Processing: data/temp.log
Event: DELETED
```

---

## Escenario 4 — Restauración del entorno de pruebas

### Objetivo

Verificar la restauración completa del entorno de pruebas.

### Procedimiento

1. Ejecutar el programa
2. Seleccionar opción `2` (Restore Test Environment)

### Resultado esperado

- Eliminación de `baseline.db`
- Recreación de archivos de prueba
- Restauración de `targets.txt`
- Restauración del contenido original de archivos

### Salida relevante

```text
Test environment restored successfully.
```

---

# 4. Verificación de Binarios

## Objetivo

Verificar diferencias entre binario debug y release.

### Procedimiento

```bash
ls -lh bin
```

### Resultado esperado

- La versión debug posee mayor tamaño
- La versión release posee menor tamaño tras aplicar `strip`

---

## Verificación de símbolos en versión Debug

### Procedimiento

```bash
nm bin/file_monitor_debug | less
```

### Resultado esperado

Visualización de símbolos y nombres de funciones originales:

```text
processFile
generateHash
insertBaseline
initializeDatabase
displayLatestBaselines
```

---

## Verificación de versión Release

### Procedimiento

```bash
nm bin/file_monitor_release
```

### Resultado esperado

- Reducción significativa de símbolos
- Mayor dificultad para reversing

---

# 5. Evidencias Relacionadas

| Evidencia | Descripción |
|---|---|
| `evidence/2do_avance/execution_1.png` | Ejecución inicial del monitor |
| `evidence/2do_avance/execution_2.png` | Detección de modificación de archivo |
| `evidence/2do_avance/deleted_event.png` | Detección de archivo eliminado |
| `evidence/2do_avance/restore_environment.png` | Restauración del entorno de pruebas |
| `evidence/2do_avance/ghidra_main.png` | Análisis estático del binario en Ghidra |

---

# 6. Observaciones Técnicas

- El sistema utiliza SQLite para persistencia de baselines.
- Los hashes se calculan mediante un rolling hash polinomial.
- El procesamiento de archivos se realiza en bloques de 4096 bytes.
- El programa fue compilado en versiones debug y release para facilitar análisis estático y comparación de reversing.
- La versión release