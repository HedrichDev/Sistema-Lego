// =================== SISTEMA DE GESTION DE LEGO ===================
//Proyecto 3 Parte 1 -  Desarrollado Por Estudiantes de Informatica de la UDONE, 0501

//Alumnos:

//Christopher Hedrich - C.I=31.821.175
//Jose M. Hurtado     - C.I=32.045.013


// =================== DEFINICIONES DE ESTRUCTURAS ===================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes del sistema
#define MAX_NAME 50        // Longitud máxima para nombres
#define MAX_CITY_CODE 5    // Longitud máxima para códigos de ciudad
#define MAX_STORES 5       // Máximo número de tiendas por almacén secundario
#define MAX_WAREHOUSES 5   // Máximo número de almacenes (principales o secundarios)

// Estructura para las tiendas
typedef struct {
    char name[MAX_NAME];              // Nombre de la tienda
    int maxCapacity;                  // Capacidad máxima de almacenamiento
    int currentStock;                 // Stock actual
    char city[MAX_CITY_CODE];        // Código de la ciudad
    int deliveryTime;                 // Tiempo de entrega estándar
    char secondaryWarehouse[MAX_NAME]; // Almacén secundario asociado
} Store;

// Estructura para almacenes secundarios
typedef struct {
    char name[MAX_NAME];              // Nombre del almacén secundario
    char city[MAX_CITY_CODE];        // Ciudad donde se encuentra
    int currentStock;                 // Stock actual
    int deliveryTimeFromMain;         // Tiempo de entrega desde almacén principal
    Store** stores;                   // Puntero doble para permitir asignación dinámica
    int storeCount;                   // Número actual de tiendas
    char mainWarehouse[MAX_NAME];     // Almacén principal asociado
} SecondaryWarehouse;

// Estructura para almacenes principales
typedef struct {
    char name[MAX_NAME];              // Nombre del almacén principal
    char city[MAX_CITY_CODE];        // Ciudad donde se encuentra
    int currentStock;                 // Stock actual
    SecondaryWarehouse* secondaryWarehouses[MAX_WAREHOUSES]; // Almacenes secundarios
    int warehouseCount;               // Número actual de almacenes secundarios
} MainWarehouse;

// Estructura principal del sistema
typedef struct {
    MainWarehouse mainWarehouses[MAX_WAREHOUSES];  // Almacenes principales
    int mainWarehouseCount;                        // Número de almacenes principales
    SecondaryWarehouse* allSecondaryWarehouses[MAX_WAREHOUSES * MAX_WAREHOUSES]; // Todos los almacenes secundarios
    int secondaryWarehouseCount;                   // Número total de almacenes secundarios
    Store* allStores[MAX_WAREHOUSES * MAX_WAREHOUSES * MAX_STORES]; // Todas las tiendas
    int storeCount;                                // Número total de tiendas
} InventorySystem;

// =================== PROTOTIPOS DE FUNCIONES ===================

// Funciones de gestión de almacenes principales
int registerMainWarehouse(InventorySystem* system, const char* name, const char* city, int initialStock);
int updateMainWarehouseName(InventorySystem* system, const char* oldName, const char* newName);

// Funciones de gestión de almacenes secundarios
int registerSecondaryWarehouse(InventorySystem* system, const char* mainWarehouseName, 
                            const char* name, const char* city, int initialStock, int deliveryTime);
int updateSecondaryWarehouseCity(InventorySystem* system, const char* name, const char* newCity);

// Funciones de gestión de tiendas
int registerStore(InventorySystem* system, const char* secondaryWarehouseName,
                const char* name, int maxCapacity, int initialStock,
                const char* city, int deliveryTime);
int removeStore(InventorySystem* system, const char* name);

// Funciones de búsqueda
Store* findStore(InventorySystem* system, const char* name);
SecondaryWarehouse* findSecondaryWarehouse(InventorySystem* system, const char* name);
MainWarehouse* findMainWarehouse(InventorySystem* system, const char* name);

