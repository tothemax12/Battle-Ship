/*
BATTLE SHIP PROGRAM

Created By Max Anderson 2021

getRand function credit Kevin Lee
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

//defining all the spaces
#define a1 1
#define a2 2
#define a3 3
#define a4 4
#define a5 5
#define a6 6
#define a7 7
#define a8 8
#define a9 9
#define a10 10

#define b1 12
#define b2 13
#define b3 14
#define b4 15
#define b5 16
#define b6 17
#define b7 18
#define b8 19
#define b9 20
#define b10 21

#define c1 23
#define c2 24
#define c3 25
#define c4 26
#define c5 27
#define c6 28
#define c7 29
#define c8 30
#define c9 31
#define c10 32

#define d1 34
#define d2 35
#define d3 36
#define d4 37
#define d5 38
#define d6 39
#define d7 40
#define d8 41
#define d9 42
#define d10 43

#define e1 45
#define e2 46
#define e3 47
#define e4 48
#define e5 49
#define e6 50
#define e7 51
#define e8 52
#define e9 53
#define e10 54

#define f1 56
#define f2 57
#define f3 58
#define f4 59
#define f5 60
#define f6 61
#define f7 62
#define f8 63
#define f9 64
#define f10 65

#define g1 67
#define g2 68
#define g3 69
#define g4 70
#define g5 71
#define g6 72
#define g7 73
#define g8 74
#define g9 75
#define g10 76

#define h1 78
#define h2 79
#define h3 80
#define h4 81
#define h5 82
#define h6 83
#define h7 84
#define h8 85
#define h9 86
#define h10 87

#define i1 89
#define i2 90
#define i3 91
#define i4 92
#define i5 93
#define i6 94
#define i7 95
#define i8 96
#define i9 97
#define i10 98

#define j1 100
#define j2 101
#define j3 102
#define j4 103
#define j5 104
#define j6 105
#define j7 106
#define j8 107
#define j9 108
#define j10 109

//directions for computers guess
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define NO_SHIP 0
#define HIT_A_SHIP 1
#define SUNK 2
#define CHECKING_HITS 3

#define TRUE 1
#define FALSE 0

/*
IMPORTANT NOTE:
To avoid conflict between board locations and ASCII codes I have change the status of ships to be seperate from the chars that represent them
- a sunk ship location in ship status is marked by a -2 (on the board it is 83 for an "S")
- a ship location that was hit is marked by -3 (instead of 72 for an "H")
*/


void mainMenu();

//char* board[100] = {"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};
char board[1000] = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
char comBoard[1000] = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
char comBoardHidden[1000] = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
int comShips[4][10] = {{0,0,0,0,0}, {0,0,0,0}, {0,0,0}, {0,0,0}, {0,0}};
int comShipsSpotsStatus[100] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int comShipsSpotsNoChange[100] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

int playerShipsSpotsStatus[100] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//this array is so the status of a certain ship location can be altered. (for seeing if a certain location is hit a miss or a ship is sunk
int playerShipsSpotsNoChange[100] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//this array store the ships locations for searching purposes but will never be changed
int playerGuesses[200] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int playerGuessCount = 0;

int ship5h[10] = {0, 0, 0, 0, 0};
int ship4h[10] = {0, 0, 0, 0};
int ship3h1[10] = {0, 0, 0};
int ship3h2[10] = {0, 0, 0};
int ship2h[10] = {0, 0};
int setup(int autoSetup);
void display(int whichBoard);
int boardSetup(int spot1, int spot2, int clear, int ship);

//functions and vars for setting up the coms board
void computerSetup();
int computerBoatPlacer (int shipHoles, int rowMax, int rowIndexMax, int vertOrHorztlShip);
int shipHoleSum = 0;
int convertInput(char points[]);
int getRand(int first, int last);

//to test the board being setup
void computerSetupDisplay();

void game();

//for computers guess on normal mode
int comGuessNormal();
int computerGuessAndOrCheck(int notRandomGuess, int guess);
int initialHit = 0; //location of first hit
int lastHit = 0; //location of last hit
int lastMove = 0;
int sunk = 0; // to check if the ship has sunk or not yet (1 sunk, 0 not sunk)
int currentDir = 9; //to see what direction the computer is currently guessing
int changeDir = FALSE;
int guessCount = 0;
int comGuesses[200] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int shipStatus = NO_SHIP; 
int guessedDirections[4] = {-1, -1, -1, -1};
int dirCount = 0;
int computerDirectionHandling(int checkingHits);
int checkingHitsDirectionHandling();
int organizeHitArray();
int wallCheckAndHandling();
int cornerCheckAndHandling();

//functions and vars for comp guess if it has hits not part of a sunk ship
int possibleInitHits[50] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int possibleInitHitHandling(int check, int shipSpotsToRemove);
int removeHitsThatWerePartOfSunkShip(int ship);

int hitCount = 0;
int firstTimeInCheckingHits = FALSE;
int currentHitBeingChecked = 0;
int allSpotsCleared = FALSE;
int shipThatWasSunk = 0;

//function for displaying a location on the board as it's string equivalent (e.g input 1 outputs "a1")
const char*  convertBoardLocation2String(int location);

//functions for testing and debugging
void playerRandomSetup();
int playerRandomBoatPlacer(int ship, int rowMax, int rowIndexMax, int vertOrHorztlShip);
int k = 0;
int firstInitalHit = 0;
void displayDirArr();

void computerSetupDisplay(int hideSpots) {
  //changing the color
  //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
if (!hideSpots) {
	
	int i;
	
	//displaying the rows letter
	int row = 65;

//displaying the top number row

	for (i=1; i<11; i++) {
		if(i==1){
			printf("  ");
		}
				printf("%d ", i);
		}

i=0;
	
	for (i = 0; i <= (strlen(comBoard))-1; i++) {
	if (i%11==0){
			printf("\n");
			printf("%c ", row);
			row++;
		} else {
			printf("%c ", comBoard[i]);
		}
}

} else if (hideSpots) {
	
		int i;
	
	//displaying the rows letter
	int row = 65;

//displaying the top number row

	for (i=1; i<11; i++) {
		if(i==1){
			printf("  ");
		}
				printf("%d ", i);
		}

i=0;
	
	for (i = 0; i <= (strlen(comBoardHidden))-1; i++) {
	if (i%11==0){
			printf("\n");
			printf("%c ", row);
			row++;
		} else {
			printf("%c ", comBoardHidden[i]);
		}
}
	
}

}

int main() {
	

	//show the main menu
	mainMenu();
	
	//guessing a random direction to begin and putting it in guessed array
	currentDir = getRand(0, 3);
	guessedDirections[dirCount] = currentDir;
	dirCount++;
	
	int setupDone = 1;
	
	computerSetup();
	
	//set up com board and clear the screen
	system("cls");
	
	/*
	//auto setup for debugging---------------------

	shipHoleSum = 0;//reset 
	playerRandomSetup();
	system("cls");
	display(0);


	//checking player ships spots after auto setup
	int i = 0;
	printf("player ships spots--> ");
	for (i = 0; i < 120; i++) {
		printf("%d ", playerShipsSpotsNoChange[i]);
	}
	
	system("pause");
    //end auto setup----------------------------------------------
	*/
	
	setupDone = setup(FALSE);
	
	
	//after player and com are setup begin game
	if (setupDone == 1) {
		game();
	}

	return 0;
}

int setup(int autoSetup) {
char points[10] = "";
int i;
int point1;
int point2;
int pointCount = 1;
int shipBeingSetup = 1;
int shipHoles = 0;
int validSpot = 0;
char userResponse = 0;

//ship 1
if (!autoSetup) {

//show the board first
display(0);

for (i = 1; i <= 5; i++) {
do {
	switch (shipBeingSetup) {
		case 1:
			shipHoles = 5;
			break;
			case 2:
				shipHoles = 4;
				break;
				case 3:
					shipHoles = 3;
					break;
					case 4:
					shipHoles = 3;
					break;
					case 5:
					shipHoles = 2;
					break;
	}
//printf("\nPlease input where you want a ship with 5 points (example 5 hole ship from a1-a6 enter as a1 and then a6");

do {
//ship 1 p1
printf("\nWhere would you like to put your %d ship? (point %d) (%d holes)\n", i, pointCount, shipHoles);
scanf("%s", points);
point1 = convertInput(points);
pointCount++;

//ship 1 p2
printf("\nWhere would you like to put your %d ship? (point %d) (%d holes)\n", i, pointCount, shipHoles);
scanf("%s", points);
point2 = convertInput(points);
validSpot = boardSetup(point1, point2, 0, shipBeingSetup); //if this returns 0 it's not a valid ship location
if (!validSpot) {
printf("\ninvalid location for ship!\n\n");
//clear the ship they just placed
pointCount = 1;
boardSetup(point1, point2, 1, shipBeingSetup);
display(0);
}
} while (validSpot == 0);
display(0);

printf("\nDid you want the ship like this? (type 1 for yes and 0 for no)\n");
scanf(" %d", &userResponse);
if (userResponse == 0) {
	//clear the ship they just placed
	pointCount = 1;
	boardSetup(point1, point2, 1, shipBeingSetup);
}
display(0);
	} while (userResponse != 1);
	system("cls");
	display(0);
	userResponse = 0;
	shipBeingSetup++;
	pointCount = 1;
}
} else if (autoSetup) {//auto setup for testing
	
	//auto setup 1
	/*
	boardSetup(1, 5, 0, 1);
	boardSetup(10, 43, 0, 2);
	boardSetup(34, 36, 0, 3);
	boardSetup(50, 72, 0, 4);
	boardSetup(90, 91, 0, 5);
	*/

	//auto setup 2 (clumped)
	/*
	boardSetup(1, 5, 0, 1);
	boardSetup(12, 15, 0, 2);
	boardSetup(23, 25, 0, 3);
	boardSetup(34, 36, 0, 4);
	boardSetup(45, 46, 0, 5);
	*/
	
	//auto setup 3 (corners)
	/*
	boardSetup(1, 5, 0, 1);
	boardSetup(10, 43, 0, 2);
	boardSetup(100, 102, 0, 3);
	boardSetup(107, 109, 0, 4);
	boardSetup(94, 105, 0, 5);
	*/
}

//copy all the ship locations from the NoChange array to the Status array
for (i = 0; i < 17; i++) {
	if (playerShipsSpotsNoChange[i] != -1) {
		playerShipsSpotsStatus[i] = playerShipsSpotsNoChange[i];
	}
}

return 1;
}

