#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#pragma warning(disable:4996)

/*
	Project Name     : Snake Game Project
	Author           : CHIEW HONG KUANG, FOO YEE SOON, LOH KANG SHENG
	Source code File : snakesAndLadders.c
	Date Completed   : 09 October 2020
*/

//Snake Game Project
//
//Main Menu(HK)
//Display Guide of the game(HK)
//How many user(min = 2, max 4) (HK)
//Display the sets of snake and ladder(HK)
//Game Start(LKS)
//Display Chart(LKS)
//Roll Dice(HK)
//When hit snake(YS)
//When hit ladder(YS)
//If user 1 hit user 2 or user 2 hit user 1 (YS)
//When user roll the dice but hit over the 100 (YS)
//Display Winner(HK)

void logo(); // Display Logo
int gameMenu(); // Display a Game Menu
char randomDif(); // Randomly select E/N/H if difficulty = R
char snakeMenu(); //Display the difficulty menu of snake
char ladderMenu(); //Display the difficulty menu of ladder
void difficulty(char*, char*); // Allow player to select the difficulty of game
void playersNameValidation(int i, char* playerName1[31], char* playerName2[31]); // Validate player name and reject the same player name
int createPlayer(char* playerName[4][31]); // Create and return number of players
void displayBoard(int* playerStep, int players, char* playerName[4][31]);// Display the board 
int dice(); // Decide how many step should players walk
int balanceProbOf6(); // Balancing of probability for roll to 6 point
int snakeE(char playerName[31], int playerStep); // Snake easy
int snakeN(char playerName[31], int playerStep); // Sanke normal
int snakeH(char playerName[31], int playerStep); // Snake hard
int snake(char snkSetChoice, char playerName[31], int playerStep); // When player step on the snake
int ladderE(char playerName[31], int playerStep); // Ladder easy
int ladderN(char playerName[31], int playerStep); // Ladder normal
int ladderH(char playerName[31], int playerStep); // Ladder hard
int ladder(char ladSetChoice, char playerName[31], int playerStep); // When player step on the ladder
int over100Check(char playerName[31], int currentPlayerStep); // Check if the user is over 100 steps
int game(int players, char* playerName[4][31], char snakeSetChoice, char ladSetChoice); // Game start and return who is the winner
void validateWinner(int winner, char* playerName[4][31]); // Validate the winner if someone step on the finish point(100)
void userGuide(); // User Guide
void ending(); // Display ending

int main()
{
	int menuChoice;
	char confirmExit;
	char* snkSetChoice;
	char* ladSetChoice;
	int players;
	int playerName[4][31];
	int winner;

	do
	{
		logo(); // Display logo
		menuChoice = gameMenu(); // Recieve user choice for main menu

		while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3) // Loop for validate user choice
		{
			printf("\n\n Oops! Looks like you press a wrong button! Please try again!\n\n");

			logo();
			menuChoice = gameMenu();
		}

		switch (menuChoice) // Process user choice
		{
		case 1: // Game Start
			difficulty(&snkSetChoice, &ladSetChoice);
			players = createPlayer(&playerName); // Recieve number od players
			winner = game(players, &playerName, snkSetChoice, ladSetChoice);
			validateWinner(winner, &playerName);
			break;
		case 2: // User Guide
			userGuide(); // Display user guide
			break;
		case 3: // Exit
			break;
		}

		printf("\n End the game? (Y/N) > "); // Prompt user for end the game
		rewind(stdin);
		scanf("%c", &confirmExit);

		system("cls"); // Clear the screen
	} while (confirmExit != 'Y' && confirmExit != 'y'); // Return true while user enter any key except 'Y' and 'y'

	ending(); // Display ending

	system("pause"); // Stop the program
}

