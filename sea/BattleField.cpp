#include "BattleField.h"
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
 void Battlefield::LoadCharactShips() //присвоєння палуб кораблів
{
	for (int i = 0; i < 20; i++) //загальна кількість кораблів 20: 10 наших, 10 бота
	{
		if (i == 0 || i == 10) //для 4-х палубних
		{
			characteristic[i].deck = 4;
		}
		else if (i > 0 && i <= 2 || i > 10 && i <= 12) //для 3-х палубних
		{
			characteristic[i].deck = 3;
		}
		else if (i > 2 && i <= 5 || i > 12 && i <= 15) //для 2-х палубних
		{
			characteristic[i].deck = 2;
		}
		else if (i > 5 && i <= 9 || i > 15 && i <= 19) ///для 1-о палубних
		{
			characteristic[i].deck = 1;
		}
	}
}

 void Battlefield::SetCursor(int x, int y) //функція для встановлення курсора на координати х та у
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}
 void Battlefield::setColor(Color text, Color background) //функція для зміни кольору тексту та заднього фону
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
 void Battlefield::createBattleField(bool enemy)// функція створення поля
{
	int X, num_color;
	if (enemy == false) {// якщо створюємо поле для нас, то ставимо курсор на початок(лівий верхній куток консолі)
		X = 0;
		num_color = 2;// ставимо колір зелений
	}
	else
	{
		X = 35;// якщо для ворога, то справа від нашого поля
		num_color = 5;//ставимо інший колір
	}
	SetCursor(X, 1);
	char mas[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	setColor(White, Color(num_color));
	int A = 0, B = 0;
	cout << "  " << mas[0]; //друкуємо А, бо вона просто так сама не надрукується
	for (int i = 0; i < 12; i++)
	{
		if (B == 0) //потрібна для виводу буковок
		{
			SetCursor(X + 3, 1 + i);// встановлюємо курсор на місце Б, бо А вже вивели
			B++;
		}
		else //інакше
		{
			SetCursor(X, 1 + i); //ставимо на початок поля
		}
		for (int g = 0; g < 23; g++) //виконуємо 23 рази, бо кількість стовпців 24 - для цифр зліва 2, кожна клітинка під буквами 2 (20шт) і 2 справа під кінець
		{
			if (i == 0 && g == 22) //колір для границі поля справа і зліва
			{
				setColor(Color(num_color), Color(num_color));

				cout << '+'; //малюємо будь-що, оскільки воно намалюється квадратом
			}
			if (i == 0 && g > 0 && g < 10) //виводимо букви
			{
				setColor(White, Color(num_color));

				cout << " " << mas[g];
			}
			else if (i > 0 && i < 11 && g == 0) //виводимо номери рядків
			{
				setColor(White, Color(num_color));
				if (i < 10) //для рядків 1-9 виводимо в кінці пробіл, щоб було рівненько
				{

					cout << i << ' ';
				}
				else
				{

					cout << i; //10 має 2 цифри, тому пробіл не треба
				}
			}
			else if (i == 11 || g > 20 && g < 23) //потрібно щоб вивести 2 останні кубика в останньому рядку
			{
				if (A == 0 && i == 11)
				{

					cout << "+";
					A++;
				}
				setColor(Color(num_color), Color(num_color));

				cout << '+';
			}
			else if (i > 0)// малюємо саме поле білим кольором
			{

				setColor(White, White);
				cout << '+';
			}
		}
	}
	setColor(Black, Black); //просто ставимо колір таким яким він був спочатку
}
 void Battlefield::Paint(char variant[2][30], int T) //вибір ростановки кораблів
{
	system("cls"); //очищуємо консоль
	for (int i = 0; i < 2; i++)// створюємо два елемента з репліками(Random location, manual location)
	{
		SetCursor(0, 15 + i); //ставимо курсор під полем
		for (int p = 0; p < 30; p++)
		{
			if (i == T)//перевірка на вибраний пункт
			{
				setColor(Black, White); //підсвічуємо вибраний пункт
			}
			else //інакше
			{
				setColor(White, Black); //прибираємо підсвітку
			}
			cout << variant[i][p]; //виводимо репліки як текст
		}
	}
	createBattleField(false); //створюємо поле знову
}

 void Battlefield::PaintPos(int mas[12][24], int x, int num_color) //промалбовка карти згідно з встановленими корабликами
{
	for (int i = 1; i < 11; i++) //виконуємо 10 разів, бо 10 рядків
	{
		int y = 1 + i; //встановлюємо координати 2;2 оскільки там початок саме ігрового поля
		SetCursor(x, y);//переміщаємо туди курсор

		for (int g = 2; g < 22; g++)  //кількість стовпців 20 (2 на 10 букв)
		{
			if (mas[i][g] == 2) //якщо в масиві на цьому місці 2
			{
				setColor(LightGray, LightGray); //то сіра клітинка, так буде позначатися порожня клітинка від пострілу
			}
			else if (mas[i][g] == 3) //якщо 3
			{
				setColor(LightMagenta, LightMagenta); //то така клітинка, так буде позначатися клітинка в яку попали і в якій був корабель
			}
			else if (mas[i][g] >= 4) //якщо більше 4
			{
				setColor(Color(num_color), Color(num_color)); //встановлюємо колір кораблів (наші - чорні / ворога - білі)
			}
			else //в інших випадках біла клітинка
			{
				setColor(White, White);
			}
			cout << "+";
		}
		//cout << "\n"; //перехід на новий рядок для повної окраски рядка
	}
}
