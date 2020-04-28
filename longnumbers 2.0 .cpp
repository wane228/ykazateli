#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <ctime>
using namespace std;


class longnum
{
public:
	string usernum;
	void get_time(longnum num1, longnum num2);
	longnum()
	{
		usernum = "";
		firstminustr = 0;
	}
	~longnum() { }
private:
	string result1;
	vector<int>num1;
	bool firstminustr;
	void fill();
	void summ1(vector<int> num2);
	void diff2(vector<int>num2);
	void mult1(vector<int> num2);
	void div1(vector<int>num2);
	bool checkforbiggest1(vector<int> num1, vector<int> num2);
	vector<int> summformult(vector<int>num1, vector<int>num2);
	vector<int> difffordiv(vector<int>num1, vector<int>num2);
	bool checkfomistake();
	friend ostream& operator <<(ostream& out, longnum num)
	{
		out << num.result1;
		return out;
	}
	friend istream& operator >>(istream& in, longnum& num)
	{
		in >> num.usernum;
		return in;
	}
	friend longnum operator+(longnum num1, longnum num2)
	{
		if (num1.checkfomistake() == 1)
			num1.fill();
		else
			return num1;
		if (num1.checkfomistake() == 1)
			num2.fill();
		else
			return num1;

		if (num1.firstminustr == 0 && num2.firstminustr == 0)
		{
			num1.summ1(num2.num1);
			return num1;
		}
		else if (num1.firstminustr == 1 && num2.firstminustr == 0)
		{
			if (num1.num1.size() > num2.num1.size())
			{
				num1.result1 += '-';
			}
			else if (num1.num1.size() == num2.num1.size())
			{
				if (num1.checkforbiggest1(num1.num1, num2.num1) == 0)
				{
					num1.result1 += '-';
				}
			}
			num1.diff2(num2.num1);
			return num1;
		}
		else if (num1.firstminustr == 1 && num2.firstminustr == 1)
		{
			num1.result1 += '-';
			num1.summ1(num2.num1);
			return num1;
		}
		else if (num1.firstminustr == 0 && num2.firstminustr == 1)
		{
			if (num1.num1.size() < num2.num1.size())
			{
				num2.result1 += '-';
			}
			else if (num1.num1.size() == num2.num1.size())
			{
				if (num1.checkforbiggest1(num1.num1,num2.num1) == 1)
				{
					num2.result1 += '-';
				}
			}
			num2.diff2(num1.num1);
			return num2;
		}
	}
	friend longnum operator-(longnum num1, longnum num2)
	{
		if (num1.checkfomistake() == 1)
			num1.fill();
		else
			return num1;
		if (num1.checkfomistake() == 1)
			num2.fill();
		else
			return num1;

		if (num1.firstminustr == 0 && num2.firstminustr == 0)
		{
			if (num1.num1.size() < num2.num1.size())
			{
				num1.result1 += '-';
			}
			else if (num1.num1.size() == num2.num1.size())
			{
				if (num1.checkforbiggest1(num1.num1,num2.num1) == 1)
				{
					num1.result1 += '-';
				}
			}
			num1.diff2(num2.num1);
			return num1;
		}
		else if (num1.firstminustr == 1 && num2.firstminustr == 0)
		{
			num1.result1 += '-';
			num1.summ1(num2.num1);
			return num1;
		}
		else if (num1.firstminustr == 1 && num2.firstminustr == 1)
		{
			if (num1.num1.size() > num2.num1.size())
			{
				num1.result1 += '-';
			}
			else if (num1.num1.size() == num2.num1.size())
			{
				if (num1.checkforbiggest1(num1.num1, num2.num1) == 0)
				{
					num1.result1 += '-';
				}
			}
			num1.diff2(num2.num1);
			return num1;
		}
		else if (num1.firstminustr == 0 && num2.firstminustr == 1)
		{
			num1.summ1(num2.num1);
			return num1;
		}
	}
	friend longnum operator*(longnum num1, longnum num2)
	{
		if (num1.checkfomistake() == 1)
			num1.fill();
		else
			return num1;
		if (num1.checkfomistake() == 1)
			num2.fill();
		else
			return num1;

		if (num1.firstminustr == 1 && num2.firstminustr == 1)
		{
        }
		else if (num1.firstminustr == 1 || num2.firstminustr == 1)
		{
          num1.result1 += '-';
		}
		num1.mult1(num2.num1);
	
		return num1;
	}
	friend longnum operator/(longnum num1, longnum num2)
	{
		if (num1.checkfomistake() == 1)
			num1.fill();
		else
			return num1;
		if (num2.checkfomistake() == 1)
			num2.fill();
		else
			return num1;

		if (num1.firstminustr == 1 && num2.firstminustr == 1)
		{

		}
		else if (num1.firstminustr == 1 || num2.firstminustr == 1)
		{
			num1.result1 += '-';
		}
		num1.div1(num2.num1);
		return num1;
	}
};

