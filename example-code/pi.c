#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long num_points = 1e9; // Number of random points
    long count = 0;
    double x, y;
    unsigned int seed;

    #pragma omp parallel private(x, y, seed) reduction(+:count)
    {
        seed = omp_get_thread_num();
        #pragma omp for
        for (long i = 0; i < num_points; i++) {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                count++;
            }
        }
    }

    double pi = 4.0 * (double)count / (double)num_points;
    printf("Estimated Pi = %f\n", pi);
    return 0;
}
