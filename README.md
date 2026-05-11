# Sistema de Integridad de Archivos (SIA)

## Objetivo del Proyecto

Desarrollar un sistema modular en C++ capaz de detectar cambios en archivos mediante el uso de funciones hash y comparación contra un baseline previamente almacenado.

El sistema permitirá identificar modificaciones en archivos críticos simulando técnicas reales utilizadas en herramientas de ciberseguridad para monitoreo de integridad de archivos.

---

## Descripción Técnica

Este proyecto implementa un **Sistema de Integridad de Archivos (SIA)** desarrollado en C++, bajo una arquitectura modular.

El sistema realiza las siguientes operaciones:

* Leer archivos del sistema
* Generar un valor hash representativo del contenido
* Guardar un baseline inicial
* Comparar hashes en ejecuciones posteriores
* Detectar modificaciones en archivos
* Evolucionar hacia persistencia estructurada mediante SQLite para soportar multiples registros y monitoreo estable

Los módulos principales del sistema son:

* **File Scanner:** Lectura del archivo objetivo
* **Hash Engine:** Generación del hash del contenido
* **Baseline Manager:** Creacion y Lectura del Baseline
* **Risk Analyzer:** Evaluacion del estado del archivo

---

## Alcance y Límites

### Alcance (Primera Entrega)

El sistema actualmente es capaz de:

* Leer un archivo fijo ubicado en:

data/test_file.txt

* Generar un hash del contenido
* Crear un baseline inicial si no existe
* Comparar hashes en ejecuciones posteriores
* Detectar modificaciones en el archivo
* Mostrar el estado del archivo:

SAFE
MODIFIED

* Compilar correctamente mediante Makefile
* Ejecutarse en entorno Linux dentro de una Maquina Virtual

---

### Límites (Primera Entrega)

No se implementá aún:

* Monitoreo de múltiples archivos
* Seleccion dinamica de archivos
* Configuración mediante archivos externos
* Uso de algoritmos criptografcos (SHA256)
* Persistencia estructurada mediante SQLite
* Monitoreo periódico automático

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
│   └── risk_analyzer.cpp
│
├── include/
│   ├── file_scanner.h
│   ├── hash_engine.h
│   ├── baseline_manager.h
│   └── risk_analyzer.h
│
├── docs/
│   ├── design.md
│   ├── roadmap-md
│   └── project_overview.md
│
├── evidence/
│
└── data/
    ├── test_file.txt
    └── baseline.txt
```

---

## Integrantes y Responsabilidades Técnicas

Ricardo Hervey Estrada Garcia— File Scanner
Responsable de la lectura de archivos y verificación de existencia.

Marco Antonio Guadalupe — Hash Engine
Responsable de la generación del hash del contenido del archivo.

Josue Israel Castro Aguilar — Baseline Manager e Integracion
Responsable del almacenamiento y comparación del baseline.

Sergio Pedro Sepulveda Rodriguez — Risk Analyzer
Responsable de la interpretación del estado del archivo.

---

## Tecnologías Utilizadas

Lenguaje:

C++

Herramientas:

* g++
* Make
* Git
* Github
* Visual Studio Code
* Ubuntu Virtual Machine
* SQLite (planeado para avance 2)

---

## Estado Actual del Proyecto

Fase:

Primer Avance - Funcionalidad Base Implementada

El sistema actualmente:

* Compila correctamente
* Ejecuta sin errores
* Genera Hashes
* Crea Baseline
* Detecta modificaciones

---

## Notas Técnicas
El sistema utiliza actualmente un algoritmo de hash simple basado en operaciones aritméticas para el primer avance.

Durante la segunda fase del proyecto, el Hash Engine evolucionará hacia un procesamiento más eficiente por bloques y los hashes serán manejados mediante std::string para mantener compatibilidad con futuras mejoras criptográficas.

La persistencia del baseline evolucionará de archivo plano hacia almacenamiento estructurado utilizando SQLite.

En fases posteriores se contempla la integración de algoritmos criptográficos más robustos como SHA256.

El sistema se encuentra preparado para escalabilidad, soporte multiarchivo y clasificación avanzada de eventos.