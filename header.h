#ifndef CONNECT_FOUR_H
#define CONNECT_FOUR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct cell
{
	int row;
	int col;
	int occupied; // false, not occupied
	char token;
} Cell; // 13 bytes of memory required

void init_board(Cell board[][7], int num_rows, int num_cols);
void print_board(Cell board[][7], int num_rows, int num_cols);
int place_token(Cell board[][7], int num_rows, int num_cols,
	int column_drop, char token);
void welcome_screen();
int who_goes_first();
//typedef struct cell Cell;

//void init_cell(Cell *cell_ptr);
//void print_cell(Cell c);

#endif

