#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum orientation {UP, DOWN, LEFT, RIGHT};

enum shiptype { DESTROYER, SUBMARINE, CRUSIER, BATTLESHIP, CARRIER };

void ComputerSetUp();

void UserSetUp();

void GenerateComputerGrid(char waterArray[][10]);

void InitializeDefaultBoard(char emptyArray[][10]);

void UserShipPlacement(char waterArray[][10]);

void ValidateUserInput(char waterArray[][10], int& shipLength, int& row, int& column, string& shipOrientation);

void PrintBoard(char array[][10]);

void AddShipVertical(char array[][10], int shipLength);

void AddShipHorizontal(char array[][10], int shipLength);

bool IsComputerShipOverlap(char array[][10], int ranRowsorColumns, int shipLength, orientation shipDirection);

bool IsUserShipOverlap(char array[][10], int row, int column, int shipLength, orientation shipDirection);

bool IsOutOfBounds(int row, int column, int shipLength, orientation shipDirection);

void PlaceUserShip(char array[][10], int row, int column, int shipLength, orientation shipDirection);

void OutOfBoundsMessage();

void InvalidInputMessage();

void OverlapMessage();

void UpdatedBoardMessage();

int main()
{
	srand(unsigned int(time(NULL)));

	ComputerSetUp();

	//User set up
	UserSetUp();

	return 0;
}

void ComputerSetUp()
{
	char computerGuessGrid[10][10];
	char computerShipGrid[10][10];

	//Sets empty 10 x 10 array to water ('~') for computer guess grid
	InitializeDefaultBoard(computerGuessGrid);

	//Sets empty 10 x 10 array to water ('~')
	InitializeDefaultBoard(computerShipGrid);

	//Randomly select 5 places on the water grid to place a ship
	GenerateComputerGrid(computerShipGrid);
}

void UserSetUp()
{
	char userGuessGrid[10][10];
	char userShipGrid[10][10];

	//Initialize user's guess grid to water ('~')
	InitializeDefaultBoard(userGuessGrid);

	//Initialize user's ship grid to water ('~')
	InitializeDefaultBoard(userShipGrid);

	//Allows user to place ships and validates ship positions at the same time
	UserShipPlacement(userShipGrid);
}