void logo() // Function for display logo
{
	printf("                                                               \n");
	printf(" ++=========================================================++ \n");
	printf(" ||                                                         || \n");
	printf(" ||     =============++                 // //      //   //  || \n");
	printf(" ||    ==           ^  ]~              // //      //   //   || \n");
	printf(" ||   ===       =====++               // //######// 0 //    || \n");
	printf(" ||   ===      ===                   // //      //   //     || \n");
	printf(" ||    ===      ===                 // //      //   //      || \n");
	printf(" ||      ===      ===              // //######// 0 //       || \n");
	printf(" ||        ===      ===           // //      //   //        || \n");
	printf(" ||         ===      ===         // //      //   //         || \n");
	printf(" ||    <<=====       ===        // //######// 0 //          || \n");
	printf(" ||  <<              ==        // //      //   //           || \n");
	printf(" ||    <<=============        // //      //   //            || \n");
	printf(" ||                                                         || \n");
	printf(" ++=========================================================++ \n");
	printf("    Hello! Glad you to use FENRIR Snakes and Ladders Game!!    \n");
}

int gameMenu() // Function for display main menu
{
	int menuChoice;

	printf("                                                               \n");
	printf("            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^           \n");
	printf("            ^^   FENRIR Snakes and Ladders Game   ^^           \n");
	printf("            ^^           1) Game Start            ^^           \n");
	printf("            ^^           2) User Guide            ^^           \n");
	printf("            ^^           3)    Exit               ^^           \n");
	printf("            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^           \n");
	printf(" Press 1 to start the game > ");
	rewind(stdin);
	scanf("%d", &menuChoice);

	system("cls"); // Clear the screen

	return menuChoice; // Return user choice for main menu
}

char randomDif() // Function random choose difficulty if player enter R
{
	char setChoice = 'R';
	int randNum = rand() % 3 + 1;

	switch (randNum)
	{
	case 1:
		setChoice = 'E';
		break;
	case 2:
		setChoice = 'N';
		break;
	case 3:
		setChoice = 'H';
		break;
	}

	printf("\n\t Random choice > %c\n\n", setChoice);
	return setChoice;
}

char snakeMenu()
{
	char snkSetChoice;

	printf(" Snake Difficulty\n");
	printf(" ================\n");
	printf(" E - Easy\n");
	printf(" N - Normal\n");
	printf(" H - Hard\n");
	printf(" R - Random\n");
	printf(" Please select the difficulty of snake > ");
	rewind(stdin);
	scanf("%c", &snkSetChoice);

	snkSetChoice = toupper(snkSetChoice);

	if (snkSetChoice == 'R')
	{
		snkSetChoice = randomDif();
	}

	return snkSetChoice;
}

char ladderMenu()
{
	char ladSetChoice;

	printf(" Ladder Difficulty\n");
	printf(" ================\n");
	printf(" E - Easy\n");
	printf(" N - Normal\n");
	printf(" H - Hard\n");
	printf(" R - Random\n");
	printf(" Please select the difficulty of ladder > ");
	rewind(stdin);
	scanf("%c", &ladSetChoice);

	ladSetChoice = toupper(ladSetChoice);

	if (ladSetChoice == 'R')
	{
		ladSetChoice = randomDif();
	}

	return ladSetChoice;
}

void difficulty(char* snkSetChoice, char* ladSetChoice)
{
	char confirmDif;

	do
	{
		srand(time(NULL));

		*snkSetChoice = snakeMenu();

		while (*snkSetChoice != 'E' && *snkSetChoice != 'N' && *snkSetChoice != 'H' && *snkSetChoice != 'R')
		{
			printf("\n\n Oops! Looks like you press a wrong button! Please try again!\n\n");

			srand(time(NULL));

			*snkSetChoice = snakeMenu();
		}

		srand(time(NULL));

		*ladSetChoice = ladderMenu();

		while (*ladSetChoice != 'E' && *ladSetChoice != 'N' && *ladSetChoice != 'H' && *ladSetChoice != 'R')
		{
			printf("\n\n Oops! Looks like you press a wrong button! Please try again!\n\n");

			srand(time(NULL));

			*ladSetChoice = ladderMenu();
		}

		printf("\n Sure to choice %c for snake and %c for ladder? (Y/N) > ", *snkSetChoice, *ladSetChoice);
		rewind(stdin);
		scanf("%c", &confirmDif);

		system("cls"); // Clear the screen
	} while (confirmDif != 'Y' && confirmDif != 'y'); // Return true while player enter any key except 'Y' and 'y'
}

