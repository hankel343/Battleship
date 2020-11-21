#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum Orientation { ROW, COLUMN };

enum ShipType { DESTROYER, SUBMARINE, CRUSIER, BATTLESHIP, CARRIER };

void ComputerSetUp();

void GenerateComputerGrid(char waterArray[][10]);

void InitializeDefaultBoard(char emptyArray[][10]);

void UserShipPlacement(char waterArray[][10]);

void PrintBoard(char array[][10]);

void AddShipVertical(char array[][10], int shipLength);

void AddShipHorizontal(char array[][10], int shipLength);

bool IsShipOverlap(char array[][10], int ranRowsorColumns, int shipLength, Orientation code);

int main()
{
	srand(unsigned int(time(NULL)));

	ComputerSetUp();

	//User set up
	char userGuessGrid[10][10];
	char userShipGrid[10][10];

	InitializeDefaultBoard(userShipGrid);



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

	PrintBoard(computerShipGrid);
}

void UserShipPlacement(char waterArray[][10])
{
	cout << "The computer has arranged its ships on the grid.\n";
	cout << "You need to do the same with the following board: \n";

	PrintBoard(waterArray);


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
	for (ShipType ship = DESTROYER; ship <= CARRIER; ship = ShipType(ship + 1))
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

		repeatLoop = IsShipOverlap(array, ranColumn, shipLength, COLUMN);

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

		repeatLoop = IsShipOverlap(array, ranRow, shipLength, ROW);

		if (repeatLoop == false)
		{
			//Creates a ship oriented vertically
			for (shipLength; shipLength > 0; --shipLength)
			{
				array[ranRow][shipLength] = '#';
			}
		}
	} while (repeatLoop);

}

bool IsShipOverlap(char array[][10], int ranRowsorColumns, int shipLength, Orientation code)
{

	if (code == COLUMN) //Verifying if a column for a ship
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
	else if (code == ROW) //verifying if a row for a ship
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