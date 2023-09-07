/*
    Universidad del Valle de Guatemala
    Computación paralela y distribuida
    Hoja de trabajo #2
*/

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h> 

int main(int argc, char *argv[]) {
    int rank, size;
    char message[100];

    MPI_Init(&argc, &argv); // Iniciar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el rango (ID) del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el número total de procesos

    if (argc != 2) {
        if (rank == 0) {
            printf("Uso incorrecto. Debes proporcionar la cantidad de procesos.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int num_processes = atoi(argv[1]);

    if (num_processes != size) {
        if (rank == 0) {
            printf("El número de procesos especificado debe coincidir con la cantidad de procesos MPI.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        printf("Hi, I'm process %d of %d and I'm receiving!\n", rank, size);
        for (int sender = 1; sender < size; sender++) {
            MPI_Recv(message, sizeof(message), MPI_CHAR, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s, I'm process %d of %d\n", message, sender, size);
        }
    } else {
        sprintf(message, "Greetings process 0");
        printf("Hi, I'm process %d from %d and i'm sending a message to 0!\n", rank, size);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize(); // Finalizar MPI
    return 0;
}


