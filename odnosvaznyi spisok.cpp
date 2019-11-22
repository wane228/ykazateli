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
	~list_elem() { }
};
class list
{

public:
	int size;
	void push_back(int data);
	void push_front(int data);
	void remove_first_elem();
	void remove_all_list();
	void remove_by_index(int index);
	void add_to_any_place(int index, int data);
	int GetSize() { return size; }
	void show_by_index(int index);
	void show_all_list();
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
	if (size == 0)
	{
		head = new list_elem(data);
		size++;
	}
	else
	{
	list_elem* temp = new list_elem(data);
	temp->pNext = head;
	head = temp;
	size++;
	}
}


void list::remove_first_elem()
{
	if (size != 0)
	{
		list_elem* temp = head;
		head = head->pNext;
		delete temp;
		size--;
	}
	else
	{
		return;
	}
}

void list::remove_all_list()
{
	while (size)
	{
		remove_first_elem();
	}
}

void list::remove_by_index(int index)
{
	if (size == 0)
	{
		return;
	}
	else if (index > size || index < 0)
	{
		std::cout << std::endl << "Choose element from 1 to " << size << std::endl;
		return;
	}
	else 
	{
		if (index == 1)
		{
			remove_first_elem();
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
	}
}

void list::add_to_any_place(int index, int data)
{
	if (index < 0 || index > size + 1)
	{
		std::cout << std::endl << "List elments are located in the range from 1 to " << size << std::endl;
		return;
	}
	else if (index == size + 1)
	{
		push_back(data);
		return;
	}
	else
	{
		if (index == 1)
		{
			push_front(data);

		}
		else
		{
			list_elem* temp = head;
			for (int i = 2; i < index; i++)
			{
				temp = temp->pNext;
			}
			list_elem* newlist_elem = new list_elem(data, temp->pNext);
			temp->pNext = newlist_elem;
			size++;
		}
	}
}

void list::show_by_index(int index)
{
	if (index < 0)
	{
		std::cout << "List elments are located in the range from 1 to " << size << std::endl;
		return;
	}
	if (size != 0 && index > 0)
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
		std::cout << std::endl << "The list is empty" << std::endl;
	}
}

void list::show_all_list()
{
	if (size != 0)
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
		std::cout << std::endl << "The list is empty" << std::endl;
	}
}



list::list()
{
	head = nullptr;
	size = 0;
}

list::~list()
{
	remove_all_list();
}



int main()
{
	list x;
	x.show_all_list();
}
