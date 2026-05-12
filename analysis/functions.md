# Análisis de Funciones mediante Ingeniería Inversa (Ghidra)

## Proyecto: Sistema de Integridad de Archivos (SIA) - 2.º Avance

Este documento detalla las funciones principales identificadas en el binario a través de las vistas **Symbol Tree**, **Decompiler** y **Defined Strings** de Ghidra. El análisis describe la responsabilidad de cada función y los hallazgos relevantes observados en el decompilador.

| Módulo | Función Detectada | Dirección (Entry Point) | Responsable | Comentario Técnico |
| :--- | :--- | :--- | :--- | :--- |
| Main / Integración | `main` | `00108f20` | Josué Castro | Punto de entrada del programa. Presenta un menú de 3 opciones por consola. Opción 1: inicializa la BD, carga `data/targets.txt` en un vector, llama a `processFile()` por cada ruta y finaliza mostrando los baselines. Opción 2: restaura el entorno de prueba. El bucle sobre el vector es visible en el decompilador como iteradores `__gnu_cxx::__normal_iterator`. |
| File Scanner / Risk Analyzer | `processFile` | `0010915a` | Ricardo Estrada / Sergio Sepúlveda | Función central del monitor. Evalúa si el archivo existe en disco (`existsOnSystem`) y en la BD (`existsInDatabase`) para determinar el evento: archivo nuevo → lo registra e inserta baseline; archivo existente → calcula hash e inserta baseline; archivo eliminado → inserta baseline con `EventType = "DELETED"`. El string `"DELETED"` aparece hardcodeado y es visible en Defined Strings. |
| Módulo 2: Hash Engine | `generateHash` | `00108890` | Marco Vargas | Implementa un rolling hash polinomial (`hash = hash * 31 + byte`). El decompilador muestra `0x1f` (31 en decimal) como multiplicador. Lee el archivo en bloques de 4096 bytes (`char buffer[4096]` visible en el stack frame), evitando cargar archivos completos en RAM. Retorna el hash como `std::string` para almacenarlo en SQLite. |
| Módulo 3: Baseline Manager | `initializeDatabase` | `00104f4a` | Josué Castro | Abre `data/baseline.db` con `sqlite3_open` y crea las tablas `Files` y `Baselines` con `sqlite3_exec`. Las sentencias SQL completas están embebidas en texto plano en el binario y son visibles en Defined Strings. Maneja errores de creación de cada tabla de forma independiente con `sqlite3_free`. |
| Módulo 3: Baseline Manager | `insertBaseline` | `00105370` | Josué Castro | Registra el estado de integridad de un archivo en la tabla `Baselines`, vinculando `FileID`, hash, timestamp y tipo de evento. Es llamada por `processFile` en cada ciclo de monitoreo. |
| Módulo 3: Baseline Manager | `displayLatestBaselines` | `00105020` | Josué Castro | Abre la BD y ejecuta un `INNER JOIN` entre `Baselines` y `Files` filtrando con `MAX(BaselineID) GROUP BY FileID`, lo que garantiza mostrar solo el evento más reciente por archivo. La consulta SQL completa es visible en Defined Strings. Formatea la salida en columnas de ancho fijo con `std::setw`. |

---

## Notas de Análisis del Binario

**Binario non-stripped:** Los nombres de todas las funciones se conservan en la tabla de símbolos. Esto permitió identificar directamente la responsabilidad de cada función desde el Symbol Tree, sin necesidad de inferirla desde el comportamiento del código.

**Strings SQL en texto plano:** Las sentencias `CREATE TABLE` y `SELECT` están embebidas sin ofuscación en el segmento `.rodata`. Desde Defined Strings es posible reconstruir el schema completo de la BD (`Files` y `Baselines`) y la lógica de consulta sin ejecutar el programa.

**Stack Canary en todas las funciones:** El decompilador muestra en todas las funciones analizadas una lectura de `in_FS_OFFSET + 0x28` al inicio y una verificación del mismo valor antes de retornar. Indica que el binario fue compilado con protección contra buffer overflow (`-fstack-protector`).

**Rutas hardcodeadas:** Las rutas `data/baseline.db` y `data/targets.txt` aparecen como strings fijos en el binario, visibles en Defined Strings. El programa depende de que esas rutas existan relativas al directorio de trabajo.
