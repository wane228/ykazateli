
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
	list_elem()
	{
		data = 0;
		pNext = nullptr;
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
	void deletion_first_elem();
	void deletion_all_list();
	void ydalenie_po_indexy(int index);
	void add_v_proizvolnoe_mesto(int index, int data);
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


void list::deletion_first_elem() // добавить проверку, чтобы хед не был nullptr
{
	list_elem* temp = head;
	head = head->pNext;
	delete temp;
	size--;
} 

void list::deletion_all_list()
{
	while (size)
	{
		deletion_first_elem();
	}
}

void list::ydalenie_po_indexy(int index) // добавить проверку, чтобы хед не был nullptr
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
		list_elem* ydalaemiy_elem = temp->pNext;
		temp->pNext = temp->pNext->pNext;
		delete ydalaemiy_elem;
		size--;

	}
}

bool list::add_v_proizvolnoe_mesto(int indexE, int data) // добавить проверку, чтобы хед не был nullptr
{
	if (indexE < 0 || indexE >= this->size) {
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

void list::vivod_all_spisok()
{
	list_elem* temp = head;
	std::cout << std::endl;
	while (temp != nullptr)
	{
		std::cout << temp->data << std::endl;
		temp = temp->pNext;
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
	x.push_back(5);
	x.push_back(6);
	x.push_back(7);
	x.push_front(8);
	x.push_front(9);
	x.vivod_all_spisok();
	x.add_v_proizvolnoe_mesto(1, 19);
	x.vivod_all_spisok(); 
	x.ydalenie_po_indexy(4);
	x.vivod_all_spisok();

		


}
