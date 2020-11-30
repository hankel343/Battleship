#include <iostream>
#include <time.h>
#include <Windows.h>
#include <iomanip>

using namespace std;

//Typedef for computer and user 10 x 10 arrays
typedef char gameboard[10][10];

class player {

	//These attributes keep track of hits and misses for the user and the computer
	float cumulativeHits = 0;
	float cumulativeMisses = 0;

public:
	//Two 10 x 10 arrays are generated for both the player and the computer
	gameboard guessArray;
	gameboard shipArray;
 
	void SetNumOfHits(int hits) {cumulativeHits += hits;}
	//Pre:The game has terminated and the number of hits has been passed as an argument
	//Post The total number of hits during program execution is updated

	void SetNumOfMisses(int misses) {cumulativeMisses += misses;}
	//Pre: The game has terminated and the number of misses has been passed as an argument
	//Post: The total number of misses during program execution is updated

	float GetHits() {return cumulativeHits;}
	//Pre: None - initialized to zero
	//Post: The number hits on enemy ships is printed to the console

	float GetMisses() {return cumulativeMisses;}
	//Pre: None - initialized to zero
	//Post: The number of missed shots is printed to the console

	float PrintAccuracy() {return cumulativeHits / (cumulativeHits + cumulativeMisses);}
	//Pre: None - both cumulative hits and misses are initialized to zero.
	//Post: Prints the ratio of his to shots taken for both the user and the computer.

} user, computer; //Instantiates two player objects

enum orientation {UP, DOWN, LEFT, RIGHT};

enum shiptype {DESTROYER, SUBMARINE, CRUSIER, BATTLESHIP, CARRIER};

void ComputerSetUp();
//Pre: Two 10 x 10 char arrays must exist for the function to manipulate.
//Post: Two 10 x 10 char arrays are initialized for the game - one for the computer's guess grid and another for the comptuer's ship grid.

void UserSetUp();
//Pre: Two 10 x 10 char arrays must exist fo the function to manipulate.
//Post: Two 10 x 10 char arrays are initialized for the user - one for the user's guess grid and another for the user's ship grid.

void ComputerTurn(int& computerHits, int& computerMisses);
//Pre: Gameboards for computer and user must be generated; Counters for computer hits and misses must be initialized and passed by reference as well.
//Post: A message is printed to the screen stating if the computer landed a hit or not and increments hit and miss counters.

void UserTurn(int& userHits, int& userMisses);
//Pre: Gameboards for computer and user must be generated; Counters for user hits and misses must be initialized and passed by reference.
//Post: The user has completed their turn.

void CheckWinConditions(int computerHits, int computerMisses, int userHits, int userMisses, bool hasSurrendered, bool& isEndOfGame, int& numOfLosses, int& numOfWins);
//Pre: Both the computer and user have completed their turns
//Post: Function determines whether or not the game is compeleted.

void Menu(bool& hasSurrendered, int& userHits, int& userMisses);
//Pre: Function is able to reference the computer's ship grid; Function is passed two intitialized counter arguements and an initialized bool arguement.
//Post: User has completed all allowable actions for their turn.

bool NewGameMenu();
//Pre: A single game has been completed
//Post: Function returns whether or not a new game will be started

void Surrender(bool& hasSurrendered);
//Pre: User has selected "surrender" from the user turn menu and a bool argument determining if the player has surrendered is initialized and passed by reference.
//Post: The user's choice to surrender has been validated.

bool Fire(char shipGrid[][10], char guessGrid[][10], int xcoordinate, int ycoordinate);
//Pre: The function has the ability to reference both sets of the computer's and user's grids; Function is passed array indexes of location to fire on
//Post: Function determines if a ship has been hit and updates guess grids with either 'H' or 'M'

void GenerateComputerShipGrid();
//Pre: Program has access to the computer's ship grid
//Post: The computer's ship grid is randomly populated with ships with differing orientations

void InitializeDefaultBoard(char emptyArray[][10]);
//Pre: Program has access to the an empty array of a declared size
//Post: The array is initailized to contain 10 x 10 grid of water ('~')

void UserShipPlacement();
//Pre: Function is able to access the user's inititialized blank ship array
//Post: The user has placed their ships on their ship grid

void ValidateUserInput(int& shipLength);
//Pre: The user's ship and guess arrays have been successfully initialized
//Post: The user's input has been validated and ships have been placed on the user's ship grid.

