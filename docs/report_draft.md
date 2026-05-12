# Borrador Técnico — Segundo Avance
## Sistema de Integridad de Archivos (SIA)

**Equipo:** Ricardo Estrada · Marco Vargas · Josue Castro · Sergio Sepúlveda
**Fecha:** Mayo 2026

---

## Descripción del Sistema

El Sistema de Integridad de Archivos (SIA) es una herramienta de ciberseguridad desarrollada en C++ que detecta modificaciones no autorizadas en archivos del sistema mediante comparación de hashes contra un baseline almacenado.

El sistema simula técnicas reales utilizadas en herramientas como Tripwire y AIDE, empleadas en entornos profesionales para monitoreo de integridad de archivos críticos.

---

## Diseño y Arquitectura

El sistema opera bajo una arquitectura modular de cuatro componentes que trabajan en secuencia:

* **File Scanner:** Lee el archivo objetivo y verifica su existencia en el sistema
* **Hash Engine:** Procesa el contenido por bloques y genera un hash representativo
* **Baseline Manager:** Consulta o actualiza el registro del archivo en la base de datos SQLite
* **Risk Analyzer:** Compara el hash actual contra el almacenado y determina el estado del archivo

El flujo de operación es el siguiente:

```
Archivo objetivo
      |
File Scanner → lectura y validación
      |
Hash Engine → generación del hash
      |
Baseline Manager → consulta SQLite
      |
Risk Analyzer → NEW / UNCHANGED / MODIFIED / DELETED
```

---

## Pruebas Realizadas

### Compilación

```bash
make
```

Genera el ejecutable en la raíz del repositorio:

```
./file_monitor
```

> **Nota:** Los ejecutables en la carpeta `bin/` (`file_monitor_debug` y `file_monitor_release`) fueron generados manualmente durante esta fase. El Makefile será ajustado para producirlos automáticamente en la siguiente entrega.

### Ejecución

Al ejecutar el programa se presenta un menú interactivo con las siguientes opciones:

```
===== File Integrity Monitor =====

1. Run Monitor
2. Restore Test Environment
3. Exit

Select an option:
```

**Opción 1 — Run Monitor:** Inicializa la base de datos, carga la lista de archivos desde `data/targets.txt` y procesa cada uno. Al finalizar muestra una tabla con el estado actual de todos los archivos monitoreados.

**Opción 2 — Restore Test Environment:** Restaura el entorno de prueba al estado inicial, permitiendo repetir las pruebas desde cero.

**Opción 3 — Exit:** Cierra el programa.

Para agregar archivos al monitoreo, se debe incluir su ruta dentro de `data/targets.txt`. Los resultados pueden no ser tan consistentes como con los archivos de prueba utilizados en las evidencias, dependiendo del contenido y ubicación de los archivos agregados.

---

### Caso 1 — Primera ejecución (baseline vacío)

Al ejecutar la opción 1 por primera vez, el sistema registra todos los archivos como nuevos:

```
Select an option: 1

Database initialized successfully!
Files table created successfully!
Baselines table created successfully!

Processing: data/config.txt
File inserted successfully!
Baseline inserted successfully!
Event: NEW

Processing: data/notes.txt
File inserted successfully!
Baseline inserted successfully!
Event: NEW

Processing: data/system.conf
File inserted successfully!
Baseline inserted successfully!
Event: NEW

Processing: data/temp.log
File inserted successfully!
Baseline inserted successfully!
Event: NEW

========================= Latest Baselines =========================
File                    Event       Timestamp
-------------------------------------------------------------------
data/config.txt         NEW         2026-05-12 01:36:22
data/notes.txt          NEW         2026-05-12 01:36:22
data/system.conf        NEW         2026-05-12 01:36:22
data/temp.log           NEW         2026-05-12 01:36:22
====================================================================
```

---

### Caso 2 — Archivo modificado

Tras modificar `data/config.txt` y ejecutar nuevamente la opción 1:

```
Select an option: 1

Database initialized successfully!
Files table created successfully!
Baselines table created successfully!

Processing: data/config.txt
Baseline inserted successfully!
Event: MODIFIED

Processing: data/notes.txt
Baseline inserted successfully!
Event: UNCHANGED

Processing: data/system.conf
Baseline inserted successfully!
Event: UNCHANGED

Processing: data/temp.log
Baseline inserted successfully!
Event: UNCHANGED

========================= Latest Baselines =========================
File                    Event       Timestamp
-------------------------------------------------------------------
data/config.txt         MODIFIED    2026-05-12 01:39:09
data/notes.txt          UNCHANGED   2026-05-12 01:39:09
data/system.conf        UNCHANGED   2026-05-12 01:39:09
data/temp.log           UNCHANGED   2026-05-12 01:39:09
====================================================================
```

