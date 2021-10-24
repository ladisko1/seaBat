#include "gameCenter.h"

GameCenter::GameCenter(int t)
{
	Battlefield a;
	a.createBattleField(false);

	char variant[2][30] = { "RANDOM LOCATION","MANUAL LOCATION" };
	int key = 1, y = 2, x = 2, num = 0, change = 1, A = 0, xx = 37, yy = 2, up = 0, down = 0, over = 0;
	bool manual_placement = true, your_turn = 0 + rand() % 2, start = false;
	a.Paint(variant, change);
	do
	{
		key = _getch();//отримуємо номер натимсненої клавіші
		switch (key) //перевіряємо ключ
		{
		case Up: //якщо стрілка вгору
			if (y > 0) //якщо у більше 0
			{
				y--; //віднімаємо 1 в у
				change = y;
				a.Paint(variant, change); //виводимо пункт на екран
			}
			break;
		case Down: //якщо нажали стрілка вниз
			if (y < 1) //якщо у менше 1
			{
				y++; //збільшуємо у
				change = y;
				a.Paint(variant, change); //виводимо пункт на екран
			}
			break;
		case Enter:
			do
			{
				switch (change)
				{
				case 0: // якщо у був 0
					manual_placement = false; //автоматичне розташування
					A++; //змінна для завершення циклу вибору розташування
					break;
				case 1:
					manual_placement = true; //ручне розташування
					A++; //змінна для завершення циклу вибору розташування
					y++; //збільшуємо у
					break;
				}
			} while (key != Enter);
		}
	} while (A < 1);
	system("cls"); //очищуємо консоль
	a.createBattleField(false);

	x = 2, y = 2;
	if (manual_placement == true && num < 10) //ручна розкладка
	{
		do //запускаємо цикл, де в залежності від натисненої клавіші виконується та чи інша дія
		{
			a.PaintPos(a.ship_pos, 2, 0); //перемальовуємо ігрову локацію з урахувати с урахуванням зміни(поставили корабель)
			a.SetCursor(x, y); //ставимо курсор на змінені координати
			a.setColor(Black, Black); //встановлюємо чорний колір малювання корабля
			if (a.characteristic[num].horizontal == true) //якщо корабель ставиться по горизонталі
			{
				for (int i = 0; i < a.characteristic[num].deck; i++) //запускаємо цикл відмальовки відповідного корабля з відповідною кількістю палуб
				{
					cout << "++"; //малюємо 2 знака, бо клітинка займає 2 місця
				}
			}
			else if (a.characteristic[num].horizontal == false)// якщо по вертикалі
			{
				y += a.characteristic[num].deck; //змінюємо у
				for (int i = 0; i < a.characteristic[num].deck; i++)  //запускаємо цикл відмальовки відповідного корабля з відповідною кількістю палуб
				{
					cout << "++"; //малюємо 2 знака, бо клітинка займає 2 місця
					y--; //спускаємося на 1 клітинку
					a.SetCursor(x, y); //устанавлюємо курсор на 1 клітинку нижче
				}
			}
			key = _getch();//визначаємо нажату клавішу
			switch (key) //згідно з нажатою клавішою виконуємо відповідні дії
			{
			case Left: //якщо нажати стрілка вліво
				if (x > 3) //позиція до якої дозволено рух вліво
				{
					x -= 2; //віднімаємо від х одну позицію
				}
				break;
			case Right: //якщо нажали стрілку вправо
				if (a.characteristic[num].horizontal == true) //якщо кораблик має горизонтальне положення
				{
					if (x < 22 - a.characteristic[num].deck * 2) // перевіряємо чи не пройшов корабель границю поля
					{
						x += 2; //міняємо х на 2, оскільки клітинка займає 2 позиції
					}
				}
				else  //якщо кораблик має вертикальне положення
				{
					if (x < 20) // перевіряємо чи не пройшов корабель границю поля
					{
						x += 2; //міняємо х на 2, оскільки клітинка займає 2 позиції
					}
				}
				break;
			case Up: //якщо нажали "стрілочка вверх"
				if (y > 2) //позиція до якої дозволено рух вверх
				{
					y--;  //міняємо значення по Y на -1
				}
				break;
			case Down: //якщо нажали "Стрілочка вниз"
				if (a.characteristic[num].horizontal == false) //якщо кораблик має вертикальне положення
				{
					if (y < 12 - a.characteristic[num].deck) // перевіряємо чи не перейшов корабель границі
					{
						y++;  //міняємо значення по Y на +1
					}
				}
				else
				{
					if (y < 11) //перевіряємо чи не перейшов корабель границі
					{
						y++;  //меняем значение по Y на +1
					}
				}
				break;
			case Q: //якщо нажали "Q"
				a.characteristic[num].horizontal = !a.characteristic[num].horizontal; //змінюємо орієнтацію кораблика на протилежну
				if (a.characteristic[num].horizontal == false && y + a.characteristic[num].deck >= 13)
					//перевіряємо чи не зачепить кораблик границю по вертикалі
				{
					y -= y + a.characteristic[num].deck - 12; //якщо так, то змінюємо його позицію так, щоб він  не пройшов скрізь границі поля
				}
				else if (a.characteristic[num].horizontal == true && x + a.characteristic[num].deck * 2 >= 24)
					//перевіряємо чи не зачепить кораблик границю по вертикалі
				{
					x -= (x + a.characteristic[num].deck * 2) - 22; //якщо так, то змінюємо його позицію так, щоб він  не пройшов скрізь границі поля
				}
				for (int i = 0; i < 10 - num; i++) //змінюємо орієнтацію для подальших кораблів
				{
					a.characteristic[num + i].horizontal = a.characteristic[num].horizontal; // змінюємо положення наступного корабля на те що вибране зараз
				}
				break;
			case Enter: // якщо нажали ЕНТЕР
				if (a.characteristic[num].horizontal == true && a.ship_pos[y - 1][x] == 0 && a.ship_pos[y - 1][x + a.characteristic[num].deck * 2 - 2] == 0)
				{
					a.characteristic[num].x = x + 2, a.characteristic[num].y = y;
					for (size_t q = 0; q < 3; q++) //виконуємо триччі, оскільки нам треба щоб кораблі не стояли  поруч
					{
						for (size_t w = 1; w < a.characteristic[num].deck * 3 + 1; w++) //виконуємо одинадцять раз, оскільки нам треба щоб 4 палубний повністю окупував місця
						{
							a.ship_pos[y - 2 + q][x - 3 + w] = 1; //змінюємо значення в двовимірному масиві на різні цифри, тут на 1(буде виведений білий колір)
						}
					}
					for (int g = 0; g < 2 * a.characteristic[num].deck; g++) //виконуємо 8 раз, оскільки одна палуба це дві клітинки в ширину 
					{
						a.ship_pos[y - 1][x + g] = 13 - num;  //змінюємо значення в двовимірному масиві на різні цифри, тут будуть числа більше 4(буде виведений чорний колір)
					}
					num++; //переходим до наступного кораблика
				}
				if (a.characteristic[num].horizontal == false && a.ship_pos[y - 1][x] == 0 && a.ship_pos[y + a.characteristic[num].deck - 2][x] == 0)
				{
					a.characteristic[num].x = x + 2, a.characteristic[num].y = y;
					for (size_t q = 0; q < a.characteristic[num].deck + 2; q++)
					{
						for (size_t w = 0; w < 6; w++) //виконуємо шість раз, оскільки нам треба щоб кораблі не стояли  поруч
						{
							a.ship_pos[y - 2 + q][x - 2 + w] = 1; //змінюємо значення в двовимірному масиві на різні цифри, тут на 1(буде виведений білий колір)
						}
					}
					for (int g = 0; g < a.characteristic[num].deck; g++)
					{
						for (int n = 0; n < 2; n++) //виконуємо двіччі, оскільки одна палуба це 2 клітинки
						{
							a.ship_pos[y - 1 + g][x + n] = 13 - num; //змінюємо значення в двовимірному масиві на різні цифри, тут будуть числа більше 4(буде виведений чорний колір)
						}
					}
					num++; //переходимо до наступного корабля
				}
			}
			start = true;//запускаємо гру
		} while (num <= 9); //цикл працює до тих пір поки кількість поставлених кораблів не дорівнює 10
	}

	a.createBattleField(true);
}
