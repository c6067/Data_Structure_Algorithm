/*priority queue:set priority node linear arrays(from samllest to largest/ or opposit)
  this structrue core,only need 'front' assign sequence,not need rear.so enqueue means
  adjust samll and large sequence,and dequeue means delete front's node.
*/

//implement priority queue with linked list

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 255

struct pqnode
{
	int data;
	int priority;
	struct pqnode *next;
};

struct priority_queue
{
	struct pqnode *front;
};

struct priority_queue* init_pq(){
	struct priority_queue *pq = (struct priority_queue*)malloc(sizeof(struct priority_queue));
	if(pq == NULL)
		exit(EXIT_FAILURE);
	pq->front = NULL;
	return pq;
}

struct pqnode* creat_pq_node(int data, int priority){
	struct pqnode *new_node = (struct pqnode*)malloc(sizeof(struct pqnode));
	if(new_node == NULL)
		exit(EXIT_FAILURE);
	new_node->data = data;
	new_node->priority = priority;
	new_node->next = NULL;
	return new_node;
}

void enqueue_priority(struct priority_queue *pq, int data, int priority){
	struct pqnode *new_node = creat_pq_node(data, priority);

	if(pq->front == NULL || pq->front->priority < priority){	//samllest sequence
		new_node->next = pq->front;
		pq->front = new_node;
	}else{
		struct pqnode *current = pq->front;
		while(current->next != NULL && current->next->priority >= priority)
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
}

int dequeue_priority(struct priority_queue *pq){
	if(pq->front == NULL){
		printf("priority queue was empty.\n");
		return -1;
	}

	struct pqnode *del = pq->front;
	int value = del->data;
	pq->front = pq->front->next;
	free(del);
	return value;
}

bool search_bypriority(struct priority_queue *pq, int target_priority){
	if(pq->front == NULL){
		printf("priority queue was empty.\n");
		return false;
	}

	struct pqnode *current = pq->front;
	while(current){
		if(current->priority == target_priority){			
			return true;
		}
		current = current->next;
	}	
	
	printf("not found match node.\n");
	return false;	
}

//implement priority queue with array
struct pqanode
{
	int data;
	int priority;
};

struct pqarr
{
	struct pqanode nodes[MAX];
	int size;
};

void init_pqarr(struct pqarr *pqa){
	pqa->size = 0;
}

bool isempty_pqarr(struct pqarr *pqa){
	return pqa->size == 0;
}

void enqueue_pqa(struct pqarr *pqa, int value, int priority){
	if(pqa->size == MAX){
		printf("priority queue was full.\n");
		return;
	}

	int i;
	// 'pqa->nodes[i].priority > priority',that sort from smallest to largest
	// if change '<', this sort from largest to smallest
	for (i = pqa->size - 1; i >= 0 && pqa->nodes[i].priority > priority ; i--){
		pqa->nodes[i + 1] = pqa->nodes[i];
	}
	pqa->nodes[i + 1].data = value;
	pqa->nodes[i + 1].priority = priority;
	pqa->size++;
}

int dequeue_pqa(struct pqarr *pqa){
	if(isempty_pqarr(pqa)){
		printf("priority queue was empty.\n");
		return -1;
	}
	return pqa->nodes[--pqa->size].data;
}

//implement circular queue
struct circular_queue{
	int data[MAX];
	int size;
	int front;
	int rear;
};

void init_circular_queue(struct circular_queue *cq){
	cq->front = cq->rear = 0;
	cq->size = 0;
}

bool isempty_circular_queue(struct circular_queue *cq){
	return cq->size == 0;
}

bool isfull_circular_queue(struct circular_queue *cq){
	return cq->size == MAX;
}

void enqueue_circular_queue(struct circular_queue *cq, int value){
	if(isfull_circular_queue(cq)){
		printf("circular queue is full.\n");
		return;
	}
	cq->data[cq->rear] = value;
	cq->rear = (cq->rear + 1) % MAX;
	cq->size++;
}

void dequeue_circular_queue(struct circular_queue *cq){
	if(isempty_circular_queue(cq)){
		printf("circular queue is empty.\n");
		return;
	}
	int value = cq->data[cq->front];
	printf("data: %d\n",value);
	cq->front = (cq->front + 1) % MAX;
	cq->size--;
}

void display_circular_queue(struct circular_queue *cq){
	if (isempty_circular_queue(cq)){
		printf("circular queue empty.\n");
		return;
	}
	printf("circular queue element: \n");
	int i = cq->front;
	int count = 0;
	while(count < cq->size){
		printf("%d\n",cq->data);
		i = (i + 1) % MAX;
		count++;
	}
	printf("\n");
}
