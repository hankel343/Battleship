#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum orientation {UP, DOWN, LEFT, RIGHT};

enum shiptype { DESTROYER, SUBMARINE, CRUSIER, BATTLESHIP, CARRIER };

void ComputerSetUp();

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

int main()
{
	srand(unsigned int(time(NULL)));

	ComputerSetUp();

	//User set up
	char userGuessGrid[10][10];
	char userShipGrid[10][10];

	InitializeDefaultBoard(userShipGrid);

	UserShipPlacement(userShipGrid);


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

			cout << "\n\nThis is now your board: \n";
			PrintBoard(waterArray);
			break;

		case SUBMARINE:
			shipLength = 3;

			cout << "\n\nPlace your submarine (3 places)";

			ValidateUserInput(waterArray, shipLength, row, column, shipOrientation);

			cout << "\nThis is now your board: \n";
			PrintBoard(waterArray);
			break;

		case CRUSIER:
			shipLength = 3;

			cout << "\n\nPlace your carrier (3 places)";

			ValidateUserInput(waterArray, shipLength, row, column, shipOrientation);

			cout << "\nThis is now your board: \n";
			PrintBoard(waterArray);
			break;

		case BATTLESHIP:
			shipLength = 4;

			cout << "\n\nPlace your battleship (4 places)";

			ValidateUserInput(waterArray, shipLength, row, column, shipOrientation);

			cout << "\nThis is now your board: \n";
			PrintBoard(waterArray);
			break;

		case CARRIER:
			shipLength = 5;

			cout << "\n\nPlace your carrier (5 places)";

			ValidateUserInput(waterArray, shipLength, row, column, shipOrientation);

			cout << "\nThis is now your board: \n";
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
	for (int i = 0; i < 10; ++i)
	{
		if (i == 0)
			cout << "  " << i << " ";

		if (i > 0)
			cout << i << " ";

		if (i == 9)
			cout << endl;
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << i << " ";
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
	//Semi-random way of determining if the computer orients a ship vertically or horizontally



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

		while (!cin || row < 0 || row > 9)
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid data - your input should be an integer between 0 and 9 inclusive\n";
			cout << "Try again: ";
			cin >> row;
		}

		cout << "\nEnter the starting column coordinate for your ship: ";
		cin >> column;

		while (!cin || column < 0 || column > 9)
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << "Invalid data - your input should be an integer between 0 and 9 inclusive\n";
			cout << "Try again: ";
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

				if (IsOutOfBounds(row, column, shipLength, UP) == true)
				{
					isInvalidInput = true;

					cout << "\n\nThe coordinates you entered along with the ship orientation are outside of the bounds of the game board.\n";
					cout << "Re-enter your ship coordinates with this in mind.\n";
				}

				if (IsUserShipOverlap(waterArray, row, column, shipLength, UP) == true)
				{
					isInvalidInput = true;

					cout << "\n\nThe coordinates you entered along with the ship orientation have over lap with another one of your ships. \n";
					cout << "Re-enter your ship coordinates with this in mind.\n";
				}
					
				if (isInvalidInput == false)
				{
					PlaceUserShip(waterArray, row, column, shipLength, UP);
				}

				break;

			case 'D':

				if (IsOutOfBounds(row, column, shipLength, DOWN) == true)
				{
					isInvalidInput = true;

					cout << "\n\nThe coordinates you entered along with the ship orientation are outside of the bounds of the game board.\n";
					cout << "Re-enter your ship coordinates with this in mind.\n";
				}

				if (IsUserShipOverlap(waterArray, row, column, shipLength, DOWN) == true)
				{
					isInvalidInput = true;

					cout << "\n\nThe coordinates you entered along with the ship orientation have over lap with another one of your ships. \n";
					cout << "Re-enter your ship coordinates with this in mind.\n";
				}
					

				if (isInvalidInput == false)
				{
					PlaceUserShip(waterArray, row, column, shipLength, DOWN);
				}
				break;

			case 'L':

				if (IsOutOfBounds(row, column, shipLength, LEFT) == true)
				{
					isInvalidInput = true;

					cout << "\n\nThe coordinates you entered along with the ship orientation are outside of the bounds of the game board.\n";
					cout << "Re-enter your ship coordinates with this in mind.\n";
				}

				if (IsUserShipOverlap(waterArray, row, column, shipLength, LEFT) == true)
				{
					isInvalidInput = true;

					cout << "\n\nThe coordinates you entered along with the ship orientation have over lap with another one of your ships. \n";
					cout << "Re-enter your ship coordinates with this in mind.\n";

				}

				if (isInvalidInput == false)
				{
					PlaceUserShip(waterArray, row, column, shipLength, LEFT);
				}
				break;

			case 'R':

				if (IsOutOfBounds(row, column, shipLength, RIGHT) == true)
				{
					isInvalidInput = true;

					cout << "\n\nThe coordinates you entered along with the ship orientation are outside of the bounds of the game board.\n";
					cout << "Re-enter your ship coordinates with this in mind.\n";
				}

				if (IsUserShipOverlap(waterArray, row, column, shipLength, RIGHT) == true)
				{
					isInvalidInput = true;

					cout << "\n\nThe coordinates you entered along with the ship orientation have over lap with another one of your ships. \n";
					cout << "Re-enter your ship coordinates with this in mind.\n";

				}

				if (isInvalidInput == false)
				{
					PlaceUserShip(waterArray, row, column, shipLength, RIGHT);
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