void playersNameValidation(int i, char* playerName1[31], char* playerName2[31]) // Function for validate player name
{
	int result;

	result = strcmp(playerName1, playerName2); // Compare both player name

	while (result == 0) // Loop while both player name are same and prompt user to rename
	{
		printf("\n This Player Name already exist! Please use another name!\n\n");

		printf("\t P%d: ", i + 1);
		rewind(stdin);
		scanf("%[^\n]", playerName2);

		result = strcmp(playerName1, playerName2);
	}
}

int createPlayer(char* playerName[4][31]) // Function for create players
{
	int players;
	int i;
	int validateCount = 1;
	char startChoice;

	do
	{
		printf("\n Please enter how many players want to play the game (MAX 4P) > "); // Allow user to enter number of players
		rewind(stdin);
		scanf("%d", &players);

		while (players < 2 || players > 4) // Loop for validate number of players
		{
			if (players < 2) // Situation if number of players less than 2
			{
				printf("\n Oh man! You can't really play this game with less than 2 person!");
				printf("\n Go to find some friends and I'll wait for you.\n");
			}
			else if (players > 4) // Situation if number of players more than 4
			{
				printf("\n Sorry @^@, I can't handle too many people!");
				printf("\n The players allowed are maximum of 4 people only!\n");
			}

			printf("\n Please enter how many players want to play the game (MAX 4P) > ");
			rewind(stdin);
			scanf("%d", &players);
		}

		printf("\n Please enter a name for each player: \n"); // Allow user to create player name for each player

		for (i = 0; i < players; i++)
		{
			printf("\t P%d: ", i + 1);
			rewind(stdin);
			scanf("%[^\n]", playerName + i);

			switch (i) // Validate player name and reject the same player name
			{
			case 1:
				playersNameValidation(i, &playerName[0], &playerName[1]);
				break;
			case 2:
				do
				{
					playersNameValidation(i, &playerName[0], &playerName[2]);
					playersNameValidation(i, &playerName[1], &playerName[2]);
					validateCount++;
				} while (validateCount <= 5); // Validate at least 5 times
				break;
			case 3:
				do
				{
					playersNameValidation(i, &playerName[0], &playerName[3]);
					playersNameValidation(i, &playerName[1], &playerName[3]);
					playersNameValidation(i, &playerName[2], &playerName[3]);
					validateCount++;
				} while (validateCount <= 5); // Validate at least 5 times
				break;
			}
		}

		printf("\n Are you ready to start the game? (Y/N) > "); // Prompt player to really start the game
		rewind(stdin);
		scanf("%c", &startChoice);

		system("cls"); // Clear the screen
	} while (startChoice != 'Y' && startChoice != 'y'); // Return true while player enter any key except 'Y' and 'y'

	return players; // Return number of players
}

void displayBoard(int* playerStep, int players, char* playerName[4][31])
{
	int i, j, num = 100; // Declare

	system("cls"); // Clean the screen

	printf(" ++============================++\n");

	for (i = 0; i < players; i++)
	{
		printf(" || %-15.15s (P%d) > %3d ||\n", playerName[i], i + 1, playerStep[i]);
	}

	printf(" ++============================++\n\n");

	for (i = 10; i > 0; i--) // Loop to display the board
	{
		if (num / 10 % 2 == 0 || num >= 0 && num <= 10)
		{
			for (j = 1; j <= 10; j++)
			{
				if (*(playerStep) == num || *(playerStep + 1) == num || *(playerStep + 2) == num || *(playerStep + 3) == num)
				{
					if (*(playerStep) == num)
					{
						printf("$P1$");
					}
					else if (*(playerStep + 1) == num)
					{
						printf("$P2$");
					}
					else if (*(playerStep + 2) == num)
					{
						printf("$P3$");
					}
					else if (*(playerStep + 3) == num)
					{
						printf("$P4$");
					}
				}
				else
				{
					printf("%3d", num);
				}

				--num;
			}

			printf("\n");
		}
		else
		{
			num -= 10;

			for (j = 1; j <= 10; j++)
			{
				if (*(playerStep) == num + j || *(playerStep + 1) == num + j || *(playerStep + 2) == num + j || *(playerStep + 3) == num + j)
				{
					if (*(playerStep) == num + j)
					{
						printf("$P1$");
					}
					else if (*(playerStep + 1) == num + j)
					{
						printf("$P2$");
					}
					else if (*(playerStep + 2) == num + j)
					{
						printf("$P3$");
					}
					else if (*(playerStep + 3) == num + j)
					{
						printf("$P4$");
					}
				}
				else
				{
					printf("%3d", num + j);
				}
			}

			printf("\n");
		}
	}
}

