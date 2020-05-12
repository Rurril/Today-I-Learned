# Backtracking - 백트래킹



## 1. 설명

백 트래킹은 '조합 알고리즘 문제'에 대해 모든 가능한 해를 나열하는 방법이다.
** 즉, 백 트래킹은 모든 조합의 수를 살펴보는 것인데 단 조건이 만족할 때.**
(알고리즘이라기보다는 문제에 접근하는 방식을 말한다.)

모든 경우의 수를 다 탐색하기에는 시간적으로 부족할 수 있으므로 한정된 조건(CSP)을 적용해서 경우의 수를 줄여나가자는 방법을 말한다. 

### 1.1 대표적인 문제

백 트래킹의 대표적인 문제는 n-Queen 문제이다. 

> N * N 체스판에 최대한 많은 Queen을 놓고 싶다. 다만, 서로를 공격하지 않게 올려놓고 싶다. 총 몇 가지 경우의 수가 있을까?
>> 모든 경우의 수 = 컬럼의 수 ^ 한 컬럼에 Queen을 놓는 경우의 수 = N ^ N (Power N of N) 

단순히 모든 경우의 수를 계산한다고 한다면, 시간 복잡도는 O(N^N)으로 무수한 경우의 수가 존재한다. N = 10이라고 한다면 무려 100억 개나 되는 경우의 수를 다 찾아야한다고 할 수 있다. 

이제 백트래킹을 이용해보자. 한 컬럼에 Queen을 두었으면 오른쪽 컬럼에 가능한 자리에 Queen을 둔다. 또 다시 오른쪽 컬럼 중에서 가능한 자리에 Queen을 둔다. 이 과정을 반복한다. **만약에 N개의 Queen을 두었다면 카운트를 증가 시킨다.** 

**이제부터가 중요한데, 성공하기 직전으로 상태를 되돌린다(back).** 그리고 N번째 컬럼 중 다른 칸들을 시도한다. 만약에 없다면 N-1번째 컬럼에 있는 Queen을 들어서 다음으로 가능한 칸으로 옮긴다. 다시 N번째 컬럼에 Queen을 둘 수 있는 곳을 찾는다. N-1번째 컬럼의 모든 경우를 시도했다면, N-2번째로 되돌아가 다음으로 가능한 위치로 Queen을 옮긴다.

퀸을 놓기 위해서는 다른 퀸들이 같은 행이나 열 그리고 대각선에 위치하지 않는다는 **한정 조건(CSP - Constrain Satisfaction Problems)이 된다. ** 결과적으로, 한정조건을 이용한 검색은 모든 경우의 수를 검색하는 것보다 훨씬 경우의 수가 적다. 


```java

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class question9663_sub {
	static int n;
	static int count;
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(br.readLine());
		
		// 각 행에는 하나의 열에만 퀸이 놓여질 수 있다. 
		// 1 열부터 N열까지 돌면서 각 1행 N열에 퀸을 놓았을때 가능한 경우를 확인하다. 
		
		for(int i=1;i<=n;i++) {
			int[] col = new int[n+1]; // n * n 행렬이기에 열도 인덱스를 n까지 갖을 수 있게 한다. 
			
			// 1행 i열에 퀸을 놓았다. 
			col[1] = i;
			// 1행 i열에 퀸을 놓았을 경우 가능한 횟수를 dfs로 구한다.
			dfs(col, 1);				
		}
		
		System.out.println(count);
	}
	
	public static void dfs(int[] col, int row) {
		if(row == n) {
			count++;
		}else {
			// 1열 부터 N 열까지 반복하면서 (row+1, i)에 퀸을 놓을 수 있는 경우가 있는지 확인한다.
			// 있으면 다음행의 dfs를 호출한다.
			for(int i = 1; i <= n; i++) {
				col[row+1] = i;
				if(isPossible(col, row+1)) {
					dfs(col, row+1);
				}
			}						
		}
	}
	
	public static boolean isPossible(int[] col, int row) {
		// 1행부터 row 행까지 같은 열 혹은 대각선에 위치하는 퀸이 있는지 확인한다.
		
		for(int i=1; i<row;i++) {
			// i행과 row 행의 열 값이 같으면 퀸을 놓을 수 없다.
			if(col[i] == col[row]) return false;
			
			// i행과 row 행의 열 값이 대각선에 위치하는 절대값이면 안된다.
			if(Math.abs(i - row) == Math.abs(col[i] - col[row]))return false;
			// 대각선의 정의를 abs(row1 - row2) == asb(col1 - col2) 로 간단하게 끝내버렸다... 와우. 
		}
		return true; 
	}
	
}


``` 
BOJ의 9663번 문제로 n-Queen을 푼 것을 참고자료로 올린다.(DFS를 사용하였다)

## 2. 완전 탐색 방법들

대표적인 완전 탐색 방법으로는 DFS(Depth First Search)와 BFS(Breadth Frist Search)가 있다. 

자세한 것은 각자 문서를 만들어서 설명하도록 하겠다. 


### 2.1 DFS(Depth First Search)



### 2.2 BFS(Breadth First Search)

### 2.3 휴리스틱 탐색

## 4. 참고자료

https://medium.com/@jeongdowon/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-backtracking-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-13492b18bfa1

https://namu.wiki/w/%EB%B0%B1%ED%8A%B8%EB%9E%98%ED%82%B9

