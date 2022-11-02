#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <mpi.h>

#include "primes.h"
#include "rc.h"


// Dimensional constants.
#define NDIMS   3
#define NNBRS   NDIMS * 2

// Upper bound of RNG, exclusive.
#define MAX_RAND   1000

// Number of primes to send.
#define N_ITERS   500

// Filenames.
#define FILENAME_FORMATTER    "./logs_task05/log_R%02d.txt"
#define MAX_FILENAME_LENGTH   256


int main(int argc, char *argv[])
{
    // Store the MPI routine return value for debugging.
    int rc = MPI_SUCCESS;

    // Initialize the MPI environment.
    int size, rank_global;
    rc = MPI_Init(&argc, &argv);
    rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank_global);

    // Retrieve the grid dimensions from the CLI if it is
    // specified by the user, otherwise let MPI decides an
    // optimal value later.
    const bool DIMS_SPECIFIED = (argc == NDIMS+1);
    int dims[] = {
        DIMS_SPECIFIED ? atoi(argv[1]) : 0,
        DIMS_SPECIFIED ? atoi(argv[2]) : 0,
        DIMS_SPECIFIED ? atoi(argv[3]) : 0
    };

    // MPI chooses an optimal grid dimensions, and we will
    // stick to this.
    rc = MPI_Dims_create(size, NDIMS, dims);

    // Create a new communicator with the topolgy information
    // attached.
    const int
        // Disable wrap around (in all axes).
        PERIODS[] = {[0 ... NDIMS-1] = false},
        // Enable ranking reordering.
        REORDER = true;
    MPI_Comm comm_cart;
    rc = MPI_Cart_create(
        MPI_COMM_WORLD,
        NDIMS,
        dims,
        PERIODS,
        REORDER,
        &comm_cart
    );

    // Retrieve node position in Cartesian grid.
    int coords[NDIMS], rank_cart;
    rc = MPI_Cart_coords(comm_cart, rank_global, NDIMS, coords);
    rc = MPI_Cart_rank(comm_cart, coords, &rank_cart);

    // Compute the rank of the neighbours.
    int nbrs[NNBRS];
    const int DISPLACEMENT = 1;
    for (unsigned int axis=0; axis<NDIMS; axis++)
        rc = MPI_Cart_shift(
            comm_cart,
            axis,
            DISPLACEMENT,
            &nbrs[2*axis],
            &nbrs[2*axis+1]
        );

    // Open the file for writing
    char filename[MAX_FILENAME_LENGTH];
    sprintf(filename, FILENAME_FORMATTER, rank_global);
    FILE *fptr = fopen(filename, "w");

    // Print log header.
    fprintf(
        fptr,
        "Global rank: %d. Cartesian rank: %d. "
        "Coordinates: (%d, %d, %d). "
        "Rear: %d. Front: %d. "
        "Top: %d. Bottom: %d. "
        "Left: %d. Right: %d\n",
        rank_global, rank_cart,
        coords[0], coords[1], coords[2],
        nbrs[0], nbrs[1],
        nbrs[2], nbrs[3],
        nbrs[4], nbrs[5]
    );

    unsigned int
        dir,
        seed = rank_cart * time(NULL);
    int
        nbr,
        rand_num,
        recv_primes[NNBRS];
    MPI_Request
        send_req[NNBRS],
        recv_req[NNBRS];
    MPI_Status
        send_status[NNBRS],
        recv_status[NNBRS];

    for (int iter=0; iter<N_ITERS; iter++) {
        // Generate random primes in range [0, MAX_RAND).
        do
            rand_num = rand_r(&seed) % MAX_RAND;
        while (!is_prime(rand_num));

        // Exchange primes with neighbouring nodes.
        // Use non-blocking send/receive and a barrier
        // after to not serialise the exchange operations.
        for (dir=0; dir<NNBRS; dir++) {
            nbr = nbrs[dir];
            rc = MPI_Isend(
                &rand_num,      // Send the computed prime.
                1,              // Send only 1 prime.
                MPI_INT,        // Sending type is integer.
                nbr,            // Send to a neighbour.
                0,              // Send with an arbitrary tag.
                comm_cart,      // Send using the grid communicator.
                &send_req[dir]  // Get the send request for tracking.
            );
            rc = MPI_Irecv(
                &recv_primes[dir],  // Store the received prime in array.
                1,                  // Receive only 1 prime.
                MPI_INT,            // Receiving an integer.
                nbr,                // Receiving from a neighbour
                MPI_ANY_TAG,        // Receive regardless of attached tag.
                comm_cart,          // Using the grid communicator.
                &recv_req[dir]      // Get the receive request for tracking.
            );
        }
        MPI_Waitall(NNBRS, send_req, send_status);
        MPI_Waitall(NNBRS, recv_req, recv_status);

        // Compare the received primes and log the event should there be a match.
        for (dir=0; dir<NNBRS; dir++)
            if (rand_num == recv_primes[dir])
                fprintf(
                    fptr,
                    "ITER %4d: matched %3d with rank %2d (direction %d).\n",
                    iter, rand_num, nbrs[dir], dir
                );
    }

    // Clean up.
    fclose(fptr);
    rc = MPI_Comm_free(&comm_cart);
    rc = MPI_Finalize();

    return SUCCESS;
}
