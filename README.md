# Sistema de Integridad de Archivos (SIA)

## Objetivo del Proyecto

Desarrollar un sistema modular en C++ capaz de detectar cambios en archivos mediante el uso de funciones hash y comparación contra un baseline previamente almacenado.

El sistema permitirá identificar modificaciones en archivos críticos simulando técnicas reales utilizadas en herramientas de ciberseguridad.

---

## Descripción Técnica

Este proyecto implementa un **File Integrity Monitoring System (FIM)** desarrollado en C++, diseñado para:

* Leer archivos del sistema
* Generar un valor hash representativo del contenido
* Guardar un baseline inicial
* Comparar hashes en ejecuciones posteriores
* Detectar cambios en archivos monitoreados

El sistema está diseñado bajo una **arquitectura modular**, permitiendo la separación clara de responsabilidades entre componentes.

Los módulos principales del sistema son:

* **File Scanner:** Lectura de archivos
* **Hash Engine:** Generación de hashes
* **Baseline Manager:** Gestión del baseline
* **Risk Analyzer:** Clasificación del estado del archivo

---

## Alcance y Límites

### Alcance (Primera Entrega)

El sistema será capaz de:

* Leer un archivo fijo ubicado en:

data/test_file.txt

* Generar un hash del contenido
* Crear un baseline inicial si no existe
* Comparar hashes en ejecuciones posteriores
* Detectar modificaciones en el archivo
* Mostrar el estado del archivo:

SAFE
MODIFIED

---

### Límites (Primera Entrega)

No se implementará aún:

* Monitoreo de múltiples archivos
* Entrada interactiva por usuario
* Configuración mediante archivos externos
* Monitoreo periódico automático
* Clasificación avanzada de riesgos

Estas funcionalidades se desarrollarán en entregas posteriores.

---

## Compilación

Para compilar el proyecto:

```bash
make
```

Esto generará el ejecutable:

file_monitor

---

## Ejecución

Para ejecutar el programa:

```bash
./file_monitor
```

El programa analizará el archivo:

data/test_file.txt

---

## Estructura del Proyecto

```text
PIA_Sistema_Integridad_Archivos/
│
├── README.md
├── Makefile
├── .gitignore
│
├── src/
│   ├── main.cpp
│   ├── file_scanner.cpp
│   ├── hash_engine.cpp
│   ├── baseline_manager.cpp
│   ├── risk_analyzer.cpp
│
├── include/
│   ├── file_scanner.h
│   ├── hash_engine.h
│   ├── baseline_manager.h
│   ├── risk_analyzer.h
│
├── docs/
│   └── design.md
│
├── evidence/
│
└── data/
    ├── test_file.txt
    └── baseline.txt

---

## Integrantes y Responsabilidades Técnicas

(Asignación inicial sugerida)

Integrante 1 — File Scanner
Responsable de la lectura de archivos y verificación de existencia.

Integrante 2 — Hash Engine
Responsable de la generación del hash del contenido del archivo.

Integrante 3 — Baseline Manager
Responsable del almacenamiento y comparación del baseline.

Integrante 4 — Risk Analyzer
Responsable de la interpretación del estado del archivo.

---

## Tecnologías Utilizadas

Lenguaje:

C++

Herramientas:

* g++
* Make
* Visual Studio Code
* Ubuntu Virtual Machine

---

## Estado Actual del Proyecto

Fase: Desarrollo inicial (Primer Avance)

Funcionalidad mínima implementada:

* Lectura de archivo
* Generación de hash simple
* Creación de baseline
* Comparación de hashes
* Detección de cambios

Funcionalidad en desarrollo:

* Modularización completa
* Clasificación de eventos
* Mejora del sistema de hashing

---

## Notas Técnicas

El sistema utiliza un algoritmo de hash simple basado en operaciones aritméticas para el primer avance.

En fases posteriores se migrará a algoritmos criptográficos más robustos como SHA256.