bool IsValidOrientation(int row, int column, string shipOrientation, int shipLength);
//Pre: User input has been validated to be of the correct data type and the user's ship array has been declared and initialized.
//Post: The user's ship orientation has been verified to be with in array bounds and not overlap other ships

void PrintBoard(char array[][10]);
//Pre: Array to be printed has been declared and initialized
//Post: The array is output to the screen

void AddShipVertical(int shipLength);
//Pre: Computer ship array has been declared and initialized
//Post: A ship is added vertically to the computer's ship array

void AddShipHorizontal(int shipLength);
//Pre: Computer ship array has been decared and initialized
//Post: A ship is added horizontally to the computer's ship array

bool IsComputerShipOverlap(int ranRowsorColumns, int shipLength, orientation shipDirection);
//Pre: Computer ship array has been declared and initialized
//Post: Computer has verified if there is ship overlap on the computer's ship array

bool IsUserShipOverlap(int row, int column, int shipLength, orientation shipDirection);
//Pre: User ship array has been declared and inititalized; function is passed user input for array coordinates
//Post: Computer has verified if there is ship overlap on the user's ship array

bool IsOutOfBounds(int row, int column, int shipLength, orientation shipDirection);
//Pre: User ship array has been declared and initialized; Function is passed user's array coordinates and ship orientation
//Post: Computer has verified that the user's array coordinates in conjunction with the orientation of the ship are within the array bounds.

void PlaceUserShip(int row, int column, int shipLength, string shipOrientation);
//Pre: User ship array has been declared and initalized; Computer has verified that ship placement will be within array bounds and not overlap other ships
//Post: The user's ships are placed on the board at the given coordinates and orientation

void OutOfBoundsMessage();
//Pre: User has entered ship coordinates that are outside of the array bounds either by coordinates themselves or with valid coordinates with a orientation that overruns the array bounds
//Post: A message explaining the user's error is printed to the screen.

void InvalidInputMessage();
//Pre: User has entered an invalid data type during a prompt.
//Post: A message explaining the user's error is printed to the screen.

void OverlapMessage();
//Pre: User has entered ship coordinates and orientation that overlaps with another ship on their board
//Post: A message explaining the user's error is printed to the screen.

void UpdatedBoardMessage();
//Pre: User has entered valid coordinates and orientation for their ship.
//Post: A message telling the user their ship was placed is printed to the screen

void PrintScoreBoard(int numOfGames, int numOfLosses, int numOfWins);
//Pre: The user has chosen to not start a new game and therefore end program execution
//Post: A scoreboard of wins, losses, and user statistics are printed to the screen before program exit.

int main()
{
	srand(unsigned int(time(NULL)));

	//Boolean data types for loop control in main()
	bool isNewGame;
	bool isEndOfGame;
	bool hasSurrendered;
	
	//Track game progress.
	int numOfGames = 1;
	int numOfWins = 0;
	int numOfLosses = 0;
	int userHits;
	int userMisses;
	int computerHits;
	int computerMisses;
	do
	{
		system("cls");

		//Tracks how many hits have been made (17 in total for each gameboard)
		computerHits = 0;
		computerMisses = 0;
		userHits = 0;
		userMisses = 0;

		//Initializes and populates computer's board
		ComputerSetUp();

		//Initializes and allows user to place their ships
		UserSetUp();

		isEndOfGame = false;
		hasSurrendered = false;

		do
		{
			ComputerTurn(computerHits, computerMisses);

			Menu(hasSurrendered, userHits, userMisses);

			CheckWinConditions(computerHits, computerMisses, userHits, userMisses, hasSurrendered, isEndOfGame, numOfLosses, numOfWins);

		} while (!isEndOfGame);

	} while (NewGameMenu());

	PrintScoreBoard(numOfGames, numOfLosses, numOfWins);

	cout << "\n\nGoodbye...\n";

	return 0;
}

void ComputerSetUp()
{

	//Sets empty 10 x 10 array to water ('~') for computer guess grid
	InitializeDefaultBoard(computer.guessArray);

	//Sets empty 10 x 10 array to water ('~')
	InitializeDefaultBoard(computer.shipArray);

	//Randomly select 5 places on the water grid to place a ship
	GenerateComputerShipGrid();
}

