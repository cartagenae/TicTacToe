#include <cstdio>				//c syntax
#include <iostream>				//c++ syntax
#include <string.h>				//string manipulation
#include <cctype>				//toupper function
#include <time.h>				//seed random number
#include <cstdlib>				//random generator
//#include <conio.h>				//getche function
//#include "getche.h"				//Included because I'm working on this project from a Linux machine
#define LETTER 0
#define NUMBER 1
#define SIZE 3
/**********************************************\
| Find a way to work with the Getche function. |
\**********************************************/
using namespace std;
typedef union {
	char letter;
	int number;
} coordinateUnion;
typedef struct {
	coordinateUnion dataType;
	int tag;
} jointStructure;
typedef struct {
	jointStructure x;
	jointStructure y;
} coordinateStructure;
//Determine the winner of the game-------------------------
int DetermineWinner(int playerCoordinates[][SIZE],
	bool &isGameOver);
//Display the grid, regardless of its size-----------------
void DisplayGrid(int playerCoordinates[][SIZE]);
//Prompt user to enter coordinate for the play-------------
void EnterCoordinates(char *userName,
	int playerCoordinates[][SIZE], int lastCoordinate[]);
//Computer generates a random coordinate-------------------
void GenerateComputerCoordinates(int playerCoordinates[][SIZE]);
//Initialize each value within array to zero for a new game
void InitializeCoordinates(int playerCoordinates[][SIZE],
	int arraySize);
//Prompts user if he or she wants to contnue playing-------
bool PromptUserContinue(int lastCoordinate[], char userName[],
	int winner);