// =================== IMPLEMENTACIÓN DE FUNCIONES ===================

// Implementación de funciones de inventario
int registerMainWarehouse(InventorySystem* system, const char* name, const char* city, int initialStock) {
    if (system->mainWarehouseCount >= MAX_WAREHOUSES) {
        return 0;
    }

    MainWarehouse* warehouse = &system->mainWarehouses[system->mainWarehouseCount];
    strncpy(warehouse->name, name, MAX_NAME - 1);
    warehouse->name[MAX_NAME - 1] = '\0';
    strncpy(warehouse->city, city, MAX_CITY_CODE - 1);
    warehouse->city[MAX_CITY_CODE - 1] = '\0';
    warehouse->currentStock = initialStock;
    warehouse->warehouseCount = 0;
    system->mainWarehouseCount++;
    return 1;
}

int updateMainWarehouseName(InventorySystem* system, const char* oldName, const char* newName) {
    MainWarehouse* warehouse = findMainWarehouse(system, oldName);
    if (warehouse == NULL) return 0;

    strncpy(warehouse->name, newName, MAX_NAME - 1);
    warehouse->name[MAX_NAME - 1] = '\0';
    return 1;
}

int registerSecondaryWarehouse(InventorySystem* system, const char* mainWarehouseName, 
                            const char* name, const char* city, int initialStock, int deliveryTime) {
    MainWarehouse* mainWarehouse = findMainWarehouse(system, mainWarehouseName);
    if (mainWarehouse == NULL || mainWarehouse->warehouseCount >= MAX_WAREHOUSES) {
        return 0;
    }

    SecondaryWarehouse* warehouse = (SecondaryWarehouse*)malloc(sizeof(SecondaryWarehouse));
    if (warehouse == NULL) return 0;

    strncpy(warehouse->name, name, MAX_NAME - 1);
    warehouse->name[MAX_NAME - 1] = '\0';
    strncpy(warehouse->city, city, MAX_CITY_CODE - 1);
    warehouse->city[MAX_CITY_CODE - 1] = '\0';
    strncpy(warehouse->mainWarehouse, mainWarehouseName, MAX_NAME - 1);
    warehouse->mainWarehouse[MAX_NAME - 1] = '\0';
    warehouse->currentStock = initialStock;
    warehouse->deliveryTimeFromMain = deliveryTime;
    warehouse->storeCount = 0;
    warehouse->stores = (Store**)malloc(MAX_STORES * sizeof(Store*));
    if (warehouse->stores == NULL) {
        free(warehouse);
        return 0;
    }

    mainWarehouse->secondaryWarehouses[mainWarehouse->warehouseCount] = warehouse;
    system->allSecondaryWarehouses[system->secondaryWarehouseCount] = warehouse;

    mainWarehouse->warehouseCount++;
    system->secondaryWarehouseCount++;
    return 1;
}

int updateSecondaryWarehouseCity(InventorySystem* system, const char* name, const char* newCity) {
    SecondaryWarehouse* warehouse = findSecondaryWarehouse(system, name);
    if (warehouse == NULL) return 0;

    strncpy(warehouse->city, newCity, MAX_CITY_CODE - 1);
    warehouse->city[MAX_CITY_CODE - 1] = '\0';
    return 1;
}

int registerStore(InventorySystem* system, const char* secondaryWarehouseName,
                const char* name, int maxCapacity, int initialStock,
                const char* city, int deliveryTime) {
    SecondaryWarehouse* warehouse = findSecondaryWarehouse(system, secondaryWarehouseName);
    if (warehouse == NULL || warehouse->storeCount >= MAX_STORES) {
        return 0;
    }

    Store* store = (Store*)malloc(sizeof(Store));
    if (store == NULL) return 0;

    strncpy(store->name, name, MAX_NAME - 1);
    store->name[MAX_NAME - 1] = '\0';
    strncpy(store->city, city, MAX_CITY_CODE - 1);
    store->city[MAX_CITY_CODE - 1] = '\0';
    strncpy(store->secondaryWarehouse, secondaryWarehouseName, MAX_NAME - 1);
    store->secondaryWarehouse[MAX_NAME - 1] = '\0';
    store->maxCapacity = maxCapacity;
    store->currentStock = initialStock;
    store->deliveryTime = deliveryTime;

    warehouse->stores[warehouse->storeCount] = store;
    system->allStores[system->storeCount] = store;

    warehouse->storeCount++;
    system->storeCount++;
    return 1;
}

