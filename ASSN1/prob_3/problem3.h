using namespace std;

typedef struct node
{
	int* data;
	int ii, jj;
	struct node *next;
} NODE;

typedef struct
{
	NODE* front;
	NODE* rear;
} QUEUE;

void enqueue(QUEUE* q, int* data, int ii, int jj);

void search(QUEUE* q, int* data, int arr[1000][1000], int x, int y, int h, int w);

int isEmpty(QUEUE* q);

int* dequeue(QUEUE* q, int*ii, int* jj);

int arr[1000][1000] = { 0 };