void UserSetUp()
{
	
	//Initialize user's guess grid to water ('~')
	InitializeDefaultBoard(user.guessArray);

	//Initialize user's ship grid to water ('~')
	InitializeDefaultBoard(user.shipArray);

	//Allows user to place ships and validates ship positions at the same time
	UserShipPlacement();
}

void ComputerTurn(int& computerHits, int& computerMisses)
{
	//Ran num range must be 1 - 10 because the Fire() function subtracts one for user input.
	//In other words 1 is subtracted because these values are passed for array processing where valid array indexes are 1 - 9.
	int ranXCoordinate = rand() % 10 + 1;
	int ranYCoordinate = rand() % 10 + 1;

	if (Fire(user.shipArray, computer.guessArray, ranXCoordinate, ranYCoordinate) == true) //If there is a '#' at the random coordinates that computer has generated.
	{
		cout << "\nThe computer landed a hit!\n\n";
		computerHits++;
	}
	else {
		cout << "\nThe computer missed!\n";
		computerMisses++;
	}
		
}

void UserTurn(int& userHits, int& userMisses)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int xcoordinate;
	int ycoordinate;

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

	if (Fire(computer.shipArray, user.guessArray, xcoordinate, ycoordinate) == true) {
		cout << "\n\nYou landed a ";
		SetConsoleTextAttribute(hConsole, 12); //Sets console color to red
		cout << "hit!\n";
		userHits++;
	}
	else {
		cout << "\n\nYou";
		SetConsoleTextAttribute(hConsole, 10); //Sets console color to green
		cout << " missed!\n";
		userMisses++;
	}

	SetConsoleTextAttribute(hConsole, 15); //Sets console text back to white
}

void Menu(bool& hasSurrendered, int& userHits, int& userMisses)
{
	int selection;
	bool isEndOfTurn;

	cout << "Here is your guess grid: \n";

	PrintBoard(user.guessArray);

	cout << "\nEnter your selection from the following menu: \n";

	do
	{
		isEndOfTurn = false;

		cout << "1 - Fire\n";
		cout << "2 - View the computer's guess grid\n";
		cout << "3 - Review your ship grid\n";
		cout << "4 - Surrender\n";
		cout << "Enter your choice: ";
		cin >> selection;

		switch (selection)
		{
		case 1:
			system("cls");
			PrintBoard(user.guessArray);
			UserTurn(userHits, userMisses);
			isEndOfTurn = true;
			break;

		case 2:
			system("cls");
			cout << "########################################\n";
			cout << "These are the computer's guesses so far: \n";
			PrintBoard(computer.guessArray);
			cout << "########################################\n\n";
			break;

		case 3:
			system("cls");
			cout << "#######################\n";
			cout << "Here is your ship grid: \n";
			PrintBoard(user.shipArray);
			cout << "#######################\n\n";
			break;

		case 4:
			Surrender(hasSurrendered);
			isEndOfTurn = true;
			break;

		default:

			if (!cin) {
				cin.clear();
				cin.ignore(1000, '\n');
			}

			cout << "\n\nUnknown selection - your input should be an integer from the menu above.\n";
			cout << "Try again.\n\n";
		}
	} while (!isEndOfTurn);
	
}

bool NewGameMenu()
{
	string input;

	cout << "\n\nWould you like to start a new game?\n";
	cout << "Y/N: ";
	cin >> input;

	//While the input stream is not in the failed state or the first letter of the input string is not a 'Y' or a 'N'.
	while (!cin || (toupper(input[0]) != 'N' && toupper(input[0]) != 'Y'))
	{
		cout << "\n*******************************************";
		cout << "\n\nYour input should either be a 'Y' or an 'N'\a\n";
		cout << "*******************************************\n";
		cout << "Try again: ";
		cin >> input;
	}

	//If user enters an N game loop will be exited because this function will return as a false condition for the loop control of the game
	if (input[0] == 'N')
		return false;
	else
		return true;
}