void computerSetup() {
	int i;
	int success = 0;
	int vertOrHorztlShip;

//repeat until all the boats are placed
for (i = 1; i <= 5; i++) {
	
	//boat 1 (5 holes) setting valid placement for vert or horizontal cases
	switch(i) {
		case 1:

			do {
			vertOrHorztlShip = getRand(0, 1); //allowing for random orientation of boats for every boat
			
			if(vertOrHorztlShip) {//horizontal
			do {
success = computerBoatPlacer(i, 10, 6, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = computerBoatPlacer(i, 6, 10, vertOrHorztlShip);
}while(success == 0);
			}
			
			} while(success == 0);
			break;
		
			case 2: //2nd boat (4 holes)
			
			do {
			vertOrHorztlShip = getRand(0, 1);
			
					if(vertOrHorztlShip) {//horizontal
			do {
success = computerBoatPlacer(i, 10, 7, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = computerBoatPlacer(i, 7, 10, vertOrHorztlShip);
}while(success == 0);
			}
			} while(success == 0);
			break;
			
			case 3: //3nd boat (3 holes)
			do {
			vertOrHorztlShip = getRand(0, 1);
			
					if(vertOrHorztlShip) {//horizontal
			do {
success = computerBoatPlacer(i, 10, 8, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = computerBoatPlacer(i, 8, 10, vertOrHorztlShip);
}while(success == 0);
			}
			}while(success == 0);
			break;

			case 4: //4th boat (3 holes)
			
				do {
			vertOrHorztlShip = getRand(0, 1);
					
					if(vertOrHorztlShip) {//horizontal
			do {
success = computerBoatPlacer(i, 10, 8, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = computerBoatPlacer(i, 8, 10, vertOrHorztlShip);
}while(success == 0);
			}

} while(success == 0);			
			break;	
			
			case 5: //5th boat (2 holes)
			
				do {
			vertOrHorztlShip = getRand(0, 1);
			
					if(vertOrHorztlShip) {//horizontal
			do {
success = computerBoatPlacer(i, 10, 9, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = computerBoatPlacer(i, 9, 10, vertOrHorztlShip);
}while(success == 0);
			}
			
			}while(success == 0);
			break;		
			
}
}
/*
	//check to see what the list of spots is for debugging
			for (i=0; i<=20; i++) {
				printf("%d", comShipsSpots[i]);
			}
*/
}

int computerBoatPlacer(int ship, int rowMax, int rowIndexMax, int vertOrHorztlShip) {
	int row;
	int rowIndex;
	int shipCount;
	int i;
	int j;
	int k;
	int l;
	int matchCount = 0; //for if boats are overlapping
	
	int matches[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	//flag if spot is taken
	int validPlacement = 0;
	
	
	//ship being setup
	int shipHoles;
	
		switch (ship) {
		case 1:
			shipHoles = 5;
			break;
			case 2:
				shipHoles = 4;
				break;
				case 3:
					shipHoles = 3;
					break;
					case 4:
					shipHoles = 3;
					break;
					case 5:
					shipHoles = 2;
					break;
	}
	
	row = getRand(1, rowMax);
	
	//mapping input to board
	//rowIndex is the last index it can be for the row selected
	rowIndexMax += (11*(row-1));
	
	
		switch (row) {
		case 1://row a
			rowIndex = getRand(a1, rowIndexMax);
			break;
		case 2://row b
			rowIndex = getRand(b1, rowIndexMax);
			break;
		case 3:// row c
			rowIndex = getRand(c1, rowIndexMax);
			break;
		case 4:// row d
		rowIndex = getRand(d1, rowIndexMax);
			break;
		case 5:// row e
		rowIndex = getRand(e1, rowIndexMax);
			break;	
		case 6:// row f
		rowIndex = getRand(f1, rowIndexMax);
			break;
		case 7:// row g
		rowIndex = getRand(g1, rowIndexMax);
			break;
		case 8:// row h
		rowIndex = getRand(h1, rowIndexMax);
			break;
		case 9:// row i
		rowIndex = getRand(i1, rowIndexMax);
			break;
		case 10:// row j
		rowIndex = getRand(j1, rowIndexMax);
			break;
	} 
	
	
		//display to see if this thing works
		if (!vertOrHorztlShip) {
		for (i = rowIndex; i < rowIndex+(shipHoles*11); i+=11) {
		comBoard[i] = 45;

		
		
		//just put them in a big list
		comShipsSpotsStatus[(((i-rowIndex)+1)/11)+1+(shipHoleSum-1)] = i;
		comShipsSpotsNoChange[(((i-rowIndex)+1)/11)+1+(shipHoleSum-1)] = i;
		}
	} else if(vertOrHorztlShip) {
		for (i = rowIndex; i < (rowIndex+shipHoles); i++) {
		comBoard[i] = 45;

		
		//just put them in a big list 
		comShipsSpotsStatus[(i-rowIndex)+1+(shipHoleSum-1)] = i;
		comShipsSpotsNoChange[(i-rowIndex)+1+(shipHoleSum-1)] = i;
		}
	}	
	

	
//FINAL BOAT CHECK
//checking if the current boat was placed in a spot where there already was a boat
if(shipHoleSum >= 5) {//checking after first ship was placed
for (i = shipHoleSum; i <= shipHoleSum+(shipHoles-1); i++) { //current ship holes
	//printf("\n i IS %d\n", i);

for (j = 0; j < shipHoleSum; j++) { //checking previous ship holes
	
	if (comShipsSpotsNoChange[i] == comShipsSpotsNoChange[j]) {
		matches[matchCount] = comShipsSpotsNoChange[i];
		matchCount++;
	}
	
}

}
}

int flag; //for checking if it should put a spot back
if (matchCount != 0) {
		//if it's a match put 0's back and place again
	if (!vertOrHorztlShip) {//vertical
		for (k = rowIndex; k < rowIndex+(shipHoles*11); k+=11) {
		//don't get rid of spots for previous ships
		for(i = 0; i < matchCount; i++) {
		if (k == matches[i]) {
			flag = 1;
		} 
	}
		//if it's not a match
		if (!flag) {
		comBoard[k] = 48;
		}
		flag = 0;
}
		return 0; //spot already taken-
	} else if(vertOrHorztlShip) {
		for (k = rowIndex; k < (rowIndex+shipHoles); k++) {//horizontal
		//don't get rid of spots for previous ships
	for(i = 0; i < matchCount; i++) {
		if (k == matches[i]) {
		flag = 1;
		}
	}
	//if it's not a match
	if (!flag) {
		comBoard[k] = 48;
	}
	
	flag = 0;
}
		return 0; //spot already taken
}
}

shipHoleSum += shipHoles;

return 1; //saying it worked for testing
}




int getRand(int first, int last)
{
   static int firstTime = 1;
   int amountOfNumbers;
   if (firstTime == 1){
      //first time in this function, seed the random number generator
       firstTime = 0;
	   srand(time(NULL));
   }
   amountOfNumbers = last - first + 1;
   return(rand() % amountOfNumbers + first);
}

//this just displays the board
void display(int whichBoard) {
	//displaying the players board
	if (!whichBoard) {
	int i;
	
	//displaying the rows letter
	int row = 65;

//displaying the top number row

	for (i=1; i<11; i++) {
		if(i==1){
			printf("  ");
		}
				printf("%d ", i);
		}

i=0;
	
	for (i = 0; i <= (strlen(board))-1; i++) {
	if (i%11==0){
			printf("\n");
			printf("%c ", row);
			row++;
		} else {
			printf("%c ", board[i]);
		}
}
} else if (whichBoard) { //display the computers board
		int i;
	
	//displaying the rows letter
	int row = 65;

//displaying the top number row

	for (i=1; i<11; i++) {
		if(i==1){
			printf("  ");
		}
				printf("%d ", i);
		}

i=0;
	
	for (i = 0; i <= (strlen(comBoard))-1; i++) {
	if (i%11==0){
			printf("\n");
			printf("%c ", row);
			row++;
		} else {
			printf("%c ", comBoard[i]);
		}
}
}
}

//this function takes input and maps it to the board
int convertInput(char points[]) {
	//printf("strlen %d", strlen(points));
	int point = 0;
	
	//converting string to board value
	//finding letter row
	switch (points[0]) {
	//row a
	case (97):
	//finding number for row a
	switch (points[1]) {
		case (49):
			point = a1;
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
		point = a2;
		return point;
		break;
			case(51):
		point = a3;
		return point;
		break;
				case(52):
		point = a4;
		return point;
		break;
		case(53):
		point = a5;
		return point;
		break;
			case(54):
		point = a6;
		return point;
		break;
				case(55):
		point = a7;
		return point;
		break;
				case(56):
		point = a8;
		return point;
		break;
				case(57):
		point = a9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
			point = a10;
			return point;
			break;
		}
		
	//row b
	case (98):
	//finding number for row b
	switch (points[1]) {
		case (49):
			point = b1;
			//return if its actually b1 not b10
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
		point = b2;
		return point;
		break;
			case(51):
		point = b3;
		return point;
		break;
				case(52):
		point = b4;
		return point;
		break;
		case(53):
		point = b5;
		return point;
		break;
			case(54):
		point = b6;
		return point;
		break;
				case(55):
		point = b7;
		return point;
		break;
				case(56):
		point = b8;
		return point;
		break;
				case(57):
		point = b9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
			point = b10;
			return point;
			break;
		}
		
			//row c
	case (99):
	//finding number for row c
	switch (points[1]) {
		case (49):
			point = c1;
			//return if its actually b1 not b10
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
		point = c2;
		return point;
		break;
			case(51):
		point = c3;
		return point;
		break;
				case(52):
		point = c4;
		return point;
		break;
		case(53):
		point = c5;
		return point;
		break;
			case(54):
		point = c6;
		return point;
		break;
				case(55):
		point = c7;
		return point;
		break;
				case(56):
		point = c8;
		return point;
		break;
				case(57):
		point = c9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
			point = c10;
			return point;
			break;
		}
		
		//row d
		case (100):
	//finding number for row d
	switch (points[1]) {
		case (49):
			point = d1;
			//return if its actually b1 not b10
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
			//printf("test 2");
		point = d2;
		return point;
		break;
			case(51):
				//printf("test 3");
		point = d3;
		return point;
		break;
				case(52):
					//printf("test 4");
		point = d4;
		return point;
		break;
		case(53):
		//printf("test 5");
		point = d5;
		return point;
		break;
			case(54):
				//printf("test 6");
		point = d6;
		return point;
		break;
				case(55):
					//printf("test 7");
		point = d7;
		return point;
		break;
				case(56):
					//printf("test 8");
		point = d8;
		return point;
		break;
				case(57):
					//printf("test 9");
		point = d9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
				//printf("test 10");
			point = d10;
			return point;
			break;
		}
		
				//row e
		case (101):
	//finding number for row a
	switch (points[1]) {
		case (49):
			//printf("test 1");
			point = e1;
			//return if its actually b1 not b10
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
			//printf("test 2");
		point = e2;
		return point;
		break;
			case(51):
				//printf("test 3");
		point = e3;
		return point;
		break;
				case(52):
					//printf("test 4");
		point = e4;
		return point;
		break;
		case(53):
		//printf("test 5");
		point = e5;
		return point;
		break;
			case(54):
				//printf("test 6");
		point = e6;
		return point;
		break;
				case(55):
					//printf("test 7");
		point = e7;
		return point;
		break;
				case(56):
					//printf("test 8");
		point = e8;
		return point;
		break;
				case(57):
					//printf("test 9");
		point = e9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
				//printf("test 10");
			point = e10;
			return point;
			break;
		}
		
		case (102):
	//finding number for row f
	switch (points[1]) {
		case (49):
			//printf("test 1");
			point = f1;
			//return if its actually b1 not b10
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
			//printf("test 2");
		point = f2;
		return point;
		break;
			case(51):
				//printf("test 3");
		point = f3;
		return point;
		break;
				case(52):
					//printf("test 4");
		point = f4;
		return point;
		break;
		case(53):
		//printf("test 5");
		point = f5;
		return point;
		break;
			case(54):
				//printf("test 6");
		point = f6;
		return point;
		break;
				case(55):
					//printf("test 7");
		point = f7;
		return point;
		break;
				case(56):
					//printf("test 8");
		point = f8;
		return point;
		break;
				case(57):
					//printf("test 9");
		point = f9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
				//printf("test 10");
			point = f10;
			return point;
			break;
		}
		
				case (103):
	//finding number for row g
	switch (points[1]) {
		case (49):
			//printf("test 1");
			point = g1;
			//return if its actually b1 not b10
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
			//printf("test 2");
		point = g2;
		return point;
		break;
			case(51):
				//printf("test 3");
		point = g3;
		return point;
		break;
				case(52):
					//printf("test 4");
		point = g4;
		return point;
		break;
		case(53):
		//printf("test 5");
		point = g5;
		return point;
		break;
			case(54):
				//printf("test 6");
		point = g6;
		return point;
		break;
				case(55):
					//printf("test 7");
		point = g7;
		return point;
		break;
				case(56):
					//printf("test 8");
		point = g8;
		return point;
		break;
				case(57):
					//printf("test 9");
		point = g9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
				//printf("test 10");
			point = g10;
			return point;
			break;
		}
				
				case (104):
	//finding number for row h
	switch (points[1]) {
		case (49):
			//printf("test 1");
			point = h1;
			//return if its actually b1 not b10
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
			//printf("test 2");
		point = h2;
		return point;
		break;
			case(51):
				//printf("test 3");
		point = h3;
		return point;
		break;
				case(52):
					//printf("test 4");
		point = h4;
		return point;
		break;
		case(53):
		//printf("test 5");
		point = h5;
		return point;
		break;
			case(54):
				//printf("test 6");
		point = h6;
		return point;
		break;
				case(55):
					//printf("test 7");
		point = h7;
		return point;
		break;
				case(56):
					//printf("test 8");
		point = h8;
		return point;
		break;
				case(57):
					//printf("test 9");
		point = h9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
				//printf("test 10");
			point = h10;
			return point;
			break;
		}
						
				case (105):
	//finding number for row f
	switch (points[1]) {
		case (49):
			//printf("test 1");
			point = i1;
			//return if its actually b1 not b10
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
			//printf("test 2");
		point = i2;
		return point;
		break;
			case(51):
				//printf("test 3");
		point = i3;
		return point;
		break;
				case(52):
					//printf("test 4");
		point = i4;
		return point;
		break;
		case(53):
		//printf("test 5");
		point = i5;
		return point;
		break;
			case(54):
				//printf("test 6");
		point = i6;
		return point;
		break;
				case(55):
					//printf("test 7");
		point = i7;
		return point;
		break;
				case(56):
					//printf("test 8");
		point = i8;
		return point;
		break;
				case(57):
					//printf("test 9");
		point = i9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
				//printf("test 10");
			point = i10;
			return point;
			break;
		}

			
					
	case (106):
		
	//finding number for row f
	switch (points[1]) {
		case (49):
			//printf("test 1");
			point = j1;
			//return if its actually b1 not b10
			if(strlen(points)<=2){
				return point;
			}
			break;
		case(50):
			//printf("test 2");
		point = j2;
		return point;
		break;
			case(51):
				//printf("test 3");
		point = j3;
		return point;
		break;
				case(52):
					//printf("test 4");
		point = j4;
		return point;
		break;
		case(53):
		//printf("test 5");
		point = j5;
		return point;
		break;
			case(54):
				//printf("test 6");
		point = j6;
		return point;
		break;
				case(55):
					//printf("test 7");
		point = j7;
		return point;
		break;
				case(56):
					//printf("test 8");
		point = j8;
		return point;
		break;
				case(57):
					//printf("test 9");
		point = j9;
		return point;
		break;	
	}
		switch(points[2]) {
			case(48):
				//printf("test 10");
			point = j10;
			return point;
			break;
		}

	//printf("%d", point);
	}
}



int boardSetup(int spot1, int spot2, int clear, int ship) {
	int i;
	int j;
	//printf("\n spot1 = %d spot2 = %d abs test spot1-spot2=%d\n", spot1, spot2, abs(spot1-spot2));
	int validCheck = -1;
	//this is for if they are setting up there ships-----------------------------------------------------------------------------------
	
	//if they put a ship in an invalid spot
	switch(ship) {
		//ship 1 5 holes
		case 1:
			if ((abs(spot1-spot2) < 44 && abs(spot1-spot2) != 4) || (abs(spot1-spot2) > 44 && abs(spot1-spot2) != 4) || abs(spot1-spot2) < 4 || (abs(spot1-spot2) > 4 && abs(spot1-spot2) != 44)) {
				//printf("the difference between ship points is %d", abs(spot1-spot2));
				//the ship can't go here
				validCheck = 0;
			}
			break;
			//ship 2 4 holes
			case 2:
			if ((abs(spot1-spot2) < 33 && abs(spot1-spot2) != 3) || (abs(spot1-spot2) > 33 && abs(spot1-spot2) != 3) || abs(spot1-spot2) < 3 || (abs(spot1-spot2) > 3 && abs(spot1-spot2) != 33)) {
				//printf("the difference between ship points is %d", abs(spot1-spot2));
				//the ship can't go here
				validCheck = 0;
			}
			break;
			//ship 3 3 holes
			case 3:
			if ((abs(spot1-spot2) < 22 && abs(spot1-spot2) != 2) || (abs(spot1-spot2) > 22 && abs(spot1-spot2) != 2) || abs(spot1-spot2) < 2 || (abs(spot1-spot2) > 2 && abs(spot1-spot2) != 22)) {
				//printf("the difference between ship points is %d", abs(spot1-spot2));
				//the ship can't go here
				validCheck = 0;
			}
			break;
			//ship 4 3 holes
			case 4:
			if ((abs(spot1-spot2) < 22 && abs(spot1-spot2) != 2) || (abs(spot1-spot2) > 22 && abs(spot1-spot2) != 2) || abs(spot1-spot2) < 2 || (abs(spot1-spot2) > 2 && abs(spot1-spot2) != 22)) {
				//printf("the difference between ship points is %d", abs(spot1-spot2));
				//the ship can't go here
				validCheck = 0;
			}
			break;
				//ship 5 2 holes
			case 5:
			if ((abs(spot1-spot2) < 11 && abs(spot1-spot2) != 1) || (abs(spot1-spot2) > 11 && abs(spot1-spot2) != 1) || abs(spot1-spot2) < 1 || (abs(spot1-spot2) > 1 && abs(spot1-spot2) != 11)) {
				//printf("the difference between ship points is %d", abs(spot1-spot2));
				//the ship can't go here
				validCheck = 0;
			}
			break;
			
	}
	
		//setting j to the right index depending on the ship
		switch (ship) {
			case 1:
					j = 0;
				break;
				case 2:
					j = 5;
				break;
				case 3:
					j = 9;
				break;
				case 4:
					j = 12;
				break;
				case 5:
					j = 15;
				break;
		}
	
	if (validCheck != 0) {
	if (spot2 != 0 && clear != 1) {
//checking if the spaces are on the same row or not
if(abs(spot1-spot2)<10){
	
	for (i=spot1; i<=spot2; i++){
		//putting the ship locations into a convienent array
	playerShipsSpotsNoChange[j] = i;
	j++;
		//ASCII code for X is 88
		board[i] = 88;
	}
	j = 0;
	
	/*
	printf("playerShipsSpots ");
	for (j = 0; j < 17; j++) {
	printf("%d ", playerShipsSpotsNoChange[j]);
}
*/

}
//if they are in different rows
if(abs(spot1-spot2)>10){
	for (i=spot1; i<=spot2; i+=11){
	playerShipsSpotsNoChange[j] = i;
	j++;
	
		board[i] = 88;
	}
	j = 0;
	
	/*
	printf("playerShipsSpots ");
	for (j = 0; j < 17; j++) {
	printf("%d ", playerShipsSpotsNoChange[j]);
}
*/
}

validCheck = 1;
}
}

//clearing a spot-----------------------------------------------------------
if (spot2 != 0 && clear == 1) {
	//clearing a spot in the same row
if(abs(spot1-spot2)<10) {
	for (i=spot1; i<=spot2; i++){
		//ASCII code for 0 to clear the board
		board[i] = 48;
	}
}

//clearing a ship not in the same row
if(abs(spot1-spot2)>10) {
	for (i=spot1; i<=spot2; i+=11){
		board[i] = 48;
	}
}
}

return validCheck;
}

void game() {
	int gameOver = FALSE;
	int winner = -1;
	char guessString[10] = "";
	int playerGuess;
	int validPlayerGuess = 0;
	int i;
	int j;
	int hit = 0;
	char key = "";
	int guessCount = 0;
	int comGuess = 0;
	
	int comShip5[10] = {0, 0, 0, 0, 0};
	int comShip4[10] = {0, 0, 0, 0};
	int comShip3[10] = {0, 0, 0};
	int comShip3Two[10] = {0, 0, 0};
	int comShip2[10] = {0, 0};
	
	int playerShip5[10] = {0, 0, 0, 0, 0};
	int playerShip4[10] = {0, 0, 0, 0};
	int playerShip3[10] = {0, 0, 0};
	int playerShip3Two[10] = {0, 0, 0};
	int playerShip2[10] = {0, 0};
	
	//keeping the ship spots in seperate arrays for reference
	//COMPUTER SHIPS-------------------------------------------------------------------------------
	for (i = 0; i < 17; i++) {
		//ship 1
		if (i < 5) {
			comShip5[i] = comShipsSpotsNoChange[i];
			//for checking if they are put in correctly
			//printf("%d", comShip5[i]);
		if (i == 4) {
			//printf("\n");
		}
		}
		//ship 2
		if (i >= 5 && i < 9) {
			comShip4[8 % i] = comShipsSpotsNoChange[i];
		
		//printf("comShip4[i % 8] = %d at i = %d ** ", comShip4[8 % 1], (8 % i));
		if (i == 8) {
			//printf("\n");
		}
		}
		//ship 3
		if (i >= 9 && i < 12) {
			comShip3[11 % i] = comShipsSpotsNoChange[i];
		
		//printf("%d", comShip3[11 % i]);
		if (i == 11) {
			//printf("\n");
		}
		}
		//ship 3 #2
		if (i >= 12 && i < 15) {
			comShip3Two[14 % i] = comShipsSpotsNoChange[i];
		
		//printf("%d", comShip3Two[14 % i]);
		if (i == 14) {
			//printf("\n");
		}
		}
		//ship 4
		if (i >= 15 && i < 17) {
			comShip2[16 % i] = comShipsSpotsNoChange[i];
		
		//printf("%d", comShip2[16 % i]);
		if (i == 16) {
			//printf("\n");
		}
		}
	}	
	//--------------------------------------------------------------------------------
	//PLAYER SHIPS--------------------------------------------------------------------
		for (i = 0; i < 17; i++) {
		//ship 1
		if (i < 5) {
			playerShip5[i] = playerShipsSpotsNoChange[i];
			//for checking if they are put in correctly
			//printf("%d", playerShip5[i]);
		if (i == 4) {
			//printf("\n");
		}
		}
		//ship 2
		if (i >= 5 && i < 9) {
			playerShip4[8 % i] = playerShipsSpotsNoChange[i];
		
		//printf("comShip4[i % 8] = %d at i = %d ** ", playerShip4[8 % 1], (8 % i));
		if (i == 8) {
			//printf("\n");
		}
		}
		//ship 3
		if (i >= 9 && i < 12) {
			playerShip3[11 % i] = playerShipsSpotsNoChange[i];
		
		//printf("%d", playerShip3[11 % i]);
		if (i == 11) {
			//printf("\n");
		}
		}
		//ship 3 #2
		if (i >= 12 && i < 15) {
			playerShip3Two[14 % i] = playerShipsSpotsNoChange[i];
		
		//printf("%d", playerShip3Two[14 % i]);
		if (i == 14) {
			//printf("\n");
		}
		}
		//ship 4
		if (i >= 15 && i < 17) {
			playerShip2[16 % i] = playerShipsSpotsNoChange[i];
		
		//printf("%d", playerShip2[16 % i]);
		if (i == 16) {
			//printf("\n");
		}
		}
	}
	//----------------------------------------------------------------------------------
	
	do {
		//clear and update the board every turn
		system("cls");
		computerSetupDisplay(TRUE);
		
		//making it look nice
		printf("\n###############################################\n");
		
		display(0);
		
		//user guesses
		do {
		printf("\nWhere would you like to launch?\n");
		scanf("%s", &guessString);
		
		
		//REPEATING GUESS FOR DEBUGGING THE GAME
			//guessString[0] = "a1";
			
			/*
			//stop when all spots guessed
			k++;
			if (k >= 100) {
				system("pause");
			}
			*/
		
		//making the string a spot on the board
		int playerGuessFlag = 0;
		
		playerGuess = convertInput(guessString);
		
		if (playerGuess >= 1 && playerGuess <= 109) {//making sure players guess is on the board
		
		//seeing if they already guessed that location
		for (i = 0; i <= 200; i++) {
			if (playerGuess == playerGuesses[i]) {
				printf("\nYou already guessed %s!\n", convertBoardLocation2String(playerGuess));
				validPlayerGuess = FALSE;
				playerGuessFlag = 1;
				break;
			}
		} 
			if (i == 201 & playerGuessFlag == 0) {
				playerGuesses[playerGuessCount] = playerGuess;
				playerGuessCount++;
				
				validPlayerGuess = TRUE;
			}
		
		} else if (playerGuess < 1 || playerGuess > 109) {
		printf("Invalid guess!\n");
		validPlayerGuess = FALSE;		
		}
		} while (validPlayerGuess != TRUE);
		//printf("guessString = %s, playerGuess = %d", guessString, playerGuess);
		
		//checking if it's one of the coms ships locations
		hit = 0;
		for (i = 0; i <= 17; i++) {
			if (comShipsSpotsNoChange[i] == playerGuess) {
				printf("\nHIT!\n");
				//marking the spot with an H to show it's hit
				comShipsSpotsStatus[i] = 72;
				comBoard[playerGuess] = 72;
				
				//for the board where the ship locations are not seen
				comBoardHidden[playerGuess] = 72;
				hit = 1;
				
			//checking to see if a ship sunk
			//--------------------------------------------------------------------------------------------------------------
			//first ship (5 hole)
		if (comShipsSpotsStatus[0] == 72 && comShipsSpotsStatus[1] == 72 && comShipsSpotsStatus[2] == 72 && comShipsSpotsStatus[3] == 72 && comShipsSpotsStatus[4] == 72) {
			printf("\nPlayer sunk 5 hole ship!\n");
			for (j = 0; j < 5; j++) {
				//marking a sunk ship with S's
				//printf("comShipsSpots %d = %d", j, comShipsSpots[j]);
				
				//marking the board and comShipSpots
				comBoard[comShip5[j]] = 83;
				comBoardHidden[comShip5[j]] = 83;
				comShipsSpotsStatus[j] = 83;
			}
		}//second ship (4 hole)
		if (comShipsSpotsStatus[5] == 72 && comShipsSpotsStatus[6] == 72 && comShipsSpotsStatus[7] == 72 && comShipsSpotsStatus[8] == 72) {
			printf("\nPlayer sunk 4 hole ship!\n");
			for (j = 0; j < 4; j++) {
				//marking a sunk ship with S's
				//printf("comBoard[%d]", j, comShip4[j]);
				
				//marking the board and comShipSpots
				comBoard[comShip4[j]] = 83;
				comBoardHidden[comShip4[j]] = 83;
				comShipsSpotsStatus[5+j] = 83;
			}
		}//third ship (3 hole)
		if (comShipsSpotsStatus[9] == 72 && comShipsSpotsStatus[10] == 72 && comShipsSpotsStatus[11] == 72) {
			printf("\nPlayer sunk 3 hole ship!\n");
			for (j = 0; j < 3; j++) {
				//marking a sunk ship with S's
				//printf("comBoard[%d]", j, comShip4[j]);
				
				//marking the board and comShipSpots
				comBoard[comShip3[j]] = 83;
				comBoardHidden[comShip3[j]] = 83;
				comShipsSpotsStatus[9+j] = 83;
			}
		}//fourth ship (3 hole)
		if (comShipsSpotsStatus[12] == 72 && comShipsSpotsStatus[13] == 72 && comShipsSpotsStatus[14] == 72) {
			printf("\nPlayer sunk 3 hole ship!\n");
			for (j = 0; j < 3; j++) {
				//marking a sunk ship with S's
				//printf("comBoard[%d]", j, comShip3Two[j]);
				
				//marking the board and comShipSpots
				comBoard[comShip3Two[j]] = 83;
				comBoardHidden[comShip3Two[j]] = 83;
				comShipsSpotsStatus[12+j] = 83;
			}
		}//fifth ship (2 hole)
		if (comShipsSpotsStatus[15] == 72 && comShipsSpotsStatus[16] == 72) {
			printf("\nPlayer sunk 2 hole ship!\n");
			for (j = 0; j < 2; j++) {
				//marking a sunk ship with S's
				//printf("comBoard[%d]", j, comShip2[j]);
				
				//marking the board and comShipSpots
				comBoard[comShip2[j]] = 83;
				comBoardHidden[comShip2[j]] = 83;
				comShipsSpotsStatus[15+j] = 83;
			}
		}
			} else if (i == 17 && hit == 0) { // if it was a miss
				printf("\nMissed!\n");
				//marking missed spot with an M
				comBoard[playerGuess] = 77;
				comBoardHidden[playerGuess] = 77;
				
				//don't pause when debugging
				//system("pause");
			}
			
			
			
		}
		/*
		//checking the array
		printf("comShipsSpots Array -> ");
		for (i = 0; i < 17; i++) {
			printf("%d ", comShipsSpots[i]);
		} 
		printf("\n");
		*/
		
			//if all com ships are sunk
		if (comShipsSpotsStatus[0] == 83 && comShipsSpotsStatus[1] == 83 && comShipsSpotsStatus[2] == 83 && comShipsSpotsStatus[3] == 83 && comShipsSpotsStatus[4] == 83 
			&& comShipsSpotsStatus[5] == 83 && comShipsSpotsStatus[6] == 83 && comShipsSpotsStatus[7] == 83 && comShipsSpotsStatus[8] == 83 && 
			comShipsSpotsStatus[9] == 83 && comShipsSpotsStatus[10] == 83 && comShipsSpotsStatus[11] == 83 &&
			comShipsSpotsStatus[12] == 83 && comShipsSpotsStatus[13] == 83 && comShipsSpotsStatus[14] == 83 &&
			comShipsSpotsStatus[15] == 83 && comShipsSpotsStatus[16] == 83) {
			//printf("GAME OVER PLAYER WINS!!!!");
			//system("pause");
			gameOver = 1;
			winner = 1;
			}
			
			int flag = FALSE;
			//computers turn------------------------------------------------------------------------------------------------------------------------
			
			comGuess = comGuessNormal(); //computers guess
			
			printf("\nComputer guessed spot %s\n", convertBoardLocation2String(comGuess));
			
			//printf("in game function! comGuess = %d", comGuess);
			for (i = 0; i <= 17; i++) {
			if (playerShipsSpotsNoChange[i] == comGuess) {//if computers guess is a hit
				printf("\nComputer HIT!\n");
				system("pause");
				
				//putting the potential initial hit into an array seeing if it's part of a sunk ship
				possibleInitHits[hitCount] = comGuess;
		        hitCount++;
				
				flag = TRUE;
				
				//marking the spot with an H to show it's hit
				playerShipsSpotsStatus[i] = -3;
				board[comGuess] = 72;
				
				//setting lastHit and ship status to hit for the com guess function
				lastHit = comGuess;
				lastMove = 1; //last moves a hit
				changeDir = FALSE; //it was a hit so don't change the current direction
				
				//determine if this is an initial hit and set it accordingly
				if (shipStatus == NO_SHIP) {
					initialHit = comGuess;
				}
				
				shipStatus = HIT_A_SHIP;
				
				
			//checking to see if a ship was sunk by the computer (PLAYERS SHIPS)
			//--------------------------------------------------------------------------------------------------------------
			//first ship (5 hole)
		if (playerShipsSpotsStatus[0] == -3 && playerShipsSpotsStatus[1] == -3 && playerShipsSpotsStatus[2] == -3 && playerShipsSpotsStatus[3] == -3 && playerShipsSpotsStatus[4] == -3) {
			printf("\nComputer sunk your 5 hole ship!\n");
			system("pause");
			for (j = 0; j < 5; j++) {
				//marking a sunk ship with S's
				//marking the board and comShipSpots
				board[playerShip5[j]] = 83;
				playerShipsSpotsStatus[j] = -2; //in the ship status array -2 will represent a sunk ship to avoid conflict with ascii code and location 83
			}
		shipThatWasSunk = 1;
		shipStatus = SUNK; //if the ship that was sunk had the initial hit, all the spots are taken care of
		
		}//second ship (4 hole)
		if (playerShipsSpotsStatus[5] == -3 && playerShipsSpotsStatus[6] == -3 && playerShipsSpotsStatus[7] == -3 && playerShipsSpotsStatus[8] == -3) {
			printf("\nComputer sunk your 4 hole ship!\n");
			system("pause");
			for (j = 0; j < 4; j++) {
				//marking a sunk ship with S's
				//marking the board and comShipSpots
				board[playerShip4[j]] = 83;
				playerShipsSpotsStatus[5+j] = -2;
			}

		shipThatWasSunk = 2;
		shipStatus = SUNK;
		
		
		}//third ship (3 hole)
		if (playerShipsSpotsStatus[9] == -3 && playerShipsSpotsStatus[10] == -3 && playerShipsSpotsStatus[11] == -3) {
			printf("\nComputer sunk your 3 hole ship!\n");
			system("pause");
			for (j = 0; j < 3; j++) {
				//marking a sunk ship with S's
				//marking the board and comShipSpots
				board[playerShip3[j]] = 83;
				playerShipsSpotsStatus[9+j] = -2;
			}
		
		shipThatWasSunk = 3;
		shipStatus = SUNK;
		
		
		}//fourth ship (3 hole)
		if (playerShipsSpotsStatus[12] == -3 && playerShipsSpotsStatus[13] == -3 && playerShipsSpotsStatus[14] == -3) {
			printf("\nComputer sunk your 3 hole ship!\n");
			system("pause");
			for (j = 0; j < 3; j++) {
				//marking a sunk ship with S's
				//marking the board and comShipSpots
				board[playerShip3Two[j]] = 83;
				playerShipsSpotsStatus[12+j] = -2;
			}
			
		shipThatWasSunk = 4;
		shipStatus = SUNK; 
		
		
		}//fifth ship (2 hole)
		if (playerShipsSpotsStatus[15] == -3 && playerShipsSpotsStatus[16] == -3) {
			printf("\nComputer sunk your 2 hole ship!\n");
			system("pause");
			for (j = 0; j < 2; j++) {
				//marking a sunk ship with S's
				//marking the board and comShipSpots
				board[playerShip2[j]] = 83;
				playerShipsSpotsStatus[15+j] = -2;
			}
		shipThatWasSunk = 5;
		shipStatus = SUNK;
		
		
		}
		
	} else if (i == 17 && flag == FALSE) { // if it was a miss
				printf("\nComputer Missed!\n");
				system("pause");
				//marking missed spot with an M
				board[comGuess] = 77;
				
				//don't pause when debugging
				//system("pause");
				
				lastMove = 0; //last move was a miss
				
				//if a ship was hit and the next turn it was a miss then change the direction that you guess
				if (shipStatus == HIT_A_SHIP) {
					changeDir = TRUE;
				}
			}
		
					//if all player ships are sunk
		if (playerShipsSpotsStatus[0] == -2 && playerShipsSpotsStatus[1] == -2 && playerShipsSpotsStatus[2] == -2 && playerShipsSpotsStatus[3] == -2 && playerShipsSpotsStatus[4] == -2 
			&& playerShipsSpotsStatus[5] == -2 && playerShipsSpotsStatus[6] == -2 && playerShipsSpotsStatus[7] == -2 && playerShipsSpotsStatus[8] == -2 && 
			playerShipsSpotsStatus[9] == -2 && playerShipsSpotsStatus[10] == -2 && playerShipsSpotsStatus[11] == -2 &&
			playerShipsSpotsStatus[12] == -2 && playerShipsSpotsStatus[13] == -2 && playerShipsSpotsStatus[14] == -2 &&
			playerShipsSpotsStatus[15] == -2 && playerShipsSpotsStatus[16] == -2) {
			gameOver = 1;
			winner = 0;//computer won
			
				//don't pause when debugging
				//system("pause");
				
		  } 
	}
	} while (gameOver != 1);
	
	//code for when the game is over
	system("cls"); 
		
		computerSetupDisplay(FALSE);
		
		//making it look nice
		printf("\n###############################################\n");
		
		display(0);
		
		printf("\n\n");
		
	//show the results
	if (winner == 1) {
	printf("GAME OVER PLAYER WINS!!!!\n\n");	
	} else if (winner == 0) {
		printf("GAME OVER COMPUTER WINS!!!!\n\n");
	}
		system("pause");
}

int comGuessNormal() {
	//setting an initial hit for corner debugging
	
	//printf("INITIAL HIT = %d", initialHit);
	
	int guess = 0;
	int i = 0;
	int j = 0;
	int goodGuess = 0;
	int flag = 0;
	int dirFlag = 0;
	
	//for checking hits case
	int check = -1;
	
	//has a ship been hit?
	//printf("ship status = %d, lastMove = %d", shipStatus, lastMove);
	switch (shipStatus) {
	
	case NO_SHIP://have not hit a ship guess any spot on the board 	
		
	if (!lastMove) {//if a ship was not hit last move guess a random spot on the board
	guess = computerGuessAndOrCheck(FALSE, -1);
	}
		break;
		
		case HIT_A_SHIP:
		computerDirectionHandling(FALSE);
			break;
			
			case SUNK:
			allSpotsCleared = possibleInitHitHandling(TRUE, shipThatWasSunk);
			shipThatWasSunk = 0; //reset for the next ship that is sunk
			
			if (allSpotsCleared) {
			//if all spots in the arr are cleared then continue like normal sunk ship 
			
			//if it's sunk reset everything and go back to guessing random
				shipStatus = NO_SHIP;
				
				//reset direction array
				for (i = 0; i < 4; i++) {
					guessedDirections[i] = -1;
				}
				
				dirCount = 0;
				
				//random direction for next ship
				currentDir = getRand(0, 3);
				guessedDirections[dirCount] = currentDir;
				dirCount++;
		
		//printf("\n\nguessing from SUNK case!\n\n");
		guess = computerGuessAndOrCheck(FALSE, -1);
			
		} else if (!allSpotsCleared) {//if all the spots are not cleared then check them
			//printf("\n\nSTILL POSSIBLE HIT SPOTS TO CHECK/n/n");
		
		shipStatus = CHECKING_HITS;
		
		//reset direction array and get new dir
		for (i = 0; i < 4; i++) {
		guessedDirections[i] = -1;
		}
		
		dirCount = 0;
		
		currentDir = getRand(0, 3);
		guessedDirections[dirCount] = currentDir;
		dirCount++;
		
		changeDir = FALSE;
		
		//set the initialPoint to the first possible hit
		for (i = 0; i < 50; i++) {
			if (possibleInitHits[i] != -1) {
				initialHit = possibleInitHits[i];
				break;
			}
		}
		lastMove = 1;
		lastHit = initialHit;
		
		check = checkingHitsDirectionHandling();
		
		
		}

		break;
		case CHECKING_HITS:
			check = checkingHitsDirectionHandling();
			
			if (check == 0) {//all directions for that spot have been tried, reset array and try a new spot
			//printf("\n\nALL DIRECTIONS HAVE BEEN TRIED RESET DIR ARRAY AND TRY NEW HIT LOCATION\n\n");
			for (i = 0; i < 4; i++) {
				guessedDirections[i] = -1;
			}
			
			//set a new direction
			currentDir = getRand(0, 3);	
			
			//remove checked point from array
			for (i = 0; i < 50; i++) {
				if (initialHit == possibleInitHits[i]) {
					possibleInitHits[i] = -1;//removing checked point from array
				}
			}
			
			//checking the next spot
		for (i = 0; i < 50; i++) {
			if (possibleInitHits[i] != -1) {
				initialHit = possibleInitHits[i];
				break;
			}
		}
		lastMove = 1;
		lastHit = initialHit;
		
			} else {
				return check; //if the check was not a 0 then it was a valid guess
			}
			break;
	}
}

int computerGuessAndOrCheck(int notRandomGuess, int guess) {
	
	if (!notRandomGuess) { //random guess not associated with a direction. Just guess a random spot and see if it's taken	
	int i = 0;
	int j = 0;
	int goodGuess = 0;
	int guess = 0;
	int flag = 0;
	
	while (!goodGuess) {//loop until you don't guess a duplicate
		
		
		do { //making sure the guess is on the board
		guess = getRand(1, 109);
	    } while ((guess < 1 || guess > 109) || (guess == 11 || guess == 22 || guess == 33 || guess == 44 || guess == 55 || guess == 66 || guess == 77 || guess == 88 || guess == 99));
	    
		//search array for duplicate guesses so they don't guess the same spot like a stupid dum dum robot
		for (i = 0; i < 109; i++) {
			if (comGuesses[i] == guess) {
				//printf("\nbad (duplicate) guess! at indece i = [%d] (%d)\n", i, comGuesses[i]);
				//system("pause");
				flag = 1;
				break;
			} else if (i == 108 && flag == 0) {
				goodGuess = 1;
				//printf("\ngood guess!\n");
			}
		}
		flag = 0;
}

		//putting non-dup computers guesses into an array so it doesn't guess the same spot twice
		comGuesses[guessCount] = guess;
		guessCount++;
		
		return guess;
	} else if (notRandomGuess) { //just checking a already decided spot to see if its valid. for example when a direction is changed or going a certain direction
	//printf("\n$$$dealing with a direction, seeing if the guessed spot is taken$$$\n");
	
	int i = 0;
	int goodGuess = 0;
	int flag = 0;
	
		//search array for duplicate guesses so they don't guess the same spot like a stupid dum dum robot
		for (i = 0; i < 109; i++) {
			if (comGuesses[i] == guess) {
				//printf("\nbad (duplicate) guess! at indece i = [%d] (%d)\n", i, comGuesses[i]);
				//system("pause");
				
				flag = 1;
				
				return FALSE;
				break;
			} else if (i == 108 && flag == 0) {
				goodGuess = 1;
				//printf("\ngood guess!\n");
		
		//putting non-dup computers guesses into an array so it doesn't guess the same spot twice
		comGuesses[guessCount] = guess;
		guessCount++;

				return TRUE;
			}
		}
		
	}
}

int computerDirectionHandling(int checkingHits) {
		int guess = 0;
		int guessFlag = 0;
		int dirFlag = 0;
		int i = 0;
		int corner;
		int wall;
		
		if (!changeDir) {//if your not changing the direction of guesses then continue from the last guess
			//printf("\n$$in hit a ship case, going in direction %d, last hit was %d\n$$", currentDir, lastHit);
			
			switch (currentDir) {
				case LEFT:
					guess = lastHit - 1;
					
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
					
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
					
					} else {
						//printf("\n##GUESS WAS ALREADY GUESSED TRY A DIFFERENT DIRECTION##\n");
						//since it was a direction that was guessed put it in the guessed dir arr
						//guessedDirections[dirCount] = currentDir;
						//dirCount++;
						
						changeDir = TRUE; //this direction has a spot that was already guessed, change direction and try again
						computerDirectionHandling(FALSE);
					}
					
					//return guess;
					break;
					case RIGHT:
						guess = lastHit + 1;
					
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
					
						if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
					
					} else {
						changeDir = TRUE; //this direction has a spot that was already guessed, change direction and try again
						computerDirectionHandling(FALSE);
					}
					//return guess;
						break;
					case UP:
						guess = lastHit - 11;
						
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
						
					} else {
						changeDir = TRUE; //this direction has a spot that was already guessed, change direction and try again
						computerDirectionHandling(FALSE);
					}
					//return guess;
						break;
					case DOWN:
						guess = lastHit + 11;
					
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						
							if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						return guess;
					} else {
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
						
					} else {
						changeDir = TRUE; //this direction has a spot that was already guessed, change direction and try again
						computerDirectionHandling(FALSE);
					}
					
					//return guess;
						break;
						
			}
			
		} else if (changeDir) { //if it was a miss then try a new direction otherwise just guess the same
		//seeing the current guessed directions
		/*
		for (i = 0; i < 4; i++) {
			printf("\n%%%%CURRENT DIRECTION ARRAY (right before changing directions) --> ");
			printf("%d ", guessedDirections[i]);
			printf("%%%%\n");
		}
		*/	
			
			dirFlag = 1;
			
			//making sure they don't guess the same direction
			while (dirFlag) {
			dirFlag = 0;
			
			
			//determine whether the initial hit is by a wall a corner or neither
			
			corner = cornerCheckAndHandling(); //sees if the inital hit was a corner and sets the current direction to a valid direction based on which corner
			wall = wallCheckAndHandling(); //checks if the inital hit was a wall and sets the current direction to a valid direction based on which wall
			
			/*
			if (corner) {
			printf("initalHit WAS a corner!");	
			} 
			
			if (wall) {
				printf("initialHit WAS a wall!");
			}
			*/
			
			if (!corner && !wall) {
			currentDir = getRand(0, 3);//if it's not a corner or wall you can guess any direction
		}
		
			//seeing if they already guessed a direction
			for (i = 0; i < 4; i++) {
			if (currentDir == guessedDirections[i]) {
				//printf("\n##bad direction dir choice = %d is same as direction guessed at guesseDirections[i] = %d##\n", currentDir, i);
				dirFlag = 1;
			} else if (i == 3 && dirFlag != 1) {
				//printf("\n##good choice guessed direction %d, does not equal a-ything in array!##\n", currentDir);
				guessedDirections[dirCount] = currentDir;
			}
		}
	}
		dirFlag = 1;
		dirCount++;
			
		//if your changing the direction of guesses then use the initial hit as a pivot because it's on of four directions from that point
		//printf("\nMISS! TIME TO CHANGE DIRECTION\n");
			switch (currentDir) {
				case LEFT:
					guess = initialHit - 1;
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						//printf("\n###location %d was NOT taken!###\n", guess);
						
						//making sure the guess is on the board
		            if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {
						changeDir = FALSE;//done changing direction
						return guess;
						} else {//if it's not on the board change directions
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
						}
						
					} else {
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
					//return guess;
					break;
					case RIGHT:
						guess = initialHit + 1;
			
						if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						//printf("\n###location %d was NOT taken!###\n", guess);
						
						//making sure the guess is on the board
					    if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {
						changeDir = FALSE;//done changing direction
						return guess;
						} else {//if it's not on the board change directions
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
						}
						
					} else {
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
					
					//return guess;
						break;
					case UP:
						guess = initialHit - 11;
						
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						//printf("\n###location %d was NOT taken!###\n", guess);
						
						//changeDir = FALSE; //done changing direction
						//return guess;
						
						//making sure the guess is on the board
						if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {
						changeDir = FALSE;//done changing direction
						return guess;
						} else {//if it's not on the board change directions
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
						}
						
					} else {
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
					
					//return guess;
						break;
					case DOWN:
						guess = initialHit + 11;
						
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						
						//making sure the guess is on the board
						if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {
						changeDir = FALSE;//done changing direction
						return guess;
						} else {//if it's not on the board change directions
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
						}
						
					} else {
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
					
						break;
			}
		}
	

			

		//return guess;
}


void playerRandomSetup() {
	int i;
	int success = 0;
	int vertOrHorztlShip;
//if 5 hole ship vertical test
//computerBoatPlacer(1, 6, 10, 0);

//if 5 hole ship horizontal test

//repeat until all the boats are placed

for (i = 1; i <= 5; i++) {
	
	//boat 1 (5 holes) setting valid placement for vert or horizontal cases
	switch(i) {
		case 1:

			do {
			vertOrHorztlShip = getRand(0, 1); //allowing for random orientation of boats for every boat
			
			if(vertOrHorztlShip) {//horizontal
			do {
success = playerRandomBoatPlacer(i, 10, 6, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = playerRandomBoatPlacer(i, 6, 10, vertOrHorztlShip);
}while(success == 0);
			}
			
			} while(success == 0);
			break;
		
			case 2: //2nd boat (4 holes)
			
			do {
			vertOrHorztlShip = getRand(0, 1);
			
					if(vertOrHorztlShip) {//horizontal
			do {
success = playerRandomBoatPlacer(i, 10, 7, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = playerRandomBoatPlacer(i, 7, 10, vertOrHorztlShip);
}while(success == 0);
			}
			} while(success == 0);
			break;
			
			case 3: //3nd boat (3 holes)
			do {
			vertOrHorztlShip = getRand(0, 1);
			
					if(vertOrHorztlShip) {//horizontal
			do {
success = playerRandomBoatPlacer(i, 10, 8, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = playerRandomBoatPlacer(i, 8, 10, vertOrHorztlShip);
}while(success == 0);
			}
			}while(success == 0);
			break;

			case 4: //4th boat (3 holes)
			
				do {
			vertOrHorztlShip = getRand(0, 1);
					
					if(vertOrHorztlShip) {//horizontal
			do {
success = playerRandomBoatPlacer(i, 10, 8, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = playerRandomBoatPlacer(i, 8, 10, vertOrHorztlShip);
}while(success == 0);
			}

} while(success == 0);			
			break;	
			
			case 5: //5th boat (2 holes)
			
				do {
			vertOrHorztlShip = getRand(0, 1);
			
					if(vertOrHorztlShip) {//horizontal
			do {
success = playerRandomBoatPlacer(i, 10, 9, vertOrHorztlShip);
}while(success == 0);
			} else if (!vertOrHorztlShip) {//vertical
							do {
success = playerRandomBoatPlacer(i, 9, 10, vertOrHorztlShip);
}while(success == 0);
			}
			
			}while(success == 0);
			break;		
			
}
}
	//check to see what the list of spots is for debugging
			/*
			for (i=0; i<=20; i++) {
				printf("%d", playerShipsSpotsNoChange[i]);
			}
			*/
}

int playerRandomBoatPlacer(int ship, int rowMax, int rowIndexMax, int vertOrHorztlShip) {
//	int vertOrHorztlShip = getRand(0, 1);
	int row;
	int rowIndex;
	int shipCount;
	int i;
	int j;
	int k;
	int l;
	int matchCount = 0; //for if boats are overlapping
	
	int matches[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	//flag if spot is taken
	int validPlacement = 0;
	
	//ship being setup
	int shipHoles;
	
		switch (ship) {
		case 1:
			shipHoles = 5;
			break;
			case 2:
				shipHoles = 4;
				break;
				case 3:
					shipHoles = 3;
					break;
					case 4:
					shipHoles = 3;
					break;
					case 5:
					shipHoles = 2;
					break;
	}
	
	row = getRand(1, rowMax);
	
	//mapping input to board
	//rowIndex is the last index it can be for the row selected
	rowIndexMax += (11*(row-1));
	
	
		switch (row) {
		case 1://row a
			rowIndex = getRand(a1, rowIndexMax);
			break;
		case 2://row b
			rowIndex = getRand(b1, rowIndexMax);
			break;
		case 3:// row c
			rowIndex = getRand(c1, rowIndexMax);
			break;
		case 4:// row d
		rowIndex = getRand(d1, rowIndexMax);
			break;
		case 5:// row e
		rowIndex = getRand(e1, rowIndexMax);
			break;	
		case 6:// row f
		rowIndex = getRand(f1, rowIndexMax);
			break;
		case 7:// row g
		rowIndex = getRand(g1, rowIndexMax);
			break;
		case 8:// row h
		rowIndex = getRand(h1, rowIndexMax);
			break;
		case 9:// row i
		rowIndex = getRand(i1, rowIndexMax);
			break;
		case 10:// row j
		rowIndex = getRand(j1, rowIndexMax);
			break;
	} 
		
		//display to see if this thing works
		if (!vertOrHorztlShip) {
		for (i = rowIndex; i < rowIndex+(shipHoles*11); i+=11) {
		board[i] = 88;

		
		//just put them in a big list
		playerShipsSpotsNoChange[(((i-rowIndex)+1)/11)+1+(shipHoleSum-1)] = i;
		
		}
		display(0);
	} else if(vertOrHorztlShip) {
		for (i = rowIndex; i < (rowIndex+shipHoles); i++) {
		board[i] = 88;
		
		//for checking what spot
		//printf("(horizontal) current indece %d", (i-rowIndex)+(shipHoleSum-1));
		
		//just put them in a big list 
		playerShipsSpotsNoChange[(i-rowIndex)+1+(shipHoleSum-1)] = i;
		}
		display(0);
	}	
		
//FINAL BOAT CHECK
//checking if the current boat was placed in a spot where there already was a boat
if(shipHoleSum >= 5) {//checking after first ship was placed
for (i = shipHoleSum; i <= shipHoleSum+(shipHoles-1); i++) { //current ship holes

for (j = 0; j < shipHoleSum; j++) { //checking previous ship holes	
	if (playerShipsSpotsNoChange[i] == playerShipsSpotsNoChange[j]) {
		matches[matchCount] = playerShipsSpotsNoChange[i];
		matchCount++;
	}
	
}

}
}


int flag; //for checking if it should put a spot back
if (matchCount != 0) {
		//if it's a match put 0's back and place again
	if (!vertOrHorztlShip) {//vertical
		for (k = rowIndex; k < rowIndex+(shipHoles*11); k+=11) {
		//don't get rid of spots for previous ships
		for(i = 0; i < matchCount; i++) {
		if (k == matches[i]) {
			flag = 1;
		//printf("\n!----k spot %d, matches spot %d (at i = %d)----!\n", k, matches[i], i);
		} 
	}
		//if it's not a match
		if (!flag) {
		//printf("\n not a match put 0 back at spot %d \n", k);
		board[k] = 48;
		}
		//printf("\nk is currently %d\n", k);
		flag = 0;
}
		display(0);
		return 0; //spot already taken-
	} else if(vertOrHorztlShip) {
		for (k = rowIndex; k < (rowIndex+shipHoles); k++) {//horizontal
	for(i = 0; i < matchCount; i++) {
		if (k == matches[i]) {
		flag = 1;
		}
	}
	//if it's not a match
	if (!flag) {
		//printf("\n not a match put 0 back at spot %d \n", k);
		board[k] = 48;
	}
	
	flag = 0;
}
		display(0);
		return 0; //spot already taken
}
}

shipHoleSum += shipHoles;

//printf("\nshipHoleSum = %d\n", shipHoleSum);
return 1; //saying it worked for testing
}

int possibleInitHitHandling(int check, int shipSpotsToRemove) {
	int flag = 0;
	int i = 0;
	int j = 0;
	
		if (check) {//seeing if array is cleared, then all spots are taken care of and it is sunk
		
		return removeHitsThatWerePartOfSunkShip(shipSpotsToRemove);
		
		} else if (!check) {//handle the next hit location that was not part of a sunk ship, treat it like the initial location
		
		//if every directions been tried for a certain point reset it and move to the next possible hit
		if (guessedDirections[0] != -1 && guessedDirections[1] != -1 && guessedDirections[2] != -1 && guessedDirections[3] != -1) {
			//printf("EVERY DIRECTION TRIED RESETTING DIRECTION ARRAY");
			for (i = 0; i < 4; i++) {
				guessedDirections[i] = -1;
				currentHitBeingChecked++;
			}
		}
		
		if (guessedDirections[0] == -1 && guessedDirections[1] == -1 && guessedDirections[2] == -1 && guessedDirections[3] == -1) {
			//printf("DIRECTION ARRAY CLEAR NEW INITIAL POINT AT %d (hitCount = %d)", possibleInitHits[hitCount], hitCount);
			initialHit = possibleInitHits[hitCount];
		}
		
		
		}
}

int checkingHitsDirectionHandling() {
		int guess = 0;
		int dirFlag = 0;
		int i = 0;
		
		//seeing the current guessed directions
	    //displayDirArr();
	
		if (!changeDir) {//if your not changing the direction of guesses then continue from the last guess
			switch (currentDir) {
				case LEFT:
					guess = lastHit - 1;
					
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
					
					//making sure it's on the board
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
					
					} else {
						changeDir = TRUE; //this direction has a spot that was already guessed, change direction and try again
						checkingHitsDirectionHandling();
					}
					
					//return guess;
					break;
					case RIGHT:
						guess = lastHit + 1;
					
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
						
					} else {					
						changeDir = TRUE; //this direction has a spot that was already guessed, change direction and try again
						checkingHitsDirectionHandling();
					}
					//return guess;
						break;
					case UP:
						guess = lastHit - 11;
						
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						
					//making sure it's on the board
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
						
					} else {
						//seeing the current guessed directions
		                //displayDirArr();
						
						changeDir = TRUE; //this direction has a spot that was already guessed, change direction and try again
						checkingHitsDirectionHandling();
					}
					//return guess;
						break;
					case DOWN:
						guess = lastHit + 11;
					
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
						
					} else {
						//seeing the current guessed directions
                        displayDirArr();
                        
						changeDir = TRUE; //this direction has a spot that was already guessed, change direction and try again
						checkingHitsDirectionHandling();
					}
					
					//return guess;
						break;
						
			}
			
		} else if (changeDir) { //if it was a miss then try a new direction otherwise just guess the same
			dirFlag = 1;
			
			//making sure they don't guess the same direction
			while (dirFlag) {
				
			//if every directions been tried reset the array and return 0, indicating that a new spot should be tried.
			int flag = 0;
			for (i = 0; i < 4; i++) {
				if (guessedDirections[i] == -1) {
					flag = 1;
				}
			}
			if (flag == 0) {
				return FALSE;
			}
			
			dirFlag = 0;
			currentDir = getRand(0, 3);
			
			//seeing if they already guessed a direction
			for (i = 0; i < 4; i++) {
			if (currentDir == guessedDirections[i]) {
				//printf("\n##bad direction dir choice = %d is same as direction guessed at guessedDirections[i] = %d##\n", currentDir, i);
				dirFlag = 1;
			} else if (i == 3 && dirFlag != 1) {
				//printf("\n##good choice guessed direction %d, does not equal anything in array!##\n", currentDir);
				guessedDirections[dirCount] = currentDir;
			}
		}
	}
		dirFlag = 1;
		dirCount++;
			
		//if your changing the direction of guesses then use the initial hit as a pivot because it's on of four directions from that point
		//printf("\nMISS! TIME TO CHANGE DIRECTION\n");
			switch (currentDir) {
				case LEFT:
					guess = initialHit - 1;
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						//printf("\n###location %d was NOT taken!###\n", guess);
					
					//making sure it's on the board
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						changeDir = FALSE;
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}

					} else {						
						changeDir = TRUE;
						checkingHitsDirectionHandling();
					}
					//return guess;
					break;
					case RIGHT:
						guess = initialHit + 1;
			
						if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						//printf("\n###location %d was NOT taken!###\n", guess);
						
					//making sure it's on the board
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						changeDir = FALSE;
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
		
					} else {
						//seeing the current guessed directions
                        displayDirArr();
							
						changeDir = TRUE;
						checkingHitsDirectionHandling();
					}
					
					//return guess;
						break;
					case UP:
						guess = initialHit - 11;
						
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						//printf("\n###location %d was NOT taken!###\n", guess);

					//making sure it's on the board
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						changeDir = FALSE;
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}

					} else {
						changeDir = TRUE;
						checkingHitsDirectionHandling();
					}
					
					//return guess;
						break;
					case DOWN:
						guess = initialHit + 11;
						
					if (computerGuessAndOrCheck(TRUE, guess)) { //if the spot is not taken return the guess, otherwise guess a different direction
						//printf("\n###location %d was NOT taken!###\n", guess);
						
					//making sure it's on the board
					if (guess >= a1 && guess <= j10 && guess != 11 && guess != 22 && guess != 33 && guess != 44 && guess != 55 && guess != 66 && guess != 77 && guess != 88 && guess != 99) {//making sure the guess is on the board
						changeDir = FALSE;
						return guess;
					} else {
						//printf("GUESS WAS OFF THE BOARD");
						changeDir = TRUE;
						computerDirectionHandling(FALSE);
					}
						
					} else {						
						changeDir = TRUE;
						checkingHitsDirectionHandling();
					}
						
					//return guess;
						break;
				
					//changeDir = FALSE; //done changing direction
			}
		}
}

