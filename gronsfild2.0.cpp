#include <iostream>
#include <conio.h>

using namespace std;

void decryption(char word[5], char encryptedword[5], char decryptedword[5], int* check)
{
	char hack;
	int count = 0;
	for (int i = 4; i > -1;)
	{
		hack = encryptedword[i];
		for (int j = 0; j < 10; j++)
		{
			hack--;
			if (hack < 97)
			{
				hack = 122;
			}
			if (hack == word[i])
			{
				decryptedword[i] = hack;
				i--;
				continue;
			}
		}
		count++;
		if (count > 15)
		{
			*check = 0;
			return;
		}
	}
	*check = 1;
}

void print(char encryptedword[5], char word1[5], char word2[5], char word3[5], char word4[5], char word5[5], char decryptedword[5])
{
	int check = 0;
	decryption(word1, encryptedword, decryptedword, &check);
	if (check == 1)
	{
		cout << "Decrypted word: ";
		for (int i = 0; i < 5; i++)
		{
			cout << decryptedword[i];
		}
		cout << endl;
		return;
	}
	decryption(word2, encryptedword, decryptedword, &check);
	if (check == 1)
	{
		cout << "Decrypted word: ";
		for (int i = 0; i < 5; i++)
		{
			cout << decryptedword[i];
		}
		cout << endl;
		return;
	}
	decryption(word3, encryptedword, decryptedword, &check);
	if (check == 1)
	{
		cout << "Decrypted word: ";
		for (int i = 0; i < 5; i++)
		{
			cout << decryptedword[i];
		}
		cout << endl;
		return;
	}
	decryption(word4, encryptedword, decryptedword, &check);
	if (check == 1)
	{
		cout << "Decrypted word: ";
		for (int i = 0; i < 5; i++)
		{
			cout << decryptedword[i];
		}
		cout << endl;
		return;
	}
	decryption(word5, encryptedword, decryptedword, &check);
	if (check == 1)
	{
		cout << "Decrypted word: ";
		for (int i = 0; i < 5; i++)
		{
			cout << decryptedword[i];
		}
		cout << endl;
		return;
	}
	else
	{
		cout << "Failed to decrypt the word!!" << endl;
	}
}

void encryption(char word[5], char encryptedword[5])
{
	char hack;
	int count;
	int key[5];
	cout << "Enter your world: " << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> word[i];
	}
	cout << "Your word: ";
	for (int i = 0; i < 5; i++)
	{
		cout << word[i];
	}
	cout << endl;
	cout << "Enter your key: " << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> key[i];
	}
	cout << "Your key: ";
	for (int i = 0; i < 5; i++)
	{
		cout << key[i];
	}
	cout << endl;
	cout << "Encrypted word: ";
	for (int i = 0; i < 5; i++)
	{
		hack = word[i];
		count = key[i];
		for (int i = 0; i < count;)
		{
			if (hack == 122)
			{
				hack = 97;
			}
			else
			{
				hack++;
				i++;
			}
		}
		cout << hack;
		encryptedword[i] = hack;
	}
	cout << endl;

}







int main()
{
	char word1[5]{ 'h', 'e', 'l', 'l', 'o' };
	char word2[5]{ 'm', 'o', 'n', 'e', 'y' };
	char word3[5]{ 'm', 'u', 's', 'i', 'c' };
	char word4[5]{ 's', 'h', 'a', 'r', 'e' };
	char word5[5]{ 's', 't', 'e', 'a', 'm' };
	char myword[5];
	char encryptedword[5];
	char decryptedword[5];

	while (1)
	{
		encryption(myword, encryptedword);
		print(encryptedword, word1, word2, word3, word4, word5, decryptedword);
		_getche();
		system("cls");
	}
	return 0;
}