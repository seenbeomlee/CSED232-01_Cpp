#include<iostream>
#include<stdlib.h>

#define SIZE 1000000

int array[SIZE];

int main(void)
{
	int highest1 = 0, highest2 = 0; // 1�� ���ʿ������� �� �� �ִ밪�� �����ϴ� �����̰�, 2�� �����ʿ������� �� �� �ִ밪�� �����ϴ� �����̴�.
	int temp;
	int num;
	int sum = 0;

	scanf("%d", &num); // ���� ������ ������ �Է¹޴´�

	printf("\n");

	for (int i = 0; i < num; i++)	scanf("%d", &array[i]); // ���� ������ ���̸� �Է¹޴´�

	for (int i = 0; i < num; i++) // ���ʿ��� ������ �� ���̴� ���������� ������ ����Ѵ�
	{
		temp = array[i];

		if (temp > highest1) // ����, ���� ���� �� ���������� ���̺��� temp�� ���̰� ��ٸ�, temp�� highest �� �ǰ�, ���̴� ���������� ������ 1���� �߰��ȴ�.
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


	printf("%d", sum); // ���ʿ��� ������ �� ���������� ���� + �����ʿ��� ������ �� ���������� ����

	return 0;
}