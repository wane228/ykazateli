#include <iostream>

struct Yzel
{
public:
	int data;
	Yzel* pNext;
	Yzel(int data, Yzel* pNext = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
	}
	~Yzel()
	{

	}


};
class list
{

public:
	Yzel* head;
	int size;
	void push_back(int data);
	void push_front(int data);
	void deletion_last_elem();
	void deletion_first_elem();
	void deletion_all_list();
	void add_v_proizvolnoe_mesto(int index, int data);
	int GetSize() { return size + 1; }
	void vivod(int index);
	void vivod_all_spisok();
	list();
    ~list();

};


void list::push_back(int data)
{
	if (head == nullptr)
	{
		head = new Yzel(data);
	}
	else
	{
		Yzel* temp = head;
		while (temp->pNext != nullptr)
		{
			temp = temp->pNext;
		}
		temp->pNext = new Yzel(data);
	}
	size++;
}

void list::push_front(int data)
{
	Yzel* temp = head;
	temp = new Yzel(data);
	temp->pNext = head;
	head = temp;
	size++;

}

void list::deletion_last_elem()
{

}

void list::deletion_first_elem()
{
	Yzel* temp = head;
	head = head->pNext;
	delete temp;
	size--;;
}

void list::deletion_all_list()
{
	while (size)
	{
		deletion_first_elem();
	}
}

void list::add_v_proizvolnoe_mesto(int indexE, int data)
{
	if (indexE == 1)
	{
		push_front(data);
	}
	else
	{
		Yzel* previous = head;
		for (int i = 2; i < indexE ; i++)
		{
				previous = previous->pNext;
		}

		Yzel* newNode = new Yzel(data, previous->pNext);

		previous->pNext = newNode;

		size++;
	}
}

void list::vivod(int index)
{
	int counter = 1;
	Yzel* current = head;
	while (current != nullptr)
	{
		if (counter == index)
		{
		   std::cout << current->data << std::endl;
		}
		current = current->pNext;
		counter++;
	}
}

void list::vivod_all_spisok()
{
	Yzel* temp = head;
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
	std::cout << std::endl;
	x.add_v_proizvolnoe_mesto(1,19);
	x.vivod_all_spisok();








}