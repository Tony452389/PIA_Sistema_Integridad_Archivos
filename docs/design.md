# Diseño Técnico — Sistema de Integridad de Archivos (SIA)

## Arquitectura General

El sistema sigue una arquitectura modular diseñada para detectar cambios en archivos mediante el uso de funciones hash y comparación contra un baseline almacenado previamente.

La arquitectura está preparada para evolucionar hacia un modelo de persistencia estructurada utilizando SQLite, permitiendo soportar múltiples registros y monitoreo escalable.

El sistema se compone de cuatro módulos principales que trabajan de forma secuencial:

File Scanner → Hash Engine → Baseline Manager → Risk Analyzer

Cada módulo cumple una función específica dentro del flujo general del programa.

---

## Módulos del Sistema

### 1. File Scanner

Responsable de:

- Verificar la existencia del archivo
- Leer el contenido completo del archivo
- Retornar el contenido como string

Archivo:

src/file_scanner.cpp  
include/file_scanner.h

---

### 2. Hash Engine

Responsable de:

- Generar un hash del contenido del archivo
- Mantener consistencia del algoritmo
- Preparar compatibilidad futura con algoritmos criptográficos avanzados

Versión actual del algoritmo:

hash = hash * 31 + caracter

La evolución planeada del módulo incluye:

- Procesamiento de archivos por bloques
- Manejo de hashes mediante std::string
- Compatibilidad futura con SHA256

Archivo:

src/hash_engine.cpp  
include/hash_engine.h

---

### 3. Baseline Manager

Responsable de:

- Verificar si existe un baseline
- Guardar hashes de integridad
- Leer registros almacenados
- Preparar datos para comparación
- Gestionar persistencia del sistema

La evolución del módulo contempla migración desde almacenamiento plano hacia persistencia estructurada mediante SQLite.

Archivo:

src/baseline_manager.cpp  
include/baseline_manager.h

---

### 4. Risk Analyzer

Responsable de:

- Comparar hashes
- Determinar estado del archivo

Estados posibles:

SAFE  
MODIFIED

Archivo:

src/risk_analyzer.cpp  
include/risk_analyzer.h

---

## Flujo General del Programa

1. El sistema lee el archivo objetivo.
2. Se genera un hash del contenido.
3. Se consulta el baseline almacenado.
4. Si no existe registro previo, se crea uno.
5. Si existe, se compara el hash actual con el almacenado.
6. La persistencia evoluciona hacia almacenamiento estructurado mediante SQLite.
7. Se determina el estado del archivo:

SAFE → No hubo cambios  
MODIFIED → Archivo alterado  

---

## Dependencias Técnicas

Lenguaje:

C++

Herramientas:

- g++
- Make
- Ubuntu Virtual Machine
- Git y GitHub

Dependencias externas:

Dependencias externas previstas:

- SQLite3 (persistencia estructurada)
- OpenSSL (integración futura opcional)

La versión actual del sistema no requiere dependencias externas obligatorias.

---

## Viabilidad Técnica

El sistema está diseñado para permitir expansión futura, incluyendo:

- Soporte para múltiples archivos
- Persistencia estructurada mediante SQLite
- Historial de eventos y trazabilidad
- Uso de algoritmos criptográficos (SHA256)
- Clasificación avanzada de riesgos
- Monitoreo automatizado