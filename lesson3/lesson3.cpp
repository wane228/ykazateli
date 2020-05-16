#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <ctime>
#include <conio.h>

using namespace std;
using json = nlohmann::json;

class chiper
{
public:
    virtual void encryp1() = 0;
    virtual void decryp1() = 0;
    virtual void key_generation() = 0;
};

class interface
{
public:
    void encrypt(chiper* x)
    {
        x->encryp1();
    }
    void decrypt(chiper* x)
    {
        x->decryp1();
    }
    void key_generation(chiper* x)
    {
        x->key_generation();
    }
};

class replacement : public chiper
{
private:
    void encryp1() override
    {
        string pathtokey;
        cout << ">> Введите путь к файлу с ключом(.key): ";
        cin >> pathtokey;
        string temp;
        bool trigger = 0;
        int i = 0;
        while (pathtokey[i] != '\0')
        {
            if (pathtokey[i] == '.' && pathtokey[i + 1] == 'k')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtokey[i];
            }
            i++;
        }
        if (temp != ".key")
        {
            cout << ">> Ошибка:: файл c ключом должен быть формата .key" << endl;
            return;
        }
        cout << ">> Введите путь к файлу с текстом(.txt): ";
        string pathtotext;
        cin >> pathtotext;
        temp.clear();
        i = 0;
        trigger = 0;
        while (pathtotext[i] != '\0')
        {
            if (pathtotext[i] == '.' && pathtotext[i + 1] == 't')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtotext[i];
            }
            i++;
        }
        if (temp != ".txt")
        {
            cout << ">> Ошибка:: файл c текстом должен быть формата .txt" << endl;
            return;
        }
        string userword;
        string encryptword;
        string alph1;
        string key;
        json keyj;
        ifstream file(pathtokey);

        if (check(pathtokey) == 0)
            return;

        file >> keyj;
        file.close();
        if (keyj.at("alg_type") != "replacement")
        {
            cout << ">> Ошибка:: метод шифрования ключа не соответствует выбранному\n";
            return;
        }
        for (int i = 0; i < keyj.at("key").size(); i++)
        {
            alph1 += keyj.at("key").at(i).at(0);
            key += keyj.at("key").at(i).at(1);
        }
        json j;
        j["alg_type"] = "replacement";
        j["text"] = { };
        ifstream file1(pathtotext);

        if (check(pathtotext) == 0)
            return;

        while (getline(file1, userword))
        {
            if (checkformistake(alph1, userword) == 1)
            {
                for (int k = 0; k < userword.size(); k++)
                {
                    for (int n = 0; n < key.size(); ++n)
                    {
                        if (userword[k] == alph1[n])
                        {
                            encryptword += key[n];
                            break;
                        }
                    }

                }
                j.at("text").push_back(encryptword);
                encryptword.clear();
            }
            else
            {
                return;
            }
        }
        file1.close();
        string pathtoencrypt = pathtotext;
        pathtoencrypt += ".encrypt";
        ofstream file2(pathtoencrypt);
        file2 << j;
        file2.close();
        check2(pathtoencrypt);
    }
    void decryp1() override
    {
        string pathtokey;
        cout << ">> Введите путь к файлу с ключом(.key): ";
        cin >> pathtokey;
        string temp;
        bool trigger = 0;
        int i = 0;
        while (pathtokey[i] != '\0')
        {
            if (pathtokey[i] == '.' && pathtokey[i + 1] == 'k')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtokey[i];
            }
            i++;
        }
        if (temp != ".key")
        {
            cout << ">> Ошибка:: файл c ключом должен быть формата .key\n";
            return;
        }
        cout << ">> Введите путь к файлу с зашифрованным текстом(.encrypt): ";
        string pathtotext;
        cin >> pathtotext;
        temp.clear();
        i = 0;
        trigger = 0;
        while (pathtotext[i] != '\0')
        {
            if (pathtotext[i] == '.' && pathtotext[i + 1] == 'e')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtotext[i];
            }
            i++;
        }
        if (temp != ".encrypt")
        {
            cout << ">> Ошибка:: файл c зашифрованным текстом должен быть формата .encrypt" << endl;
            return;
        }
        string userword;
        string alph1;
        string key;
        json keyj;
        ifstream file(pathtokey);
        if (check(pathtokey) == 0)
            return;
        file >> keyj;
        file.close();
        if (keyj.at("alg_type") != "replacement")
        {
            cout << ">> Ошибка:: метод шифрования ключа не соответствует выбранному!!\n";
            return;
        }
        for (int i = 0; i < keyj.at("key").size(); i++)
        {
            alph1 += keyj.at("key").at(i).at(0);
            key += keyj.at("key").at(i).at(1);
        }
        json encr;
        string encryptword;
        ifstream encrypt(pathtotext);
        if (check(pathtotext) == 0)
            return;
        encrypt >> encr;
        json decrypt;
        decrypt["alg_type"] = "replacement";
        decrypt["text"] = { };
        for (int i = 0; i < encr.at("text").size(); i++)
        {
            encryptword = encr.at("text").at(i);
			if (checkformistake(alph1, encryptword) == 1)
			{
				for (int k = 0; k < encryptword.size(); k++)
				{

					for (int n = 0; n < key.size(); ++n)
					{
						if (encryptword[k] == key[n])
						{
							userword += alph1[n];
							break;
						}
					}

				}
				decrypt["text"].push_back(userword);
				userword.clear();
			}
			else
			{
				return;
			}
        }
        encrypt.close();
        string pathtodecrypt = pathtotext;
        pathtodecrypt += ".decrypt";
        ofstream file2(pathtodecrypt);
        file2 << decrypt;
        file2.close();
        check2(pathtodecrypt);
    }
    void key_generation() override
    {
        string pathtoalph;
        cout << ">> Ведите путь к файлу с алфавитом(.alph): ";
        cin >> pathtoalph;
        string temp;
        bool trigger = 0;
        int i = 0;
        while (pathtoalph[i] != '\0')
        {
            if (pathtoalph[i] == '.' && pathtoalph[i + 1] == 'a')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtoalph[i];
            }
            i++;
        }
        if (temp != ".alph")
        {
            cout << "Ошибка:: файл c алфавитом должен быть формата .alph" << endl;
            return;
        }
        srand(time(NULL));
        json alph;
        string alph2;
        string key2;
        ifstream file(pathtoalph);
        if (check(pathtoalph) == 0)
            return;
        file >> alph;
        file.close();
        for (int i = 0; i < alph.at("alph").size(); i++)
        {
            alph2 += alph.at("alph").at(i);
        }
        for (int i = 0; i < alph2.size(); i++)
        {
			if (alph2.size() == alph.at("alph").size())
			{
				bool trigger2 = 0;
				char chipletter;

				chipletter = alph2[rand() % alph.at("alph").size()];
				for (int j = 0; j < key2.size(); j++)
				{
					if (chipletter == key2[j])
					{
						trigger2 = 1;
						break;
					}
					else
					{
						trigger2 = 0;
					}
				}
				if (trigger2 == 0)
				{
					key2 += chipletter;
				}
				else
				{
					i--;
				}
			}
			else
			{
				cout << ">> Ошибка:: неизвестная ошибка" << endl;
				return;
			}
        }
        json keyj;
        keyj["alg_type"] = "replacement";
        keyj["key"] = { };
        for (int i = 0; i < alph2.size(); i++)
        {
            string first;
            string second;
            first = alph2[i];
            second = key2[i];
            keyj.at("key").push_back(json::array({ first,second }));

        }
        string pathtokey = pathtoalph;
        pathtokey += ".key";
        ofstream file2(pathtokey);
        file2 << keyj;
        file2.close();
        check2(pathtokey);
    }
    bool checkformistake(string alph, string word) 
    {
        for (int i = 0; i < word.size(); i++)
        {
            bool trigger = 0;
			if (word[i] == 'а' || word[i] == 'б' || word[i] == 'в' || word[i] == 'г' || word[i] == 'д' || word[i] == 'е' || word[i] == 'ё' || word[i] == 'ж' || word[i] == 'з' || word[i] == 'и' || word[i] == 'к' || word[i] == 'л' || word[i] == 'м' || word[i] == 'н' || word[i] == 'й' || word[i] == 'о' || word[i] == 'п' || word[i] == 'р' || word[i] == 'с' || word[i] == 'т' || word[i] == 'у' || word[i] == 'ф' || word[i] == 'х' || word[i] == 'ц' || word[i] == 'ч' || word[i] == 'ш' || word[i] == 'щ' || word[i] == 'ъ' || word[i] == 'ы' || word[i] == 'ь' || word[i] == 'э' || word[i] == 'ю' || word[i] == 'я')
			{
				cout << ">> Ошибка:: нельзя использовать русские символы";
				return 0;
			}
			else if(word[i] == 'А' || word[i] == 'Б' || word[i] == 'В' || word[i] == 'Г' || word[i] == 'Д' || word[i] == 'Е' || word[i] == 'Ё' || word[i] == 'Ж' || word[i] == 'З' || word[i] == 'И' || word[i] == 'К' || word[i] == 'Л' || word[i] == 'М' || word[i] == 'Н' || word[i] == 'Й' || word[i] == 'О' || word[i] == 'П' || word[i] == 'Р' || word[i] == 'С' || word[i] == 'Т' || word[i] == 'У' || word[i] == 'Ф' || word[i] == 'Х' || word[i] == 'Ц' || word[i] == 'Ч' || word[i] == 'Ш' || word[i] == 'Щ' || word[i] == 'Ъ' || word[i] == 'Ы' || word[i] == 'Ь' || word[i] == 'Э' || word[i] == 'Ю' || word[i] == 'Я')
			{
				cout << ">> Ошибка:: нельзя использовать русские символы";
				return 0;
			}
            else
			{
				for (int j = 0; j < alph.size(); j++)
            
                if (word[i] == alph[j])
                {
                    trigger = 1;
                }
            }
            if (trigger == 0)
            {
                cout << ">> Ошибка:: используемый в тексте символ отсутствует в алфавите";
                return 0;
            }
        }
        return 1;
    }
    bool check(string pathtofile)
    {
        bool enable = 0;
        ifstream file(pathtofile);
        if (file.is_open())
        {
            enable = 1;
        }
        else
        {
            enable = 0;
            cout << ">> Ошибка:: файла не существует" << endl;
        }
        file.close();
        return enable;
    }
    void check2(string pathtofile)
    {
        ifstream file(pathtofile);
        if (file.is_open())
        {
            cout << ">> Ваш файл был сохранён: " << pathtofile << endl;

        }
        else
        {
            cout << ">> Ошибка:: не удалось сохранить файл" << endl;
        }
        file.close();
        return;
    }
};

