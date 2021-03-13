#include <stdio.h>
#define N 10000000

__global__ void cuda_hello(){
    printf("Hello World from GPU!\n");
}

//out = a + b, n is length
void vector_add(float *out, float *a, float *b, int n){
    for(int i = 0; i < n; i++){
        out[i] = a[i] + b[i];
    }
}

int main(){
    float *a, *b, *out;

    a = (float*)malloc(sizeof(float) * N);
    b = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);
    
    for(int i = 0; i < N; i++){
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    vector_add(out, a, b, N);
    
    for(int i = 0; i < 10; i++)
    {
        printf("%f ",out[i]);
    }
    printf("\n");
    cuda_hello<<<1,1>>>();
    return 0;
}