int removeStore(InventorySystem* system, const char* name) {
    Store* storeToRemove = NULL;
    int storeIndex = -1;

    // Find the store and its index
    for (int i = 0; i < system->storeCount; i++) {
        if (strcmp(system->allStores[i]->name, name) == 0) {
            storeToRemove = system->allStores[i];
            storeIndex = i;
            break;
        }
    }

    if (storeToRemove == NULL) return 0;

    // Remove from secondary warehouse
    SecondaryWarehouse* warehouse = findSecondaryWarehouse(system, storeToRemove->secondaryWarehouse);
    if (warehouse != NULL) {
        for (int j = 0; j < warehouse->storeCount; j++) {
            if (warehouse->stores[j] == storeToRemove) {
                for (int k = j; k < warehouse->storeCount - 1; k++) {
                    warehouse->stores[k] = warehouse->stores[k + 1];
                }
                warehouse->storeCount--;
                break;
            }
        }
    }

    // Remove from system's store array
    for (int j = storeIndex; j < system->storeCount - 1; j++) {
        system->allStores[j] = system->allStores[j + 1];
    }
    system->storeCount--;

    free(storeToRemove);
    return 1;
}

Store* findStore(InventorySystem* system, const char* name) {
    for (int i = 0; i < system->storeCount; i++) {
        if (strcmp(system->allStores[i]->name, name) == 0) {
            return system->allStores[i];
        }
    }
    return NULL;
}

SecondaryWarehouse* findSecondaryWarehouse(InventorySystem* system, const char* name) {
    for (int i = 0; i < system->secondaryWarehouseCount; i++) {
        if (strcmp(system->allSecondaryWarehouses[i]->name, name) == 0) {
            return system->allSecondaryWarehouses[i];
        }
    }
    return NULL;
}

MainWarehouse* findMainWarehouse(InventorySystem* system, const char* name) {
    for (int i = 0; i < system->mainWarehouseCount; i++) {
        if (strcmp(system->mainWarehouses[i].name, name) == 0) {
            return &system->mainWarehouses[i];
        }
    }
    return NULL;
}

