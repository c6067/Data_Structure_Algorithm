#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef int DataType;


typedef struct linked {
	DataType data;	
	struct linked *next;
}linked;

void print_linked(linked *node){
	while(node!=NULL){
		printf("%d->",node->data);	
		printf("%p :",node->next);	
		node=node->next;
	}	
	printf("NULL\n");
}

linked *create_node(DataType n){		
	linked *new_node = (linked*)malloc(sizeof(linked));
	if(NULL == new_node){  			//judge pointer type variable wether NULL is C programmer's good habit!
		printf("malloc fail!\n");
		exit(-1);
	}	
	new_node->data = n;
	new_node->next = NULL;

	return new_node;
}

void linked_push_back(linked **node, DataType n){
	linked *new_node = create_node(n);
	if(*node == NULL){		
		*node = new_node;
	}else{
		//link isn't null,found tail node
		linked* tail = *node;
		while(tail->next != NULL){		
			tail=tail->next;
		}		
		tail->next = new_node;
	 }
}

void linked_push_front(linked **head, DataType n){
	//first node must is head(transfer parameters mechanism)
	//so new node's next pointer point to head, and move node
	linked *new_node = create_node(n);		
	new_node->next = *head;	
	*head = new_node;
}

void linked_pop_back(linked **node){
	if(NULL == *node){
		return;
	}
	/*make three judgments:
	/ 1.poinert is null,
	/ 2.current node is tail node,
	/ 3.still nodes left */
	if(NULL == (*node)->next){
		free(*node);
		*node = NULL;
	}else{
		linked *prev = NULL;
		linked *tail = *node;		
		while(tail->next != NULL){			
			prev = tail;
			tail = tail->next;
		}		
		free(tail);
		tail = NULL;
		//set prev's next pointer is null,become new tail node
		//but,CAUTION!! if tail just is head,procedure will crash
		prev->next = NULL;
	}
}

void linked_pop_front(linked **node){
	if(NULL == *node){
		return;
	}
	
	linked *new_head = (*node)->next;	
	free(*node);
	*node = new_head;
}

linked *linked_find(linked *node, DataType n){
	linked* current = node;
	while(current){
		if(current->data == n){
		printf("find!");			
			return current;
		}else{
			current = current->next;
		}
	}
	
	printf("no find.");
	return NULL;
}

//position insert(before)
void linked_insert(linked **node, linked *pos, DataType n){
	if(NULL == pos){
		printf("NULL ERROR\n");
		return;
	}	
	
	linked *new_node = create_node(n);	
	linked *prev = *node;				//set previous node of seek
	if(*node == pos){				//judge this node whether head		 
		new_node->next = *node;			//push before
		*node = new_node;		
	}else{		
		while(prev->next != pos){		//loop search previous	
			prev = prev->next;
		}
		
		prev->next = new_node;			//update pointer
		new_node->next = pos;
	}
}

//position insert(after;suit more for single linked list)
void linked_insert_after(linked *pos, DataType n){
	if(NULL == pos){
		printf("NULL ERROR\n");
		return;
	}

	linked *new_node = create_node(n);		
	new_node->next = pos->next;			//alter pointer linked	
	pos->next = new_node;	
}

//position delete(before)
void linked_erase(linked **head, linked *pos){
	if(pos == NULL){
		printf("NULL ERROR\n");
		return;
	}

	if(*head == pos){		
		*head = pos->next;  			//head node move back
		free(pos);
		pos = NULL;
		/*or call function:linked_pop_front(node);*/
	}else{
		linked *prev = *head;
		while(prev->next != pos){	   	 //search backward
			prev = prev->next;
		}		
		prev->next = pos->next;			//alter head and position's pointer
		free(pos);
		pos = NULL;
	}
}

//position erase(after;suit single linked list)
void linked_erase_after(linked *pos){
	if(pos == NULL){
		printf("NULL ERROR\n");
		return;
	}	
	
	linked *del = pos->next;	
	pos->next = del->next;
	free(del);
	del = NULL;
}

//destory linked list
void linked_destroy(linked **node){	
	if(NULL == *node){
		return;
	}
	
	while(*node){		
		free(*node);		
		*node = (*node)->next;
	}	
	*node = NULL;
}


