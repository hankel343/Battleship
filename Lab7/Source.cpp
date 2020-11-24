#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum orientation {UP, DOWN, LEFT, RIGHT};

enum shiptype { DESTROYER, SUBMARINE, CRUSIER, BATTLESHIP, CARRIER };

void ComputerSetUp(char guessGrid[][10], char shipGrid[][10]);

void UserSetUp(char guessGrid[][10], char shipGrid[][10]);

void Instructions();

void ComputerTurn(char shipGrid[][10], char guessGrid[][10], int& computerHits);

void UserTurn(char shipGrid[][10], char guessGrid[][10], int& userHits);

bool Fire(char shipGrid[][10], char computerGuessGrid[][10], int xcoordinate, int ycoordinate);

void GenerateComputerGrid(char waterArray[][10]);

void InitializeDefaultBoard(char emptyArray[][10]);

void UserShipPlacement(char waterArray[][10]);

void ValidateUserInput(char waterArray[][10], int& shipLength);

bool IsValidOrientation(char waterArray[][10], int row, int column, string shipOrientation, int shipLength);

void PrintBoard(char array[][10]);

void AddShipVertical(char array[][10], int shipLength);

void AddShipHorizontal(char array[][10], int shipLength);

bool IsComputerShipOverlap(char array[][10], int ranRowsorColumns, int shipLength, orientation shipDirection);

bool IsUserShipOverlap(char array[][10], int row, int column, int shipLength, orientation shipDirection);

bool IsOutOfBounds(int row, int column, int shipLength, orientation shipDirection);

void PlaceUserShip(char array[][10], int row, int column, int shipLength, string shipOrientation);

void OutOfBoundsMessage();

void InvalidInputMessage();

void OverlapMessage();

void UpdatedBoardMessage();

int main()
{
	srand(unsigned int(time(NULL)));

	char computerGuessGrid[10][10];
	char computerShipGrid[10][10];

	char userGuessGrid[10][10];
	char userShipGrid[10][10];

	bool isNewGame;
	bool isEndOfGame;
	int numOfGames = 1;

	int userHits = 0;
	int computerHits = 0;
	do
	{
		if (numOfGames == 1)
		{
			//Instructions();
		}

		isNewGame = false;
		//Initializes and populates computer's board
		ComputerSetUp(computerGuessGrid, computerShipGrid);

		//Initializes and allows user to place their ships
		UserSetUp(userGuessGrid, userShipGrid);

		isEndOfGame = false;

		do
		{
			ComputerTurn(userShipGrid, computerGuessGrid, computerHits);

			UserTurn(computerShipGrid, userGuessGrid, userHits);

			if (computerHits == 17 || userHits == 17)
			{
				isEndOfGame = true;
			}


		} while (!isEndOfGame);
	} while (isNewGame);
	

	return 0;
}

void ComputerSetUp(char guessGrid[][10], char shipGrid[][10])
{

	//Sets empty 10 x 10 array to water ('~') for computer guess grid
	InitializeDefaultBoard(guessGrid);

	//Sets empty 10 x 10 array to water ('~')
	InitializeDefaultBoard(shipGrid);

	//Randomly select 5 places on the water grid to place a ship
	GenerateComputerGrid(shipGrid);
}

void UserSetUp(char guessGrid[][10], char shipGrid[][10])
{

	//Initialize user's guess grid to water ('~')
	InitializeDefaultBoard(guessGrid);

	//Initialize user's ship grid to water ('~')
	InitializeDefaultBoard(shipGrid);

	//Allows user to place ships and validates ship positions at the same time
	UserShipPlacement(shipGrid);
}

void Instructions()
{

}

void ComputerTurn(char shipGrid[][10], char guessGrid[][10], int& computerHits)
{
	int ranXCoordinate = rand() % 10;
	int ranYCoordinate = rand() % 10;

	if (Fire(shipGrid, guessGrid, ranXCoordinate, ranYCoordinate) == true)
	{
		cout << "\nThe computer landed a hit!\n\n";
		computerHits++;
	}

	cout << "This is the computer's guess grid: \n";
	PrintBoard(guessGrid);
}

