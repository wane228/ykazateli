#include <iostream>


struct list_elem
{
public:
	int data;
	list_elem* pNext;
	list_elem(int data, list_elem* pNext = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
	}
	~list_elem()
	{

	}


};
class list
{

public:
	int size;
	void push_back(int data);
	void push_front(int data);
	bool deletion_first_elem();
	void deletion_all_list();
	bool ydalenie_po_indexy(int index);
	bool add_v_proizvolnoe_mesto(int index, int data);
	int GetSize() { return size + 1; }
	void vivod(int index);
	void vivod_all_spisok();
	list();
	~list();
private:
	list_elem* head;

};



void list::push_back(int data)
{
	if (head == nullptr)
	{
		head = new list_elem(data);
	}
	else
	{
		list_elem* temp = head;
		while (temp->pNext != nullptr)
		{
			temp = temp->pNext;
		}
		temp->pNext = new list_elem(data);
	}
	size++;
}

void list::push_front(int data)
{
	list_elem* temp = new list_elem(data);
	temp->pNext = head;
	head = temp;
	size++;

}


bool list::deletion_first_elem() 
{
	if (head != nullptr)
	{
		list_elem* temp = head;
		head = head->pNext;
		delete temp;
		size--;
		return true;
	}
	else
	{
		return false;
	}
}

void list::deletion_all_list()
{
	while (size)
	{
		deletion_first_elem();
	}
}

bool list::ydalenie_po_indexy( int index) 
{
	if (head != nullptr && (index < 0 || index >= this->size))
	{
			if (index == 1)
			{
				deletion_first_elem();
			}
			else
			{
				list_elem* temp = head;
				for (int i = 2; i < index; i++)
				{
					temp = temp->pNext;

				}
				list_elem* remove_elem = temp->pNext;
				temp->pNext = temp->pNext->pNext;
				delete remove_elem;
				size--;

			}
			return true;
	}
	else
	{
			return false;
	}
}

bool list::add_v_proizvolnoe_mesto(int indexE, int data) 
{
	if (indexE < 0 || indexE >= this->size)
	{
		return false;
	}
	if (indexE == 1)
	{
		push_front(data);
	}
	else
	{
		list_elem* temp = head;
		for (int i = 2; i < indexE; i++)
		{
			temp = temp->pNext;
		}

		list_elem* newlist_elem = new list_elem(data, temp->pNext);

		temp->pNext = newlist_elem;

		size++;
	}
	return true;
}

void list::vivod(int index)
{
	if (head != nullptr)
	{
		int counter = 1;
		list_elem* temp = head;
		while (temp != nullptr)
		{
			if (counter == index)
			{
				std::cout << temp->data << std::endl;
				break;
			}
			temp = temp->pNext;
			counter++;
		}
	}
	else
	{
		std::cout << std::endl << "The list is empty"<< std::endl;
	}
}

void list::vivod_all_spisok()
{
	if (head != nullptr)
	{
		list_elem* temp = head;
		std::cout << std::endl;
		while (temp != nullptr)
		{
			std::cout << temp->data << std::endl;
			temp = temp->pNext;
		}
	}
	else
	{
		std::cout << std::endl <<"The list is empty" << std::endl;
	}
}



list::list()
{
	head = nullptr;
	size = 0;

}

list::~list()
{

	deletion_all_list();
}




int main()
{
	
	list x;
	x.push_back(6);
	x.push_front(8);
	x.vivod_all_spisok();
	x.deletion_first_elem();
	x.push_back(5);
	x.vivod_all_spisok();





}