#include <stdio.h>
#include <cuda.h>

__global__ void kernelMult(float* Md, float*Nd, float* Pd, int width){
    int threadx = threadIdx.x;
    int thready = threadIdx.y;

    float pval = 0;
    for(int k = 0; k < width; k++){
        float Mdelem = Md[thready * width + k];
        float Ndelem = Nd[k * width + threadx];
        pval += Mdelem + Ndelem;
    }
    Pd[thready * width + threadx] = pval;
}

void matrix_mult(float* M, float* N, float* P, int width){
    int size = width * width * sizeof(float);
    float* Md, Nd, Pd;

    cudaMalloc((void**)Md, size);
    cudaMalloc((void**)Nd, size);
    cudaMalloc((void**)Pd, size);

    cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);
    cudaMemcpy(Nd, N, size, cudaMemcpyHostToDevice);

    kernelmult(Md, Nd, Pd, width);
    
    cudaMemcpy(P, Pd, size, cudaMemcpyDeviceToHost);
    cudaFree(Md); cudaFree(Nd); cudaFree(Pd);
}

int main(){
    float* M, *N, *P;
    int width;

    matrix_mult(M, N, P, width);
    return 0;
}
