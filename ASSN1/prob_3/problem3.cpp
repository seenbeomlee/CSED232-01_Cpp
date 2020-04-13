#include <iostream>
#include <stdlib.h>
#include "problem3.h"

/*������ �� ���α׷��� ������ �ٸ� ����� �������� ���� ���� �ϼ��Ͽ����ϴ�.��*/

int main(void)
{
	int w, h, y; // �������� ����, ����, �� ���� �����ϴ� ����
	int num = 0; // ������ ������ ���� ����
	int* d;
	int ii, jj;
	QUEUE queue; // ť

	// ť �ʱ�ȭ
	queue.front = NULL;
	queue.rear = NULL;

	scanf("%d %d %d", &w, &h, &y); // �������� ����, ����, �� ���� �Է����ش�.

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			scanf("%d", &arr[i][j]); // �������� �迭�� �� ���̸� �Է����ش�.
		} 
	}

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			arr[i][j] -= y; // -y �� �����ν�, y�� ���� ���ϰ��� �迭�� �����ߴ�.

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (arr[i][j] > 0) // �����ǿ��� �������� ���ϸ� �߰����� ��
			{
				num++;
				arr[i][j] = 0; // �������Ƿ�, ���ϰ��� 0���� ������ش�.
				enqueue(&queue, &arr[i][j], i, j);

				while (!isEmpty(&queue))
				{
					d = dequeue(&queue, &ii, &jj);

					search(&queue, d, arr, ii, jj, h, w); // �� ��, search �� �迭�� arr[i][j]�� �ƴ�, dequeue�� ���� ���� arr[ii][jj] ���̴�.
				}
			}

		}
	}

	printf("%d", num);

	return 0;
}

void enqueue(QUEUE* q, int* data, int ii, int jj)
{
	NODE *temp;

	temp = (NODE*)malloc(sizeof(NODE));

	temp->data = data; // ������ ����� data�� �迭�� �ּڰ� ����
	temp->ii = ii;
	temp->jj = jj;
	temp->next = NULL; // �ʱ�ȭ


	if (isEmpty(q)) // ť�� ��� �ִ� ���(isEmpty �Լ��� ť�� ������� �� 1��ȯ)
	{
		q->front = temp;
		q->rear = temp;
	}
	else
	{
		q->rear->next = temp;
		q->rear = temp;
	}
}

void search(QUEUE* q, int* data, int arr[1000][1000],int x, int y, int h, int w) // �ּҸ� �޾Ƽ� �ش� �迭�� �� -> �� -> �� -> �츦 ��ġ�ϴ� �Լ� 
{
	if ( (x > 0) && (arr[x - 1][y] > 0)) // ���� 0���� ū �� (���ϰ� ��������) �� ������, �� �ڸ��� 0 ���� �����, �� �ڸ��� �ּڰ��� enqueue�� �Ѱ� bfs�� �Ѵ�.
	{
		arr[x - 1][y] = 0;
		enqueue(q, &arr[x - 1][y],x-1 , y);
	}

	if ((y > 0) && (arr[x][y-1] > 0)) // ����, �Ѱܹ��� arr[x][y]���� y = 0  �̶��, y = -1 �̶�� �迭�� �������� �����Ƿ�, �˻��� ������ ����.
	{
		arr[x][y-1] = 0;
		enqueue(q, &arr[x][y-1],x, y-1);
	}

	if ((x < h) && (arr[x + 1][y] > 0))
	{
		arr[x + 1][y] = 0;
		enqueue(q, &arr[x + 1][y],x+1, y);
	}

	if ((y < w) && (arr[x][y + 1] > 0))
	{
		arr[x][y + 1] = 0;
		enqueue(q, &arr[x][y + 1], x, y+1);
	}
}

int isEmpty(QUEUE* q) // QUEUE�� ������� 1��ȯ, �������� 0��ȯ
{
	return q->front == NULL;
}

int* dequeue(QUEUE* q, int*ii, int* jj) // bfs �� �� �� ���������� Ž���ϱ� ���� dequeue�� �ؾ��Ѵ�.
{
	NODE *temp;
	int* data;

	temp = q->front;

	data = temp->data;
	*ii = temp->ii; // �����͸� �̿��� *ii ���� �Ѱ��ش�. ���� &�� �̿��ϴ� ���� �ͼ����� �ʾƼ� �����͸� �̿��ߴ�.
	*jj = temp->jj;

	q->front = temp->next;

	free(temp);

	return data;
}