# Diseño Técnico — Sistema de Integridad de Archivos (SIA)

## Arquitectura General

El sistema sigue una arquitectura modular diseñada para detectar cambios en archivos mediante el uso de funciones hash y comparación contra un baseline almacenado previamente.

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
- Usar un algoritmo hash simple basado en:

hash = hash * 31 + caracter

Archivo:

src/hash_engine.cpp  
include/hash_engine.h

---

### 3. Baseline Manager

Responsable de:

- Verificar si existe un baseline
- Guardar el hash inicial
- Leer el hash almacenado
- Preparar datos para comparación

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
3. Se verifica si existe un baseline.
4. Si no existe, se crea uno.
5. Si existe, se compara el hash actual con el almacenado.
6. Se determina el estado del archivo:

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

No se utilizan librerías externas en esta versión inicial.

---

## Viabilidad Técnica

El sistema está diseñado para permitir expansión futura, incluyendo:

- Soporte para múltiples archivos
- Uso de algoritmos criptográficos (SHA256)
- Clasificación avanzada de riesgos
- Monitoreo automatizado