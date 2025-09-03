#include <stdio.h>
#include <omp.h>

// Recursive Fibonacci with OpenMP tasks
int fib(int n) {
    if (n < 2)
        return n;

    int i, j;

    #pragma omp task shared(i)
    i = fib(n - 1);

    #pragma omp task shared(j)
    j = fib(n - 2);

    #pragma omp taskwait
    return i + j;
}

int main() {
    int n = 30; // Fibonacci number to calculate
    int result;
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }

    end_time = omp_get_wtime();

    printf("Fib(%d) = %d\n", n, result);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
