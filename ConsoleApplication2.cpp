#include <iostream>
using namespace std;

void zapolnenie_massiva(int* stroki, int *stolbi, int** array2)
{

	for (int i = 0; i < *stroki; i++)
	{
		for (int j = 0; j < *stolbi; j++)
		{
			cin >> array2[i][j];
		}
    
	}
}

void vivod_massiva(int* stroki, int* stolbi, int** array2)
{
	for (int i = 0; i < *stroki; i++)
	{
		for (int j = 0; j < *stolbi; j++)
		{
			cout << array2[i][j] << " ";
		}
		cout << endl;
	}
}

void ydalenie_massiva(int* stroki1, int** array2)
{
	for (int i = 0; i < *stroki1; i++)
	{
		delete[] array2[i];
	}
	delete[] array2;
}

int main()
{
	int stroki;
	int stolbi;
	cin >> stroki >> stolbi;
	int** array1 = new int*[stroki];
	for (int i = 0; i < stroki; i++)
		array1[i] = new int[stolbi];
	zapolnenie_massiva( &stroki, &stolbi, array1);
	vivod_massiva(&stroki, &stolbi, array1);
	ydalenie_massiva(&stroki, array1);

}

