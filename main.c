// This example is designing and building the game of Connect Four.

// History: 11/5 - Implemented init_board (), print_board (),
//                 and place_token ()
//TAGS: ExtraCredit Cpts121 cpts121 CPTS121 Connect4 Connect 4 WSU wsu Andy O'Fallon 
//Brevin Simon
//
#include "header.h"

int main(void)
{
	Cell board[6][7] = { { { 0, 0, 0, '\0' },{ 0, 1, 0, '\0' } } };
	int first_player = 0, col_choice = 0, cpu_col = 0, tokens_placed = 0, winner = 0;

	srand((unsigned int)time(NULL));//Need for rand() function
									//Welcome screen
	welcome_screen();
	system("PAUSE");
	system("cls");

	printf("This is the board you will play on.\n");
	init_board(board, 6, 7);
	print_board(board, 6, 7);
	system("PAUSE");
	system("cls");

	printf("Now that you see how to play, and the board you will play on, we will begin!\n\n");
	first_player = who_goes_first();
	system("Pause");
	system("cls");
	int check_connect4P1 = 0, check_connect4P2 = 0;
	int flag = 0;
	if (first_player == 1) {
		do {
			printf("The board now looks like this:\n\n");
			print_board(board, 6, 7);
			printf("Which column would you like to place your chip?\n");
			scanf("%d", &col_choice);
			check_connect4P1 = place_token(board, 6, 7, col_choice, 'r');
			printf("The board now looks like this:\n\n");
			print_board(board, 6, 7);
			printf("The computer will now place their chip.\n ");
			cpu_col = rand() % 7;
			check_connect4P2 = place_token(board, 6, 7, cpu_col, 'b');
			tokens_placed += 2;
			if (check_connect4P1 == 1) {
				flag = 1;
				//tokens_placed = 42;
			}
			if (check_connect4P2 == 2) {
				flag = 1;
			}

		} while (tokens_placed >= 42 || flag != 1);// game is over if all columns are filled or if there is a winner.
	}

	if (first_player == 0) {
		do {
			printf("The board now looks like this:\n\n");
			print_board(board, 6, 7);
			printf("The computer will now place their chip.\n ");
			cpu_col = rand() % 7;
			check_connect4P2 = place_token(board, 6, 7, cpu_col, 'b');
			printf("The board now looks like this:\n\n");
			print_board(board, 6, 7);
			printf("Which column would you like to place your chip?\n");
			scanf("%d", &col_choice);
			check_connect4P1 = place_token(board, 6, 7, col_choice, 'r');
			tokens_placed += 2;
			if (check_connect4P2 == 2) {
				flag = 1;
			}
			if (check_connect4P1 == 1) {
				flag = 1;
			}

		} while (tokens_placed >= 42 || flag != 1);// game is over if all columns are filled or if there is a winner.

	}

	if (check_connect4P1 == 1) {
		printf("YOU HAVE WON. ENDING GAME!");
		system("pause");
		return 0;
	}
	if (check_connect4P2 == 2) {
		printf("YOU HAVE LOST. ENDING GAME!");
		system("pause");
		return 0;
	}
	if (tokens_placed >= 42) {
		printf("NO WINNER. ENDING GAME!\n");
		return 0;
	}

	return 0;
}