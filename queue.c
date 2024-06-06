//queue:First In First Out(FIFO),data enter from rear,output from front
//implement with array(two index)
struct queue_a{
	int data[MAX];
	int front;
	int rear;
};

struct queue_a* init_queue_a(){
	struct queue_a *qa = (struct queue_a*)malloc(sizeof(struct queue_a));
	qa->front = qa->rear = -1;
	return qa;
}

bool isfull_queue_a(struct queue_a *qa){
	return qa->rear == MAX - 1;
}

bool isempty_queue_a(struct queue_a *qa){
	return qa->rear == qa->front || qa->front == -1;
}

void enqueue_a(struct queue_a *qa, int value){
	if(isfull_queue_a(qa)){
		printf("queue was full.\n");
		return;
	}else{
		if(isempty_queue_a(qa))
			qa->front = 0;
		qa->data[++qa->rear] = value;
	}
}

int dequeue_a(struct queue_a *qa){
	int res;
	if(isempty_queue_a(qa)){
		printf("queue was empty.\n");
		res = -1;
	}else{
		res = qa->data[qa->front++];
		if(qa->front > qa->rear)		//judge front whether beyond rear
			qa->front = qa->rear = -1;
	}
	return res;
}

//implement with linked list
struct nodeq{
	int data;
	struct nodeq *next;
};

struct queue_l{
	struct nodeq *front;
	struct nodeq *rear;
	int size;
	int max_size;
};

struct queue_l* init_queue_l(int max_size){
	struct queue_l *ql = (struct queue_l*)malloc(sizeof(struct queue_l));
	ql->front = ql->rear = NULL;
	ql->size = 0;
	ql->max_size = max_size;
	return ql;
}

struct nodeq* creat_ql_node(int data){
	struct nodeq *new_node = (struct nodeq*)malloc(sizeof(struct nodeq));
	if(new_node){
		new_node->data = data;
		new_node->next = NULL;
		return new_node;
	}else{
		printf("allocate memory fail.\n");
		return NULL;
	}
}

bool isempty_queue_l(struct queue_l *ql){
	return ql->front == NULL;
}

bool isfull_queue_l(struct queue_l *ql){
	return ql->size == ql->max_size;
}

void enqueue_l(struct queue_l *ql, int data){
	if(ql->size >= ql->max_size){
		printf("queue was full.\n");
		return;
	}

	struct nodeq *new_node = creat_ql_node(data);
	if(ql->rear == NULL){
		ql->rear = ql->front = new_node;
		return;
	}
	ql->rear->next = new_node;
	ql->rear = new_node;
	ql->size++;
}

int dequeue_l(struct queue_l *ql){
	if(ql->front == NULL){
		printf("queue was empty.\n");
		return -1;
	}

	struct nodeq *deq = ql->front;
	int value = deq->data;
	ql->front = ql->front->next;
	if(ql->front == NULL){
		ql->rear = NULL;
	}
	free(deq);
	ql->size--;
	return value; 
}
