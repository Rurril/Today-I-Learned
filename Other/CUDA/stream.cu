
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>

__global__ void kernel(int* in, int* out) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    for (int i = 0;i < 5;i++) {
        out[tid] += in[tid];
    }
}

int main()
{
    const int nStreams = 15;
    const int nBlocks = 65535;
    const int nThreads = 512;
    const int N = 512 * 65535;
    const int size = N * sizeof(int);

    int* host_in;
    int* host_out;

    // 호스트 메모리 할당
    cudaMallocHost((void**)&host_in, size);
    cudaMallocHost((void**)&host_out, size);

    for (int i = 0;i<N;i++) {
        host_in[i] = i;
        host_out[i] = 0;
    }

    int* dev_in, * dev_out;

    // 디바이스 메모리 할당
    cudaMalloc((void**)&dev_in, size);
    cudaMalloc((void**)&dev_out, size);

    cudaMemset(dev_in, 0, size);
    cudaMemset(dev_out, 0, size);

    cudaEvent_t start, end;
    float time;

    cudaEventCreate(&start);
    cudaEventCreate(&end);

    cudaEventRecord(start, 0);

    // HOST TO DEVICE 데이터 전송
    cudaMemcpy(dev_in, host_in, size, cudaMemcpyHostToDevice);

    // 덧셈 계산
    kernel << <nBlocks, nThreads >> > (dev_in, dev_out);

    // DEVICE TO HOST 데이터 전송
    cudaMemcpy(host_out, dev_out, size, cudaMemcpyDeviceToHost);

    cudaEventRecord(end, 0); // 측정 종료
    cudaEventSynchronize(end);

    cudaEventElapsedTime(&time, start, end);

    printf("동기 실행 시간 : %f msec\n", time);

    // ---------------------------------------------------------------------

    for (int i = 0;i < N;i++) {
        host_in[i] = i;
        host_out[i] = 0;
    }

    cudaMemset(dev_in, 0, size);
    cudaMemset(dev_out, 0, size);

    cudaStream_t* streams = (cudaStream_t*)malloc(nStreams * sizeof(cudaStream_t));

    for (int i = 0;i < nStreams; i++) {
        cudaStreamCreate(&(streams[i]));
    }
    
    // 병행 실행 시간 측정
    cudaEvent_t streamStart, streamEnd;
    time = 0;

    cudaEventCreate(&streamStart);
    cudaEventCreate(&streamEnd);

    int offset = 0;

    cudaEventRecord(streamStart, 0);

    // HOST TO DEVICE 데이터 전송
    for (int i = 0; i < nStreams; i++) {
        offset = i * N / nStreams;
        cudaMemcpyAsync(dev_in + offset, host_in + offset, size, cudaMemcpyHostToDevice, streams[i]);
    }

    for (int i = 0; i < nStreams; i++) {
        offset = i * N / nStreams;
        kernel << <nBlocks / nStreams, nThreads, 0, streams[i] >> > (dev_in + offset, dev_out + offset);
    }

    // DEVICE TO HOST 데이터 전송
    for (int i = 0; i < nStreams; i++) {
        offset = i * N / nStreams;
        cudaMemcpyAsync(host_out + offset, dev_out + offset, size, cudaMemcpyDeviceToHost, streams[i]);
    }

    cudaEventRecord(streamEnd, 0);
    cudaEventSynchronize(streamEnd);

    cudaEventElapsedTime(&time, streamStart, streamEnd);

    printf("스트림 실행 시간 : %f msec\n", time);

    cudaEventDestroy(start);
    cudaEventDestroy(end);
    cudaEventDestroy(streamStart);
    cudaEventDestroy(streamEnd);

    for (int i = 0;i < nStreams;i++)
        cudaStreamDestroy(streams[i]);

    cudaFree(dev_in);
    cudaFree(dev_out);

    cudaFreeHost(host_in);
    cudaFreeHost(host_out);
    
    return 0;
}