int organizeHitArray() {
	//int arr[10] = {};
	int i = 0;
	int j = 0;
	int k = 0;
	int flag = 0;
	int numCount = 0;
	
	//determining how many numbers need to be sorted
		for (i = 0; i < 50; i++) {
		if (possibleInitHits[i] != -1) {
			numCount++;
		}
	}
	
	//organizing the array
	for (i = 0; i < 50; i++) {
	
		if (possibleInitHits[i] == -1) {
			for (j = 49; j >= 1; j--) {
				if (possibleInitHits[j] != -1) {
					possibleInitHits[i] = possibleInitHits[j];
					possibleInitHits[j] = -1;
					break;
				}
			}
		}
		
		
		//check if it's organized
		flag = 0;
		for (k = 0; k < numCount; k++) {
			if (possibleInitHits[k] == -1) {
				flag = 1;
			}
		}
		
		if (!flag) {
			//printf("\n\narray is sorted!\n\n");//array is sorted
			break;
		}	
	}
}

int removeHitsThatWerePartOfSunkShip(int shipSpotsToRemove) {
	int i = 0;
	int flag = 0;
			
			//removing the hits
			for (i = 0; i < 50; i++) {
				switch (shipSpotsToRemove) {
				case 1://remove the 5 hole ship because it was sunk
				//printf("\n\n5 HOLE SHIP WAS SUNK SO REMOVE HITS THAT WERE PART OF THAT SHIP\n\n");
				if (possibleInitHits[i] == playerShipsSpotsNoChange[0] || possibleInitHits[i] == playerShipsSpotsNoChange[1] || possibleInitHits[i] == playerShipsSpotsNoChange[2] || possibleInitHits[i] == playerShipsSpotsNoChange[3] || possibleInitHits[i] == playerShipsSpotsNoChange[4]){
					possibleInitHits[i] = -1;
					hitCount--;
				}
				break;
					case 2://remove the 4 hole ship because it was sunk
				//printf("\n\n4 HOLE SHIP WAS SUNK SO REMOVE HITS THAT WERE PART OF THAT SHIP\n\n");
				if (possibleInitHits[i] == playerShipsSpotsNoChange[5] || possibleInitHits[i] == playerShipsSpotsNoChange[6] || possibleInitHits[i] == playerShipsSpotsNoChange[7] || possibleInitHits[i] == playerShipsSpotsNoChange[8]){
					possibleInitHits[i] = -1;
					hitCount--;
				}
				break;
					case 3://remove the 3 hole ship because it was sunk
				//printf("\n\n3 HOLE SHIP WAS SUNK SO REMOVE HITS THAT WERE PART OF THAT SHIP\n\n");
				if (possibleInitHits[i] == playerShipsSpotsNoChange[9] || possibleInitHits[i] == playerShipsSpotsNoChange[10] || possibleInitHits[i] == playerShipsSpotsNoChange[11]){
					possibleInitHits[i] = -1;
					hitCount--;
				}
				break;
					case 4://remove the 3 hole ship because it was sunk
				//printf("\n\n3 HOLE SHIP WAS SUNK SO REMOVE HITS THAT WERE PART OF THAT SHIP\n\n");
				if (possibleInitHits[i] == playerShipsSpotsNoChange[12] || possibleInitHits[i] == playerShipsSpotsNoChange[13] || possibleInitHits[i] == playerShipsSpotsNoChange[14]){
					possibleInitHits[i] = -1;
					hitCount--;
				}
				break;
				case 5://remove the 2 hole ship because it was sunk
				//printf("\n\n2 HOLE SHIP WAS SUNK SO REMOVE HITS THAT WERE PART OF THAT SHIP\n\n");
				if (possibleInitHits[i] == playerShipsSpotsNoChange[15] || possibleInitHits[i] == playerShipsSpotsNoChange[16]){
					possibleInitHits[i] = -1;
					hitCount--;
				}
				break;
				
			}
				}
				
				//organizing the array
				organizeHitArray();
			
			//checking to see if there are any spots left to check
			for (i = 0; i < 50; i++) {
				if (possibleInitHits[i] != -1) {
				flag = 1;
				}
				}
			
			if (!flag) {
				//printf("array is clear!");
				return 1; //no locations left to check
			} else if (flag) {
				//printf("check spots!");
				return 0; //theres spots left in the array to check
			}
			
}

