#include "funciones.h"
#include <stdio.h>
#include <string.h>

extern int numClientes;

void registrarClientes(char listaClientes[][2][40], int maxClientes) {
    int cantidad;
    printf("Ingrese la cantidad de clientes a registrar:\n");
    scanf("%d", &cantidad);
    if (numClientes + cantidad > maxClientes) {
        printf("Error: No hay suficiente espacio para %d clientes.\n", cantidad);
        return;
    }
    for (int indice = numClientes; indice < numClientes + cantidad; indice++) {
        printf("Ingrese el nombre del cliente %d:\n", indice + 1);
        getchar(); // Limpia el buffer de entrada antes de usar fgets
        fgets(listaClientes[indice][0], 40, stdin);
        listaClientes[indice][0][strcspn(listaClientes[indice][0], "\n")] = '\0'; // Elimina el newline

        printf("Ingrese la cedula del cliente %d:\n", indice + 1);
        scanf("%s", listaClientes[indice][1]);

        int duplicado = 0;
        for (int j = 0; j < numClientes; j++) {
            if (strcmp(listaClientes[j][1], listaClientes[indice][1]) == 0) {
                duplicado = 1;
                break;
            }
        }
        if (duplicado) {
            printf("La cedula ya ha sido ingresada anteriormente.\n");
            indice--;
        }
    }
    numClientes += cantidad;
}

void buscarPorTipo(int *numHabitacion, char habitaciones[][3][40], double costos[]) {
    char tipo[40];
    printf("Ingrese el tipo de habitacion (Ej: Simple, Doble, Suite):\n");
    getchar(); // Limpia el buffer de entrada antes de usar fgets
    fgets(tipo, 40, stdin);
    tipo[strcspn(tipo, "\n")] = '\0'; // Elimina el newline

    int encontrado = 0;
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1], tipo) == 0) {
            printf("Habitacion %d: %s, tipo: %s, costo: %.2f\n", i + 1, habitaciones[i][0], tipo, costos[i]);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontraron habitaciones del tipo %s.\n", tipo);
    }
}

void buscarHotelPorNombre(int *numHabitacion, char habitaciones[][3][40], double costos[]) {
    char nombre[40];
    printf("Ingrese el nombre del hotel:\n");
    getchar(); // Limpia el buffer de entrada antes de usar fgets
    fgets(nombre, 40, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // Elimina el newline

    int encontrado = 0;
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2], nombre) == 0) {
            printf("Habitacion %d: %s, tipo: %s, costo: %.2f\n", i + 1, habitaciones[i][0], habitaciones[i][1], costos[i]);
            *numHabitacion = i + 1;
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontró el hotel %s.\n", nombre);
    }
}

void hacerReserva(char habitaciones[][3][40], char listaClientes[][2][40], int reservas[][4], double costos[], int maxClientes) {
    int numHabitacion;
    char cedula[40];

    printf("Ingrese el numero de habitacion que desea reservar: ");
    scanf("%d", &numHabitacion);

    int i;
    for (i = 0; i < maxClientes; i++) {
        if (reservas[i][0] == numHabitacion) {
            printf("La habitación %d ya está reservada.\n", numHabitacion);
            return;
        }
    }

    printf("Ingrese su cedula: ");
    scanf("%s", cedula);

    int clienteIndice = -1;
    for (int j = 0; j < numClientes; j++) {
        if (strcmp(listaClientes[j][1], cedula) == 0) {
            clienteIndice = j;
            break;
        }
    }

    if (clienteIndice == -1) {
        printf("No se encontró un cliente con la cedula %s.\n", cedula);
        return;
    }

    for (i = 0; i < maxClientes; i++) {
        if (reservas[i][0] != -1 && reservas[i][2] == clienteIndice + 1) {
            printf("Usted ya tiene una reserva.\n");
            return;
        }
    }

    for (i = 0; i < maxClientes; i++) {
        if (reservas[i][0] == -1) {
            reservas[i][0] = numHabitacion;
            reservas[i][1] = numHabitacion; 
            reservas[i][2] = clienteIndice + 1;
            printf("Reserva realizada con exito.\n");
            return;
        }
    }
}

void buscarReservaPorCedula(int *numReserva, char listaClientes[][2][40], int reservas[][4], int maxClientes) {
    char cedula[40];
    printf("Ingrese la cedula del cliente:\n");
    scanf("%s", cedula);

    int clienteIndice = -1;
    for (int j = 0; j < numClientes; j++) {
        if (strcmp(listaClientes[j][1], cedula) == 0) {
            clienteIndice = j + 1; // Añade 1 porque reservas almacenan los índices del cliente comenzando en 1
            break;
        }
    }

    if (clienteIndice == -1) {
        printf("No se encontró un cliente con la cedula %s.\n", cedula);
        return;
    }

    int encontrado = 0;
    for (int i = 0; i < maxClientes; i++) {
        if (reservas[i][2] == clienteIndice) {
            *numReserva = i;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró una reserva con la cedula %s.\n", cedula);
    }
}

void mostrarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double costos[], char listaClientes[][2][40], int maxClientes) {
    int cliente = reservas[numReserva][2];
    int habitacion = reservas[numReserva][0];
    printf("Reserva %d:\n", numReserva + 1);
    printf("Cliente: %s, cedula: %s\n", listaClientes[cliente - 1][0], listaClientes[cliente - 1][1]);
    printf("Habitacion: %s, tipo: %s, costo: %.2f\n", habitaciones[habitacion - 1][0], habitaciones[habitacion - 1][1], costos[habitacion - 1]);
    if (reservas[numReserva][3] == 1) {
        printf("Estado de pago: PAGADO\n");
    } else {
        printf("Estado de pago: PENDIENTE\n");
    }
}

void pagarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double costos[], char listaClientes[][2][40], int maxClientes) {
    int cliente = reservas[numReserva][2];
    int habitacion = reservas[numReserva][0];
    double costo = costos[habitacion - 1];

    printf("Reserva %d:\n", numReserva + 1);
    printf("Cliente: %s, cedula: %s\n", listaClientes[cliente - 1][0], listaClientes[cliente - 1][1]);
    printf("Habitacion: %s, tipo: %s, costo: %.2f\n", habitaciones[habitacion - 1][0], habitaciones[habitacion - 1][1], costo);

    printf("Ingrese el monto a pagar: ");
    double monto;
    scanf("%lf", &monto);

    if (monto < costo) {
        printf("El monto ingresado es insuficiente. Monto pendiente: %.2f\n", costo - monto);
        return;
    }

    printf("Pago realizado con exito. Cambio: %.2f\n", monto - costo);

    reservas[numReserva][3] = 1;
}