void PrintScoreBoard(int numOfGames, int numOfLosses, int numOfWins)
{
	system("cls");
	cout << "Here are your final stats for the program duration: \n";
	cout << "Total games: " << numOfGames << endl;
	cout << "Number of wins: " << numOfWins << endl;
	cout << "Number of losses: " << numOfLosses << endl;
	cout << "\n*********************************\n";
	cout << "\nComputer stats: \n";
	cout << "Cumulative number of hits: " << computer.GetHits() << endl;
	cout << "Cumulative number of misses: " << computer.GetMisses() << endl;
	cout << setprecision(2) << "Accuracy: " << computer.PrintAccuracy() << '%' << endl;
	cout << "\n*********************************\n";
	cout << "\nUser stats: \n";
	cout << "Cumulative number of hits: " << user.GetHits() << endl;
	cout << "Cumulative number of misses: " << user.GetMisses() << endl;
	cout << setprecision(2) << "Accuracy: " << user.PrintAccuracy() << '%' << endl;
}

void Surrender(bool& hasSurrendered)
{
	string input;

	cout << "\n\nAre you sure you want to surrender?\n";
	cout << "Y/N: ";
	cin >> input;

	if (toupper(input[0]) == 'Y')
		hasSurrendered = true;

}

void CheckWinConditions(int computerHits, int computerMisses, int userHits, int userMisses, bool hasSurrendered, bool& isEndOfGame, int& numOfLosses, int &numOfWins)
{
	if (computerHits == 17 || hasSurrendered == true) {

		isEndOfGame = true;

		system("cls");

		cout << "\n\nYou lose!\n";
		cout << "Here is the computer's ship board: \n";
		numOfLosses++;

		//Update values in player objects
		computer.SetNumOfHits(computerHits);
		computer.SetNumOfMisses(computerMisses);
		user.SetNumOfHits(userHits);
		user.SetNumOfMisses(userMisses);

		PrintBoard(computer.shipArray);
	}
	else if (userHits == 17) {

		isEndOfGame = true;

		system("cls");

		cout << "\n\nYou win!\n";
		cout << "Here is the computer's ship board: \n";
		numOfWins++;

		//Update values in player objects
		computer.SetNumOfHits(computerHits);
		computer.SetNumOfMisses(computerMisses);
		user.SetNumOfHits(userHits);
		user.SetNumOfMisses(userMisses);


		PrintBoard(computer.shipArray);
	}
}

//shipGrid[][10] and guessGrid[][10] are parameters here because both the player and computer share this function
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

void UserShipPlacement()
{
	//hConsole is of type HANDLE, which allows access to manipulate the windows console for coloring and formatting output
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//Sets console color to white
	SetConsoleTextAttribute(hConsole, 15);

	cout << "The computer has finished its set-up\n";
	cout << "You need to do the same with the following board: \n";

	PrintBoard(user.shipArray);


	int shipLength;
	//Following for-loop and switch guide player through gameboard set up.
	for (shiptype ship = DESTROYER; ship <= CARRIER; ship = shiptype(ship + 1))
	{
		switch (ship)
		{
		case DESTROYER:
			shipLength = 2;

			cout << "\n\nPlace your destroyer (2 places)";

			ValidateUserInput(shipLength);

			//Clears board on the console screen after the user has placed a ship.
			system("cls");

			UpdatedBoardMessage();
			PrintBoard(user.shipArray);
			break;

		case SUBMARINE:
			shipLength = 3;

			cout << "\n\nPlace your submarine (3 places)";

			ValidateUserInput(shipLength);

			system("cls");

			UpdatedBoardMessage();
			PrintBoard(user.shipArray);
			break;

		case CRUSIER:
			shipLength = 3;

			cout << "\n\nPlace your crusier (3 places)";

			ValidateUserInput(shipLength);

			system("cls");

			UpdatedBoardMessage();
			PrintBoard(user.shipArray);
			break;

		case BATTLESHIP:
			shipLength = 4;

			cout << "\n\nPlace your battleship (4 places)";

			ValidateUserInput(shipLength);

			system("cls");

			UpdatedBoardMessage();
			PrintBoard(user.shipArray);
			break;

		case CARRIER:
			shipLength = 5;

			cout << "\n\nPlace your carrier (5 places)";

			ValidateUserInput(shipLength);

			system("cls");

			break;
		}
	}


}

//Array must be a parameter of this function because it is shared by both the user and the computer's gameboards
void InitializeDefaultBoard(char emptyArray[][10])
{
	//Initializes this array to water '~'
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			emptyArray[i][j] = '~';
		}
	}
}

