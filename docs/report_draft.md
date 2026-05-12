# Borrador Técnico — Segundo Avance
## Sistema de Integridad de Archivos (SIA)

**Equipo:** Ricardo Hervey · Marco Guadalupe · Josue Castro · Sergio Sepúlveda
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
Risk Analyzer → SAFE / MODIFIED / NEW
```

---

## Pruebas Realizadas

### Compilación

```bash
make
```

Genera los binarios:

```
bin/file_monitor          # con símbolos
bin/file_monitor_strip    # sin símbolos
```

### Caso 1 — Archivo nuevo (sin baseline previo)

```bash
./bin/file_monitor data/test_file.txt
```

Salida:

```
[INFO] Archivo nuevo detectado: data/test_file.txt
[INFO] Hash generado: 4a7f3c8d
[OK]   Estado: NEW — Baseline registrado en SQLite.
```

### Caso 2 — Archivo sin modificaciones

```bash
./bin/file_monitor data/test_file.txt
```

Salida:

```
[INFO] Escaneando: data/test_file.txt
[OK]   Estado: SAFE — Sin modificaciones detectadas.
```

### Caso 3 — Archivo modificado

```bash
echo "modificacion de prueba" >> data/test_file.txt
./bin/file_monitor data/test_file.txt
```

Salida:

```
[INFO] Escaneando: data/test_file.txt
[WARN] Estado: MODIFIED — Hash no coincide con el baseline.
```

### Análisis estático del binario

```bash
strings bin/file_monitor > analysis/strings_output.txt
r2 -A bin/file_monitor_strip
```

Ver capturas en `/evidence/`.

---

## Hallazgos del Análisis

### Strings extraídos relevantes

```
SAFE
MODIFIED
NEW
baseline.db
data/test_file.txt
[INFO]
[WARN]
[ERROR]
libsqlite3.so
```

No se encontraron credenciales ni rutas absolutas embebidas en el binario.

### Funciones identificadas (Ghidra / Radare2)

| Función | Descripción |
|---------|-------------|
| `main` | Punto de entrada, orquesta los módulos |
| `scan_file` | Apertura y lectura del archivo objetivo |
| `compute_hash` | Procesamiento por bloques para generar el hash |
| `load_baseline` | Consulta SQLite para obtener el hash previo |
| `save_baseline` | Inserción o actualización del registro en SQLite |
| `analyze_risk` | Comparación de hashes y clasificación del estado |

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
| Binario debug expone símbolos | Baja | Distribución usa versión strip |

---

## Trabajo Pendiente

No se implementa aún:

* Algoritmo criptográfico SHA-256 mediante OpenSSL
* Monitoreo periódico automático
* Configuración externa mediante archivo `.conf`
* Clasificación avanzada de eventos: `TAMPERED`, `DELETED`, `RESTORED`
* Firma del baseline para prevenir manipulación de la referencia
* Reporte de salida en formato JSON

Estas funcionalidades se desarrollarán en la entrega final del proyecto.

---

*Borrador técnico — Segundo Avance del PIA. Sujeto a actualización.*
