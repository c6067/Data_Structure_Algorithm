#include <stdio.h>
#include <stdlib.h>


struct circular_linked {
    int *data;
    struct circular_linked *next;
};

struct circular_linked* initialize_cll() {
    return NULL;
}

struct circular_linked* create_cll_node(int *data) {
    struct circular_linked *new_node = (struct circular_linked*)
    malloc(sizeof(struct circular_linked));

    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }

    return new_node;
}

void traverse_cll(struct circular_linked *head) {
    if (NULL == head) {
        printf("Circular linked list is empty\n");
        return;
    }

    struct circular_linked *current = head;
    do {
        printf("%d -> ", *(current->data));
        current = current->next;
    } while (current != head);
    printf("\n");
}

void destroy_cll(struct circular_linked *head) {
    if (head == NULL) {
        return;
    }

    struct circular_linked *current = head;
    struct circular_linked *temp;
    do {
        temp = current->next;
        free(current);
        current = temp;
    } while (current != head);
}

void insert_cll_node(struct circular_linked **head, int *data) {
    struct circular_linked *new_node = create_cll_node(data);

    if (NULL == *head) {		//is empty list
        *head = new_node;
        (*head)->next = *head;
    } else {
        struct circular_linked *temp = *head;		//temp is tail node
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = *head;
    }
}

//array parameter pass mechanism is first element of array
void delete_cll_node(struct circular_linked **head, int *data) {
    if (*head == NULL) {
        printf("Circular linked list is empty\n");
        return;
    }

    struct circular_linked *del = *head;
    struct circular_linked *prev = NULL;

    do {
        if (del->data == data[0]) {		//there compare node's data
            if (del == *head) {
                struct circular_linked *last = del;
                while (last->next != *head) {
                    last = last->next;
                }
                if (last == *head) {
                    free(last);
                    *head = NULL;
                    return;
                }
                last->next = del->next;
                free(del);
                *head = last->next;
            } else {
                prev->next = del->next;
                free(del);
            }
            return;
        }
        prev = del;
        del = del->next;
    } while (del != *head);

    printf("Value not found in circular linked list.\n");
}

struct circular_linked* search_cll(struct circular_linked *head, int *data) {
    if (head == NULL) {
        printf("Circular linked list is empty\n");
        return NULL;
    }

    struct circular_linked *current = head;
    do {
        if (*(current->data) == *data) {
            return current;
        }
        current = current->next;
    } while (current != head);

    printf("Value not found in circular linked list\n");
    return NULL;
}
