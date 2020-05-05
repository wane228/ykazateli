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
    void encrypt(chiper *x)
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
            cout << ">> Ошибка:: файл c текстом должен быть формата .txt"<<endl;
            return;
        }
        string userword;
        string encryptword;
        vector<string>alph1;
        vector<string>key;
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
            alph1.push_back(keyj.at("key").at(i).at(0));
            key.push_back(keyj.at("key").at(i).at(1));
        }
        ifstream file1(pathtotext);

        if (check(pathtotext) == 0)
            return;

        getline(file1, userword);
        for (int k = 0; k < userword.size(); k++)
        {
            for (int n = 0; n < key.size(); ++n)
            {
                if (userword[k] == alph1[n][0])
                {
                    encryptword += key[n][0];
                    break;
                }
            }

        }
        json j;
        j["alg_type"] = "replacement";
        j[userword] = encryptword;
        string pathtoencrypt = pathtotext;
        pathtoencrypt += ".encrypt";
        ofstream file2(pathtoencrypt);
        file2 << j;
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
            cout << ">> Ошибка:: файл c текстом должен быть формата .txt"<<endl;
            return;
        }
        string encryptword, userword;
        vector<string>alph1;
        vector<string>key;
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
            alph1.push_back(keyj.at("key").at(i).at(0));
            key.push_back(keyj.at("key").at(i).at(1));
        }
        ifstream file1(pathtotext);
        if (check(pathtokey) == 0)
            return;
        getline(file1, encryptword);
        for (int k = 0; k < encryptword.size(); k++)
        {

            for (int n = 0; n < key.size(); ++n)
            {
                if (encryptword[k] == key[n][0])
                {
                    userword += alph1[n][0];
                    break;
                }
            }

        }
        json decrypt;
        decrypt["alg_type"] = "replacement";
        decrypt[encryptword] = userword;
        string pathtodecrypt = pathtotext;
        pathtodecrypt += ".decrypt";
        ofstream file2(pathtodecrypt);
        file2 << decrypt;
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
            int trigger = rand() % 2;
            bool trigger2 = 0;
            char chipletter;
            if (trigger == 0)
            {
                chipletter = 65 + rand() % 26;
            }
            else
            {
                chipletter = 97 + rand() % 26;
            }
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
        check2(pathtokey);
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

        getline(file1, userword);
        vector<char>encryptword;
        if (blocksize == userword.size())
        {
            encryptword.resize(blocksize);
            for (int i = 0; i < encryptword.size(); i++)
            {
                encryptword[i] = userword[key[i]-1];
            }
        }
        else 
        {
            int x = userword.size();
            int y = blocksize;
            int i = 1;
            while(x%y != 0)
            {
                userword.push_back(userword[i - 1]);
                i++;
                x++;
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
                encryptword[i] = userword[(key[n]-1) + k];
                n++;
            }
        }
        json j;
        j["alg_type"] = "transposition";
        string chars;
        for (int i = 0; i < encryptword.size(); i++)
        {
            chars += encryptword[i];
        }
        j[userword] = chars;
        pathtotext += ".encrypt";
        ofstream file2(pathtotext);
        file2 << j;
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
            cout << ">> Ошибка:: файл c ключом должен быть формата .key"<<endl;
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
            cout << ">> Ошибка:: файл c текстом должен быть формата .txt!!!" << endl;
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
        ifstream file1(pathtotext);

        if (check(pathtotext) == 0)
            return;

        getline(file1, encryptword);
        vector<char>decryptword(encryptword.size());
        if (blocksize == encryptword.size())
        {
            for (int i = 0; i < encryptword.size(); i++)
            {
                decryptword[key[i] - 1] = encryptword[i];
            }
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
        }
        json j;
        j["alg_type"] = "transposition";
        string chars;
        for (int i = 0; i < decryptword.size(); i++)
        {
            chars += decryptword[i];
        }
        j[encryptword] = chars;
        pathtotext += ".decrypt";
        ofstream file2(pathtotext);
        file2 << j;
        check2(pathtotext);
    }
    void key_generation() override
    {
        srand(time(0));
        int blocksize = 2 + rand() % + 6;
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
        pathtokey += 92;
        pathtokey += filename;
        ofstream file2(pathtokey);
        file2 << j;
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
        int blocksize = keyj.at("blocksize");
        vector<int>key;
        string key2;
        for (int i = 0; i < keyj.at("key").size(); i++)
        {
            key2=keyj.at("key").at(i);
            key.push_back(stoi(key2));
        }
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
        ifstream file1(pathtotext);

        if (check(pathtotext) == 0)
            return;

        getline(file1, userword);

        string encryptword;
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
        }
            json j;
            j["alg_type"] = "gamming";
            j["blocksize"] = blocksize;
            j[userword] = encryptword;
            pathtotext += ".encrypt";
            ofstream file2(pathtotext);
            file2 << j;
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
            cout << ">> Ошибка:: файл c текстом должен быть формата .txt"<<endl;
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
        int blocksize = keyj.at("blocksize");
        vector<int>key;
        string key2;
        for (int i = 0; i < keyj.at("key").size(); i++)
        {
            key2 = keyj.at("key").at(i);
            key.push_back(stoi(key2));
        }
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
            cout << ">> Ошибка:: файл c текстом должен быть формата .alph"<< endl;
            return;
        }
        ifstream file3(pathtoalph);
        if (check(pathtoalph) == 0)
            return;
        file3 >> alph;
        file.close();
        for (int i = 0; i < alph.at("alph").size(); i++)
        {
            alph2 += alph.at("alph").at(i);
        }
        string encryptword;;
        ifstream file1(pathtotext);

        if (check(pathtotext) == 0)
            return;

        getline(file1, encryptword);
        string userword;
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
                int temp2 = num - key[i];
                if (temp2 < 0)
                {
                    temp2 = (temp2 % alph2.size()) + alph2.size();
                }
                temp2 = temp2 % alph2.size();
                userword += alph2[temp2];
            }
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
                int temp2 = num - key[n];            
                if (temp2 < 0)
                {
                    temp2 += alph2.size();
                    temp2 = temp2 % alph2.size();
                }
                temp2 = temp2 % alph2.size();
                userword += alph2[temp2];
                n++;
            }
        }
        json j;
        j["alg_type"] = "gamming";
        j[encryptword] = userword;
        pathtotext += ".decrypt";
        ofstream file2(pathtotext);
        file2 << j;
        check2(pathtotext);
    }
    void key_generation() override
    {
        srand(time(0));
        int blocksize = 2 + rand() % 7;
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
        j["blocksize"] = blocksize;
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
        pathtokey += 92;
        pathtokey += filename;
        ofstream file2(pathtokey);
        file2 << j;
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