// Funciones auxiliares
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readString(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void showMenu() {
    printf("\n=== Sistema de Gestión de Lego - By HΞDЯICH Hurtado===\n");
    printf("1. Registrar Almacén Principal\n");
    printf("2. Actualizar Nombre de Almacén Principal\n");
    printf("3. Registrar Almacén Secundario\n");
    printf("4. Registrar Tienda\n");
    printf("5. Eliminar Tienda\n");
    printf("6. Actualizar Ciudad de Almacén Secundario\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
}

void freeSystemResources(InventorySystem* system) {
    // Liberar memoria de las tiendas
    for (int i = 0; i < system->storeCount; i++) {
        free(system->allStores[i]);
    }

    // Liberar memoria de los almacenes secundarios
    for (int i = 0; i < system->secondaryWarehouseCount; i++) {
        if (system->allSecondaryWarehouses[i]->stores != NULL) {
            free(system->allSecondaryWarehouses[i]->stores);
        }
        free(system->allSecondaryWarehouses[i]);
    }
}

int validatePositiveNumber(const char* prompt, int* value) {
    printf("%s", prompt);
    if (scanf("%d", value) != 1 || *value < 0) {
        printf("Por favor ingrese un número positivo válido.\n");
        clearBuffer();
        return 0;
    }
    clearBuffer();
    return 1;
}

// Función principal
int main() {
    InventorySystem system = {0};  // Inicialización del sistema
    int option;
    char name[MAX_NAME], city[MAX_CITY_CODE], newName[MAX_NAME];
    int stock, maxCapacity, deliveryTime;

    do {
        showMenu();
        if (scanf("%d", &option) != 1) {
            printf("Opción inválida.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (option) {
            case 1: {
                printf("Nombre del almacén principal: ");
                readString(name, MAX_NAME);

                printf("Ciudad (código): ");
                readString(city, MAX_CITY_CODE);

                if (!validatePositiveNumber("Stock inicial: ", &stock)) {
                    continue;
                }

                if (registerMainWarehouse(&system, name, city, stock)) {
                    printf("Almacén principal registrado exitosamente.\n");
                } else {
                    printf("Error al registrar almacén principal.\n");
                }
                break;
            }

            case 2: {
                printf("Nombre actual del almacén principal: ");
                readString(name, MAX_NAME);

                printf("Nuevo nombre: ");
                readString(newName, MAX_NAME);

                if (updateMainWarehouseName(&system, name, newName)) {
                    printf("Nombre actualizado exitosamente.\n");
                } else {
                    printf("Error al actualizar el nombre.\n");
                }
                break;
            }

            case 3: {
                char mainName[MAX_NAME];
                printf("Nombre del almacén principal: ");
                readString(mainName, MAX_NAME);

                printf("Nombre del almacén secundario: ");
                readString(name, MAX_NAME);

                printf("Ciudad (código): ");
                readString(city, MAX_CITY_CODE);

                if (!validatePositiveNumber("Stock inicial: ", &stock)) {
                    continue;
                }

                if (!validatePositiveNumber("Tiempo de entrega desde almacén principal: ", &deliveryTime)) {
                    continue;
                }

                if (registerSecondaryWarehouse(&system, mainName, name, city, stock, deliveryTime)) {
                    printf("Almacén secundario registrado exitosamente.\n");
                } else {
                    printf("Error al registrar almacén secundario.\n");
                }
                break;
            }

            case 4: {
                char secondaryName[MAX_NAME];
                printf("Nombre del almacén secundario: ");
                readString(secondaryName, MAX_NAME);

                printf("Nombre de la tienda: ");
                readString(name, MAX_NAME);

                printf("Ciudad (código): ");
                readString(city, MAX_CITY_CODE);

                if (!validatePositiveNumber("Capacidad máxima: ", &maxCapacity)) {
                    continue;
                }

                if (!validatePositiveNumber("Stock inicial: ", &stock)) {
                    continue;
                }

                if (!validatePositiveNumber("Tiempo de entrega estándar: ", &deliveryTime)) {
                    continue;
                }

                if (registerStore(&system, secondaryName, name, maxCapacity, stock, city, deliveryTime)) {
                    printf("Tienda registrada exitosamente.\n");
                } else {
                    printf("Error al registrar tienda.\n");
                }
                break;
            }

            case 5: {
                printf("Nombre de la tienda a eliminar: ");
                readString(name, MAX_NAME);

                if (removeStore(&system, name)) {
                    printf("Tienda eliminada exitosamente.\n");
                } else {
                    printf("Error al eliminar la tienda.\n");
                }
                break;
            }

            case 6: {
                printf("Nombre del almacén secundario: ");
                readString(name, MAX_NAME);

                printf("Nueva ciudad (código): ");
                readString(city, MAX_CITY_CODE);

                if (updateSecondaryWarehouseCity(&system, name, city)) {
                    printf("Ciudad actualizada exitosamente.\n");
                } else {
                    printf("Error al actualizar la ciudad.\n");
                }
                break;
            }

            case 0:
                printf("¡Gracias por usar el sistema Desarrollado por Hedrich y Hurtado!\n");
                break;

            default:
                printf("Opción no válida.\n");
        }

        if (option != 0) {
            printf("\nPresione Enter para continuar...");
            getchar();
            clearScreen();
        }

    } while (option != 0);

    freeSystemResources(&system);
    return 0;
}
