# Resumen Técnico del Proyecto
Sistema de Integridad de Archivos (SIA)

---

# Descripción General

El Sistema de Integridad de Archivos (SIA) es una
herramienta defensiva de ciberseguridad desarrollada
en C++ enfocada en detectar modificaciones no
autorizadas en archivos mediante monitoreo de integridad.

El sistema utiliza funciones hash para generar
identificadores representativos del contenido
de los archivos monitoreados.

Estos hashes son almacenados como baseline y
posteriormente comparados contra el estado actual
del archivo para detectar cambios.

---

# Objetivo Principal

Desarrollar un sistema modular en C++ capaz de:

- Monitorear archivos
- Generar hashes de integridad
- Detectar modificaciones
- Mantener persistencia estructurada
- Clasificar eventos de riesgo
- Registrar eventos relevantes

---

# Arquitectura General

El sistema sigue una arquitectura modular dividida
en cuatro componentes principales:

1. File Scanner
2. Hash Engine
3. Baseline Manager
4. Risk Analyzer

Flujo principal:

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

# Fundamento Técnico

Conceptos utilizados:

- Entrada/salida de archivos
- Hashing de contenido
- Persistencia de datos
- Comparación de integridad
- Clasificación de eventos
- Arquitectura modular

---

# Persistencia del Sistema

## Avance 1

El sistema utiliza persistencia básica mediante
archivo plano para almacenar el baseline inicial.

---

## Avance 2

El sistema migra a persistencia estructurada
mediante SQLite3.

Esto permite:

- Manejo de múltiples registros
- Asociación archivo ↔ hash
- Escalabilidad
- Persistencia organizada

---

## Entrega Final

La persistencia evoluciona hacia un sistema
con historial de eventos y seguimiento de cambios.

Capacidades esperadas:

- Historial de modificaciones
- Registro temporal
- Eventos históricos
- Trazabilidad de integridad

---

# Evolución del Hash Engine

## Avance 1

- Hash básico del contenido completo

---

## Avance 2

- Procesamiento por bloques
- Migración a hashes manejados como std::string

---

## Entrega Final

Posibles mejoras:

- SHA256
- Validación avanzada
- Soporte para múltiples algoritmos

---

# Clasificación de Riesgo

## Avance 1

Estados:

- SAFE
- MODIFIED

---

## Avance 2

Eventos:

- NEW
- MODIFIED
- DELETED

Riesgos:

- LOW
- MEDIUM
- HIGH

---

## Entrega Final

Clasificación avanzada basada en:

- Criticidad del archivo
- Frecuencia de eventos
- Historial de modificaciones

---

# Dependencias Técnicas

Lenguaje:

- C++

Herramientas:

- g++
- Make
- Git/GitHub
- Virtual Machines

Dependencias externas previstas:

- SQLite3
- OpenSSL (posible integración futura)

---

# Capacidad de Simulación

El sistema puede probarse fácilmente mediante:

Crear archivo:

echo "test" > file.txt

Modificar archivo:

echo "change" >> file.txt

Eliminar archivo:

rm file.txt

Estas acciones permiten simular eventos
de integridad reales dentro de un entorno seguro.

---

# Objetivo Académico y Técnico

El proyecto busca demostrar:

- Desarrollo modular en C++
- Diseño escalable
- Persistencia estructurada
- Monitoreo de integridad
- Clasificación de riesgo
- Simulación defensiva de ciberseguridad

---

# Fin del Documento