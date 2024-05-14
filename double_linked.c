#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



struct dlist{
	int value;
	struct dlist *prev;
	struct dlist *next;
};

struct dlist* dl_init(){
	return NULL;
}

void dl_destroy(struct dlist *head){
	while(head != NULL){
		struct dlist *temp = head;
		head = head->next;
		free(temp);
	}
	head = NULL;
}

struct dlist* create_dl_node(int value){
	struct dlist* new_node = (struct dlist*)malloc(sizeof(struct dlist));
	if(! new_node){
		perror("Unable to allocate memory for new node");
        exit(EXIT_FAILURE);
	}
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

void dl_push_back(struct dlist **head, int value){
	struct dlist *new_node = create_dl_node(value);

	if(*head == NULL){
		*head = new_node;
	}else{
		struct dlist *current = *head;
		while(current->next != NULL){
			current = current->next;
		}
		current->next = new_node;
		new_node->prev = current;
	}
}

int dl_pop_back(struct dlist **head){
	if(*head == NULL){
		printf("list is empty.\n");
		return -1;
	}

	struct dlist *current = *head;
	int value = current->value;
	while(current->next != NULL){
		current = current->next;
	}

	if(current->prev == NULL){
		*head = NULL;
	}else{
		current->prev->next = NULL;
	}
	free(current);
	return value;
}

void dl_push_front(struct dlist **head, int value){
	struct dlist *new_node = create_dl_node(value);

	if(*head != NULL){
		(*head)->prev = new_node;
	}
	*head = new_node;
}

int dl_pop_front(struct dlist **head){
	if(*head == NULL){
		printf("list is empty.\n");
		return -1;
	}

	struct dlist *current = *head;
	int value = current->value;
	*head = current->next;
	if(*head != NULL){
		(*head)->prev = NULL;
	}
	free(current);
	return value;
}

struct dlist* dl_find_node(struct dlist *head, int value){
	struct dlist *current = head;
	while(current != NULL){
		if(value == current->value)
			return current;
		current = current->next;
	}
	printf("not found node.\n");
	return NULL;
}

void dl_print(struct dlist *head){
	struct dlist *cur = head;
	while(cur != NULL){
		printf("Value: %d\n",cur->value);
		cur = cur->next;
	}
	printf("\n");
}

//add double linked list with sentinel
//sentinel simplify dl list operate,
//but MUST remember sentinel node is specific
struct dlist* dl_sentinel_init(){
	struct dlist *sentinel = (struct dlist*)malloc(sizeof(struct dlist));
	sentinel->value = 999;
	sentinel->prev = NULL;
	sentinel->next = NULL;
	return sentinel;
}

void dl_sentinel_insert(struct dlist *head, int value){
	struct dlist *new_node = (struct dlist*)malloc(sizeof(struct dlist));
	new_node->value = value;

	new_node->next = head->next;
	if(head->next != NULL){
		head->next->prev = new_node;	//because sentinel node is placeholder and boundary,
	}									//its prev points to the last node.so,its next  
	head->next = new_node;				//update need to update its prev
	new_node->prev = head;
}

void dl_sentinel_del(struct dlist *head){
	head->prev->next = head->next;
	if(head->next != NULL){
		head->next->prev = head->prev;		//set current node pointer list's tail  
	}										//but,CAUTION! double linked list is complex!
	free(head);
}

void dl_sentinel_traverse(struct dlist *head){
	struct dlist *current = head->next;			//Caution: point next
	while(current != NULL){
		printf("value: \n", current->value);
		current = current->next;
	}
}