void displayDirArr() {
	int i = 0;
	
	/*
		printf("\n\n$$$CURRENT DIRECTION ARRAY (in checkingHitsDirectionHandling)--> ");
		for (i = 0; i < 4; i++) {
			printf("%d ", guessedDirections[i]);
		}
		printf("$$$\n");
	*/
}

int cornerCheckAndHandling() {
			int corner = 0;
			int topLeft = 0;
			int topRight = 0;
			int bottomLeft = 0;
			int bottomRight = 0;
			int pickingCornerDirection = 0;
			
				if (initialHit == 1 || initialHit == 10 || initialHit == 100 || initialHit == 110) {
				corner = TRUE;
				
				//check which corner 
				switch (initialHit) {
					case 1:
						//printf("\n\ninitialHit is the top left!\n\n");
						topLeft = TRUE;
						break;
							case 10:
								//printf("\n\ninitialHit is the top right!\n\n");
								topRight = TRUE;
						break;
							case 100:
								//printf("\n\ninitialHit is the bottom left!\n\n");
								bottomLeft = TRUE;
						break;
							case 110:
								//printf("\n\ninitialHit is the bottom right!\n\n");
								bottomRight = TRUE;
						break;
				}
			
				
			//if it's on a corner, set the direction accordingly
			if (topLeft) {
				
				pickingCornerDirection = getRand(0, 1);//it's going to be right or down from the top left corner
				if (pickingCornerDirection) {
					currentDir = 1; //go to the right of the corner
				} else if (!pickingCornerDirection) {
					currentDir = 3; //go down from the corner
				}				
			} else if (topRight) {
				
				pickingCornerDirection = getRand(0, 1);//it's going to be left or down from the top left corner
				if (pickingCornerDirection) {
					currentDir = 0; //go to the left of the corner
				} else if (!pickingCornerDirection) {
					currentDir = 3; //go down from the corner
				}
			} else if (bottomLeft) {
				
				pickingCornerDirection = getRand(0, 1);//it's going to be right or up from the top left corner
				if (pickingCornerDirection) {
					currentDir = 1; //go to the right of the corner
				} else if (!pickingCornerDirection) {
					currentDir = 2; //go up from the corner
				}				
			} else if (bottomRight) {
				
				pickingCornerDirection = getRand(0, 1);//it's going to be left or up from the top left corner
				if (pickingCornerDirection) {
					currentDir = 0; //go to the left of the corner
				} else if (!pickingCornerDirection) {
					currentDir = 2; //go up from the corner
				}
			}
			
			return 1; //it was a corner
			
	} else if (!corner) {
		return 0; //was not a corner
	}
}

