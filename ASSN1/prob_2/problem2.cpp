#include<iostream>
#include<stdlib.h>
#include<algorithm>

using namespace std;

#define SIZE 1000000

int arr[SIZE] = { 0 };

int result_array[SIZE] = { 0 };

int main(void)
{
	

	int num;
	int result;
	int lowerbound; // longest increasing subsequence 를 찾기위한 lowerbound 를 기억한다.

	int length = 0;

	scanf("%d", &num);

	for (int i = 0; i < num; i++) scanf( "%d", &arr[i]);

	for (int i = 0; i < num; i++) // index 가 0 부터 num -1 까지 있는 배열을 탐색하여 최장 증가 배열을 만드는 과정이다.
	{
		if (arr[i] > result_array[length]) // 만약, arr[i] 가 최장 증가 배열의 마지막 원소보다 크다면, length++ 을 해주고 result_array의 마지막에 arr[i] 값을 넣어준다.
		{
			length++;
			result_array[length] = arr[i];
		}

		else // arr[i] 가 result_array의 마지막 원소보다 작다면, lowerbound를 찾아 result_array[lowerbound] 에 arr[i] 를 넣어준다.
		{
			lowerbound = lower_bound(result_array, result_array + length, arr[i]) - result_array + 1;

			// <algorithm> 헤더파일에 들어있는 lower_bound 함수를 이용해 변수의 lower_bound 를 구했다.

			result_array[lowerbound] = arr[i];
		}
	}

	printf("%d", length);

	return 0;
}