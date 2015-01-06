#include<iostream>
#include<cstdlib>
#include<time.h>
#include<Windows.h>
#include<string>
#include<conio.h>
using namespace std;


//Define escape button with a number
#define ESC 27
#define P 0x50


//Game Variables
string name;  //for player name
int snake_body[200][2];  //2d array for x,y coordinations
int ini_pos = 1;   //initial position
int snake_size = 3; //initial snake size
int iniX = 10;  //initial x position
int iniY = 15;  //initial y position 
int xTar = 30;  //initial x position for food
int yTar = 15;  //initial y position for food
int snake_direction = 3;
int snake_speed = 80;   //controlling snake speed
int score_val = 0;
int i = 0;           //for game over check
char movement_key;  //for checking esc button 
char choice;

//setting cursor on screen to certain position
void _posXY(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}
//Drawing the map
void draw_board()
{
	//horizontal lines
	for (int c = 1; c < 78; c++)
	{
		_posXY(c, 1);
		cout << "#";
		_posXY(c, 23);
		cout << "#";
	}
	//vertical lines
	for (int c = 1; c < 23; c++)
	{
		_posXY(1, c);
		cout << "#";
		_posXY(77, c);
		cout << "#";
	}

}
//saving the snake position to make all parts move in same order
void store_snake_pos()
{
	snake_body[ini_pos][0] = iniX;   //one dimension of the two for x-axis
	snake_body[ini_pos][1] = iniY;  //the other for y-axis
	ini_pos++;
	if (ini_pos == snake_size)
	{
		ini_pos = 1;      //re-assign the initial position to snake size so it wont exceed the size of the snake 
	}
}
//Drawing the snake body
void draw_snake_body()
{
	for (int c = 1; c < snake_size; c++)
	{
		_posXY(snake_body[c][0], snake_body[c][1]);//assigning the position of the snake to the position of the cursor
		cout << "X";   //snake body symbol
	}
}
//Removing the tail of the snake after moving
void rem_snake_body()
{
	_posXY(snake_body[ini_pos][0], snake_body[ini_pos][1]);//printing blank spaces to the ex-position of the snake so it wont leave traces
	printf(" ");
}
//Moving the snake by keyboard
void mov_snake()
{
	if (GetAsyncKeyState(VK_UP))   //function used to check whether arrow key was pressed or not
	{
		if (snake_direction != 2)
		{
			snake_direction = 1;
		}
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (snake_direction != 1)
		{
			snake_direction = 2;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (snake_direction != 4)
		{
			snake_direction = 3;
		}
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (snake_direction != 3)
		{
			snake_direction = 4;
		}
	}
}
//Adding food to the map
int inc_snake_size()
{
	if (iniX == xTar && iniY == yTar)
	{
		xTar = (rand() % 73) + 2;//generating food randomly on x-axis
		yTar = (rand() % 19) + 2;//generating food randomly on y-axis
		snake_size += 1; //increasing the size of snake after eating
		score_val += 10;//increasing score after eating
		PlaySound(TEXT("C:\\Users\\Moe\\Documents\\Visual Studio 2013\\Projects\\snake\\snake\\Debug\\coindrop.wav"), NULL, SND_FILENAME | SND_ASYNC);
		_posXY(xTar, yTar);//assigning the position to the cursor and prinint food symbol
		cout << "@"; //food symbol
		return 0;
	}
}
//Game over checker
int game_over()
{

	if (iniY == 1 || iniY == 23 || iniX == 1 || iniX == 77)//if the snake hits the map's borders
	{
		i = 0;
		PlaySound(TEXT("failtrombone"), NULL, SND_FILENAME | SND_ASYNC);
		//PlaySound(TEXT("C:\\Users\\Moe\\Documents\\Visual Studio 2013\\Projects\\snake\\snake\\Debug\\failtrombone.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return i;
	}

	for (int c = snake_size - 1; c > 0; c--)
	{
		if (snake_body[c][0] == iniX && snake_body[c][1] == iniY) //if the snake hits it self
		{
			i = 0;
			PlaySound(TEXT("failtrombone"), NULL, SND_FILENAME | SND_ASYNC);
			//PlaySound(TEXT("C:\\Users\\Moe\\Documents\\Visual Studio 2013\\Projects\\snake\\snake\\Debug\\failtrombone.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return i;
		}
	}
	i = 1;
	return i;
}
//printing score and name of player
void score()
{
	_posXY(5, 0);
	cout << "player: " << name;
	_posXY(60, 0);
	cout << "Score: " << score_val;
	_posXY(35, 0);
	cout << "'P' to pause";
}
void speed()//for setting snake speed 
{
	if (snake_direction == 1)
	{
		iniY--;
		Sleep(snake_speed + 10);
	}
	if (snake_direction == 2)
	{
		iniY += 1;
		Sleep(snake_speed + 10);
	}
	if (snake_direction == 3)
	{
		iniX += 1;
		Sleep(snake_speed);
	}
	if (snake_direction == 4)
	{
		iniX -= 1;
		Sleep(snake_speed);
	}
}
inline void pause() //pause function to pause the game if "P" button is pressed
{
	if (_kbhit()) //kbhit function returns integer if a key is in buffer
	{
		if (GetAsyncKeyState(P) == true)
			system("PAUSE>>NULL");
	}
}