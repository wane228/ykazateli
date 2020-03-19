#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

void build(char arr[12][12]) {
	for (int x = 0; x < 12; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			arr[x][y] = ' ';
			arr[x][0] = '#';
			arr[0][y] = '#';
			arr[11][y] = '#';
			arr[x][11] = '#';

		}
	}
}

void generate_ships(char map[12][12], int ships_size, int ships_count)
{
	bool installation_is_possible;
	int direction = 0;
	int x, y;
	int count = 0;
	while (1)
	{
		
		while (count < ships_count)
		{
			installation_is_possible = 1;
			x = 1 + rand() % 11;
			y = 1 + rand() % 11;
			int x_temp = x;
			int y_temp = y;
			direction = 1 + rand() % 4;
			for (int i = 1; i < ships_size + 1; i++)
			{
				if (map[x_temp][y_temp] == '#')
				{
					installation_is_possible = false;
					break;
				}
				if (map[x_temp][y_temp] == '*')
				{
					installation_is_possible = false;
					break;
				}
				if (map[x_temp+1][y_temp +1] == '*' || map[x_temp +1][y_temp-1] == '*' || map[x_temp-1][y_temp] == '*' || map[x_temp -1][y_temp +1] == '*')
				{
					installation_is_possible = false;
					break;
				}
				if (map[x_temp - 1][y_temp - 1] == '*' || map[x_temp][y_temp + 1] == '*' || map[x_temp][y_temp - 1] == '*' || map[x_temp + 1][y_temp] == '*')
				{
					installation_is_possible = false;
					break;
				}
	
				switch (direction)
				{
				case 1:  x_temp++; break;
				case 2:  y_temp++; break;
				case 3:  x_temp--; break;
				case 4:  y_temp--; break;
				}
				
			}

			if (installation_is_possible == true)
			{
				for (int i = 0; i < ships_size; i++)
				{
					map[x][y] = '*';
					switch (direction)
					{
					case 1:  x++; break;
					case 2:  y++; break;
					case 3:  x--; break;
					case 4:  y--; break;
					}
				}
				count++;
			}
		}
		return;
	}
}

void print_map(char map[12][12])
{

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	srand(time(NULL));
	char map[12][12];
	int count1 = 4;
	int	count2 = 1;
	while (1)
	{
		build(map);
		while (count2 != 5)
		{
			while (count1 != 0)
			{
				generate_ships(map, count1, count2);
				count2++;
				break;
			}
			count1--;
		}
		print_map(map);
		_getch();
		system("cls");
		count1 = 4;
		count2 = 1;
	}

	
	 
}
