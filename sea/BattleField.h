#ifndef BATTLE_H
#define BATTLE_H
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>


using namespace std;

enum Color { Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue = 9, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };
enum Move { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, BackSpace = 8, Q = 113 };
class Battlefield
{
public:

	struct Ships
	{
		int deck = 0;
		bool horizontal = true;
		bool alive = true;
		int x, y;
	};

	int ship_pos[12][24] = { 0 }; //масив в який вписано наші кораблі, необхідний для їх відстеження та запису
	int enemy_ship_pos[12][24] = { 0 }; //масив необхідний для ворожих кораблів
	Ships* characteristic = new Ships[20];// масив кораблів

	inline Battlefield()
	{
		LoadCharactShips();
	}

	 void LoadCharactShips(); //присвоєння палуб кораблів

	 void SetCursor(int x, int y); //функція для встановлення курсора на координати х та у

	 void setColor(Color text, Color background); //функція для зміни кольору тексту та заднього фону

	 void createBattleField(bool enemy);// функція створення поля
	
	 void Paint(char variant[2][30], int T); //вибір ростановки кораблів

	 void PaintPos(int mas[12][24], int x, int num_color); //промалбовка карти згідно з встановленими корабликами
};

#endif