class transposition : public chiper
{
private:
    bool check(string pathtofile)
    {
        bool enable = 0;
        ifstream file(pathtofile);
        if (file.is_open())
        {
            enable = 1;
        }
        else
        {
            enable = 0;
            cout << "Ошибка:: файла не существует" << endl;
        }
        file.close();
        return enable;
    }
    void check2(string pathtofile)
    {
        ifstream file(pathtofile);
        if (file.is_open())
        {
            cout << ">> Ваш файл был сохранён: " << pathtofile << endl;

        }
        else
        {
            cout << ">> Ошибка:: не удалось сохранить файл" << endl;
        }
        file.close();
        return;
    }
	bool checkformistake(string word)
	{
		for (int i = 0; i < word.size(); i++)
		{
			if (word[i] == 'а' || word[i] == 'б' || word[i] == 'в' || word[i] == 'г' || word[i] == 'д' || word[i] == 'е' || word[i] == 'ё' || word[i] == 'ж' || word[i] == 'з' || word[i] == 'и' || word[i] == 'к' || word[i] == 'л' || word[i] == 'м' || word[i] == 'н' || word[i] == 'й' || word[i] == 'о' || word[i] == 'п' || word[i] == 'р' || word[i] == 'с' || word[i] == 'т' || word[i] == 'у' || word[i] == 'ф' || word[i] == 'х' || word[i] == 'ц' || word[i] == 'ч' || word[i] == 'ш' || word[i] == 'щ' || word[i] == 'ъ' || word[i] == 'ы' || word[i] == 'ь' || word[i] == 'э' || word[i] == 'ю' || word[i] == 'я')
			{
				cout << ">> Ошибка:: нельзя использовать русские символы";
				return 0;
			}
			else if (word[i] == 'А' || word[i] == 'Б' || word[i] == 'В' || word[i] == 'Г' || word[i] == 'Д' || word[i] == 'Е' || word[i] == 'Ё' || word[i] == 'Ж' || word[i] == 'З' || word[i] == 'И' || word[i] == 'К' || word[i] == 'Л' || word[i] == 'М' || word[i] == 'Н' || word[i] == 'Й' || word[i] == 'О' || word[i] == 'П' || word[i] == 'Р' || word[i] == 'С' || word[i] == 'Т' || word[i] == 'У' || word[i] == 'Ф' || word[i] == 'Х' || word[i] == 'Ц' || word[i] == 'Ч' || word[i] == 'Ш' || word[i] == 'Щ' || word[i] == 'Ъ' || word[i] == 'Ы' || word[i] == 'Ь' || word[i] == 'Э' || word[i] == 'Ю' || word[i] == 'Я')
			{
				cout << ">> Ошибка:: нельзя использовать русские символы";
				return 0;
			}			
		}
		return 1;
	}
    void encryp1() override
    {
        srand(time(0));
        string pathtokey;
        cout << ">> Введите путь к файлу с ключом(.key): ";
        cin >> pathtokey;
        string temp;
        bool trigger = 0;
        int i = 0;
        while (pathtokey[i] != '\0')
        {
            if (pathtokey[i] == '.' && pathtokey[i + 1] == 'k')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtokey[i];
            }
            i++;
        }
        if (temp != ".key")
        {
            cout << ">> Ошибка:: файл c ключом должен быть формата .key" << endl;
            return;
        }
        cout << ">> Введите путь к файлу с текстом(.txt): ";
        string pathtotext;
        cin >> pathtotext;
        temp.clear();
        i = 0;
        trigger = 0;
        while (pathtotext[i] != '\0')
        {
            if (pathtotext[i] == '.' && pathtotext[i + 1] == 't')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtotext[i];
            }
            i++;
        }
        if (temp != ".txt")
        {
            cout << ">> Ошибка:: файл c текстом должен быть формата .txt" << endl;
            return;
        }
        json keyj;
        ifstream file(pathtokey);

        if (check(pathtokey) == 0)
            return;

        file >> keyj;
        file.close();
        if (keyj.at("alg_type") != "transposition")
        {
            cout << ">> Ошибка:: метод шифрования ключа не соответствует выбранному\n";
            return;
        }
        int blocksize = keyj.at("blocksize");
        vector<int>key;
        for (int i = 0; i < keyj.at("key").size(); i++)
        {
            key.push_back(keyj.at("key").at(i));
        }

        string userword;
        ifstream file1(pathtotext);

        if (check(pathtotext) == 0)
            return;
        vector<char>encryptword;
        json j;
        j["alg_type"] = "transposition";
        j["text"] = { };
        while (getline(file1, userword))
        {
			if (checkformistake(userword) == 0)
			{
				return;
			}
            if (blocksize == userword.size())
            {
                encryptword.resize(blocksize);
                for (int i = 0; i < encryptword.size(); i++)
                {
                    encryptword[i] = userword[key[i] - 1];
                }
                string encrtowrite;
                for (int i = 0; i < encryptword.size(); i++)
                {
                    encrtowrite += encryptword[i];
                }
                j["text"].push_back(encrtowrite);
            }
            else
            {
                while (userword.size() % blocksize != 0)
                {
                    userword += userword[rand() % userword.size()];
                }
                int count = userword.size() / blocksize;
                encryptword.resize(blocksize * count);
                int n = 0;
                int k = 0;
                for (int i = 0; i < encryptword.size(); i++)
                {
                    if (n > key.size() - 1)
                    {
                        n = 0;
                        k += blocksize;
                    }
                    encryptword[i] = userword[(key[n] - 1) + k];
                    n++;
                }
                string encrtowrite;
                for (int i = 0; i < encryptword.size(); i++)
                {
                    encrtowrite += encryptword[i];
                }
                j.at("text").push_back(encrtowrite);
            }
        }
        file1.close();
        pathtotext += ".encrypt";
        ofstream file2(pathtotext);
        file2 << j;
        file2.close();
        check2(pathtotext);
    }
    void decryp1() override
    {
        string pathtokey;
        cout << ">> Введите путь к файлу с ключом(.key): ";
        cin >> pathtokey;
        string temp;
        bool trigger = 0;
        int i = 0;
        while (pathtokey[i] != '\0')
        {
            if (pathtokey[i] == '.' && pathtokey[i + 1] == 'k')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtokey[i];
            }
            i++;
        }
        if (temp != ".key")
        {
            cout << ">> Ошибка:: файл c ключом должен быть формата .key" << endl;
            return;
        }
        cout << ">> Введите путь к файлу с зашифрованным текстом(.encrypt): ";
        string pathtotext;
        cin >> pathtotext;
        temp.clear();
        i = 0;
        trigger = 0;
        while (pathtotext[i] != '\0')
        {
            if (pathtotext[i] == '.' && pathtotext[i + 1] == 'e')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtotext[i];
            }
            i++;
        }
        if (temp != ".encrypt")
        {
            cout << ">> Ошибка:: файл c зашифрованным текстом должен быть формата .encrypt" << endl;
            return;
        }
        json keyj;
        ifstream file(pathtokey);

        if (check(pathtokey) == 0)
            return;

        file >> keyj;
        file.close();
        if (keyj.at("alg_type") != "transposition")
        {
            cout << ">> Ошибка:: метод шифрования ключа не соответствует выбранному\n";
            return;
        }
        int blocksize = keyj.at("blocksize");
        vector<int>key;
        for (int i = 0; i < keyj.at("key").size(); i++)
        {
            key.push_back(keyj.at("key").at(i));
        }
        string encryptword;
        json encr;
        ifstream encrypt(pathtotext);
        if (check(pathtotext) == 0)
            return;
        encrypt >> encr;
        vector<char>decryptword;
        json j;
        j["alg_type"] = "transposition";
        j["text"] = { };
        for (int l = 0; l < encr.at("text").size(); l++)
        {          
            encryptword = encr.at("text").at(l);
			if (checkformistake(encryptword) == 0)
			{
				return;
			}
            decryptword.resize(encryptword.size());
            if (blocksize == encryptword.size())
            {
                for (int i = 0; i < encryptword.size(); i++)
                {
                    decryptword[key[i] - 1] = encryptword[i];
                }
                string encrtowrite;
                for (int i = 0; i < decryptword.size(); i++)
                {
                    encrtowrite += decryptword[i];
                }
                j["text"].push_back(encrtowrite);
            }
            else
            {
                int k = 0;
                int n = 0;
                for (int i = 0; i < encryptword.size(); i++)
                {
                    if (n > key.size() - 1)
                    {
                        n = 0;
                        k += blocksize;
                    }
                    decryptword[(key[n] - 1) + k] = encryptword[i];
                    n++;
                }
                string encrtowrite;
                for (int i = 0; i < decryptword.size(); i++)
                {
                    encrtowrite += decryptword[i];
                }
                j["text"].push_back(encrtowrite);
            }
        }
        encrypt.close();
        pathtotext += ".decrypt";
        ofstream file2(pathtotext);
        file2 << j;
        file2.close();
        check2(pathtotext);
    }
    void key_generation() override
    {
        srand(time(0));
        int blocksize;
        cout << ">> Введите желаемый размер блока: ";
        cin >> blocksize;
        if (blocksize <= 0)
        {
            cout << ">> Ошибка:: размер блока должен быть >= 1";
            return;
        }
        vector<int>key;
        bool trigger = 0;
        for (int i = 0; i < blocksize; i++)
        {
            int n = 1 + rand() % + blocksize;
            for (int j = 0; j < key.size(); j++)
            {
                if (n == key[j])
                {
                    trigger = 1;
                    break;
                }
                else
                {
                    trigger = 0;
                }
            }
            if (trigger == 0)
            {
                key.push_back(n);
            }
            else
            {
                i--;
            }
        }
        json j;
        j["alg_type"] = "transposition";
        j["blocksize"] = blocksize;
        j["key"] = { };
        for (int i = 0; i < key.size(); i++)
        {
            j.at("key").push_back(key[i]);
        }
        string pathtokey, filename;
        cout << ">> Введите путь, куда желаете сохранить файл с ключом: ";
        cin >> pathtokey;
        cout << ">> Введите название файла(включая .key): ";
        cin >> filename;
        if (pathtokey[pathtokey.size() - 1] != 92 && filename[0] != 92)
        {
            pathtokey += 92;
        }
        pathtokey += filename;
        ofstream file2(pathtokey);
        file2 << j;
        file2.close();
        check2(pathtokey);
    }
};

