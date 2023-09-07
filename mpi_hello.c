/*
    Universidad del Valle de Guatemala
    Computación paralela y distribuida
    Hoja de trabajo #2
*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h> 

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv); // Iniciar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el rango (ID) del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el número total de procesos

    if (argc != 2) {
        if (rank == 0) {
            printf("Debes proporcionar la cantidad de procesos.\n");
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

    printf("Hello World, I'm process %d of %d!\n", rank, size);

    MPI_Finalize(); // Finalizar MPI
    return 0;
}

