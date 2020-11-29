#include <stdio.h>
#include <stdlib.h>

//will execute on device, called by host
__global__ void add(int* a, int* b, int* c){
    int index = threadID.x + blockID.x * blockDim.x;
    if(index < N){
        c[index] = a[index] + b[index];
    }
}

//there are device pointers(gpu mem) 
//there are host pointers(cpu mem)

//cudaMalloc(), cudaFree(), cudaMemcpy()

#define N (2048 * 2048)
#define THREADS_PER_BLOCK 512

int main(void){
    int a, b, c;
    int *d_a, *d_b, *d_c;
    int size = sizeof(int);

    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    a = (int*)malloc(size); random_ints(a, N);
    b = (int*)malloc(size); random_ints(b, N);
    c = (int*)malloc(size);

    a = 2;
    b = 7;

    cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);

    //add<<<N, 1>>>(d_a, d_b, d_c); //blocks, use blockID.x in __global__ add
    //add<<<1, N>>>(d_a, d_b, d_c); //for threads, use threadID.x
    //add<<<N/THREADS_PER_BLOCK, THREADS_PER_BLOCK>>>(d_a, d_b, d_c);
    add<<<(N+M-1)/M, M>>>(d_a, d_b, d_c, N);

    cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost); //bringing data from the gpu

    free(a); free(b); free(c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;

}
