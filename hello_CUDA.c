//make sure to use nvcc, nvidia's compiler

#include <stdio.h>

//this runs on the device, and is called by host (cpu)
__global__ void mykernel(void){
}

int main(void){
    mykernel<<<1, 1>>>(); //triple angle brackets mean that this is from host to device(cpu to gpu)
    printf("Hello World\n");
    return 0;
}


