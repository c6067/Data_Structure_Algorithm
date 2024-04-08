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

linked *linked_reverse(linked *node){	
	if(node==NULL){
		return NULL;
	}

	/* linked* prev = NULL;
	linked* back = NULL;
	linked* current = node;
	while(current != NULL){
		back = current->next;
		current->next = prev;
		prev = current;					//reverse means null pointer move previous
		current = back;
	}	
	return prev; */

	//push front method
	linked *current = node;
	linked *head = NULL;
	while(current){
		linked *temp = current->next;
		current->next = head;			//reverse,head local is current back
		head = current;
		current = temp;
	}
	
	return head;
}

//search middle value(single linked list)
linked *find_middle(linked *node) {
    //fast&slow pointer method	
    linked *fast = node;    
    linked *slow = node;
    while (fast && fast->next) {        
        fast = fast->next->next;		//fast pointer move two step,slow move one
        slow = slow->next;			//such as slow equal middle value. amazimg!!
    }
    
    return slow;
}

//linked list merge
linked *merge_two(linked *list1, linked *list2){
    linked *head = NULL;
    linked *tail = NULL;

    //key:compare two list's value,littel please to list1;big please list2
    //traverse continue
    while (list1 && list2) {    	   
        if (list1->data <= list2->data) {        	  	
            head = tail = list1;
            list1 = list1->next;
        } else {        	  	
            head = tail = list2;
            list2 = list2->next;
        }        
        tail = tail->next;
    }
    //deal with list2 node of left	
    if(list2){
        tail->next = list2; 		    	
    }
    return head;
}


//partitioning linked list
linked *partition(linked *head, int key) {
    //define two new null linked list    
    linked *small_head = NULL;
    linked *small_tail = NULL;
    linked *great_head = NULL;
    linked *great_tail = NULL;    
    //traverse original linked list
    while (head) {        
        if (head->data < key) {        	  
            if (small_head == NULL) {
                small_head = small_tail = head;
            } else {
            	 //push back
                small_tail->next = head;
                small_tail = head;
            }
        } else {
        	  //if current data greater than key
            if (great_head == NULL) {
                great_head = great_tail = head;
            } else {            	 
                great_tail->next = head;
                great_tail = head;
            }
        }        
        head->next = NULL;        
        head = head->next;
    }
    
    if (small_head == NULL) {
        return great_head;
    } else {    	   	
        small_tail->next = great_head;
        return small_head;
    }
}

//hashlist***
linked *intersection_hashlist(linked *head_a, linked *head_b) {    
   linked* node_set[10000] = { NULL };    
	
    /*(intptr_t) is type conversion operator.
    / it's to use converts the pointer address to an integer of type intptr_t, 
    / this is to use pointer address as an index of hash table, in order to 
    / store and find the address of node */
    while (head_a) {    	
        node_set[(intptr_t)head_a] = head_a;
        head_a = head_a->next;
    }    
    while (head_b) {
    	//compare with head_a node
        if (node_set[(intptr_t)head_b] == head_b) {
            return head_b;
        }
        head_b = head_b->next;
    }       
    return NULL;	 //not found result
}

//double pointer method
linked *intersection_dp(linked *head1, linked *head2) {    
    linked *p1 = head1;
    linked *p2 = head2;
    
    //double pointer alternate traverse linked lists,until found or traverse to end
    while (p1 != p2) {
        if (p1 == NULL) {
            p1 = head2;			//p1 list' tail link to list2' head
        } else {
            p1 = p1->next;
        }        
        
        if (p2 == NULL) {
            p2 = head1;
        } else {
            p2 = p2->next;
        }
    }    
    
    return p1;
}

