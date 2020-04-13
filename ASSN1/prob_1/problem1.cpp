#include<iostream>
#include<stdlib.h>

#define SIZE 1000000

int array[SIZE];

int main(void)
{
	int highest1 = 0, highest2 = 0; // 1은 왼쪽에서부터 볼 때 최대값을 저장하는 변수이고, 2는 오른쪽에서부터 볼 때 최대값을 저장하는 변수이다.
	int temp;
	int num;
	int sum = 0;

	scanf("%d", &num); // 나무 막대의 개수를 입력받는다

	printf("\n");

	for (int i = 0; i < num; i++)	scanf("%d", &array[i]); // 나무 막대의 높이를 입력받는다

	for (int i = 0; i < num; i++) // 왼쪽에서 보았을 때 보이는 나무막대의 개수를 계산한다
	{
		temp = array[i];

		if (temp > highest1) // 만약, 현재 가장 긴 나무막대의 길이보다 temp의 길이가 길다면, temp가 highest 가 되고, 보이는 나무막대의 개수는 1개가 추가된다.
		{
			highest1 = temp;
			sum++;
		}
	}

	for (int i = num - 1; i >= 0; i--)
	{
		temp = array[i];

		if (temp > highest2)
		{
			highest2 = temp;
			sum++;
		}
	}


	printf("%d", sum); // 왼쪽에서 보았을 때 나무막대의 개수 + 오른쪽에서 보았을 때 나무막대의 개수

	return 0;
}