int dice() // Function for roll the dice
{
	int point;
	int maxPoint = 6;
	int minPoint = 1;

	printf("\n It's time to roll the dice! Press enter key to continue > "); // Prompt player for press enter key to roll the dice
	rewind(stdin);
	getchar();

	point = rand() % ((maxPoint + 1) - minPoint) + minPoint; // Generate a random point between 1 and 6

	printf("\t The point is %d!\n", point); // Display the point that been generated

	return point; // Return the point
}

int balanceProbOf6() // Function for balancing the probability to get 6 points when rolling the dice
{
	int dice6Count = 0;
	int maxDice6Count = 3;
	int point;
	int steps;
	int sumOfSteps = 0;
	bool strike;

	do
	{
		srand(time(NULL)); // Generate a seed for random number in each loop

		point = dice();
		steps = point;
		sumOfSteps = sumOfSteps + steps;

		if (point == 6)
		{
			dice6Count++;

			if (dice6Count == 1)
			{
				printf(" Nice! You have another chance to roll the dice!\n");
			}
			else if (dice6Count == 2)
			{
				printf(" Great! I think you are the luckiest guy in this game!\n");
				printf(" Try to roll 6 points once again to indicate whether you have the chance to continue the strike.\n");
			}
			else if (dice6Count == 3)
			{
				printf(" Excellent! Seems like you are so lucky! Go ahead to surpass the other players!\n");

				sumOfSteps = sumOfSteps - steps;
			}

			strike = true;
		}
		else
		{
			if (dice6Count == 2)
			{
				printf(" Oh! You lost the 3rd chance to roll the dice!\n");

				sumOfSteps = sumOfSteps - steps;
			}

			strike = false;
		}
	} while (strike == true && dice6Count <= maxDice6Count); // Loop for roll the dice if the player gets 6 points continuously (maximum 3 times)

	if (dice6Count <= 1)
	{
		printf("\n Here you go! Your points is %d!", sumOfSteps); // Display total points
	}
	else
	{
		printf("\n Here you go! Your total points is %d!", sumOfSteps); // Display total points
	}

	rewind(stdin);
	getchar();

	system("cls"); // Clear the screen

	return sumOfSteps;
}

struct snkSetE // Snake easy
{
	int snkHead[6];
	int snkTail[6];
} snkE;

struct snkSetN // Snake normal
{
	int snkHead[6];
	int snkTail[6];
} snkN;

struct snkSetH //Snake hard
{
	int snkHead[6];
	int snkTail[6];
} snkH;

int snakeE(char playerName[31], int playerStep) // Function for step on easy snake
{
	int tempPlayerStep = playerStep;
	int i;
	struct snkSetE snkE = { { 11, 21, 37, 59, 72, 95 }, { 4, 16, 25, 50, 64, 89 } };
	int snkHead[6];
	int snkTail[6];

	for (i = 0; i < 6; i++) // Loop for assign snake head and snake tail form struct to varaibles
	{
		snkHead[i] = snkE.snkHead[i];
		snkTail[i] = snkE.snkTail[i];
	}

	for (i = 0; i < 6; i++) // Loop for checking whether player hit the snake or not
	{
		if (playerStep == snkHead[i])
		{
			printf(" Oh no! You hit a snake head!\n");

			playerStep = snkTail[i];

			printf(" %s from %d drop to %d!\n", playerName, tempPlayerStep, playerStep);

			rewind(stdin);
			getchar();
		}
	}

	return playerStep; // Return player current step
}