//Prompt user to enter his or her name---------------------
void ScanName(char userName[]);
//main function--------------------------------------------
int main() {
	bool isContinue;												//-->Determines if user wants to continue.
	bool isGameOver;												//-->Determines if the game is over.
	int lastCoordinate[2];											//-->Used to display them when user wins or ties.
	int playerCoordinates[SIZE][SIZE];								//-->Player and Computer coordinates. Main Array.
	int playerSize = sizeof(playerCoordinates)/sizeof(int);			//-->Calculate size of playerCoordinates array.
	char userName[25];												//-->userName used in ScanName function.
	int winner = 0;													//-->Stores the winner. 1 = user; 2 = computer.
	printf("\n\n\t\tPlay some Tic Tac Toe\n\n\n");
	ScanName(userName);												//-->Prompt user for his or her name.
	do {
		isGameOver = false;
		InitializeCoordinates(playerCoordinates, playerSize);
		do {
			DisplayGrid(playerCoordinates);							//-->Displays the grid to the player.
			EnterCoordinates(userName, playerCoordinates,			//-->Prompts player to enter coordinates.
				lastCoordinate);
			winner =												//-->Function call to determine winner of game
				DetermineWinner(playerCoordinates, isGameOver);		//and store value in winner variable.
			if(!isGameOver) {										//-->If game not over, call following functions.
				GenerateComputerCoordinates(playerCoordinates);		//-->Generates random coordinates against player.
				winner =											//-->Function call to determine winner of game
					DetermineWinner(playerCoordinates, isGameOver);	//and store value in winner variable.
			}
		} while(!isGameOver);										//-->Iterate while the game is not over.
		DisplayGrid(playerCoordinates);								//-->Display the grid to the user one more time.
		isContinue =												//-->Prompt the user if he or she wants to cont.
			PromptUserContinue(lastCoordinate, userName, winner);
	} while(isContinue);											//-->Iterate as long as user wants to continue.
	printf("\t\tGAME OVER...\n\n");									//-->If not, print GAME OVER...
	return 0;
}
//Determine the winner of the game-------------------------
int DetermineWinner(int playerCoordinates[][SIZE],
	bool &isGameOver) {
	int computerColumnAccumulated = 0;								//-->Check for computer's columns.
	int computerLeftDiagonalAccumulated = 0;						//-->Check for computer's left diagonal line.
	int computerRightDiagonalAccumulated = 0;						//-->Check for computer's right diagonal line.
	int computerRowAccumulated = 0;									//-->Check for computer's rows.
	int emptyCoordinateCounter = 0;									//-->Count for any empty coordinates.
	int playerColumnAccumulated = 0;								//-->Check for user's columns.
	int playerLeftDiagonalAccumulated = 0;							//-->Check for user's left diagonal line.
	int playerRightDiagonalAccumulated = 0;							//-->Check for user's right diagonal line.
	int playerRowAccumulated = 0;									//-->Check for user's rows.
	int rightDiagonalColumn = SIZE - 1;								//-->Used to check for right diagonal line
	int winner = 0;
	for(int row = 0; row < SIZE; row++) {							//-->Iterate through columns to check if there
		for(int column = 0; column < SIZE; column++) {				//are any variables lined up in a column.
			if(playerCoordinates[row][column] == 1) {
				playerColumnAccumulated += 1;
			}
			else if(playerCoordinates[row][column] == 2) {
				computerColumnAccumulated += 2;
			}
		}
		if(playerColumnAccumulated == SIZE) {						//-->If columnAccumulated == SIZE declare user
			winner = 1;												//as the winner
			isGameOver = true;
			break;
		}
		else if(computerColumnAccumulated == (SIZE * 2)) {			//-->If columnAccumulated equals double the
			winner = 2;												//SIZE, declare computer as winner.
			isGameOver = true;
			break;
		}
		computerColumnAccumulated = 0;								//reset the computerColumnAccumulated and
		playerColumnAccumulated = 0;								//playerColumnAccumulated variables for reuse
	}																//on the next row iteration
	if(!isGameOver) {
		for(int column = 0; column < SIZE; column++) {				//-->Iterate through columns to check if there
			for(int row = 0; row < SIZE; row++) {					//are any variables lined up in a row.
				if(playerCoordinates[row][column] == 1) {
					playerRowAccumulated += 1;
				}
				else if(playerCoordinates[row][column] == 2) {
					computerRowAccumulated += 2;
				}
			}
			if(playerRowAccumulated == SIZE) {						//-->If playerRowAccumulated = SIZE, then
				winner = 1;											//winner = 1 for player 1.
				isGameOver = true;
				break;												//-->Break out of the for loop.
			}
			else if(computerRowAccumulated == (SIZE * 2)) {			//-->If computerRowAccumulated = SIZE * 2 then
				winner = 2;											//winner = 2 for player 2.
				isGameOver = true;
				break;												//-->Break out of the for loop.
			}
			computerRowAccumulated = 0;								//-->Reset computerRowAccumulated and
			playerRowAccumulated = 0;								//playerRowAccumulated everytime the focus
		}															//to a new column.
	}
	if(!isGameOver) {
		for(int subscript = 0; subscript < SIZE; subscript++) {		//-->Iterate through a subscript to check if
			if(playerCoordinates[subscript][subscript] == 1) {		//if any values are aligned diagonally from
				playerLeftDiagonalAccumulated += 1;					//left to right.
			}
			else if(playerCoordinates[subscript][subscript] == 2) {
				computerLeftDiagonalAccumulated += 2;
			}
		}
		if(playerLeftDiagonalAccumulated == SIZE) {					//-->If a diagonal line from left to right
			winner = 1;												//accumulating to 3 was found, then the winner
			isGameOver = true;										//is player 1 and the game is over.
		}
		else if(computerLeftDiagonalAccumulated == (SIZE * 2)) {	//-->If a diagonal line from left to right
			winner = 2;												//accumulating to 6 was found, then the winner
			isGameOver = true;										//is player 2 and the game is over.
		}
	}
	if(!isGameOver) {
		for(int row = 0; row < SIZE; row++) {						//-->Iterate through a subscript to check if
			if(playerCoordinates[row][rightDiagonalColumn] == 1) {	//any values are alijned diagonally from
				playerRightDiagonalAccumulated += 1;				//right to left.
			}
			else if(playerCoordinates[row][rightDiagonalColumn] == 2) {
				computerRightDiagonalAccumulated += 2;
			}
			rightDiagonalColumn--;
		}
		if(playerRightDiagonalAccumulated == SIZE) {				//-->If a diagonal line from right to left
			winner = 1;												//accumulating to 3 was found, then the winner
			isGameOver = true;										//is player 1 and the game is over.
		}
		else if(computerRightDiagonalAccumulated == (SIZE * 2)) {	//-->If a diagonal line from right to left
			winner = 2;												//accumulating to 6 was found, then the winner
			isGameOver = true;										//is player 2 and the game is over.
		}
	}
	for(int row = 0; row < SIZE; row++) {							//-->Finally if the game is not over and all
		for(int column = 0; column < SIZE; column++) {				//coordinates have been filled, then iterate
			if(playerCoordinates[row][column] == 0)					//through the playerCoordinates array for
				emptyCoordinateCounter++;							//empty coordinates and accumulate the empty
		}															//coordinates to determine a tie game.
	}
	if((computerLeftDiagonalAccumulated == 0 ||
		computerRightDiagonalAccumulated == 0 ||
		computerRowAccumulated == 0 ||
		playerLeftDiagonalAccumulated == 0 ||
		playerRightDiagonalAccumulated == 0 ||
		playerRowAccumulated == 0) &&
		emptyCoordinateCounter == 0 &&
		isGameOver == false) {
		winner = 0;													//-->When winner = 0, it's a tie game.
		isGameOver = true;
	}
	return winner;
}
//Display the grid, regardless of its size-----------------
void DisplayGrid(int playerCoordinates[][SIZE]) {
	char userCharacter[SIZE][SIZE];									//-->Array that holds characters x and y
	for(int row = 0; row < SIZE; row++) {							//according to playerCoordinates array.
		for(int column = 0; column < SIZE; column++) {				//-->Search through playerCoordinates array.
			if(playerCoordinates[row][column] == 1) {				//Append an x to the userCharacter array if the
				userCharacter[row][column] = 'X';					//playerCoordinate[row][column] = 1, y if the
			}														//playerCoordinate[row][column] = 2, and \0 if
			else if(playerCoordinates[row][column] == 2) {			//the playerCoordinate[row][column] = 0
				userCharacter[row][column] = 'O';
			}
			else {
				userCharacter[row][column] = '\0';
			}
		}
	}																//-->Print the tic tac toe grid...
	printf("\t ");
	for(int index = 0; index < SIZE; index++) {
		printf("%6d", index + 1);
	}
	printf("\n\t      ");
	for(int index = 0; index < SIZE; index++) {
		printf("%c     ", index + 65);
	}
	printf("\n");
	for(int row = 0; row < SIZE; row++) {
		printf("\t   ");
		for(int index = 0; index < SIZE; index++) {
			printf("+-----");
		}
		printf("+\n%9d%c ", row + 1, row + 65);
		for(int column = 0; column < SIZE; column++) {
			if(userCharacter[row][column] == '\0') {
				printf("|     ");
			}
			else {
				printf("|  %c  ",
					userCharacter[row][column]);
			}
		}
		printf("|\n");
	}
	printf("\t   ");
	for(int index = 0; index < SIZE; index++) {
		printf("+-----");
	}
	printf("+\n\n\n");
}
//Prompt user to enter coordinate for the play-------------
void EnterCoordinates(char *userName, int playerCoordinates[][SIZE],
	int lastCoordinate[]) {
	int inRangeCounter = 0;
	bool isDuplicate;
	bool isXInRange;
	bool isYInRange;
	bool isOutOfRange;
	coordinateStructure userCoordinate;
	char userInput[100];
	int x = SIZE + 1;												//-->x = size + 1 so that it's out of its range
	int y = SIZE + 1;												//-->y = size + 1 so that it's out of its range
	do {
		isOutOfRange = true;										//-->Initialize every boolean variable so that
		isDuplicate = false;										//iterations function properly
		isXInRange = false;
		isYInRange = false;
		do {
			printf("\t\tEnter coordinate %s: ", userName);			//-->Prompt the user to enter a coordinate
			gets(userInput);										//-->Takes the user's input
			fflush(stdin);											//-->Flush the buffer
		} while(strlen(userInput) != 2);							//-->Iterate while length of string is not two
		userCoordinate.x.tag = LETTER;
		userCoordinate.x.dataType.letter = userInput[0];			//-->Set x letter variable equal to userInput[0]
		userCoordinate.x.tag = NUMBER;
		if(userCoordinate.x.dataType.letter >= 49					//-->Make calculations if x variable is a number
			&& userCoordinate.x.dataType.letter <= 49 + (SIZE - 1)) {	//character according to the ascii table.
			userCoordinate.x.dataType.number =
				(int)(userCoordinate.x.dataType.letter) - 49;
			isXInRange = true;
			inRangeCounter++;
		}
		else if(userCoordinate.x.dataType.letter >= 65				//-->Make calculations if x variable is an upper
			&& userCoordinate.x.dataType.letter < 65 + SIZE) {		//case letter according to the ascii table.
			userCoordinate.x.dataType.number =
				(int)(userCoordinate.x.dataType.letter) - 65;
			isXInRange = true;
			inRangeCounter++;
		}
		else if(userCoordinate.x.dataType.letter >= 97				//-->Make calculations if x variable is a lower
			&& userCoordinate.x.dataType.letter < 97 + SIZE) {		//case letter according to the ascii table.
			userCoordinate.x.dataType.number =
				(int)(userCoordinate.x.dataType.letter) - 97;
			isXInRange = true;
			inRangeCounter++;
		}
		userCoordinate.y.tag = LETTER;
		userCoordinate.y.dataType.letter = userInput[1];			//-->Set y letter variable equal to userInput[1]
		userCoordinate.y.tag = NUMBER;
		if(userCoordinate.y.dataType.letter >= 49					//-->Make the calculations if y is a number 
			&& userCoordinate.y.dataType.letter <= 49 + (SIZE - 1)) {	//character in the ascii table.
			userCoordinate.y.dataType.number =
				(int)(userCoordinate.y.dataType.letter) - 49;
			isYInRange = true;
			inRangeCounter++;
		}
		else if(userCoordinate.y.dataType.letter >= 65				//-->Make calculations if y is an upper case
			&& userCoordinate.y.dataType.letter < 65 + SIZE) {		//letter according to the ascii table.
			userCoordinate.y.dataType.number =
				(int)(userCoordinate.y.dataType.letter) - 65;
			isYInRange = true;
			inRangeCounter++;
		}
		else if(userCoordinate.y.dataType.letter >= 97				//-->Make calculations if y is a lower case
			&& userCoordinate.y.dataType.letter < 97 + SIZE) {		//letter according to the ascii table.
			userCoordinate.y.dataType.number =
				(int)(userCoordinate.y.dataType.letter) - 97;
			isYInRange = true;
			inRangeCounter++;
		}
		if(isXInRange && isYInRange) {								//-->If the X and Y variables are in range,
			x = userCoordinate.x.dataType.number;					//assign x and y values to their structured
			y = userCoordinate.y.dataType.number;					//variables. Otherwise they remain out of range
		}															//to avoid a segmentation fault.
		if(playerCoordinates[x][y] == 1 ||							//-->Check for duplicate coordinates. If so,
			playerCoordinates[x][y] == 2)							//isDuplicate variable equals to true.
			isDuplicate = true;
		if(inRangeCounter == 2 && !isDuplicate)						//-->If coordinate is in range and not a
			isOutOfRange = false;									//duplicate, then set isOutOfRange = false.
		else if(inRangeCounter != 2) {								//-->If either x or y is out of range, display
			isOutOfRange = true;									//Out of range and set isOutOfRange = true.
			printf("\tOut of range\n\n");
			inRangeCounter = 0;
		}
		else if(isDuplicate) {										//-->If isDuplicate == true, print to the user
			printf("\tDuplicate\n\n");								//duplicate values and reset the range counter.
			inRangeCounter = 0;
		}
	} while(isOutOfRange || isDuplicate);				//-->Iterate while numbers are duplicate or out of range.
	playerCoordinates[x][y] = 1;									//-->Set playerCoordinates[x][y] = 1 because
	lastCoordinate[0] = x + 1;										//user is player one.
	lastCoordinate[1] = y + 1;										//-->Set lastCoordinates 0 and 1 equal to the
	printf("\n");													//numerical coordinates displayed in the grid.
}
//Computer generates a random coordinate-------------------
void GenerateComputerCoordinates(int playerCoordinates[][SIZE]) {
	int emptyCoordinateCounter = 0;
	int randomRow;
	int randomColumn;
	srand(time(NULL));
	for(int row = 0; row < SIZE; row++) {							//-->Check for empty coordinates within the
		for(int column = 0; column < SIZE; column++) {				//playerCoordinates array and accumulate the
			if(playerCoordinates[row][column] == 0)					//amount of empty coordinates into the
				emptyCoordinateCounter++;							//emptyCoordinateCounter.
		}
	}
	if(emptyCoordinateCounter > 1) {								//-->If there are more than one empty
		do {														//coordinates, randomize the row and column
			randomRow = rand() % SIZE;								//containing a 0.
			randomColumn = rand() % SIZE;
		} while(playerCoordinates[randomRow][randomColumn] != 0);	//-->Iterate until ...
		playerCoordinates[randomRow][randomColumn] = 2;				//playerCoordinates[randomRow][randomColumn] = 0
	}																//and set it equals to two because the computer
}																	//is player 2.
//Initialize each value within array to zero for a new game
void InitializeCoordinates(int playerCoordinates[][SIZE],
	int arraySize) {
	for(int row = 0; row < SIZE; row++) {							//-->Initialize every coordinate of the two
		for(int column = 0; column < SIZE; column++) {				//-->dimensional array to 0.
			playerCoordinates[row][column] = 0;
		}
	}
}
//Prompts user if he or she wants to contnue playing-------
bool PromptUserContinue(int lastCoordinate[], char userName[],
	int winner) {
	int inproperResponseCounter;									//-->Used to count amount of inproper responses.
	bool isContinue;												//-->True if user chooses to play another game.
	bool isProperResponse;											//-->True if userResponse == "Y", "y", "N", "n".
	char userResponse[10];											//-->User's response to play another game.
	switch(winner) {
		case 0:														//-->If winner = 0, display to the user that
			printf("\t\t\tIts a tie %s!\n\n"						//he or she tied.
				"Last coordinates ROW: %d\n"
				"Last coordinates COLUMN: %d\n",
				userName, lastCoordinate[0], lastCoordinate[1]);
			break;
		case 1:														//-->If the user is the winner, display the
			printf("\t\t\tYou won %s!\n\n"							//following contents.
				"Last coordinates ROW: %d\n"
				"Last coordinates COLUMN: %d\n",
				userName, lastCoordinate[0], lastCoordinate[1]);
			break;
		case 2:
			printf("\t\tYou lost %s\n\n", userName);				//-->If the computer is the winner, display
			break;													//the following contents.
	}
	do {															//-->Iterate through the loop until the user
		printf("Do you want to play again (y/Y or n/N): ");			//enters a proper answer
		gets(userResponse);
		fflush(stdin);												//-->Flush the buffer
		if(strcmp(userResponse, "N") == 0 ||						//-->If user enters either "n" or "N",
			strcmp(userResponse, "n") == 0) {						//isContinue equals false, therefore the
			isContinue = false;										//user chooses to quit the program
			isProperResponse = true;
		}
		else if(strcmp(userResponse, "Y") == 0 ||					//-->If user enters either "y" or "Y",
			strcmp(userResponse, "y") == 0) {						//isContinue equals true, therefore the
			isContinue = true;										//user chooses to continue on to another game
			isProperResponse = true;
		}
		else {
			inproperResponseCounter++;								//-->Else if the user enters an improper
			isProperResponse = false;								//response, reiterate the question and
			if(inproperResponseCounter == 3) {						//quit the program after the user responds
				isContinue = false;									//inproperly three times.
				isProperResponse = true;
			}
		}
		printf("\n");
	} while(!isProperResponse);										//-->Iterate while the user has not entered a
	return isContinue;												//proper response and return the variable which
}																	//determines if user wants to continue or not.
//Prompt user to enter his or her name---------------------
void ScanName(char userName[]) {
	int commaCounter;												//-->Counts the amount of commas within userName
	bool isComma;													//-->True if userName contains only one comma.
	bool isNumber;													//-->True if userName contains any digit.
	bool isValid;													//-->False if userName contains digits, or more
	do {															//or less than one comma.
		for(int index = 0; index < strlen(userName);				//-->Initialize the entire userName char array
			index++) {												//to null values when the while loop re iterates.
			userName[index] = '\0';
		}
		commaCounter = 0;											//-->Initialize variables just in case the
		isComma = false;											//user enters the wrong input to avoid any
		isNumber = false;											//logical errors.
		isValid = true;												//----------------------------------------
		printf("Enter name: ");										//-->Prompt the user to enter his or her name.
		gets(userName);												//-->Record the user's name.
		fflush(stdin);												//-->Flush the buffer
		for(int index = 0; index < strlen(userName);				//-->Iterate through each character in the
			index++) {												//userName and count how many commas there are
			if(userName[index] == ',') {							//as well as finding any digits within the
				commaCounter++;										//char array.
			}
			if(isdigit(userName[index])) {
				isNumber = true;
			}
		}
		if(isNumber) {												//-->If userName contains any number, display
			printf("\tNo Digits\n");								//"No Digits" to the user and determine the
			isValid = false;										//string not valid.
		}
		if(commaCounter == 0) {										//-->If userName does not contain any commas,
			printf("\tNeeds comma\n");								//display "Needs comma" to the user and
			isValid = false;										//determine the string not valid.
		}
		if(commaCounter != 1 && commaCounter > 0) {					//-->If userName contains more or less than one
			printf("\tOnly one comma\n");							//comma, display "Only one comma" to the user
			isValid = false;										//and determine the string not valid.
		}
		if(commaCounter == 1 && isValid) {							//-->If userName contains only one comma and
			isComma = true;											//its contents are valid, set isComma = true
			isNumber = false;										//and isNumber = false to exit out of while loop.
		}
		printf("\n");
	} while(!isComma || isNumber);									//-->Iterate while string has more or less than
																	//one comma or contains digits.
	userName[0] = toupper(userName[0]);								//-->Capitalize first letter of userName.
	strtok(userName, ",");											//-->Truncate contents after the comma in string.
}

