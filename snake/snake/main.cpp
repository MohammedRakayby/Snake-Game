#include "functions.h"

using namespace std;

int main()
{
	srand(time(NULL));                                                  //seeding rand function with time
	cout << "Enter your name: " << endl;                                   //entering player name
	getline(cin, name);
	system("CLS");
	draw_board();                                                    // drawing map
	_posXY(xTar, yTar);                                             //positioning food
	cout << "@";
	while (movement_key != ESC && game_over())                     //game loop inturpted by esc button or game_over
	{
		rem_snake_body();                                       //romving snake body
		store_snake_pos();                                     // storing snake coordinates
		draw_snake_body();                                    //drawing snake body
		inc_snake_size();                                    //increasing snake body after eating food
		score();                                            // score function		
		mov_snake();                                       //moving snake
		speed();                                          //set snake's speed
		pause();                                         //pause game
	}
	if (game_over() == 0)
	{
		_posXY(33, 10);
		cout << "--you lost!-- " << endl;
	}

	system("pause>>NULL");
	return 0;
}