void longnum::fill()
{
	if (checkfomistake() == 1)
	{
		int i = 0;
		if (usernum[0] == '-')
		{
			firstminustr = true;
			i = 1;
		}
		while (usernum[i] != '\0')
		{
			num1.push_back(usernum[i] - '0');
			i++;			
		}
	}
}
void longnum::summ1(vector<int> num2)
{
	vector<int>result;
	int i = num1.size() - 1;
	int j = num2.size() - 1;
	int max;
	if (i >= j)
	{
		max = i;
	}
	else if (j >= i)
	{
		max = j;
	}
	while (max >= 0)
	{
		if (i >= 0 && j >= 0)
		{
			result.push_back(num1[i] + num2[j]);
		}
		if (i < 0)
		{
			result.push_back(num2[j]);
		}
		if (j < 0)
		{
			result.push_back(num1[i]);
		}
		j--;
		i--;
		max--;
	}
	for (int i = 0; i < result.size() -1; i++)
	{
		if (result[i] >= 10)
		{
				result[i] -= 10;
				result[i + 1] += 1;

		}
	}
	for (int i = result.size() - 1; i >= 0; i--)
		result1 += to_string(result[i]);
}
vector<int> longnum::summformult(vector<int>num1, vector<int>num2)
{
	vector<int>result;
	string result_s;
	int i = num1.size() - 1;
	int j = num2.size() - 1;
	int max;
	if (i >= j)
	{
		max = i;
	}
	else if (j >= i)
	{
		max = j;
	}
	while (max >= 0)
	{
		if (i >= 0 && j >= 0)
		{
			result.push_back(num1[i] + num2[j]);
		}
		if (i < 0)
		{
			result.push_back(num2[j]);
		}
		if (j < 0)
		{
			result.push_back(num1[i]);
		}
		j--;
		i--;
		max--;
	}
	for (int i = result.size() - 2; i > 0; i--)
	{
		if (result[i] >= 10 )
		{
				int count = 0;
				while (result[i] >= 10)
				{
					result[i] -= 10;
					count++;
				}
				result[i - 1] += count;
		}
	}	
	return result;
}
vector<int> longnum::difffordiv(vector<int>num1, vector<int>num2)
{
	vector<int>result;
	vector<int>result0;
	int j = num2.size() - 1;
	for (int i = num1.size() - 1; i >= 0; i--)
	{
		if (j >= 0 && i >= 0)
		{
			if (num1[i] < num2[j])
			{
				num1[i] += 10;
				num1[i - 1] -= 1;
			}
			result.push_back(num1[i] - num2[j]);
		}
		if (j < 0)
		{
			if (num1[i] < 0)
			{
				num1[i] += 10;
				num1[i - 1] -= 1;
			}
			result.push_back(num1[i]);
		}
		j--;
	}
	for (int i = result.size() - 1; i >= 0; i--)
	{
		if (i == 0)
		{
			break;
		}
		if (result[i] == 0)
		{
			result.pop_back();
		}
		else
		{
			break;
		}
	}
	for (int i = result.size() - 1; i >= 0; i--)
		result0.push_back(result[i]);
	return result0;
}
void longnum::diff2(vector<int> num2)
{
	vector<int>result;
	if (num1.size() == num2.size())
	{
		int j = num1.size() - 1;
		bool trigger = checkforbiggest1(num1,num2);
		if (trigger == 1)
		{
			for (int i = num2.size() - 1; i >= 0; i--)
			{
				if (j >= 0 && i >= 0)
				{
					if (num2[i] < num1[j])
					{
						num2[i] += 10;
						num2[i - 1] -= 1;
					}
					result.push_back(num2[i] - num1[j]);
				}
				if (j < 0)
				{
					if (num2[i] < 0)
					{
						num2[i] += 10;
						num2[i - 1] -= 1;
					}
					result.push_back(num2[i]);
				}
				j--;
			}
		}
		else
		{
			for (int i = num1.size() - 1; i >= 0; i--)
			{
				if (j >= 0 && i >= 0)
				{
					if (num1[i] < num2[j])
					{
						num1[i] += 10;
						num1[i - 1] -= 1;
					}
					result.push_back(num1[i] - num2[j]);
				}
				if (j < 0)
				{
					if (num1[i] < 0)
					{
						num1[i] += 10;
						num1[i - 1] -= 1;
					}
					result.push_back(num1[i]);
				}
				j--;
			}
		}
	}
	else if (num1.size() > num2.size())
	{
		int j = num2.size() - 1;
		for (int i = num1.size() - 1; i >= 0; i--)
		{
			if (j >= 0 && i >= 0)
			{
				if (num1[i] < num2[j])
				{
					num1[i] += 10;
					num1[i - 1] -= 1;
				}
				result.push_back(num1[i] - num2[j]);
			}
			if (j < 0)
			{
				if (num1[i] < 0)
				{
					num1[i] += 10;
					num1[i - 1] -= 1;
				}
				result.push_back(num1[i]);
			}
			j--;
		}
	}
	else if (num1.size() < num2.size())
	{
		int j = num1.size() - 1;
		for (int i = num2.size() - 1; i >= 0; i--)
		{
			if (j >= 0 && i >= 0)
			{
				if (num2[i] < num1[j])
				{
					num2[i] += 10;
					num2[i - 1] -= 1;
				}
				result.push_back(num2[i] - num1[j]);
			}
			if (j < 0)
			{
				if (num2[i] < 0)
				{
					num2[i] += 10;
					num2[i - 1] -= 1;
				}
				result.push_back(num2[i]);
			}
			j--;
		}
	}
	for (int i = result.size() - 1; i >= 0; i--)
	{
		if (i == 0)
		{
			break;
		}
		if (result[i] == 0)
		{
			result.pop_back();
		}
		else
		{
			break;
		}
	}
	for (int i = result.size() - 1; i >= 0; i--)
		result1 += to_string(result[i]);
}
void longnum::mult1(vector<int> num2)
{
	vector<int>result;
	vector<int>temp;
	vector<int>temp2;
	for (int i = num2.size()-1; i >= 0; i--)
	{
		for (int j = num1.size()-1; j >= 0; j--)
		{
			result.push_back(num2[i] * num1[j]);
		}
		for (int i = 0; i < result.size()-1; i++)
		{
			if (result[i] >= 10)
			{
				int count = 0;
				while (result[i] >= 10)
				{
					result[i] -= 10;
					count++;
				}
				result[i + 1] += count;
			}
		}
		if (i != num2.size()-1)
		{
			temp2 = summformult(temp, result);
			temp.clear();
			for (int k = temp2.size()-1; k >= 0; k--)
			{
				temp.push_back(temp2[k]);
			}
			temp.push_back(0);
		}
		else
		{
			temp.clear();
			for (int g = 0; g < result.size(); g++)
			{
				temp.push_back(result[g]);
			}
			temp.push_back(0);
		}
		result.clear();
	}

	temp.pop_back();
	for (int i = temp.size() - 1; i >= 0; i--)
		result1 += to_string(temp[i]);
	
	
}
void longnum::div1(vector<int> num2)
{
	if (num1.size() < num2.size()|| num1[0] == 0)
	{
		result1 += to_string(0);
		return;
	}
	else if (num1.size() == num2.size() && checkforbiggest1(num1, num2) == 1)
	{
		result1 += to_string(0);
		return;
	}
	if (num2[0] == 0)
	{
		cout << "You cannot divide by 0!!!";
		return;
	}
	vector<int>temp;
	vector<int>count;
	bool trigger;
	bool trigger1 = 0;
	int i = 0;
	while (temp.size() != num2.size())
	{
		temp.push_back(num1[i]);
		i++;
		trigger = 1;
	}
	for (;;)
	{
		if (checkforbiggest1(temp, num2) == 1)
		{
			if (i > num1.size() - 1)
			{
				for(int j =0; j < count.size(); j++)
				result1 += to_string(count[j]);
				return;
			}
			temp.push_back(num1[i]);
			i++;
			trigger = 1;
			trigger1 = 0;
		}
		if (trigger1 == 0 && checkforbiggest1(temp,num2) == 1)
		{
			count.push_back(0);
		}
		if (temp == num2 || checkforbiggest1(temp, num2) == 0)
		{
			temp = difffordiv(temp, num2);
			if (trigger == 1)
			{
				count.push_back(1);
				trigger = 0;
			}
			else
			{
				if ((count.size() - 1) < 0)
				{
					count.push_back(0);
				}
				count[count.size() - 1]++;
			}
			trigger1 = 1;
		}
	}
}
bool longnum::checkforbiggest1(vector<int> num1,vector<int> num2)
{
	bool trigger = 0;
	if (num1.size() > num2.size())
	{
		trigger = 0;
	}
	else if (num1.size() < num2.size())
	{
		trigger = 1;
	}
	else
	{
		for (int i = 0; i < num1.size(); i++)
		{
			if (num1[i] > num2[i])
			{
				trigger = 0;
				break;
			}
			if (num1[i] < num2[i])
			{
				trigger = 1;
				break;
			}
		}
	}
	return trigger;
}
bool longnum::checkfomistake()
{
	int i = 0;
	if (usernum[0] == '-')
	{
		i = 1;
	}
	if (cin.fail())
	{
		cin.clear();
		cout << "You can use only numbers!!" << endl;
		return false;
	}
	if (usernum == "")
	{
		cout << "Your number is empty!!!" << endl;
		return false;
	}
	if (usernum[i] == '0' && (i+1) < usernum.length())
	{
		cout << "Your number cannot start from zero!!" << endl;
		return false;
	}
	while (usernum[i] != '\0')
	{
		if (usernum[i] < '0' || usernum[i] > '9')
		{
			cout << "You can use only numbers!!" << endl;
			return false ;
		}
		i++;
	}
	return true;
}
void longnum::get_time(longnum num1, longnum num2)
{
	longnum z;
	if (num1.checkfomistake() == 1 && num2.checkfomistake() == 1)
	{
		int begintime = clock();
		for (int i = 0; i < 100; i++)
		{
			z = num1 + num2;
		}
		int endtime = clock();
		double time = ((endtime - begintime) / 100.0) / 1000.0;
		cout << "Summ time: " << time << " sec" << endl;
	    begintime = clock();
		for (int i = 0; i < 100; i++)
		{
			z = num1 - num2;
		}
	    endtime = clock();
	    time = ((endtime - begintime) / 100.0) / 1000.0 ;
		cout << "Diff time: " << time << " sec" << endl;
		begintime = clock();
		for (int i = 0; i < 100; i++)
		{
			z = num1 * num2;
		}
		endtime = clock();
		time = ((endtime - begintime) / 100.0) / 1000.0;
		cout << "Mult time: " << time << " sec" << endl;
		begintime = clock();
		for (int i = 0; i < 100; i++)
		{
			z = num1 / num2;
		}
		endtime = clock();
		time = ((endtime - begintime) / 100.0) / 1000.0;
		cout << "Div time: " << time << " sec" << endl;

	}
	else
		return;
}

int main()
{

	for (;;)
	{
		longnum x;
		longnum y;
		longnum z;
		cin >> x;
		cin >> y;
		cout << "Summ result: " << x+y << endl;
		cout << "Diff result: " << x-y << endl;
		cout << "Mult result: " << x*y << endl;
		cout << "Div result: " << x/y << endl;
		x.get_time(x, y);
		_getche();
		system("cls");
	}

}