void UserTurn(char shipGrid[][10], char guessGrid[][10], int& userHits)
{
	int xcoordinate;
	int ycoordinate;

	cout << "\n\nThis is your guess grid: \n";

	PrintBoard(guessGrid);

	cout << "\n\nEnter the x-coordinate you want to fire on: ";
	cin >> xcoordinate;

	while (!cin || xcoordinate < 1 || xcoordinate > 10)
	{
		cin.clear();
		cin.ignore(1000, '\n');

		InvalidInputMessage();
		cin >> xcoordinate;
	}

	cout << "\n\nEnter the y-coordinate you want to fire on: ";
	cin >> ycoordinate;

	while (!cin || ycoordinate < 1 || ycoordinate > 10)
	{
		cin.clear();
		cin.ignore(1000, '\n');

		InvalidInputMessage();
		cin >> ycoordinate;
	}

	if (Fire(shipGrid, guessGrid, xcoordinate, ycoordinate) == true)
	{
		cout << "\n\nYou landed a hit!\n";
		userHits++;
	}
	else
		cout << "\n\nYou missed!\n";
}

bool Fire(char shipGrid[][10], char guessGrid[][10], int xcoordinate, int ycoordinate)
{
	if (shipGrid[ycoordinate - 1][xcoordinate - 1] == '#')
	{
		guessGrid[ycoordinate - 1][xcoordinate - 1] = 'H';
		return true;
	}
	else
	{
		guessGrid[ycoordinate - 1][xcoordinate - 1] = 'M';
		return false;
	}
}

void UserShipPlacement(char waterArray[][10])
{
	
	

	cout << "The computer has arranged its ships on the grid.\n";
	cout << "You need to do the same with the following board: \n";

	PrintBoard(waterArray);


	int shipLength;
	for (shiptype ship = DESTROYER; ship <= CARRIER; ship = shiptype(ship + 1))
	{
		switch (ship)
		{
		case DESTROYER:
			shipLength = 2;

			cout << "\n\nPlace your destroyer (2 places)";

			ValidateUserInput(waterArray, shipLength);

			UpdatedBoardMessage();
			PrintBoard(waterArray);
			break;

		case SUBMARINE:
			shipLength = 3;

			cout << "\n\nPlace your submarine (3 places)";

			ValidateUserInput(waterArray, shipLength);

			UpdatedBoardMessage();
			PrintBoard(waterArray);
			break;

		case CRUSIER:
			shipLength = 3;

			cout << "\n\nPlace your crusier (3 places)";

			ValidateUserInput(waterArray, shipLength);

			UpdatedBoardMessage();
			PrintBoard(waterArray);
			break;

		case BATTLESHIP:
			shipLength = 4;

			cout << "\n\nPlace your battleship (4 places)";

			ValidateUserInput(waterArray, shipLength);

			UpdatedBoardMessage();
			PrintBoard(waterArray);
			break;

		case CARRIER:
			shipLength = 5;

			cout << "\n\nPlace your carrier (5 places)";

			ValidateUserInput(waterArray, shipLength);

			UpdatedBoardMessage();
			PrintBoard(waterArray);
			break;
		}
	}


}

void InitializeDefaultBoard(char emptyArray[][10])
{
	//Initializes to water '~'
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			emptyArray[i][j] = '~';
		}
	}
}

void PrintBoard(char array[][10])
{
	for (int i = 1; i < 11; ++i)
	{
		//This if-else statement prints the x-axis scale
		if (i == 1) {
			cout << "   " << i << " ";
		}
		else if (i > 1) {
			cout << i << " ";
		}
		
		//This statement prints a end line for the beginning of the array.
		if (i == 10) {
			cout << endl;
		}
			
	}

	for (int i = 0; i < 10; ++i)
	{
		//This if-else block prints the y-axis scale
		if (i < 9)
		{
			cout << i + 1 << "  ";
		}
		else
			cout << i + 1 << " ";
		
		for (int j = 0; j < 10; ++j)
		{

			cout << array[i][j] << ' ';

			if (j == 9)
				cout << endl;
		}
	}
}