int wallCheckAndHandling() {
	int wall = 0;
	int whichWall = -1;
	int wallDirectionDecider = 0;
	
	//top wall a2-a9
	if (initialHit == a2 || initialHit == a3 || initialHit == a4 || initialHit == a5 || initialHit == a6 || initialHit == a7 || initialHit == a8 || initialHit == a9) {
	wall = 1;
	whichWall = 0;
	}
	
	//left side wall b1-i1
	else if (initialHit == b1 || initialHit == c1 || initialHit == d1 || initialHit == e1 || initialHit == f1 || initialHit == g1 || initialHit == h1 || initialHit == i1) {
	wall = 1;
	whichWall = 1;
	}
	
	//right side wall b10-i10
	else if (initialHit == b10 || initialHit == c10 || initialHit == d10 || initialHit == e10 || initialHit == f10 || initialHit == g10 || initialHit == h10 || initialHit == i10) {
	wall = 1;
	whichWall = 2;
	}
	
	//bottom wall j2-j9
	else if (initialHit == j2 || initialHit == j3 || initialHit == j4 || initialHit == j5 || initialHit == j6 || initialHit == j7 || initialHit == j8 || initialHit == j9) {
	wall = 1;
	whichWall = 3;
	}
	
	if (wall) {
		switch (whichWall) {
			case 0://top wall can either go left, right, or down
				wallDirectionDecider = getRand(1, 3);
				
				switch (wallDirectionDecider) {
				case 1:
					currentDir = LEFT;
					break;
					case 2:
						currentDir = RIGHT;
						break;
						case 3:
							currentDir = DOWN;
							break;
				}
				
				break;
				case 1://left wall can either go right, up, or down
				wallDirectionDecider = getRand(1, 3);
				
				switch (wallDirectionDecider) {
				case 1:
					currentDir = RIGHT;
					break;
					case 2:
						currentDir = UP;
						break;
						case 3:
							currentDir = DOWN;
							break;
				}
					
				break;
				case 2://right wall can either go left, up, or down
				wallDirectionDecider = getRand(1, 3);
				
				switch (wallDirectionDecider) {
				case 1:
					currentDir = LEFT;
					break;
					case 2:
						currentDir = UP;
						break;
						case 3:
							currentDir = DOWN;
							break;
				}
					
				break;
				case 3://bottom wall can either go left, right, or up
				wallDirectionDecider = getRand(1, 3);
				
				switch (wallDirectionDecider) {
				case 1:
					currentDir = LEFT;
					break;
					case 2:
						currentDir = RIGHT;
						break;
						case 3:
							currentDir = UP;
							break;
				}
				break;
		}
		return 1; //spot was a wall	
	} else if (!wall) {
		return 0; //not a wall
	} 
	
	
}