int snakeN(char playerName[31], int playerStep) // Function for step on normal snake
{
	int tempPlayerStep = playerStep;
	int i;
	struct snkSetN snkN = { { 14, 27, 48, 65, 84, 98 }, { 5, 19, 32, 55, 78, 76 } };
	int snkHead[6];
	int snkTail[6];

	for (i = 0; i < 6; i++) // Loop for assign snake head and snake tail form struct to varaibles
	{
		snkHead[i] = snkN.snkHead[i];
		snkTail[i] = snkN.snkTail[i];
	}

	for (i = 0; i < 6; i++) // Loop for checking whether player hit the snake or not
	{
		if (playerStep == snkHead[i])
		{
			printf(" Oh no! You hit a snake head!\n");

			playerStep = snkTail[i];

			printf(" %s from %d drop to %d!\n", playerName, tempPlayerStep, playerStep);

			rewind(stdin);
			getchar();
		}
	}

	return playerStep; // Return player current step
}

int snakeH(char playerName[31], int playerStep) // Function for step on hard snake
{
	int tempPlayerStep = playerStep;
	int i;
	struct snkSetH snkH = { { 22, 47, 68, 71, 87, 99 }, { 8, 29, 40, 53, 60, 56 } };
	int snkHead[6];
	int snkTail[6];

	for (i = 0; i < 6; i++) // Loop for assign snake head and snake tail form struct to varaibles
	{
		snkHead[i] = snkH.snkHead[i];
		snkTail[i] = snkH.snkTail[i];
	}

	for (i = 0; i < 6; i++) // Loop for checking whether player hit the snake or not
	{
		if (playerStep == snkHead[i])
		{
			printf(" Oh no! You hit a snake head!\n");

			playerStep = snkTail[i];

			printf(" %s from %d drop to %d!\n", playerName, tempPlayerStep, playerStep);

			rewind(stdin);
			getchar();
		}
	}

	return playerStep; // Return player current step
}

int snake(char snkSetChoice, char playerName[31], int playerStep) // Function for step on snake
{
	switch (snkSetChoice)
	{
	case 'E': // If player choosed easy snake
		playerStep = snakeE(playerName, playerStep);
		break;
	case 'N': // If player choosed normal snake
		playerStep = snakeN(playerName, playerStep);
		break;
	case 'H': // If player choosed hard snake
		playerStep = snakeH(playerName, playerStep);
		break;
	}

	return playerStep; // Return player current step
}

struct ladSetE // Ladder easy
{
	int ladHead[6];
	int ladTail[6];
} ladE;

struct ladSetN // Ladder normal
{
	int ladHead[6];
	int ladTail[6];
} ladN;

struct ladSetH // Ladder hard
{
	int ladHead[6];
	int ladTail[6];
} ladH;

int ladderE(char playerName[31], int playerStep) // Function for step on easy ladder
{
	int tempPlayerStep = playerStep;
	int i;
	struct ladSetE ladE = { { 24, 31, 54, 63, 86, 97 }, { 3, 12, 36, 45, 66, 70 } };
	int ladHead[6];
	int ladTail[6];

	for (i = 0; i < 6; i++) // Loop for assign ladder head and ladder tail form struct to varaibles
	{
		ladHead[i] = ladE.ladHead[i];
		ladTail[i] = ladE.ladTail[i];
	}

	for (i = 0; i < 6; i++) // Loop for checking whether player hit the ladder or not
	{
		if (playerStep == ladTail[i])
		{
			printf(" Yeah! You hit a ladder!\n");

			playerStep = ladHead[i];

			printf(" %s from %d climb up %d!\n", playerName, tempPlayerStep, playerStep);

			rewind(stdin);
			getchar();
		}
	}

	return playerStep; // Return player current step
}

int ladderN(char playerName[31], int playerStep) // Function for step on normal ladder
{
	int tempPlayerStep = playerStep;
	int i;
	struct ladSetN ladN = { { 15, 33, 57, 69, 90, 96 }, { 7, 28, 41, 52, 75, 88 } };
	int ladHead[6];
	int ladTail[6];

	for (i = 0; i < 6; i++) // Loop for assign ladder head and ladder tail form struct to varaibles
	{
		ladHead[i] = ladN.ladHead[i];
		ladTail[i] = ladN.ladTail[i];
	}

	for (i = 0; i < 6; i++) // Loop for checking whether player hit the ladder or not
	{
		if (playerStep == ladTail[i])
		{
			printf(" Yeah! You hit a ladder!\n");

			playerStep = ladHead[i];

			printf(" %s from %d climb up %d!\n", playerName, tempPlayerStep, playerStep);

			rewind(stdin);
			getchar();
		}
	}

	return playerStep; // Return player current step
}

