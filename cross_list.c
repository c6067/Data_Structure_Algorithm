#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct {
	int row;
	int column;
	int value;
	struct Node *right;
	struct Node *down;
}Node;

typedef struct {
	int rows;
	int columns;
	struct Node *row_head;
	struct Node *col_head;
}Matrix;

Node *create_cross_list_node(int row, int column, int value){
	Node *new_node = (Node*)malloc(sizeof(Node));
	if(NULL == new_node){
		printf("create node fail.\n");
		exit(-1);
	}
	new_node->row = row;
	new_node->column = column;
	new_node->value = value;
	new_node->right = NULL;
	new_node->down = NULL;

	return new_node;
}

Matrix *create_matrix(int rows, int columns){
	Matrix *new_node = (Matrix*)malloc(sizeof(Matrix));
	new_node->rows = rows;
	new_node->columns = columns;

	new_node->row_head = (Node*)malloc(sizeof(Node) * rows);
	for (int i = 0; i < rows; i++){
		new_node->row_head[i].right = NULL;
	}

	new_node->col_head = (Node*)malloc(sizeof(Node) * columns);
	for (int i = 0; i < columns; i++){
		new_node->col_head[i].down = NULL;
	}

	return new_node;
}

