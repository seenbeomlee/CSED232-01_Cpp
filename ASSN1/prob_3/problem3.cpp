#include <iostream>
#include <stdlib.h>
#include "problem3.h"

/*“나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다.”*/

int main(void)
{
	int w, h, y; // 빙하판의 세로, 가로, 연 수를 저장하는 변수
	int num = 0; // 빙하의 개수를 세는 변수
	int* d;
	int ii, jj;
	QUEUE queue; // 큐

	// 큐 초기화
	queue.front = NULL;
	queue.rear = NULL;

	scanf("%d %d %d", &w, &h, &y); // 빙하판의 가로, 세로, 연 수를 입력해준다.

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			scanf("%d", &arr[i][j]); // 빙하판의 배열에 그 높이를 입력해준다.
		} 
	}

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			arr[i][j] -= y; // -y 를 함으로써, y년 뒤의 빙하값을 배열에 삽입했다.

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (arr[i][j] > 0) // 빙하판에서 녹지않은 빙하를 발견했을 때
			{
				num++;
				arr[i][j] = 0; // 세었으므로, 빙하값을 0으로 만들어준다.
				enqueue(&queue, &arr[i][j], i, j);

				while (!isEmpty(&queue))
				{
					d = dequeue(&queue, &ii, &jj);

					search(&queue, d, arr, ii, jj, h, w); // 이 때, search 할 배열은 arr[i][j]가 아닌, dequeue를 통해 얻은 arr[ii][jj] 값이다.
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

	temp->data = data; // 생성한 노드의 data에 배열의 주솟값 대입
	temp->ii = ii;
	temp->jj = jj;
	temp->next = NULL; // 초기화


	if (isEmpty(q)) // 큐가 비어 있는 경우(isEmpty 함수는 큐가 비어있을 때 1반환)
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

void search(QUEUE* q, int* data, int arr[1000][1000],int x, int y, int h, int w) // 주소를 받아서 해당 배열의 상 -> 좌 -> 하 -> 우를 서치하는 함수 
{
	if ( (x > 0) && (arr[x - 1][y] > 0)) // 만약 0보다 큰 값 (빙하가 남아있음) 이 있으면, 그 자리를 0 으로 만들고, 그 자리의 주솟값을 enqueue에 넘겨 bfs를 한다.
	{
		arr[x - 1][y] = 0;
		enqueue(q, &arr[x - 1][y],x-1 , y);
	}

	if ((y > 0) && (arr[x][y-1] > 0)) // 만일, 넘겨받은 arr[x][y]에서 y = 0  이라면, y = -1 이라는 배열은 존재하지 않으므로, 검사할 이유가 없다.
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

int isEmpty(QUEUE* q) // QUEUE가 비었으면 1반환, 차있으면 0반환
{
	return q->front == NULL;
}

int* dequeue(QUEUE* q, int*ii, int* jj) // bfs 를 할 때 순차적으로 탐색하기 위해 dequeue를 해야한다.
{
	NODE *temp;
	int* data;

	temp = q->front;

	data = temp->data;
	*ii = temp->ii; // 포인터를 이용해 *ii 값을 넘겨준다. 아직 &를 이용하는 것은 익숙하지 않아서 포인터를 이용했다.
	*jj = temp->jj;

	q->front = temp->next;

	free(temp);

	return data;
}