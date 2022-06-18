#define HOME	75
#define DOWN	80
#define NEXT	77
#define UP	72
#define ESC	27
#define INS	82
#define DEL	83
#define ENTER	13
#define TAB 9


#include "TText.h"
#include "TLink.h"
#include <Windows.h>
#include <conio.h>

void clrscr(void);
void clreol(void);
void gotoxy(int x, int y);

TMemory TLink::mem;
int LinkCount = 180;

int main() {
	setlocale(LC_ALL, "Russian");
	TLink::InitMem(LinkCount);
	TText text;
	TLink tmp;

	char s;
	char buf[80];
	bool flag = true;
	bool f = true; 
	text.Read("lab.txt");
	text.Print(); 
		
	cout << "r - прочитать из файла\n" <<
		"p - напечатать на экране\n" <<
		"s - сохранить в файле\n" <<
		"c - отчистить экран \n" <<
		"DEL - отчистить память\n" <<
		"v^<> - кнопки для навигации по тексту\n" <<
		"1 - вставить новую строку текущего уровня\n" <<
		"2 - вставить новую строку текущего уровня и включить в нее следующую строку с подстроками\n" <<
		"3 - вставить новую строку на уровень ниже\n" <<
		"4 - вставить новую строку на уровень ниже и включить в нее следующую строку с подстроками\n" <<
		"5 - удалить следующую строку этого уровня\n" <<
		"6 - удалить строку на уровень нижу\n";
		


	while (true) {

		cout << "нажмите кнопку: ";

		s = _getch();
		cout << s << endl;

		switch (s) {
		case TAB: cout <<   "r - прочитать из файла\n"<<
							"p - напечатать на экране\n" <<
							"s - сохранить в файле\n" << 
							"c - отчистить экран \n" <<
							"DEL - отчистить память\n" <<
							"v^<> - кнопки для навигации по тексту\n" << 
							"1 - вставить новую строку текущего уровня\n" << 
							"2 - вставить новую строку текущего уровня и включить в нее следующую строку с подстроками\n" <<
							"3 - вставить новую строку на уровень ниже\n" << 
							"4 - вставить новую строку на уровень ниже и включить в нее следующую строку с подстроками\n" << 
							"5 - удалить следующую строку этого уровня\n" << 
							"6 - удалить строку на уровень нижу\n";
			break;
		case 'r': 
			text.Read("lab.txt");
			if (text.GetpFirst() == NULL) 
			{ cout << "ошибка при чтении\n"; }
			else 
			{ flag = true; cout << "чтение завершено\n"; }; 
			break;
		case 'p':
			text.Print(); 
			break;
		
		case 'c': 
			clrscr();
			cout << "TAB - увидеть все кнопки\n";
			break;
		case DEL:
			if (flag) 
			{ 
				TLink::MemCleaner(text);
				flag = false;
				cout << "память была отчищена\n";
			}
				  else 
				cout << "память уже пустая\n"; 
			break;
		case 's': 
			text.Write("savefile.txt"); 
			break;
		case ESC: 
			if (flag) 
			{ TLink::MemCleaner(text); }
			return 0;
		case UP :
			text.GoPrevLink();
			text.Print();
			break;
		case DOWN:
			text.GoNextLink();
			text.Print();
			break;
		case NEXT:
			text.GoDownLink();
			text.Print();
			break;
		case HOME :
			text.GoFirstLink();
			text.Print();
			break;
		case '1': 
			cout << "введите строку: ";
			cin >> buf; text.InsNextLine(buf); 
			text.Print(); 
			break;
		case '2': 
			cout << "введите строку: ";
			cin >> buf; text.InsNextSection(buf); 
			text.Print(); 
			break;
		case '3':
			cout << "введите строку: ";
			cin >> buf;
			text.InsDownLine(buf);
			text.Print(); 
			break;
		case '4': 
			cout << "введите строку: ";
			cin >> buf;
			text.InsDownSection(buf);
			text.Print(); 
			break;
		case '5': 
			text.DelNext();
			text.Print();
			break;
		case '6':
			text.DelDown(); 
			text.Print();
			break;
		default:
			cout << "такой кнопки нет\n";
		}
	}
}




void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console) return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	DWORD Count;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X * buf.dwSize.Y, zpos, &Count);
	SetConsoleCursorPosition(Console, zpos);
}

void clreol(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;

	COORD zpos = buf.dwCursorPosition;

	zpos.X = buf.dwCursorPosition.X + 1;
	zpos.Y = buf.dwCursorPosition.Y;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X - buf.dwCursorPosition.X - 1, zpos, &Count);
	SetConsoleCursorPosition(Console, buf.dwCursorPosition);
}

void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}
