#include <iostream>
#include <ios>
#include <iomanip>
#include <random>
#include <Windows.h>
#include <conio.h>


// ---------- Default settings ---------- //

const int defaultPositionX = 1;
const int defaultPositionY = 1;
const char defaultSymbol = '@';
const char defaultBorderSymbol = '#';
const char defaultPointSymbol = '*';

// -------------------------------------- //



/*		####		 ##	   ##		##    ##		      ##
		## ##		 ##	   ##		##    ##		      ##
		##	##		 ##	   ##		##    ##		      ##
		##	 ##		 ##	   ##		##    ##		      ##
		##	  ##	 ##	   ##		##    ##		      ##
		##	   ##	 ##	   ##		##    ##		      ##
		##		##	 ##	   ##		##    ##		      ##
		##		 ##	 ##	   ##		##    ##		      ##
		##		  ## ##	   ##		##    ##		      ##
		##	       ####	   ###########    ############    ############
*/


// -------------------------- Класс отвечающий за карту -------------------------- //

class Map
{
private:
	enum { HEIGHT = 10 };
	enum { WIDTH = 50 };
	mutable char map[HEIGHT][WIDTH];
	char borderSymbol;

public:
	Map() : borderSymbol(defaultBorderSymbol)
	{
		setMap();
		showMap();
	}

	Map(char borderSym) : borderSymbol(borderSym)
	{
		setMap();
		showMap();
	};

	// -------------- GETTERS -------------- //

	int getHEIGHT() { return HEIGHT; }
	int getWIDTH() { return WIDTH; }
	char getBorderSymbol() { return borderSymbol; }

	char* getMap()
	{
		return *map;
	}

	char& getMap(int y, int x)
	{
		return map[y][x];
	}

	// ------------------------------------ //


	void setMap() 
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (i == 0 || i == (HEIGHT - 1) ) {
					map[i][j] = borderSymbol;
				} 
				else if (j == 0 || j == (WIDTH - 1))
				{
					map[i][j] = borderSymbol;
				}
				else
				{
					map[i][j] = ' ';
				}
			}
		}
	}

	/* The function that displays the map on the screen */
	void showMap()
	{
		std::ios::sync_with_stdio(0);
		std::cin.tie(0);
		std::cout.tie(0);

		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				std::cout << map[i][j];
			}
			std::cout << '\n';
		}
	}

	/* The function that is responsible for cleaning the console */
	void ClearScreen() 
	{
		HANDLE                     hStdOut;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD                      count;
		DWORD                      cellCount;
		COORD                      homeCoords = { 0, 0 };

		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) return;

		/* Get the number of cells in the current buffer */
		if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
		cellCount = csbi.dwSize.X * csbi.dwSize.Y;

		/* Fill the entire buffer with spaces */
		if (!FillConsoleOutputCharacter(
			hStdOut,
			(TCHAR)' ',
			cellCount,
			homeCoords,
			&count
		)) return;

		/* Fill the entire buffer with the current colors and attributes */
		if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
		)) return;

		/* Move the cursor home */
		SetConsoleCursorPosition(hStdOut, homeCoords);
	}

	// The function that updates the map
	void refresh() 
	{
		ClearScreen();
		showMap();
	}

};
// -------------------------------------------------------------------------------- //


/*		####		 ##	   ##		##    ##		      ##	
		#####		 ##	   ##		##    ##		      ##
		##	##		 ##	   ##		##    ##		      ##
		##	 ##		 ##	   ##		##    ##		      ##
		##	  ##	 ##	   ##		##    ##		      ##
		##	   ##	 ##	   ##		##    ##		      ##
		##		##	 ##	   ##		##    ##		      ##
		##		 ##	 ##	   ##		##    ##		      ##
		##		  #####	   ##		##    ##		      ##
		##	       ####	   ###########    ############    ############
*/


// -------------------------- Класс отвечающий за поинты -------------------------- //

class Point
{
private:
	enum { COUNT = 50 };
	int pointsPositions[2][COUNT];
	char pointSymbol;

public:
	Point() : pointSymbol(defaultPointSymbol)
	{	};

	Point(char symbol) : pointSymbol(symbol)
	{	};

	int getCOUNT() { return COUNT; }

	int* getPoints()
	{
		return *pointsPositions;
	}

	int& getPoints(int y, int x)
	{
		return pointsPositions[y][x];
	}


	void generatePoints(Map& map)
	{
		srand(time(NULL));

		for (int i = 0; i < COUNT; i++)
		{

		setX:
			int x = (rand() % map.getWIDTH() + 1);


			if (x == 0 || x == map.getWIDTH() - 1)
			{
				goto setX;
				break;
			}

			pointsPositions[1][i] = x;
		}

		for (int i = 0; i < COUNT; i++)
		{
		setY:
			int y = (rand() % map.getHEIGHT() + 1);

			if (y == 0 || y == map.getHEIGHT() - 1)
			{
				goto setY;
				break;
			}

			pointsPositions[0][i] = y;
		}
	}