void GenerateComputerGrid(char waterArray[][10])
{
	//Generate the five ship types at with random orientations
	for (shiptype ship = DESTROYER; ship <= CARRIER; ship = shiptype(ship + 1))
	{
		//Generate a 1 or 2 randomly to determine to orient verically or horizontally.
		int ranShipOrientation = rand() % 2 + 1;
		int shipLength;

		switch (ship)
		{
		case DESTROYER:

			shipLength = 2;

			if (ranShipOrientation == 1) {
				AddShipVertical(waterArray, shipLength);
			}
			else
				AddShipHorizontal(waterArray, shipLength);
			break;

		case SUBMARINE:

			shipLength = 3;

			if (ranShipOrientation == 1) {
				AddShipVertical(waterArray, shipLength);
			}
			else
				AddShipHorizontal(waterArray, shipLength);
			break;

		case CRUSIER:

			shipLength = 3;

			if (ranShipOrientation == 1) {
				AddShipVertical(waterArray, shipLength);
			}
			else
				AddShipHorizontal(waterArray, shipLength);
			break;

		case BATTLESHIP:

			shipLength = 4;

			if (ranShipOrientation == 1) {
				AddShipVertical(waterArray, shipLength);
			}
			else
				AddShipHorizontal(waterArray, shipLength);
			break;

		case CARRIER:

			shipLength = 5;

			if (ranShipOrientation == 1) {
				AddShipVertical(waterArray, shipLength);
			}
			else
				AddShipHorizontal(waterArray, shipLength);
			break;
		}
	}


}

void AddShipVertical(char array[][10], int shipLength)
{
	bool repeatLoop;
	do
	{
		//Generate a random column index
		int ranColumn = rand() % 10;

		repeatLoop = IsComputerShipOverlap(array, ranColumn, shipLength, UP);

		if (repeatLoop == false) //If no ship is found in the validation read
		{
			for (shipLength; shipLength > 0; --shipLength)
			{
				array[shipLength][ranColumn] = '#';
			}
		}

	} while (repeatLoop);
}

void AddShipHorizontal(char array[][10], int shipLength)
{
	bool repeatLoop;
	do
	{
		//Generate a random row index
		int ranRow = rand() % 10;

		repeatLoop = IsComputerShipOverlap(array, ranRow, shipLength, LEFT);

		if (repeatLoop == false)
		{
			//creates ship horizontally
			for (shipLength; shipLength > 0; --shipLength)
			{
				array[ranRow][shipLength] = '#';
			}
		}
	} while (repeatLoop);

}

bool IsComputerShipOverlap(char array[][10], int ranRowsorColumns, int shipLength, orientation shipDirection)
{
	if (shipDirection == UP) //Verifying if a column for a ship
	{
		//Does initial read of area where a ship will be added to check if a ship is already there.
		for (shipLength; shipLength > 0; --shipLength)
		{
			//Creates a ship vertically 
			if (array[shipLength][ranRowsorColumns] == '#')
			{
				return true;
			}
		}

		return false;
	}
	else if (shipDirection == LEFT) //verifying if a row for a ship
	{
		for (shipLength; shipLength > 0; --shipLength)
		{
			if (array[ranRowsorColumns][shipLength] == '#')
			{
				return true;
			}
		}

		return false;
	}
}

void ValidateUserInput(char waterArray[][10], int& shipLength)
{
	//This bool is a loop control that is set to true if the user has overlapping ships or out-of-bounds ships
	bool isInvalidInput;

	//Identifiers for user input
	int row;
	int column;
	string shipOrientation;

	do
	{
		isInvalidInput = false;

		cout << "\nEnter the starting x-coordinate for your ship: ";
		cin >> column;

		while (!cin || column < 0 || column > 10)
		{
			cin.clear();
			cin.ignore(1000, '\n');

			InvalidInputMessage();
			cin >> column;
		}

		cout << "\nEnter the starting y-coordinate for your ship: ";
		cin >> row;

		while (!cin || row < 0 || row > 10)
		{
			cin.clear();
			cin.ignore(1000, '\n');

			InvalidInputMessage();
			cin >> row;
		}

		cout << "\nEnter the orientation you want your ship to have (\"up\", \"down\", \"left\", or \"right\"): ";
		cin >> shipOrientation;

		//While the first letter of shipOrientation string is NOT equal to U, D, R, or L
		while (toupper(shipOrientation[0]) != 'U' && toupper(shipOrientation[0]) != 'D' && toupper(shipOrientation[0]) != 'L' && toupper(shipOrientation[0]) != 'R') 
		{
			cout << "\n\nInvalid input - input should be one of the following (\"up\", \"down\", \"left\", or \"right\")\a\n";
			cout << "Try again: ";
			cin >> shipOrientation;
		}

		//These are decremented by one from the values the user entered (1 - 10). This way they function as indexes for the gameboard array which has valid indexes of 0 - 9 for the coming function calls.
		row--;
		column--;

		//Checks for out of array bounds or ship overlap
		isInvalidInput = IsValidOrientation(waterArray, row, column, shipOrientation, shipLength);

		if (isInvalidInput == false)
		{

			PlaceUserShip(waterArray, row, column, shipLength, shipOrientation);
		}
		
	} while (isInvalidInput); //If overlap or out-of-array bounds then this function loops until the user enters valid data
}