int ladderH(char playerName[31], int playerStep) // Function for step on hard ladder
{
	int tempPlayerStep = playerStep;
	int i;
	struct ladSetH ladH = { { 13, 34, 51, 78, 83, 91 }, { 9, 26, 46, 67, 77, 85 } };
	int ladHead[6];
	int ladTail[6];

	for (i = 0; i < 6; i++) // Loop for assign ladder head and ladder tail form struct to varaibles
	{
		ladHead[i] = ladH.ladHead[i];
		ladTail[i] = ladH.ladTail[i];
	}

	for (i = 0; i < 6; i++) // Loop for checking whether player hit the ladder or not
	{
		if (playerStep == ladTail[i])
		{
			printf(" Yeah! You hit a ladder!\n");

			playerStep = ladHead[i];

			printf(" %s from %d climb up %d!\n", playerName, tempPlayerStep, playerStep);

			rewind(stdin);
			getchar();
		}
	}

	return playerStep; // Return player current step
}

int ladder(char ladSetChoice, char playerName[31], int playerStep) // Function for step on snake
{
	switch (ladSetChoice)
	{
	case 'E': // If player choosed easy ladder
		playerStep = ladderE(playerName, playerStep);
		break;
	case 'N': // If player ch&oosed normal ladder
		playerStep = ladderN(playerName, playerStep);
		break;
	case 'H': // If player ch&oosed hard ladder
		playerStep = ladderH(playerName, playerStep);
		break;
	}

	return playerStep; // Return player current step
}

int over100Check(char playerName[31], int currentPlayerStep)
{
	int max = 100, over, temp;

	if (currentPlayerStep > max)
	{
		temp = currentPlayerStep;
		over = currentPlayerStep - max;
		currentPlayerStep = currentPlayerStep - over * 2;

		printf(" %s have reached %d and it is over 100, you will go back to %d", playerName, temp, currentPlayerStep);

		rewind(stdin);
		getchar();
	}

	return currentPlayerStep;
}

int game(int players, char* playerName[4][31], char snakeSetChoice, char ladSetChoice)
{
	// Declare
	int i, j, num = 100;
	bool gameStatus = true;
	int playerStep[4] = { 0 };
	int winner = 0;

	displayBoard(playerStep, players, playerName); // Display Board Game

	//The game loop
	while (gameStatus)
	{
		for (i = 0; i < players; i++)
		{
			playerStep[i] += balanceProbOf6();	// Adding player step with the dice
			playerStep[i] = snake(snakeSetChoice, playerName[i], playerStep[i]); // Check if user hit a snake
			playerStep[i] = ladder(ladSetChoice, playerName[i], playerStep[i]); // Check if user hit a ladder
			playerStep[i] = over100Check(&playerName[i], playerStep[i]); // When player hit over 100

			for (j = players - 1; j >= 0; j--) // When player hit player
			{
				if (i == j)
				{
					continue;
				}

				if (playerStep[i] == playerStep[j])
				{

					playerStep[j] = 0;

					printf(" Player %d has hit player %d\n", i+1, j+1);
					printf(" Player %d has to go back to starting point :)", j+1);
					rewind(stdin);
					getchar();

					if (playerStep[j] == 0)
					{
						break;
					}
				}
			}
			//Check winner
			if (playerStep[0] == 100 || playerStep[1] == 100 || playerStep[2] == 100 || playerStep[3] == 100)//If there is a winner 
			{
				gameStatus = false;
				break;
			}

			displayBoard(playerStep, players, playerName);//Update the Board
		}
	}

	for (i = 0; i < players; i++) 	//Find the winner
	{
		if (playerStep[i] == 100)
		{
			winner = i;
		}
	}

	return winner;
}