	void setPoints(Map& map)
	{
		for (int i = 0; i < COUNT; i++)
		{
			map.getMap(pointsPositions[0][i], pointsPositions[1][i]) = pointSymbol;
		}
	}
};

// --------------------------------------------------------------------------------- //


/*		####		 ##	   ##		##    ##		      ##
		#####		 ##	   ##		##    ##		      ##
		##	##		 ##	   ##		##    ##		      ##
		##	 ##		 ##	   ##		##    ##		      ##
		##	  ##	 ##	   ##		##    ##		      ##
		##	   ##	 ##	   ##		##    ##		      ##
		##		##	 ##	   ##		##    ##		      ##
		##		 ##	 ##	   ##		##    ##		      ##
		##		  #####	   ##		##    ##		      ##
		##	       ####	   ###########    ############    ############
*/


// -------------------------- Класс отвечающий за игрока -------------------------- //

class Player
{
private:
	std::string nickname;
	char symbol;
	int	lvl;
	int	positionX;
	int	positionY;
	int	points;

public:
	Player() : lvl(0), points(0), positionX(defaultPositionX), positionY(defaultPositionY), symbol(defaultSymbol)
	{  
		srand(time(NULL));
		nickname = "Player_" + rand();
	};

	Player(std::string nick) : nickname(nick), lvl(0), points(0), positionX(defaultPositionX), positionY(defaultPositionY), symbol(defaultSymbol)
	{	};

	Player(std::string nick, char sym) : nickname(nick), lvl(0), points(0), positionX(defaultPositionX), positionY(defaultPositionY), symbol(sym)
	{	};

	// --------------- Movement methods --------------- //

	void moveUp() { positionY--; } // Movemont on up
	void moveDown() { positionY++; } // Movemont on down
	void moveLeft() { positionX--; } // Movemont on left
	void moveRight() { positionX++; } // Movemont on right

	void movement(int keycap, Map &obj)
	{
		// Сначала убирает текущую позицию игрока
		for (int i = 0; i < obj.getHEIGHT(); i++)
		{
			for (int j = 0; j < obj.getWIDTH(); j++)
			{
				if (obj.getMap(i, j) == symbol) {
					obj.getMap(i, j) = ' ';
				}
			}
		}

		switch (keycap)
		{
		case 72:
			if (obj.getMap((positionY - 1), positionX) != '#')
			{
				moveUp();
			}
			break;
		case 80:
			if (obj.getMap((positionY + 1), positionX) != '#')
			{
				moveDown();
			}
			break;
		case 75:
			if (obj.getMap((positionY), positionX - 1) != '#')
			{
				moveLeft();
			}
			break;
		case 77:
			if (obj.getMap((positionY), positionX + 1) != '#')
			{
				moveRight();
			}
			break;
		default:
			break;
		}
	}

	// ------------------------------------------------ //


	// ----------------- GETTERS ----------------- //

	std::string getNickname() { return nickname; }
	char getSymbol() { return symbol; }
	int getLVL() { return lvl; }
	int getPoints() { return points; }
	int getPositionX() { return positionX; }
	int getPositionY() { return positionY; }

	// ------------------------------------------- //

	void setPlayer(Map &obj, Point &p)
	{
		obj.getMap(positionY, positionX) = symbol;
		checkPoints(p);
		lvlUp();
	}

	void lvlUp()
	{
		static int lastCount = 0;

		if (points == 5 && lastCount != 5)
		{
			lvl++;
			lastCount = 5;
		}
		else if (points == 10 && lastCount != 10) 
		{
			lvl++;
			lastCount = 10;
		}
		else if (points == 15 && lastCount != 15)
		{
			lvl++;
			lastCount = 15;
		}
		else if (points == 20 && lastCount != 20)
		{
			lvl++;
			lastCount = 20;
		}
		else if (points == 30 && lastCount != 30)
		{
			lvl++;
			lastCount = 30;
		}
		else if (points == 40 && lastCount != 40)
		{
			lvl++;
			lastCount = 40;
		}
		else if (points == 50 && lastCount != 50)
		{
			lvl++;
			lastCount = 50;
		}

	}

	void checkPoints(Point &obj)
	{
		for (int i = 0; i < obj.getCOUNT(); i++)
		{
			if (positionY == obj.getPoints(0, i) && positionX == obj.getPoints(1, i))
			{
				obj.getPoints(0, i) = ' ';
				obj.getPoints(1, i) = ' ';
				Player::points++;
			}
		}
	}
};

// ------------------------------------------------------------------------------ //

/*		####		 ##
		#####		 ##
		##	##		 ##
		##	 ##		 ##
		##	  ##	 ##
		##	   ##	 ##
		##		##	 ##
		##		 ##	 ##
		##		  #####
		##	       ####
*/

