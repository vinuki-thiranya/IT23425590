#include <stdio.h>
#include <omp.h>

// Recursive Fibonacci
int fib(int n) {
    if (n < 2) return n;
    int i, j;
    #pragma omp task shared(i)
    i = fib(n-1);
    #pragma omp task shared(j)
    j = fib(n-2);
    #pragma omp taskwait
    return i + j;
}

int main() {
    int n = 30;
    int result;
    double start, end;

    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    end = omp_get_wtime();

    printf("Fib(%d) = %d\n", n, result);
    printf("Time taken = %f seconds\n", end - start);
    return 0;
}