class gamming : public chiper
{
private:
    bool check(string pathtofile)
    {
        bool enable = 0;
        ifstream file(pathtofile);
        if (file.is_open())
        {
            enable = 1;
        }
        else
        {
            enable = 0;
            cout << "Ошибка:: файла не существует" << endl;
        }
        file.close();
        return enable;
    }
    void check2(string pathtofile)
    {
        ifstream file(pathtofile);
        if (file.is_open())
        {
            cout << ">> Ваш файл был сохранён: " << pathtofile << endl;

        }
        else
        {
            cout << ">> Ошибка:: не удалось сохранить файл";
        }
        file.close();
        return;
    }
    void encryp1() override
    {
        string pathtokey;
        cout << ">> Введите путь к файлу с ключом(.key): ";
        cin >> pathtokey;
        string temp;
        bool trigger = 0;
        int i = 0;
        while (pathtokey[i] != '\0')
        {
            if (pathtokey[i] == '.' && pathtokey[i + 1] == 'k')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtokey[i];
            }
            i++;
        }
        if (temp != ".key")
        {
            cout << ">> Ошибка:: файл c ключом должен быть формата .key" << endl;
            return;
        }
        cout << ">> Введите путь к файлу с текстом(.txt): ";
        string pathtotext;
        cin >> pathtotext;
        temp.clear();
        i = 0;
        trigger = 0;
        while (pathtotext[i] != '\0')
        {
            if (pathtotext[i] == '.' && pathtotext[i + 1] == 't')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtotext[i];
            }
            i++;
        }
        if (temp != ".txt")
        {
            cout << ">> Ошибка:: файл c текстом должен быть формата .txt" << endl;
            return;
        }
        json keyj;
        ifstream file(pathtokey);

        if (check(pathtokey) == 0)
            return;

        file >> keyj;
        file.close();
        if (keyj.at("alg_type") != "gamming")
        {
            cout << ">> Ошибка:: метод шифрования ключа не соответствует выбранному\n";
            return;
        }
        vector<int>key;
        string key2;
        for (int i = 0; i < keyj.at("key").size(); i++)
        {
            key2 = keyj.at("key").at(i);
            key.push_back(stoi(key2));
        }
        int blocksize = key.size();
        json alph;
        string alph2;
        string pathtoalph;
        cout << ">> Ведите путь к файлу с алфавитом(.alph): ";
        cin >> pathtoalph;
        ifstream file3(pathtoalph);
        if (check(pathtoalph) == 0)
            return;
        file3 >> alph;
        file.close();
        for (int i = 0; i < alph.at("alph").size(); i++)
        {
            alph2 += alph.at("alph").at(i);
        }
        string userword;
        string encryptword;
        json j;
        j["alg_type"] = "gamming";
        j["text"] = { };
        ifstream file1(pathtotext);
        
        if (check(pathtotext) == 0)
            return;

        while (getline(file1, userword))
        {
            if (checkformistake(alph2, userword) == 1)
            {
                if (userword.size() == blocksize)
                {
                    for (int i = 0; i < userword.size(); i++)
                    {
                        int num = 0;
                        for (num; num < alph2.size(); num++)
                        {
                            if (alph2[num] == userword[i])
                            {
                                break;
                            }
                        }
                        int temp2 = num + key[i];
                        temp2 = temp2 % alph2.size();
                        encryptword += alph2[temp2];
                    }
                    j["text"].push_back(encryptword);
                    encryptword.clear();
                }
                else
                {
                    int n = 0;
                    for (int i = 0; i < userword.size(); i++)
                    {
                        if (n > key.size() - 1)
                        {
                            n = 0;
                        }
                        int num = 0;
                        for (num; num < alph2.size(); num++)
                        {
                            if (alph2[num] == userword[i])
                            {
                                break;
                            }
                        }
                        int temp2 = num + key[n];
                        temp2 = temp2 % alph2.size();
                        encryptword += alph2[temp2];
                        n++;
                    }
                    j["text"].push_back(encryptword);
                    encryptword.clear();
                }
            }
            else
            {
                return;
            }
        }
        file1.close();
        pathtotext += ".encrypt";
        ofstream file2(pathtotext);
        file2 << j;
        file2.close();
        check2(pathtotext);

    }
	bool checkformistake(string alph, string word)
	{
		for (int i = 0; i < word.size(); i++)
		{
			bool trigger = 0;
			if (word[i] == 'а' || word[i] == 'б' || word[i] == 'в' || word[i] == 'г' || word[i] == 'д' || word[i] == 'е' || word[i] == 'ё' || word[i] == 'ж' || word[i] == 'з' || word[i] == 'и' || word[i] == 'к' || word[i] == 'л' || word[i] == 'м' || word[i] == 'н' || word[i] == 'й' || word[i] == 'о' || word[i] == 'п' || word[i] == 'р' || word[i] == 'с' || word[i] == 'т' || word[i] == 'у' || word[i] == 'ф' || word[i] == 'х' || word[i] == 'ц' || word[i] == 'ч' || word[i] == 'ш' || word[i] == 'щ' || word[i] == 'ъ' || word[i] == 'ы' || word[i] == 'ь' || word[i] == 'э' || word[i] == 'ю' || word[i] == 'я')
			{
				cout << ">> Ошибка:: нельзя использовать русские символы";
				return 0;
			}
			else if (word[i] == 'А' || word[i] == 'Б' || word[i] == 'В' || word[i] == 'Г' || word[i] == 'Д' || word[i] == 'Е' || word[i] == 'Ё' || word[i] == 'Ж' || word[i] == 'З' || word[i] == 'И' || word[i] == 'К' || word[i] == 'Л' || word[i] == 'М' || word[i] == 'Н' || word[i] == 'Й' || word[i] == 'О' || word[i] == 'П' || word[i] == 'Р' || word[i] == 'С' || word[i] == 'Т' || word[i] == 'У' || word[i] == 'Ф' || word[i] == 'Х' || word[i] == 'Ц' || word[i] == 'Ч' || word[i] == 'Ш' || word[i] == 'Щ' || word[i] == 'Ъ' || word[i] == 'Ы' || word[i] == 'Ь' || word[i] == 'Э' || word[i] == 'Ю' || word[i] == 'Я')
			{
				cout << ">> Ошибка:: нельзя использовать русские символы";
				return 0;
			}
			else
			{
				for (int j = 0; j < alph.size(); j++)

					if (word[i] == alph[j])
					{
						trigger = 1;
					}
			}
			if (trigger == 0)
			{
				cout << ">> Ошибка:: используемый в тексте символ отсутствует в алфавите";
				return 0;
			}
		}
		return 1;
	}
    void decryp1() override
    {
        string pathtokey;
        cout << ">> Введите путь к файлу с ключом(.key): ";
        cin >> pathtokey;
        string temp;
        bool trigger = 0;
        int i = 0;
        while (pathtokey[i] != '\0')
        {
            if (pathtokey[i] == '.' && pathtokey[i + 1] == 'k')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtokey[i];
            }
            i++;
        }
        if (temp != ".key")
        {
            cout << ">> Ошибка:: файл c ключом должен быть формата .key" << endl;
            return;
        }
        cout << ">> Введите путь к файлу с зашифрованным текстом(.encrypt): ";
        string pathtotext;
        cin >> pathtotext;
        temp.clear();
        i = 0;
        trigger = 0;
        while (pathtotext[i] != '\0')
        {
            if (pathtotext[i] == '.' && pathtotext[i + 1] == 'e')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtotext[i];
            }
            i++;
        }
        if (temp != ".encrypt")
        {
            cout << ">> Ошибка:: файл c зашифрованным текстом должен быть формата .encrypt" << endl;
            return;
        }
        json keyj;
        ifstream file(pathtokey);

        if (check(pathtokey) == 0)
            return;

        file >> keyj;
        file.close();
        if (keyj.at("alg_type") != "gamming")
        {
            cout << ">> Ошибка:: метод шифрования ключа не соответствует выбранному\n";
            return;
        }
        vector<int>key;
        string key2;
        for (int i = 0; i < keyj.at("key").size(); i++)
        {
            key2 = keyj.at("key").at(i);
            key.push_back(stoi(key2));
        }
        int blocksize = key.size();
        json alph;
        string alph2;
        string pathtoalph;
        cout << ">> Ведите путь к файлу с алфавитом(.alph): ";
        cin >> pathtoalph;
        temp.clear();
        i = 0;
        trigger = 0;
        while (pathtoalph[i] != '\0')
        {
            if (pathtoalph[i] == '.' && pathtoalph[i + 1] == 'a')
            {
                trigger = 1;
            }
            if (trigger == 1)
            {
                temp += pathtoalph[i];
            }
            i++;
        }
        if (temp != ".alph")
        {
            cout << ">> Ошибка:: файл c текстом должен быть формата .alph" << endl;
            return;
        }
        ifstream file3(pathtoalph);
        if (check(pathtoalph) == 0)
            return;
        file3 >> alph;
        file3.close();
        for (int i = 0; i < alph.at("alph").size(); i++)
        {
            alph2 += alph.at("alph").at(i);
        }
        string encryptword;
        string userword;
        json encr;
        json j;
        j["alg_type"] = "gamming";
        j["text"] = { };
        ifstream encrypt(pathtotext);
        if (check(pathtotext) == 0)
            return;
        encrypt >> encr;
        for (int l = 0; l < encr.at("text").size(); l++)
        {
            encryptword = encr.at("text").at(l);
			if (checkformistake(alph2, encryptword) == 0)
			{
				return;
			}
            if (encryptword.size() == blocksize)
            {
                for (int i = 0; i < encryptword.size(); i++)
                {
                    int num = 0;
                    for (num; num < alph2.size(); num++)
                    {
                        if (alph2[num] == encryptword[i])
                        {
                            break;
                        }
                    }
                    int temp2 = num + alph2.size() - key[i];
                    temp2 = temp2 % alph2.size();
                    userword += alph2[temp2];
                }
                j["text"].push_back(userword);
                userword.clear();
            }
            else
            {
                int n = 0;
                for (int i = 0; i < encryptword.size(); i++)
                {
                    if (n > key.size() - 1)
                    {
                        n = 0;
                    }
                    int num = 0;
                    for (num; num < alph2.size(); num++)
                    {
                        if (alph2[num] == encryptword[i])
                        {
                            break;
                        }
                    }
                    int temp2 = num - key[n];;
                    while (temp2 <= 0)
                    {
                        temp2 += alph2.size();
                    }
                    if (temp2 != alph.size())
                    {
                        temp2 = temp2 % alph2.size();
                    }
                    userword += alph2[temp2];
                    n++;
                }
                j["text"].push_back(userword);
                userword.clear();
            }
        }
        encrypt.close();
        
        pathtotext += ".decrypt";
        ofstream file2(pathtotext);
        file2 << j;
        file2.close();
        check2(pathtotext);
    }
    void key_generation() override
    {
        srand(time(0));
        int blocksize;
        cout << ">> Введите желаемый размер блока: ";
        cin >> blocksize;
        if (blocksize <= 0)
        {
            cout << ">> Ошибка:: размер блока должен быть >= 1";
            return;
        }
        vector<int>key;
        bool trigger1 = 0;
        for (int i = 0; i < blocksize; i++)
        {
            int n = 1 + rand() % 100;
            for (int j = 0; j < key.size(); j++)
            {
                if (n == key[j])
                {
                    trigger1 = 1;
                    break;
                }
                else
                {
                    trigger1 = 0;
                }
            }
            if (trigger1 == 0)
            {
                key.push_back(n);
            }
            else
            {
                i--;
            }
        }
        json j;
        j["alg_type"] = "gamming";
        j["key"] = { };
        for (int i = 0; i < key.size(); i++)
        {
            j.at("key").push_back(to_string(key[i]));
        }
        string pathtokey, filename;
        cout << ">> Введите путь, куда желаете сохранить файл с ключом: ";
        cin >> pathtokey;
        cout << ">> Введите название файла(включая .key): ";
        cin >> filename;
        if (pathtokey[pathtokey.size() - 1] != 92 && filename[0] != 92)
        {
            pathtokey += 92;
        }
        pathtokey += filename;
        ofstream file2(pathtokey);
        file2 << j;
        file2.close();
        check2(pathtokey);
    }
};