bool IsValidOrientation(char waterArray[][10], int row, int column, string shipOrientation, int shipLength)
{
	switch (toupper(shipOrientation[0]))
	{
	case 'U':

		if (IsOutOfBounds(row, column, shipLength, UP) == true || IsUserShipOverlap(waterArray, row, column, shipLength, UP) == true)
		{

			OutOfBoundsMessage();
			PrintBoard(waterArray);

			return true;
		}

		return false;

	case 'D':

		if (IsOutOfBounds(row, column, shipLength, DOWN) == true || IsUserShipOverlap(waterArray, row, column, shipLength, DOWN) == true)
		{

			OutOfBoundsMessage();
			PrintBoard(waterArray);

			return true;
		}

		return false;

	case 'L':

		if (IsOutOfBounds(row, column, shipLength, LEFT) == true || IsUserShipOverlap(waterArray, row, column, shipLength, LEFT) == true)
		{

			OutOfBoundsMessage();
			PrintBoard(waterArray);

			return true;
		}

		return false;

	case 'R':

		if (IsOutOfBounds(row, column, shipLength, RIGHT) == true || IsUserShipOverlap(waterArray, row, column, shipLength, RIGHT) == true)
		{

			OutOfBoundsMessage();
			PrintBoard(waterArray);

			return true;
		}

		return false;
	}
}

bool IsUserShipOverlap(char array[][10], int row, int column, int shipLength, orientation shipDirection)
{
	//Limit is used to control the following for loops
	int limit;
	switch (shipDirection)
	{

	case UP:
		limit = row - shipLength;

		for (row; row > limit; --row)
		{
			if (array[row][column] == '#')
				return true;
		}

		return false;

	case DOWN:
		limit = row + shipLength;

		for (row; row <= limit; ++row)
		{
			if (array[row][column] == '#')
				return true;
		}

		return false;

	case LEFT:
		limit = column - shipLength;

		for (column; column > limit; column--)
		{
			if (array[row][column] == '#')
				return true;
		}

		return false;

	case RIGHT:
		limit = column + shipLength;

		for (column; column < limit; column++)
		{
			if (array[row][column] == '#')
				return true;
		}

		return false;
	}
}

bool IsOutOfBounds(int row, int column, int shipLength, orientation shipDirection)
{
	switch (shipDirection)
	{
	case UP:
		if (row - shipLength < -1)
			return true;

		return false;
		
	case DOWN:
		if (row + shipLength > 10)
			return true;

		return false;

	case LEFT:
		if (column - shipLength < -1)
			return true;

		return false;

	case RIGHT:
		if (column + shipLength > 10)
			return true;

		return false;
	}
}

void PlaceUserShip(char array[][10], int row, int column, int shipLength, string shipOrientation)
{
	int limit;

	switch (toupper(shipOrientation[0]))
	{
	case 'U':
		limit = row - shipLength;

		for (row; row > limit; --row)
		{
			array[row][column] = '#';
		}
		break;

	case 'D':
		limit = row + shipLength;

		for (row; row < limit; row++)
		{
			array[row][column] = '#';
		}
		break;

	case 'L':
		limit = column - shipLength;

		for (column; column > limit; --column)
		{
			array[row][column] = '#';
		}
		break;

	case 'R':
		limit = column + shipLength;

		for (column; column < limit; ++column)
		{
			array[row][column] = '#';
		}
		break;
	}

}

void OutOfBoundsMessage()
{
	cout << "\n\n********************************************************************************************************";
	cout << "\nThe coordinates you entered along with the ship orientation are outside of the bounds of the game board.\a\n";
	cout << "Re-enter your ship coordinates with this in mind.\n";
	cout << "********************************************************************************************************\n";
}

void InvalidInputMessage()
{
	cout << "\n************************************************************************\n";
	cout << "Invalid data - your input should be an integer between 1 and 10 inclusive\a\n";
	cout << "************************************************************************\n";
	cout << "Try again: ";
}

void OverlapMessage()
{
	cout << "\n\n*********************************************************************************************************";
	cout << "\nThe coordinates you entered along with the ship orientation have over lap with another one of your ships.\a\n";
	cout << "Re-enter your ship coordinates with this in mind.\n";
	cout << "*********************************************************************************************************\n";
}

void UpdatedBoardMessage()
{
	cout << "\n***********************\n";
	cout << "This is now your board: \n";
	cout << "***********************\n";
}