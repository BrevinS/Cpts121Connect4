#include "header.h"

void init_board(Cell board[][7], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			board[row_index][col_index].row = row_index;
			board[row_index][col_index].col = col_index;
			board[row_index][col_index].occupied = 0;
			board[row_index][col_index].token = '\0';
		}
	}
}

void print_board(Cell board[][7], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	printf("  0   1   2   3   4   5   6\n");

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			printf("| %c ", board[row_index][col_index].token);
		}

		printf("|\n");
	}
}

// precondition: column_drop has been validated, i.e. the column
//               is not full.
int place_token(Cell board[][7], int num_rows, int num_cols,
	int column_drop, char token)
{
	int row_counter = 0;
	int success = 0;
	for (row_counter = 1;
		board[num_rows - row_counter][column_drop].occupied;
		++row_counter);

	board[num_rows - row_counter][column_drop].token = token;
	board[num_rows - row_counter][column_drop].occupied = 1;
	
	//Check for winners under 4 different cases
	int consec_counter1 = -1, consec_counter2 = -1;
	int consec_counter3 = -1, consec_counter4 = -1;
	int consec_counter5 = 0, consec_counter6 = 0;
	//Case 1
	//OOI 
	//OIO
	//IOO
	for (int i = 1; i < 3; i++) {
		//Checks for the token and counts for each diagnol consecutive it counts
		if (board[num_rows - row_counter - i][column_drop + i].occupied == 1 
			&& board[num_rows - row_counter - i][column_drop + i].token == token) {
			consec_counter1++;
		}
		else {
			for (int j = 1; j < 5 - i; j++) {
				//This counts in the opposite direction for the diagnols example:
				//OOOI
				//OOXO
				//OIOO
				//IOOO
				//^So Say we inserted X and the I's are also our chips. The code above scans the top right I,
				//Then the code below scans for the bottom left I's. This is the same for the Case 2 Function;
				if (board[num_rows - row_counter + j][column_drop - j].occupied == 1
					&& board[num_rows - row_counter + j][column_drop - j].token == token) {
					consec_counter1++;
				}
				else {
					//IF It isnt continous then just exit the loop
					j = 6;
				}
			}
		}
	}
	//Case 2
	//IOO
	//OIO
	//OOI
	for (int i = 1; i < 3; i++) {
		if (board[num_rows - row_counter - i][column_drop - i].occupied == 1
			&& board[num_rows - row_counter - i][column_drop - i].token == token) {
			consec_counter2++;
		}
		else {
			for (int j = 1; j < 5 - i; j++) {
				if (board[num_rows - row_counter + j][column_drop + j].occupied == 1
					&& board[num_rows - row_counter + j][column_drop + j].token == token) {
					consec_counter2++;

				}
				else {
					j = 6;
				}
			}
		}
	}
	//Case 3
	//OIO
	//OIO
	//OIO
	int flag = 0;
	//Here the algorithm is to cycle down each row from index 0 and if it scans all 6 rows without 4 consecutive,
	//then the consecutive counter gets set back to zero before iterating through the next row.
	for (int i = 0; i < 6; i++) {
		consec_counter3 = 0;
		for (int j = 0; j < 7; j++) {
			if (board[j][i].token == token) {
				consec_counter3++;
			}
			else {
				//Case for NULL characters or anything that isn't the current players token
				consec_counter3 = 0;
			}
			if (consec_counter3 == 4) {
				flag = 1;
			}
			//Reset Counter For Change In Rows
			else if(j == 6 && flag != 1){
				consec_counter3 = 0;
			}
			//If We Get A Connect 4 Then Leave The Loops
			else if (flag == 1) {
				i = j = 7;
			}
		}
	}
	//Case 4
	//OOO
	//OOO
	//III
	//This algorithm is to scan from row index zero through 7 times past all the columns, similarly to Case 3
	//if we dont get 4 consecutive at the end of the column then we will set the consecutive counter to zero
	//before iterating through the next row.
	int flagAgain = 0;
	for (int i = 0; i < 6; i++) {
		consec_counter4 = 0;
		for (int j = 0; j < 7; j++) {
			if (board[i][j].token == token) {
				consec_counter4++;
			}
			else {
				consec_counter4 = 0;
			}
			if (consec_counter4 == 4) {
				flagAgain = 1;
			}
			else if (i == 6 && flagAgain != 1) {
				consec_counter4 = 0;
			}
			else if (flagAgain == 1) {
				i = j = 7;
			}
		}
	}
	//Here we are just checking with player won and printing which case or which order their connect four was in.
	switch (token) {
	case 'r':
		if (consec_counter1 >= 4) {
			printf("\nYou Have Won By NW Axis Diagnol!\n\n");
			success = 1;
		}
		if (consec_counter2 >= 4) {
			printf("\nYou Have Won By NE Axis Diagnol!\n\n");
			success = 1;
		}
		if (flag == 1) {
			printf("\nYou Have Won With A Vertical!\n\n");
			success = 1;
		}
		//consec_counter4
		if (flagAgain == 1) {
			printf("\nYou Have Won With A Horizontal!\n\n");
			success = 1;
		}
		break;
	case 'b':
		if (consec_counter1 >= 4) {
			printf("\nThe Computer Has By NW Axis Diagnol!\n\n");
			success = 2;
		}
		if (consec_counter2 >= 4) {
			printf("\nThe Computer Has Won By NE Axis Diagnol!\n\n");
			success = 2;
		}
		if (flag == 1) {
			printf("\nThe Computer Has Won With A Vertical!\n\n");
			success = 2;
		}
		if (flagAgain == 1) {
			printf("\nThe Computer Has Won With A Horizontal!\n\n");
			success = 2;
		}
		break;
	}
	//This is just bad coding practice
	consec_counter1 = -1;
	consec_counter2 = -1;
	return success;
}

void welcome_screen() {
	
	printf("**********************Welcome to Connect 4**********************\n");
	printf("              *********Brevin Simon*********             \n");
	printf("The rules for Connect 4 are as follows: Connect 4 is a 2 player game where each player takes turn placing chips in a vertical 7x6 board. You win by making a line of 4 or more of your own chips in a horizontal, vertical, or diagonal line. \n");
	printf("In this version of Connect 4 you will be playing against a computer. Your chips will be red (r) and the computers will be blue (b).\n");
}

int who_goes_first() {
	int player1 = 0, player2 = 0;
	player1 = rand() % 10 + 1;
	player2 = rand() % 10 + 1;
	if (player1 > player2) {
		printf("By random generation you go first.\n");
		return 1;
	}
	else if (player1 < player2) {
		printf("By random generation the computer goes first.\n");
		return 0;
	}
}

//int check_winner(Cell board[][7], int num_rows, int num_cols, int column_drop) {
//	if(board[])
//}