//Array must be a parameter because both the user's and computer's board share this function
void PrintBoard(char array[][10])
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 1; i < 11; ++i)
	{
		SetConsoleTextAttribute(hConsole, 15);
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
			SetConsoleTextAttribute(hConsole, 15);
			cout << i + 1 << "  ";
		}
		else {
			SetConsoleTextAttribute(hConsole, 15);
			cout << i + 1 << " ";
		}
			
		
		for (int j = 0; j < 10; ++j)
		{

			if (array[i][j] == '~') {
				SetConsoleTextAttribute(hConsole, 9); //Set console color to blue (9 = blue) if array cell contains a '~'
				cout << array[i][j] << ' ';
			}
			else if (array[i][j] == '#' || array[i][j] == 'H') { //Set console color to red (12 = red) if array cell contains a '#' or 'H'
				SetConsoleTextAttribute(hConsole, 12);
				cout << array[i][j] << ' ';
			}
			else if (array[i][j] == 'M') { //Set console color to green (10 = green) if the array cell contains an 'M'
				SetConsoleTextAttribute(hConsole, 10);
				cout << array[i][j] << ' ';
			}
			

			if (j == 9)
				cout << endl;
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
}

void GenerateComputerShipGrid()
{
	//shiptype enum is used to iterate through each ship size - using enums for cases made the switch statement's operation clearer
	for (shiptype ship = DESTROYER; ship <= CARRIER; ship = shiptype(ship + 1))
	{
		//Generate a 1 or 2 randomly to determine to orient verically or horizontally.
		int ranShipOrientation = rand() % 2 + 1;
		int shipLength;

		switch (ship)
		{
		case DESTROYER:

			shipLength = 2;

			if (ranShipOrientation == 1)
				AddShipVertical(shipLength);
			else
				AddShipHorizontal(shipLength);

			break;

		case SUBMARINE:

			shipLength = 3;

			if (ranShipOrientation == 1)
				AddShipVertical(shipLength);
			else
				AddShipHorizontal(shipLength);

			break;

		case CRUSIER:

			shipLength = 3;

			if (ranShipOrientation == 1) 
				AddShipVertical(shipLength);
			else
				AddShipHorizontal(shipLength);

			break;

		case BATTLESHIP:

			shipLength = 4;

			if (ranShipOrientation == 1)
				AddShipVertical(shipLength);
			else
				AddShipHorizontal(shipLength);

			break;

		case CARRIER:

			shipLength = 5;

			if (ranShipOrientation == 1)
				AddShipVertical(shipLength);
			else
				AddShipHorizontal(shipLength);

			break;
		}
	}


}

void AddShipVertical(int shipLength)
{
	//This bool determines if the function body should be repeated with a new random number because the first random number caused overlap
	bool isShipOverlap;
	do
	{
		//Generate a random column index
		int ranColumn = rand() % 10;

		isShipOverlap = IsComputerShipOverlap(ranColumn, shipLength, UP);

		if (isShipOverlap == false) //If no ship is found in the validation read
		{
			for (shipLength; shipLength > 0; --shipLength)
			{
				computer.shipArray[shipLength][ranColumn] = '#';
			}
		}

	} while (isShipOverlap);
}

void AddShipHorizontal(int shipLength)
{
	//This bool determines if the function body should be repeated with a new random number because the first random number caused overlap
	bool isShipOverlap;
	do
	{
		//Generate a random row index
		int ranRow = rand() % 10;

		//IsComputerShipOverlap() will return a bool value that determines if there is ship overlap or not
		isShipOverlap = IsComputerShipOverlap(ranRow, shipLength, LEFT);

		//If there wasn't ship overlap
		if (isShipOverlap == false)
		{
			//creates ship horizontally
			for (shipLength; shipLength > 0; --shipLength)
			{
				computer.shipArray[ranRow][shipLength] = '#';
			}
		}
	} while (isShipOverlap);

}

bool IsComputerShipOverlap(int ranRowsorColumns, int shipLength, orientation shipDirection)
{
	if (shipDirection == UP) //Verifying if a column for a ship
	{
		//Does initial read of area where a ship will be added to check if a ship is already there.
		for (shipLength; shipLength > 0; --shipLength)
		{
			//Creates a ship vertically 
			if (computer.shipArray[shipLength][ranRowsorColumns] == '#')
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
			if (computer.shipArray[ranRowsorColumns][shipLength] == '#')
			{
				return true;
			}
		}

		return false;
	}
}

