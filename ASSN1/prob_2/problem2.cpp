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
	int lowerbound; // longest increasing subsequence �� ã������ lowerbound �� ����Ѵ�.

	int length = 0;

	scanf("%d", &num);

	for (int i = 0; i < num; i++) scanf( "%d", &arr[i]);

	for (int i = 0; i < num; i++) // index �� 0 ���� num -1 ���� �ִ� �迭�� Ž���Ͽ� ���� ���� �迭�� ����� �����̴�.
	{
		if (arr[i] > result_array[length]) // ����, arr[i] �� ���� ���� �迭�� ������ ���Һ��� ũ�ٸ�, length++ �� ���ְ� result_array�� �������� arr[i] ���� �־��ش�.
		{
			length++;
			result_array[length] = arr[i];
		}

		else // arr[i] �� result_array�� ������ ���Һ��� �۴ٸ�, lowerbound�� ã�� result_array[lowerbound] �� arr[i] �� �־��ش�.
		{
			lowerbound = lower_bound(result_array, result_array + length, arr[i]) - result_array + 1;

			// <algorithm> ������Ͽ� ����ִ� lower_bound �Լ��� �̿��� ������ lower_bound �� ���ߴ�.

			result_array[lowerbound] = arr[i];
		}
	}

	printf("%d", length);

	return 0;
}