const char* convertBoardLocation2String(int location) {
	switch (location) {		
		//row a
		case 1:
		return "a1";
		break;
		case 2:
		return "a2";
		break;
		case 3: 
		return "a3";
		break;
		case 4: 
		return "a4";
		break;
		case 5: 
		return "a5";
		break;
		case 6:
		return "a6"; 
		break;
		case 7:
		return "a7"; 
		break;
		case 8:
		return "a8"; 
		break;
		case 9: 
		return "a9";
		break;
		case 10: 
		return "a10";
		break;
	
		//row b
		case 12:
		return "b1"; 
		break;
		case 13: 
		return "b2";
		break;
		case 14:
		return "b3"; 
		break;
		case 15: 
		return "b4";
		break;
		case 16: 
		return "b5";
		break;
		case 17: 
		return "b6";
		break;
		case 18: 
		return "b7";
		break;
		case 19: 
		return "b8";
		break;
		case 20: 
		return "b9";
		break;
		case 21: 
		return "b10";
		break;
	
		//row c
		case 23:
		return "c1";
		break;
		case 24: 
		return "c2";
		break;
		case 25:
		return "c3"; 
		break;
		case 26: 
		return "c4";
		break;
		case 27: 
		return "c5";
		break;
		case 28: 
		return "c6";
		break;
		case 29: 
		return "c7";
		break;
		case 30: 
		return "c8";
		break;
		case 31: 
		return "c9";
		break;
		case 32: 
		return "c10";
		break;
		
		//row d
		case 34: 
		return "d1";
		break;
		case 35:
		return "d2"; 
		break;
		case 36:
		return "d3"; 
		break;
		case 37:
		return "d4"; 
		break;
		case 38: 
		return "d5";
		break;
		case 39: 
		return "d6";
		break;
		case 40: 
		return "d7";
		break;
		case 41: 
		return "d8";
		break;
		case 42: 
		return "d9";
		break;
		case 43: 
		return "d10";
		break;

		//row e
		case 45: 
		return "e1";
		break;
		case 46:
		return "e2";
		break;
		case 47:
		return "e3"; 
		break;
		case 48:
		return "e4"; 
		break;
		case 49: 
		return "e5";
		break;
		case 50:
		return "e6"; 
		break;
		case 51:
		return "e7"; 
		break;
		case 52:
		return "e8"; 
		break;
		case 53:
		return "e9"; 
		break;
		case 54:
		return "e10"; 
		break;
		
		//row f
		case 56:
		return "f1"; 
		break;
		case 57:
		return "f2";
		break;
		case 58:
		return "f3"; 
		break;
		case 59:
		return "f4"; 
		break;
		case 60:
		return "f5"; 
		break;
		case 61:
		return "f6"; 
		break;
		case 62:
		return "f7"; 
		break;
		case 63:
		return "f8"; 
		break;
		case 64:
		return "f9"; 
		break;
		case 65:
		return "f10"; 
		break;

		//row g
		case 67:
		return "g1";
		break;
		case 68: 
		return "g2";
		break;
		case 69:
		return "g3"; 
		break;
		case 70:
		return "g4"; 
		break;
		case 71:
		return "g5"; 
		break;
		case 72:
		return "g6"; 
		break;
		case 73:
		return "g7"; 
		break;
		case 74:
		return "g8"; 
		break;
		case 75:
		return "g9"; 
		break;
		case 76:
		return "g10"; 
		break;
		
		//row h
		case 78:
		return "h1"; 
		break;
		case 79:
		return "h2";
		break;
		case 80: 
		return "h3";
		break;
		case 81:
		return "h4"; 
		break;
		case 82:
		return "h5"; 
		break;
		case 83:
		return "h6"; 
		break;
		case 84:
		return "h7"; 
		break;
		case 85:
		return "h8"; 
		break;
		case 86:
		return "h9"; 
		break;
		case 87:
		return "h10";
		break;

		//row i
		case 89:
		return "i1"; 
		break;
		case 90:
		return "i2"; 
		break;
		case 91:
		return "i3"; 
		break;
		case 92:
		return "i4"; 
		break;
		case 93:
		return "i5";
		break;
		case 94:
		return "i6"; 
		break;
		case 95:
		return "i7"; 
		break;
		case 96:
		return "i8"; 
		break;
		case 97:
		return "i9"; 
		break;
		case 98:
		return "i10"; 
		break;
		
		//row j
		case 100:
		return "j1";
		break;
		case 101:
		return "j2";
		break;
		case 102:
		return "j3";
		break;
		case 103:
		return "j4"; 
		break;
		case 104:
		return "j5"; 
		break;
		case 105:
		return "j6"; 
		break;
		case 106:
		return "j7"; 
		break;
		case 107:
		return "j8"; 
		break;
		case 108:
		return "j9"; 
		break;
		case 109:
		return "j10"; 
		break;
	}
}

void mainMenu() {
//title border top
printf("####################################################################################\n");		
printf("#  ######     #    ####### ####### #       #######     #####  #     # ### ######   #\n");
printf("#  #     #   # #      #       #    #       #          #     # #     #  #  #     #  #\n");
printf("#  #     #  #   #     #       #    #       #          #       #     #  #  #     #  #\n");
printf("#  ######  #     #    #       #    #       #####       #####  #######  #  ######   #\n");
printf("#  #     # #######    #       #    #       #                # #     #  #  #        #\n");
printf("#  #     # #     #    #       #    #       #          #     # #     #  #  #        #\n");
printf("#  ######  #     #    #       #    ####### #######     #####  #     # ### #        #\n");
printf("####################################################################################\n");		

printf("By: Max Anderson 2021\n\n");

	system("pause");
	system("cls");
}