---

### Caso 3 — Archivo eliminado

Al eliminar `data/temp.log` del sistema y ejecutar la opción 1:

```
Select an option: 1

Database initialized successfully!
Files table created successfully!
Baselines table created successfully!

Processing: data/config.txt
Baseline inserted successfully!
Event: UNCHANGED

Processing: data/notes.txt
Baseline inserted successfully!
Event: UNCHANGED

Processing: data/system.conf
Baseline inserted successfully!
Event: UNCHANGED

Processing: data/temp.log
Baseline inserted successfully!
Event: DELETED

========================= Latest Baselines =========================
File                    Event       Timestamp
-------------------------------------------------------------------
data/config.txt         UNCHANGED   2026-05-12 01:40:32
data/notes.txt          UNCHANGED   2026-05-12 01:40:32
data/system.conf        UNCHANGED   2026-05-12 01:40:32
data/temp.log           DELETED     2026-05-12 01:40:32
====================================================================
```

---

### Caso 4 — Restauración del entorno de prueba

Al seleccionar la opción 2, el sistema restaura todos los archivos de prueba a su estado original:

```
Select an option: 2

Test environment restored successfully.
```

---

> Ver capturas completas en `/evidence/2do_Avance/`.

---

### Análisis estático del binario

El análisis estático se realizó sobre el binario `file_monitor_debug` utilizando las herramientas `strings` y Ghidra. El objetivo fue inspeccionar el contenido embebido en el ejecutable sin necesidad de ejecutarlo, con la finalidad de verificar su comportamiento, dependencias y posibles cadenas de texto expuestas.

El proceso consistió en:

1. Ejecutar `strings` sobre el binario para extraer todas las cadenas de texto legibles embebidas directamente en el archivo.
2. Cargar el binario en Ghidra para realizar análisis de descompilación, identificar funciones mediante el Function Call Graph y revisar la lógica interna del programa sin acceso al código fuente.

```bash
strings bin/file_monitor_debug > analysis/strings_output.txt
```

Ver capturas en `/evidence/2do_Avance/`.

---

## Hallazgos del Análisis

### Strings extraídos relevantes

```
NEW
UNCHANGED
MODIFIED
DELETED
baseline.db
data/test_file.txt
libsqlite3.so.0
```

No se encontraron credenciales embebidas en el binario. Se identificó una ruta relativa (`data/test_file.txt`) correspondiente al archivo de prueba utilizado durante el desarrollo.

### Funciones identificadas (Ghidra)

El Function Call Graph generado por Ghidra muestra a `main` como nodo central que invoca directamente a los siguientes componentes:

| Función | Descripción |
|---------|-------------|
| `main` | Punto de entrada, presenta el menú y orquesta los módulos |
| `initializeDatabase` | Inicialización de la base de datos y creación de tablas |
| `loadTargets` | Lectura de la lista de archivos desde `targets.txt` |
| `processFile` | Procesamiento individual de cada archivo monitoreado |
| `displayLatestBaselines` | Presentación de la tabla de estados al finalizar |
| `restoreTestEnvironment` | Restauración de los archivos de prueba al estado inicial |

### Notas de ingeniería inversa

El hash actual es aritmético y visible en Ghidra como un loop simple sobre el buffer. No utiliza instrucciones criptográficas. Será reemplazado por SHA-256 en la entrega final.

La dependencia a `libsqlite3` es observable en la tabla de importaciones del binario, confirmando la integración con SQLite.

---

## Riesgos y Mitigaciones

| Riesgo | Severidad | Mitigación |
|--------|-----------|------------|
| Hash aritmético es colisionable | Alta | Migrar a SHA-256 en la entrega final |
| `baseline.db` no está cifrado | Media | Implementar firma HMAC en fase siguiente |
| Sin monitoreo continuo | Baja | Planificado: daemon con `inotify` o cron |
| Binario debug expone símbolos | Baja | Distribución usa versión release |

---

## Trabajo Pendiente

No se implementa aún:

* Algoritmo criptográfico SHA-256 mediante OpenSSL
* Monitoreo periódico automático
* Configuración externa mediante archivo `.conf`
* Clasificación de eventos: `TAMPERED`, `DELETED`, `RESTORED`
* Firma del baseline para prevenir manipulación de la referencia
* Reporte de salida en formato JSON

Estas funcionalidades se desarrollarán en la entrega final del proyecto.

---

*Borrador técnico — Segundo Avance del PIA. Sujeto a actualización.*
