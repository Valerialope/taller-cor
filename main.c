
#include <stdio.h>
#include <string.h>
#include "funciones.h"
#define maxClientes 10

int numClientes = 0;

int main() {
    char listaClientes[maxClientes][2][40];
    char habitaciones[9][3][40] = {
        {"1", "simple", "Dan Carlton"},
        {"2", "doble", "Dan Carlton"},
        {"3", "triple", "Dan Carlton"},
        {"4", "simple", "Swissotel"},
        {"5", "doble", "Swissotel"},
        {"6", "triple", "Swissotel"},
        {"7", "simple", "Sheraton"},
        {"8", "doble", "Sheraton"},
        {"9", "triple", "Sheraton"}
    };

    double costos[9] = {90, 120, 160, 65, 100, 140, 85, 110, 150};
    int reservas[10][4] = {{-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}};
    
    int opcion, subopcion, numHabitacion, numReserva, continuar;
    
    // Cargar datos de reservas desde el archivo
    FILE *reservasFile = fopen("reservas.txt", "r");
    if (reservasFile != NULL) {
        int i = 0;
        while (fscanf(reservasFile, "%d %d %d %d", &reservas[i][0], &reservas[i][1], &reservas[i][2], &reservas[i][3]) != EOF) {
            i++;
        }
        fclose(reservasFile);
    }

    // Cargar datos de clientes desde el archivo
    FILE *clientesFile = fopen("clientes.txt", "r");
    if (clientesFile != NULL) {
        int i = 0;
        while (fscanf(clientesFile, "%s %s", listaClientes[i][0], listaClientes[i][1]) != EOF) {
            i++;
        }
        numClientes = i;
        fclose(clientesFile);
    }

    do {
        printf("Escoja una opcion:\n1. Registrar clientes\n2. Buscar habitacion\n3. Hacer reserva\n4. Ver reservas\n5. Pagar reserva\n>>");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                registrarClientes(listaClientes, maxClientes);
                break;
            case 2:
                printf("1. Por tipo\n2. Por hotel\n>>");
                scanf("%d", &subopcion);
                switch (subopcion) {
                    case 1:
                        printf("Tipos de habitaciones:\n1. Simple\n2. Doble\n3. Triple\n>>");
                        buscarPorTipo(&numHabitacion, habitaciones, costos);
                        break;
                    case 2:
                        printf("Hoteles:\n1. Dan Carlton\n2. Swissotel\n3. Sheraton\n>>");
                        buscarHotelPorNombre(&numHabitacion, habitaciones, costos);
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                hacerReserva(habitaciones, listaClientes, reservas, costos, maxClientes);
                break;
            case 4:
                buscarReservaPorCedula(&numReserva, listaClientes, reservas, maxClientes);
                mostrarReserva(numReserva, reservas, habitaciones, costos, listaClientes, maxClientes);
                break;
            case 5:
                buscarReservaPorCedula(&numReserva, listaClientes, reservas, maxClientes);
                pagarReserva(numReserva, reservas, habitaciones, costos, listaClientes, maxClientes);
                break;
            default:
                break;
        }
        printf("Desea elegir otra opcion?\n1 = si\t2 = no\n");
        scanf("%d", &continuar);
    } while (continuar == 1);

    // Guardar datos de reservas en el archivo
    reservasFile = fopen("reservas.txt", "w");
    if (reservasFile == NULL) {
        printf("Error al abrir el archivo de reservas\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] != -1) {
            fprintf(reservasFile, "%d %d %d %d\n", reservas[i][0], reservas[i][1], reservas[i][2], reservas[i][3]);
        }
    }
    fclose(reservasFile);

    // Guardar datos de clientes en el archivo
    clientesFile = fopen("clientes.txt", "w");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes\n");
        return 1;
    }

    for (int i = 0; i < numClientes; i++) {
        fprintf(clientesFile, "%s %s\n", listaClientes[i][0], listaClientes[i][1]);
    }
    fclose(clientesFile);

    return 0;
}
