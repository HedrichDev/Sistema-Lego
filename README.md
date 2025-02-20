# !  Hola 👋, Este es el BatiProyecto 3 de HΞDЯICH 
![](https://github.com/HedrichDev/Sistema-Lego/blob/Media/Proyecto%20%20c%20-%20Sistema%20de%20Gestion%20de%20Lego.png?raw=true)

El Presente Proyecto fue realizado por alumnos de Informatica de la Universidad de Oriente UDO 
[<img
        src="https://raw.githubusercontent.com/HedrichDev/ProyectoC/refs/heads/main/LOGO%20UDONE.png" 
        width=3%
        title="Logo UDO"
        alt="Logo UDO"
    />
](https://raw.githubusercontent.com/HedrichDev/ProyectoC/refs/heads/main/LOGO%20UDONE.png) de la seccion 0501, Nueva Esparta, Venezuela

## Integrantes del Proyecto 
> 👥 Christopher Hedrich C.I 31.821.175
> 
> 👥 José Manuel Hurtado Marcano C.I: 32.045.013

# Descripción del Proyecto

[<img
        src="https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExdTF3dngzdW9mZXhyY3diNzVwMzlvd2Y0bmJtenJvbXFpNGZiNHk0YiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/3o7TKxixMV43t4D8Mo/giphy.gif" 
        width=150%
        title="BATMAN"
        alt="BATMAN"
    />
](https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExdTF3dngzdW9mZXhyY3diNzVwMzlvd2Y0bmJtenJvbXFpNGZiNHk0YiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/3o7TKxixMV43t4D8Mo/giphy.gif)  


# Sistema de Gestión de Inventario y Ventas de Lego 🏪

## Objetivo
El objetivo del proyecto es implementar un sistema de gestión de inventario y ventas para una red de tiendas Lego, que permite:
- Gestionar múltiples niveles de almacenamiento (Almacenes Principales, Secundarios y Tiendas)
- Optimizar la distribución y el seguimiento de productos
- Controlar el stock en tiempo real
- Procesar ventas y calcular rutas de entrega óptimas

## Componentes del Proyecto
El sistema está estructurado en varios componentes principales:

### 1. Estructuras de Datos
- **Tiendas (Store)**: Almacena información sobre cada punto de venta
  - Nombre, capacidad máxima, stock actual
  - Ciudad y tiempo de entrega
  - Registro de ventas totales

- **Almacenes Secundarios (SecondaryWarehouse)**:
  - Gestiona hasta 5 tiendas
  - Mantiene registro de stock y tiempos de entrega
  - Conexión con almacén principal

- **Almacenes Principales (MainWarehouse)**:
  - Control de hasta 5 almacenes secundarios
  - Gestión de stock central
  - Registro de ubicación y capacidad

### 2. Funcionalidades Principales
- Gestión de Almacenes
- Gestión de Tiendas
- Procesamiento de Ventas
- Optimización de Rutas de Entrega
- Reportes de Inventario

## Funcionamiento del Proyecto

### Entrada del Usuario
El sistema acepta las siguientes entradas a través de un menú interactivo:

1. **Gestión de Almacenes Principales**:
   - Registro de nuevos almacenes
   - Actualización de nombres
   - Gestión de stock

2. **Gestión de Almacenes Secundarios**:
   - Registro y vinculación con almacén principal
   - Actualización de ubicación
   - Control de inventario

3. **Gestión de Tiendas**:
   - Alta y baja de tiendas
   - Asignación a almacenes secundarios
   - Control de capacidad y stock

4. **Procesamiento de Ventas**:
   - Cantidad de productos
   - Ciudad de destino
   - Cálculo automático de rutas

### Almacenamiento de Resultados
- Los datos se mantienen en memoria durante la ejecución del programa
- Se utilizan estructuras enlazadas para mantener las relaciones entre entidades
- La información se gestiona de manera dinámica para optimizar el uso de memoria

### Salida de Resultados
El sistema proporciona diferentes tipos de salidas:

1. **Confirmaciones de Operaciones**:
   - Mensajes de éxito o error en cada operación
   - Detalles de las transacciones realizadas

2. **Reportes de Estado**:
   - Niveles de inventario en cada ubicación
   - Estadísticas de ventas
   - Rutas de entrega optimizadas

3. **Información de Rutas**:
   - Tiempo estimado de entrega
   - Ruta más eficiente
   - Detalles de cada punto en la cadena de distribución

## Recomendaciones para Ejecutar el Código ❗❗

### Requisitos Previos
1. Compilador C (GCC recomendado)
2. Sistema operativo compatible (Windows, Linux, macOS)
3. Terminal o línea de comandos

### Pasos para la Ejecución

1. **Compilación del Código**:
   ```bash
   gcc -Wall -o lego_system sistema_lego_completo.c
   ```

2. **Ejecución del Programa**:
   ```bash
   ./lego_system
   ```

### Consideraciones Importantes
1. **Entrada de Datos**:
   - Respetar los límites de caracteres para nombres (50) y códigos de ciudad (5)
   - Ingresar números positivos cuando se soliciten cantidades
   - Seguir el formato solicitado para cada entrada

2. **Gestión de Memoria**:
   - El sistema libera automáticamente la memoria al salir
   - Se recomienda cerrar el programa correctamente usando la opción de salida

3. **Prevención de Errores**:
   - Verificar la existencia de almacenes antes de registrar dependencias
   - No exceder los límites máximos de tiendas por almacén (5)
   - Mantener consistencia en los nombres y códigos utilizados

4. **Para Desarrollo**:
   - Se recomienda usar la versión con archivos separados para mejor mantenimiento
   - Documentar cualquier modificación en el código
   - Realizar pruebas después de cada cambio significativo

### Notas Adicionales
- El sistema incluye validaciones para prevenir errores comunes
- Se recomienda hacer respaldos de los datos importantes
- Para proyectos grandes, considerar implementar persistencia de datos

---
Desarrollado por Hedrich y Hurtado © 2024


[<img
        src="https://media2.giphy.com/media/v1.Y2lkPTc5MGI3NjExdnQ5a3dxZTE3eWFlOWVhcXhrbGVheTByZHo4azl2cXFyNzl4NDA3diZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/b0VK26c9Ne0ak/giphy.gif" 
        width=90%
        title="BATMAN"
        alt="BATMAN"
    />
](https://media2.giphy.com/media/v1.Y2lkPTc5MGI3NjExdnQ5a3dxZTE3eWFlOWVhcXhrbGVheTByZHo4azl2cXFyNzl4NDA3diZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/b0VK26c9Ne0ak/giphy.gif)  