void validateWinner(int winner, char* playerName[4][31])
{
	system("cls");

	printf("\n\t Deng DengDengDeng~ DengDeng~ Deng DengDeng~\n\n");
	printf(" Congratulation! %s is the winner!\n", playerName[winner]);
	printf(" You are the SNAKE KING!\n");
}

void userGuide()
{
	printf("                                                                                 \n");
	printf(" +-----------------------------------------------------------------------------+ \n");
	printf(" | 1.  Enter the game                                                          | \n");
	printf(" |     1.1 Enter the difficulty of snake and ladder (Easy/Normal/Hard/Random). | \n");
	printf(" |     1.2 Enter the number of players (between 2 people to 4 people).         | \n");
	printf(" |     1.3 Enter a name for each player (all player names must be different).  | \n");
	printf(" |                                                                             | \n");
	printf(" | 2.  Start the game                                                          | \n");
	printf(" |     2.1 At the beginning, all players are on the 0, which is the starting   | \n");
	printf(" |         point of the game.                                                  | \n");
	printf(" |     2.2 Each player will roll the dice on his turn and moving on the        | \n");
	printf(" |         dashboard based on the point he gets.                               | \n");
	printf(" |                                                                             | \n");
	printf(" | 3.  Dice rules                                                              | \n");
	printf(" |     3.1 In generally, each player can only roll the dice once on his turn.  | \n");
	printf(" |     3.2 But when the player rolls to 6 points, he has another chance to     | \n");
	printf(" |         roll the dice.                                                      | \n");
	printf(" |     3.3 This situation will continue until he rolls a point that other than | \n");
	printf(" |         6 or rolls 3 times 6 points.                                        | \n");
	printf(" |                                                                             | \n");
	printf(" | 4.  Events                                                                  | \n");
	printf(" |     4.1 Snakes                                                              | \n");
	printf(" |         4.1.1 When the player hits on a snake head, he will get a penalty   | \n");
	printf(" |               and drop to the snake tail.                                   | \n");
	printf(" |         4.1.2 There are totally 6 invisible snakes distributed on the       | \n");
	printf(" |               dashboard.                                                    | \n");
	printf(" |     4.2 Ladders                                                             | \n");
	printf(" |         4.2.1 When the player hits on a ladder, he can climb up the ladder. | \n");
	printf(" |         4.2.2 There are totally 6 invisible ladders distributed on the      | \n");
	printf(" |               dashboard.                                                    | \n");
	printf(" |     4.1 Overlap                                                             | \n");
	printf(" |         4.1.1 When a player hits on another player, the previous player     | \n");
	printf(" |               on that space will be kicked back to starting point (0).      | \n");
	printf(" |         4.1.2 This situation also will happen when a player hit on another  | \n");
	printf(" |               player through drop form snake head to snake tail or climb up | \n");
	printf(" |               the ladder.                                                   | \n");
	printf(" |                                                                             | \n");
	printf(" | 5.  Condition                                                               | \n");
	printf(" |     5.1 When the player steps on the 100 accurately, then he wins.          | \n");
	printf(" |     5.2 It was not be counted if the player moves over 100.                 | \n");
	printf(" |         5.2.1 For example, when the player currently on 99, then he rolls   | \n");
	printf(" |               the dice and gets 4 points.                                   | \n");
	printf(" |         5.2.2 The player will not be considered as the winner and he needs  | \n");
	printf(" |               to take steps back based on the points he overflows.          | \n");
	printf(" |         5.2.3 In this example, the player has to take 3 steps back and      | \n");
	printf(" |               lastly he will end on 97.                                     | \n");
	printf(" |                                                                             | \n");
	printf(" | 6.  Winner                                                                  | \n");
	printf(" |     6.1 A player only be considered as the winner once he steps on 100      | \n");
	printf(" |         accurately.                                                         | \n");
	printf(" |     6.2 Only one winner will exist in each game.                            | \n");
	printf(" +-----------------------------------------------------------------------------+ \n");
	printf("                                                                                 \n");
}

void ending()  // Function for display ending
{
	printf("                                                               \n");
	printf("            Looks like it's time to say goodbye T_T            \n");
	printf("        Thank for using FENRIR Snakes and Ladders Game!        \n");
	printf("                      See you next time!!                      \n");
	printf("                                                               \n");
}