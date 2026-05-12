# Roadmap de Desarrollo — Sistema de Integridad de Archivos (SIA)

---

## Descripción General

El Sistema de Integridad de Archivos (SIA) está diseñado
como una herramienta modular de monitoreo de integridad
desarrollada en C++.

El proyecto evoluciona progresivamente entre entregas,
incrementando sus capacidades técnicas sin modificar
la arquitectura base del sistema.

La evolución del proyecto se divide en tres fases:

- Avance 1
- Avance 2
- Entrega Final

Cada módulo del sistema posee responsabilidades
independientes y una evolución específica.

---

# Arquitectura Modular

El flujo principal del sistema es:

main
↓
File Scanner
↓
Hash Engine
↓
Baseline Manager
↓
Risk Analyzer
↓
Output

---

# Módulo 1 — File Scanner

## Responsabilidades

- Verificar existencia de archivos
- Leer contenido de archivos
- Manejar múltiples rutas
- Gestionar errores de lectura

---

## Avance 1

Capacidades implementadas:

- Lectura básica de un archivo
- Verificación de existencia
- Retorno del contenido como string

---

## Avance 2

Objetivos:

- Soporte para múltiples archivos
- Procesamiento secuencial de rutas
- Validación de múltiples entradas

Resultado esperado:

El sistema puede monitorear varios archivos simultáneamente.

---

## Entrega Final

Objetivos:

- Lectura desde archivo de configuración
- Exploración básica de directorios
- Monitoreo automatizado

---

# Módulo 2 — Hash Engine

## Responsabilidades

- Generar hashes del contenido
- Mantener consistencia del algoritmo
- Retornar hashes para comparación

---

## Avance 1

Capacidades implementadas:

- Generación de hash básico
- Procesamiento completo del contenido

---

## Avance 2

Objetivos:

- Procesamiento de archivos por bloques
- Mejora de eficiencia
- Migración del hash a formato std::string

Resultado esperado:

El sistema soporta archivos más grandes
y mantiene compatibilidad futura con
algoritmos criptográficos avanzados.

---

## Entrega Final

Objetivos:

- Soporte para múltiples algoritmos
- Validación de consistencia
- Manejo interno de errores

Posibles mejoras:

- SHA256
- Comparación avanzada de integridad

---

# Módulo 3 — Baseline Manager

## Responsabilidades

- Almacenar hashes
- Recuperar registros previos
- Gestionar persistencia del sistema
- Mantener historial de integridad

---

## Avance 1

Capacidades implementadas:

- Baseline basado en archivo plano
- Comparación básica de hashes
- Persistencia simple

---

## Avance 2

Objetivos:

- Migración a SQLite
- Soporte para múltiples registros
- Persistencia estructurada
- Asociación hash ↔ archivo

Resultado esperado:

El sistema mantiene múltiples baselines
de forma organizada y escalable.

---

## Entrega Final

Objetivos:

- Historial de cambios
- Registro de eventos
- Timestamps de modificaciones
- Seguimiento histórico

Resultado esperado:

Sistema con trazabilidad de integridad.

---

# Módulo 4 — Risk Analyzer

## Responsabilidades

- Interpretar resultados
- Clasificar eventos detectados
- Asignar nivel de riesgo
- Generar mensajes de salida

---

## Avance 1

Capacidades implementadas:

Estados soportados:

- SAFE
- MODIFIED

---

## Avance 2

Objetivos:

Detectar:

- NEW
- MODIFIED
- DELETED

Clasificar riesgo:

- LOW
- MEDIUM
- HIGH

Resultado esperado:

Sistema con clasificación funcional
de eventos de integridad.

---

## Entrega Final

Objetivos:

- Clasificación dinámica
- Archivos críticos
- Reportes estructurados
- Análisis avanzado

---

# Evolución Técnica del Proyecto

## Avance 1

Enfoque:

- Funcionalidad mínima real
- Arquitectura modular
- Persistencia básica

Tecnologías:

- C++
- g++
- Make
- Git/GitHub

---

## Avance 2

Enfoque:

- Persistencia estructurada
- Escalabilidad
- Multiarchivo

Tecnologías adicionales:

- SQLite3

---

## Entrega Final

Enfoque:

- Automatización
- Historial
- Clasificación avanzada
- Configuración externa

---

# Objetivo Final del Sistema

Desarrollar una herramienta modular de monitoreo
de integridad capaz de detectar modificaciones
de archivos mediante técnicas de hashing,
persistencia estructurada y clasificación de riesgo.

---

# Fin del Documento