int main()
{
    setlocale(0, "");
    interface in;
    replacement re;
    transposition tr;
    gamming gm;
    for (;;)
    {
        cout << ">> Главное меню:" << endl << ">>    1) Зашифровать/Расшифровать" << endl << ">>    2) Сгенерировать ключ" << endl << ">> Ваш выбор: ";
        int x;
        cin >> x;
        switch (x)
        {
        case 1: cout << ">> Зашифровать/Расшифровать:" << endl << ">>    1) Зашифровать " << endl << ">>    2) Расшифровать" << endl << ">> Ваш выбор: ";
            int q;
            cin >> q;
            switch (q)
            {
            case 1: cout << ">> Выберите метод шифрования:" << endl << ">>    1) Шифр замены" << endl << ">>    2) Шифр перестановки" << endl << ">>    3) Шифр гаммирования" << endl << ">> Ваш выбор: ";
                int z;
                cin >> z;
                switch (z)
                {
                case 1: in.encrypt(&re); break;
                case 2: in.encrypt(&tr); break;
                case 3: in.encrypt(&gm); break;
                default:
                    cout << ">> Ошибка:: выберите один из вариантов" << endl;
                    break;
                }
                break;
            case 2: cout << ">> Выберите метод шифрования:" << endl << ">>    1) Шифр замены " << endl << ">>    2) Шифр перестановки" << endl << ">>    3) Шифр гаммирования" << endl << ">> Ваш выбор: ";
                int a;
                cin >> a;
                switch (a)
                {
                case 1: in.decrypt(&re); break;
                case 2: in.decrypt(&tr); break;
                case 3: in.decrypt(&gm); break;
                default:
                    cout << ">> Ошибка:: выберите один из вариантов" << endl;
                    break;
                }
                break;
            default:
                cout << ">> Ошибка:: выберите один из вариантов" << endl;
                break;
            }
            break;
        case 2:
            cout << endl << ">> Выполняется процедура генерации ключа...." << endl << endl << ">> Выберите метод шифрофровки/расшифровки:" << endl << ">>    1) Шифр замены" << endl << ">>    2) Шифр перестановки" << endl << ">>    3) Шифр гаммирования" << endl;
            cout << ">> Ваш выбор: ";
            int y;
            cin >> y;
            switch (y)
            {
            case 1:  in.key_generation(&re); break;
            case 2: in.key_generation(&tr); break;
            case 3:  in.key_generation(&gm); break;
            default:
                cout << ">> Ошибка:: выберите один из вариантов" << endl;
                break;
            }
            break;
        default:
            cout << ">> Ошибка:: выберите один из вариантов" << endl;
            break;
        }
        _getche();
        system("cls");
    }



}