void UserShipPlacement(char waterArray[][10])
{
	int shipLength;
	int row;
	int column;
	string shipOrientation;

	cout << "The computer has arranged its ships on the grid.\n";
	cout << "You need to do the same with the following board: \n";

	PrintBoard(waterArray);

	for (shiptype ship = DESTROYER; ship <= CARRIER; ship = shiptype(ship + 1))
	{
		switch (ship)
		{
		case DESTROYER:
			shipLength = 2;

			cout << "\n\nPlace your destroyer (2 places)";

			ValidateUserInput(waterArray, shipLength, row, column, shipOrientation);

			UpdatedBoardMessage();
			PrintBoard(waterArray);
			break;

		case SUBMARINE:
			shipLength = 3;

			cout << "\n\nPlace your submarine (3 places)";

			ValidateUserInput(waterArray, shipLength, row, column, shipOrientation);

			UpdatedBoardMessage();
			PrintBoard(waterArray);
			break;

		case CRUSIER:
			shipLength = 3;

			cout << "\n\nPlace your carrier (3 places)";

			ValidateUserInput(waterArray, shipLength, row, column, shipOrientation);

			UpdatedBoardMessage();
			PrintBoard(waterArray);
			break;

		case BATTLESHIP:
			shipLength = 4;

			cout << "\n\nPlace your battleship (4 places)";

			ValidateUserInput(waterArray, shipLength, row, column, shipOrientation);

			UpdatedBoardMessage();
			PrintBoard(waterArray);
			break;

		case CARRIER:
			shipLength = 5;

			cout << "\n\nPlace your carrier (5 places)";

			ValidateUserInput(waterArray, shipLength, row, column, shipOrientation);

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

void ValidateUserInput(char waterArray[][10], int& shipLength, int& row, int& column, string& shipOrientation)
{
	bool isInvalidInput;

	do
	{
		isInvalidInput = false;

		cout << "\nEnter the starting row coordinate for your ship: ";
		cin >> row;

		while (!cin || row < 0 || row > 10)
		{
			cin.clear();
			cin.ignore(1000, '\n');

			InvalidInputMessage();
			cin >> row;
		}

		cout << "\nEnter the starting column coordinate for your ship: ";
		cin >> column;

		while (!cin || column < 0 || column > 10)
		{
			cin.clear();
			cin.ignore(1000, '\n');

			InvalidInputMessage();
			cin >> column;
		}

		cout << "\nEnter the orientation you want your ship to have (\"up\", \"down\", \"left\", or \"right\"): ";
		cin >> shipOrientation;

		bool isInvalidDirection = false; //Used for following do-while loop if user enters any char other than up, down, left, or right

		do
		{
			switch (toupper(shipOrientation[0]))
			{
			case 'U':

				if (IsOutOfBounds(row - 1, column - 1, shipLength, UP) == true)
				{
					isInvalidInput = true;

					OutOfBoundsMessage();
					PrintBoard(waterArray);
				}

				if (IsUserShipOverlap(waterArray, row - 1, column - 1, shipLength, UP) == true)
				{
					isInvalidInput = true;
					OverlapMessage();
					PrintBoard(waterArray);
				}
					
				if (isInvalidInput == false)
				{
					PlaceUserShip(waterArray, row - 1, column - 1, shipLength, UP);
				}

				break;

			case 'D':

				if (IsOutOfBounds(row - 1, column - 1, shipLength, DOWN) == true)
				{
					isInvalidInput = true;

					OutOfBoundsMessage();
					PrintBoard(waterArray);
				}

				if (IsUserShipOverlap(waterArray, row - 1, column - 1, shipLength, DOWN) == true)
				{
					isInvalidInput = true;

					OverlapMessage();
					PrintBoard(waterArray);
				}
					

				if (isInvalidInput == false)
				{
					PlaceUserShip(waterArray, row - 1, column - 1, shipLength, DOWN);
				}
				break;

			case 'L':

				if (IsOutOfBounds(row - 1, column - 1, shipLength, LEFT) == true)
				{
					isInvalidInput = true;

					OutOfBoundsMessage();
					PrintBoard(waterArray);
				}

				if (IsUserShipOverlap(waterArray, row - 1, column - 1, shipLength, LEFT) == true)
				{
					isInvalidInput = true;

					OverlapMessage();
					PrintBoard(waterArray);

				}

				if (isInvalidInput == false)
				{
					PlaceUserShip(waterArray, row - 1, column - 1, shipLength, LEFT);
				}
				break;

			case 'R':

				if (IsOutOfBounds(row - 1, column - 1, shipLength, RIGHT) == true)
				{
					isInvalidInput = true;

					OutOfBoundsMessage();
					PrintBoard(waterArray);
				}

				if (IsUserShipOverlap(waterArray, row - 1, column - 1, shipLength, RIGHT) == true)
				{
					isInvalidInput = true;

					OverlapMessage();
					PrintBoard(waterArray);

				}

				if (isInvalidInput == false)
				{
					PlaceUserShip(waterArray, row - 1, column - 1, shipLength, RIGHT);
				}
				break;

			default:
				isInvalidDirection = true;

				cout << "\n\nInvalid input - input should be one of the following (\"up\", \"down\", \"left\", or \"right\") \n";
				cout << "Try again: ";
				cin >> shipOrientation;

				if (shipOrientation[0] == 'U' || 'D' || 'L' || 'R')
				{
					isInvalidDirection = false;
				}
			}
		} while (isInvalidDirection);

	} while (isInvalidInput);
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

void PlaceUserShip(char array[][10], int row, int column, int shipLength, orientation shipDirection)
{
	int limit;

	switch (shipDirection)
	{
	case UP:
		limit = row - shipLength;

		for (row; row > limit; --row)
		{
			array[row][column] = '#';
		}
		break;

	case DOWN:
		limit = row + shipLength;

		for (row; row < limit; row++)
		{
			array[row][column] = '#';
		}
		break;

	case LEFT:
		limit = column - shipLength;

		for (column; column > limit; --column)
		{
			array[row][column] = '#';
		}
		break;

	case RIGHT:
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
	cout << "\nThe coordinates you entered along with the ship orientation are outside of the bounds of the game board.\n";
	cout << "Re-enter your ship coordinates with this in mind.\n";
	cout << "********************************************************************************************************\n";
}

void InvalidInputMessage()
{
	cout << "\n************************************************************************\n";
	cout << "Invalid data - your input should be an integer between 0 and 9 inclusive\n";
	cout << "************************************************************************\n";
	cout << "Try again: ";
}

void OverlapMessage()
{
	cout << "\n\n*********************************************************************************************************";
	cout << "\nThe coordinates you entered along with the ship orientation have over lap with another one of your ships. \n";
	cout << "Re-enter your ship coordinates with this in mind.\n";
	cout << "*********************************************************************************************************\n";
}

void UpdatedBoardMessage()
{
	cout << "\n***********************\n";
	cout << "This is now your board: \n";
	cout << "***********************\n";
}