void ValidateUserInput(int& shipLength)
{
	//This bool is a loop control that is set to true if the user has overlapping ships or out-of-bounds ships
	bool isValidInput;

	//Identifiers for user input
	int row;
	int column;
	string shipOrientation;

	do
	{
		isValidInput = false;

		cout << "\nEnter the starting x-coordinate for your ship: ";
		cin >> column;

		//Loops while user provides invalid input
		while (!cin || column < 0 || column > 10)
		{
			cin.clear();
			cin.ignore(1000, '\n');

			InvalidInputMessage();
			cin >> column;
		}

		cout << "\nEnter the starting y-coordinate for your ship: ";
		cin >> row;

		//Loops while user provides invalid input
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
		isValidInput = IsValidOrientation(row, column, shipOrientation, shipLength);

		//If input array indexes are not invalid
		if (isValidInput == true)
			PlaceUserShip(row, column, shipLength, shipOrientation);
		
	} while (!isValidInput); //If overlap or out-of-array bounds then this function loops until the user enters valid data
}

bool IsValidOrientation(int row, int column, string shipOrientation, int shipLength)
{
	//Switches off of the capitalized first letter of string shipOrientation that the user provides
	switch (toupper(shipOrientation[0]))
	{
	case 'U':

		//If the user's input is out of array bounds or overlaps with another ship on the board with an updward orientation
		if (IsOutOfBounds(row, column, shipLength, UP) == true || IsUserShipOverlap(row, column, shipLength, UP) == true)
		{
			//Print error message and board 
			OutOfBoundsMessage();
			PrintBoard(user.shipArray);

			return false;
		}

		return true;

	case 'D':

		//If the user's input is out of array bounds or overlaps with another ship on the board with a downward orientation
		if (IsOutOfBounds(row, column, shipLength, DOWN) == true || IsUserShipOverlap(row, column, shipLength, DOWN) == true)
		{
			//Print error message and board 
			OutOfBoundsMessage();
			PrintBoard(user.shipArray);

			return false;
		}

		return true;

	case 'L':

		//If the user's input is out of array bounds or overlaps with another ship on the board with a leftward orientation
		if (IsOutOfBounds(row, column, shipLength, LEFT) == true || IsUserShipOverlap(row, column, shipLength, LEFT) == true)
		{
			//Print error message and board 
			OutOfBoundsMessage();
			PrintBoard(user.shipArray);

			return false;
		}

		return true;

	case 'R':

		//If The user's input is out of array bounds or overlaps with another ship on the board with a rightward orientation
		if (IsOutOfBounds(row, column, shipLength, RIGHT) == true || IsUserShipOverlap(row, column, shipLength, RIGHT) == true)
		{
			//Print error message and board 
			OutOfBoundsMessage();
			PrintBoard(user.shipArray);

			return false;
		}

		return true;
	}
}

bool IsUserShipOverlap(int row, int column, int shipLength, orientation shipDirection)
{
	//Limit is used to control the following for loops
	int limit;
	switch (shipDirection)
	{

	case UP:
		limit = row - shipLength;

		for (row; row > limit; --row)
		{
			if (user.shipArray[row][column] == '#')
				return true;
		}

		return false;

	case DOWN:
		limit = row + shipLength;

		for (row; row <= limit; ++row)
		{
			if (user.shipArray[row][column] == '#')
				return true;
		}

		return false;

	case LEFT:
		limit = column - shipLength;

		for (column; column > limit; column--)
		{
			if (user.shipArray[row][column] == '#')
				return true;
		}

		return false;

	case RIGHT:
		limit = column + shipLength;

		for (column; column < limit; column++)
		{
			if (user.shipArray[row][column] == '#')
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

void PlaceUserShip(int row, int column, int shipLength, string shipOrientation)
{
	int limit;

	switch (toupper(shipOrientation[0]))
	{
	case 'U':
		limit = row - shipLength;

		for (row; row > limit; --row)
		{
			user.shipArray[row][column] = '#';
		}
		break;

	case 'D':
		limit = row + shipLength;

		for (row; row < limit; row++)
		{
			user.shipArray[row][column] = '#';
		}
		break;

	case 'L':
		limit = column - shipLength;

		for (column; column > limit; --column)
		{
			user.shipArray[row][column] = '#';
		}
		break;

	case 'R':
		limit = column + shipLength;

		for (column; column < limit; ++column)
		{
			user.shipArray[row][column] = '#';
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