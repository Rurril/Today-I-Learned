![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/1.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/2.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/3.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/4.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/5.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/6.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/7.PNG?raw=true)


![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/8.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/9.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/10.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/11.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/12.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/13.PNG?raw=true)

> 해당 코드는 cuda documentation에서 가져왔다.

조금만 설명을 하자면, 

int row : 행렬C의 계산하고자 하는 row index를 의미

int col : 행렬C의 계산하고자 하는 column index를 의미

맨 마지막 줄을보면 

`c[row*N+col] = sum;`

으로 되어있는데, C의 (row, col) 위치에 결과값을 sum에 계산해서 넣는 코드이다.

`sum += a[row*TILE_DIM+i] * b[i*N+col];`

위의 코드는 행렬A의 (row, i) 값들을 

행렬 곱셈에 매칭되는 행렬B의 (i, col) 값들에 곱해서 더해주는 코드이다.

TILE_DIM은 그림에서 'w'을 의미하며, N은 그림에서 'N'을 의미한다.


![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/14.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/15.PNG?raw=true)

## 추가적으로 공유메모리를 사용한 matrix multiplication도 정리해보도록 하겠다. 

쿠다를 사용하는 것에 장점 중 하나가 공유메모리를 사용하여 빠른 계산을 하는 것인데, 공유메모리가 블럭마다 있다보니 블럭 내의 스레드를 indexing 잘해서 사용해야 하는 것 같다.

A의 크기는 (M, w) 이고 B의 크기는 (w, N)이라고 했을 때, `TILE_DIM = w`이다.

보통 이럴 때는 커널 함수의 thread를 행렬의 x좌표로 사용하고, block을 y좌표로 사용한다고 생각하면 된다. 

```c++
Dim3 thread = (w, w);
Dim3 block = (M/w, N/w);

<<<block, thread>>>kernel(args);
```

위와 같이 함으로써 전체 thread의 개수가 C의 크기에 맞게
(M * N)로 설정한다. 

한 블럭의 크기가 (w,w)가 되는 것이고, 각 블럭마다 공유메모리를 행렬 A,B의 서브메트릭스, aTile과 bTile를 선언하여 크기를 블럭 크기와 같이 (w,w)로 설정하여 사용한다.

그리고 블럭 별 행렬곱셈을 계산하고 행렬 C에 더한다.

`곱셈 계산 전에 블럭의 스레드들이 모두 완료될 때까지 기다린다` - (의미 없는 값들의 계산이 나올 수 있기 때문)

행렬의 값들을 global memory에서 직접 그때마다 꺼내오는 것보다, shared memory에 저장하여 꺼내오는 것이 여려번 계산할 때 빠른 불러오기 속도의 장점을 갖는다. 

## CUDA documentation을 기준으로 아래 그림과 같은 속도의 차이가 난다고 한다. 



![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/16.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/17.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/18.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/19.PNG?raw=true)

![](https://github.com/Rurril/Today-I-Learned/blob/master/Other/CUDA/images/matrixmul_and_stream/20.PNG?raw=true)

