#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
int cash = 100000, betting = 0, winTimes = 0, loseTimes = 0;
int randDice[6];
void drawDice(int _i, int _number)
{
	switch (_i)
	{
		case 1:
			printf("¦£¦¡¦¡¦¡¦¤");
			break;
		case 2:
			switch (_number)
			{
				case 0:
					printf("¦¢      ¦¢");
					break;
				case 1:
				case 2:
					printf("¦¢      ¦¢");
					break;
				case 3:
					printf("¦¢    ¡Ü¦¢");
					break;
				case 4:
				case 5:
				case 6:
					printf("¦¢¡Ü  ¡Ü¦¢");
					break;
			}
			break;
		case 3:
			switch (_number)
			{
				case 0:
					printf("¦¢      ¦¢");
					break;
				case 1:
				case 3:
				case 5:
					printf("¦¢  ¡Ü  ¦¢");
					break;
				case 2:
				case 6:
					printf("¦¢¡Ü  ¡Ü¦¢");
					break;
				case 4:
					printf("¦¢      ¦¢");
					break;
			}
			break;
		case 4:
			switch (_number)
			{
				case 0:
					printf("¦¢      ¦¢");
					break;
				case 1:
				case 2:
					printf("¦¢      ¦¢");
					break;
				case 3:
					printf("¦¢¡Ü    ¦¢");
					break;
				case 4:
				case 5:
				case 6:
					printf("¦¢¡Ü  ¡Ü¦¢");
					break;
			}
			break;
		case 5:
			printf("¦¦¦¡¦¡¦¡¦¥");
			break;
	}
}
int rollDiceA()
{
	srand(time(NULL));
	randDice[0] = rand() % 6 + 1;
	randDice[1] = rand() % 6 + 1;
	randDice[2] = rand() % 6 + 1;
	return randDice[0] + randDice[1] + randDice[2];
}
void rollDiceB(int sum)
{
	do {
		randDice[3] = rand() % 6 + 1;
		randDice[4] = rand() % 6 + 1;
		randDice[5] = rand() % 6 + 1;
	} while (randDice[3] + randDice[4] + randDice[5] != sum);
}
void showDiceA()
{
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
	betting = 0;
	if (*str == '-' && *(str + 1) != 0) {
		for (int i = 1; *(str + i + 1) != 0; i++) {
			if (*(str + i) >= '0' && *(str + i) <= '9') {
				betting *= 10;
				betting += *(str + i) - '0';
			}
			else return 0;
		}
		betting *= -1;
		return 1;
	}
	for (int i = 0; *(str + i + 1) != 0; i++) {
		if (*(str + i) >= '0' && *(str + i) <= '9') {
			betting *= 10;
			betting += *(str + i) - '0';
		}
		else return 0;
	}
	return 1;
}
void showMenu()
{
	printf("1. My State\n");
	printf("2. Dice Rolling Game\n");
	printf("3. End\n\n");
	printf("Enter your choice: ");
}
void showState()
{
	printf("Current cash: %d\n", cash);
	printf("Wins: %d\n", winTimes);
	printf("Loses: %d\n\n", loseTimes);
	printf("Press any key to go main menu...\n");
}
int goGame()
{
	int sum = rollDiceA();
	if (cash <= 0) {
		printf("Current cash: 0\n");
		printf("You have no cash. You will be moved to main menu.");
		Sleep(2500);
		return 0;
	}
	printf("Current cash: %d\n", cash);
	printf("Sum of computer's dices: %d\n", sum);
	printf("Input your betting: ");
	while (1) {
		char betArray[500];
		fgets(betArray, sizeof(betArray), stdin);
		int validTest = stringParser(betArray);
		if (validTest == 0) {
			printf("\nWrong Input.\n");
			printf("Input your betting again: ");
		}
		else if (betting <= 0) {
			printf("\nYou cannot bet less than zero cash.\n");
			printf("Input your betting again: ");
		}
		else if (cash >= betting) {
			cash -= betting;
			break;
		}
		else {
			printf("\nYou cannot bet more than your cash.\n");
			printf("Input your betting again: ");
		}
	}
	return sum;
}
int endGame()
{
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
}
int resultGame(int gameType)
{
	int cnt = 0;
	printf("Stage 1\n");
	showDiceB(1);
	if (randDice[0] >= randDice[3]) {
		printf("Computer Wins");
		cnt++;
	}
	else printf("User Wins");
	Sleep(2000);
	system("cls");
	printf("Stage 2\n");
	showDiceB(2);
	if (randDice[1] >= randDice[4]) {
		printf("Computer Wins");
		cnt++;
	}
	else printf("User Wins");
	Sleep(2000);
	system("cls");
	printf("Stage 3\n");
	showDiceB(3);
	if (randDice[2] >= randDice[5]) {
		printf("Computer Wins");
		cnt++;
	}
	else printf("User Wins");
	if (cnt >= 2) {
		printf("\n\nFinal Winner: Computer\n\n");
		loseTimes++;
	}
	else if (gameType) {
		printf("\n\nFinal Winner: User\n\n");
		cash += betting * 2;
		winTimes++;
	}
	else {
		printf("\n\nFinal Winner: User\n\n");
		printf("However, the winner is computer because you surrendered.\n\n");
		loseTimes++;
	}
	return endGame();
}
void doGame()
{
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
				system("cls");
				if (resultGame(1)) {
					int sum = goGame();
					if (sum == 0) return;
					system("cls");
					break;
				}
				else return;
			}
			case 's': {
				cash -= 5000;
				system("cls");
				if (resultGame(0)) {
					int sum = goGame();
					if (sum == 0) return;
					system("cls");
					break;
				}
				else return;
			}
			default: {
				system("cls");
				break;
			}
		}
	}
}
int main()
{
	showMenu();
	while (1) {
		char selection = getch();
		switch (selection) {
			case '1': {
				system("cls");
				showState();
				getch();
				system("cls");
				showMenu();
				break;
			}
			case '2': {
				system("cls");
				doGame();
				system("cls");
				showMenu();
				break;
			}
			case '3': {
				system("cls");
				printf("Good bye.\n\n");
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