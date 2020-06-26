#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

int randDice[6];
int cash = 100000, betting = 0, winTimes = 0, loseTimes = 0;

void drawDice(int key_input, int number)
{
	/* Drawing dices into console */

	switch (key_input)
	{
		case 1:
			printf("");
			break;
		case 2:
			switch (number)
			{
				case 0:
					printf("|     |");
					break;
				case 1:
				case 2:
					printf("|     |");
					break;
				case 3:
					printf("|    O|");
					break;
				case 4:
				case 5:
				case 6:
					printf("|O   O|");
					break;
			}
			break;
		case 3:
			switch (number)
			{
				case 0:
					printf("|     |");
					break;
				case 1:
				case 3:
				case 5:
					printf("|  O  |");
					break;
				case 2:
				case 6:
					printf("|O   O|");
					break;
				case 4:
					printf("|     |");
					break;
			}
			break;
		case 4:
			switch (number)
			{
				case 0:
					printf("|     |");
					break;
				case 1:
				case 2:
					printf("|     |");
					break;
				case 3:
					printf("|O    |");
					break;
				case 4:
				case 5:
				case 6:
					printf("|O   O|");
					break;
			}
			break;
		case 5:
			printf("");
			break;
	}
}
int rollDiceA()
{
	/* Make computer's dice set */

	srand(time(NULL));
	randDice[0] = rand() % 6 + 1;
	randDice[1] = rand() % 6 + 1;
	randDice[2] = rand() % 6 + 1;
	return randDice[0] + randDice[1] + randDice[2];
}
void rollDiceB(int sum)
{
	/* Make user's dice set having sum as given */

	do {
		randDice[3] = rand() % 6 + 1;
		randDice[4] = rand() % 6 + 1;
		randDice[5] = rand() % 6 + 1;
	} while (randDice[3] + randDice[4] + randDice[5] != sum);
}
void showDiceA()
{
	/* Show computer's dice set */

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			drawDice(i + 1, 0);
		}
		printf("\n");
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			drawDice(i + 1, randDice[j + 3]);
		}
		printf("\n");
	}
}
void showDiceB(int n)
{
	/* Show user's dice set */

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < n; j++) {
			drawDice(i + 1, randDice[j]);
		}
		printf("\n");
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < n; j++) {
			drawDice(i + 1, randDice[j + 3]);
		}
		printf("\n");
	}
}
int stringParser(char* str)
{
	/* Get string input for betting amount and change it into integer */

	betting = 0;

	if (*str == '-' && *(str + 1) != 0) {
		for (int i = 1; *(str + i + 1) != 0; i++) {
			if (*(str + i) >= '0' && *(str + i) <= '9') {
				betting *= 10;
				betting += *(str + i) - '0';
			}
			else return 1;
		}
		betting *= -1;
		return 0;
	}
	else {
		for (int i = 0; *(str + i + 1) != 0; i++) {
			if (*(str + i) >= '0' && *(str + i) <= '9') {
				betting *= 10;
				betting += *(str + i) - '0';
			}
			else return 1;
		}
		return 0;
	}

	return 1;
}
void showMenu()
{
	/* Show initial menu */

	printf("1. My State\n");
	printf("2. Dice Rolling Game\n");
	printf("3. End\n\n");
	printf("Enter your choice: ");
}
void showState()
{
	/* Show current user state */

	printf("Current cash: %d\n", cash);
	printf("Wins: %d\n", winTimes);
	printf("Loses: %d\n\n", loseTimes);
	printf("Press any key to go main menu...\n");
}
int goGame()
{
	/* Prepare a game */

	// Bankrupt detection
	if (cash <= 0) {
		printf("Current cash: 0\n");
		printf("You have no cash. You will be moved to main menu.");
		Sleep(2500);

		return 0;
	}

	// Make computer's dice set
	int sum = rollDiceA();

	// Get betting
	printf("Current cash: %d\n", cash);
	printf("Sum of computer's dices: %d\n", sum);
	printf("Input your betting: ");

	while (1) {
		// Get betting as string input
		char betArray[500];
		fgets(betArray, sizeof(betArray), stdin);

		int validTest = stringParser(betArray);
		if (validTest != 0) {
			// Character that is not a number is included
			printf("\nWrong Input.\n");
			printf("Input your betting again: ");
		}
		else if (betting <= 0) {
			// Minus betting occured
			printf("\nYou cannot bet less than zero cash.\n");
			printf("Input your betting again: ");
		}
		else if (cash >= betting) {
			cash -= betting;
			break;
		}
		else {
			// Over-betting occured
			printf("\nYou cannot bet more than your cash.\n");
			printf("Input your betting again: ");
		}
	}

	// Return the sum of computer's dices
	return sum;
}
int endGame()
{
	/* Show messages after a game */

	printf("1. Retry\n");
	printf("2. Back to main menu\n\n");
	printf("Enter your choice: ");

	while (1) {
		char selection = getch();
		switch (selection) {
			case '1': {
				system("cls");
				return 1;
			}
			case '2': {
				system("cls");
				return 0;
			}
			default: {
				printf("\n\nWrong input.\n");
				printf("Press proper key again: ");
				break;
			}
		}
	}

	return 0;
}
int resultGame(int gameType)
{
	/* Show result of the game */

	int cnt = 0;

	// Stage 1
	printf("Stage 1\n");
	showDiceB(1);

	if (randDice[0] >= randDice[3]) {
		printf("Computer Wins");
		cnt++;
	}
	else printf("User Wins");

	Sleep(2000);
	system("cls");

	// Stage 2
	printf("Stage 2\n");
	showDiceB(2);

	if (randDice[1] >= randDice[4]) {
		printf("Computer Wins");
		cnt++;
	}
	else printf("User Wins");

	Sleep(2000);
	system("cls");

	// Stage 3
	printf("Stage 3\n");
	showDiceB(3);

	if (randDice[2] >= randDice[5]) {
		printf("Computer Wins");
		cnt++;
	}
	else printf("User Wins");

	// Winner check
	if (cnt >= 2) {
		printf("\n\nFinal Winner: Computer\n\n");
		loseTimes++;
	}
	else {
		printf("\n\nFinal Winner: User\n\n");

		// Check if there was user surrender
		if (gameType) {
			cash += betting * 2;
			winTimes++;
		}
		else {
			printf("However, the winner is computer because you surrendered.\n\n");
			loseTimes++;
		}
	}

	return endGame();
}
void doGame()
{
	/* Show computer's dices and start a game */

	int sum = goGame();
	if (sum == 0) return;

	system("cls");
	while (1) {
		printf("Sum of computer's dices: %d\n", sum);
		rollDiceB(sum);
		showDiceA();

		printf("Press ESC to start a game\n");
		printf("Press S to surrender\n");
		printf("Press any other key to roll the dices again\n\n");
		printf("Enter your choice: ");

		char selection = getch();
		switch (selection) {
			case 27: {
				// User agreement
				system("cls");
				if (resultGame(1)) {
					if (goGame() == 0) return;
					system("cls");

					break;
				}
				else return;
			}
			case 's': {
				// User surrender
				cash -= 5000;
				system("cls");

				if (resultGame(0)) {
					if (goGame() == 0) return;
					system("cls");

					break;
				}
				else return;
			}
			default: {
				// Roll dice again
				system("cls");

				break;
			}
		}
	}

	return;
}
int main()
{
	showMenu();

	while (1) {
		char selection = getch();
		switch (selection) {
			case '1': {
				// Show user state
				system("cls");
				showState();
				
				getch();
				system("cls");
				showMenu();

				break;
			}
			case '2': {
				// Start game
				system("cls");
				doGame();

				system("cls");
				showMenu();

				break;
			}
			case '3': {
				// Terminate
				system("cls");
				printf("Good bye.\n\n");

				return 0;
			}
			default: {
				// Undefined keyboard input
				printf("\n\nWrong input.\n");
				printf("Press proper key again: ");

				break;
			}
		}
	}

	return 0;
}