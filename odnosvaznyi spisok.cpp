#include <iostream>



class list_elem
{
public:
	int data;
	list_elem* pNext;
	list_elem* pPrev;
	list_elem(int data, list_elem* pNext = nullptr, list_elem* pPrev = nullptr)
	{

		this->data = data;
		this->pNext = pNext;
		this->pPrev = pPrev;
	}



	~list_elem()
	{

	}
};



class list

{
private:
	list_elem* head;
	list_elem* last;
public:

	int size;
	list();
	~list();
	void push_front(int data);
	void push_back(int data);
	int GetSize() { return size; }
	void show_all_list();
	void show_by_index(int index);
	void remove_first_elem();
	void remove_all_list();
	void remove_by_index(int index);
	void add_to_any_place(int index, int data);
};


list::list()
{
	head = nullptr;
	last = nullptr;
	size = 0;
}

list::~list()
{
	remove_all_list();
}

void list::show_all_list() // работает
{
	int i = 1;
	list_elem* temp = head;
	while (temp != nullptr)
	{
		std::cout << "[" << i << "]: " << temp->data << " ";
		temp = temp->pNext;
		i++;
	}
	std::cout << std::endl;
}

void list::push_front(int data) // работает
{
	if (size == 0)
	{
		head = new list_elem(data);
		last = head;
		size++;
	}
	else
	{
		list_elem* temp = new list_elem(data, head);
		head->pPrev = temp;
		head = temp;
		size++;
	}
}

void list::push_back(int data) // работает
{
	if (size == 0)
	{
		push_front(data);
	}
	else
	{
		list_elem* temp = new list_elem(data, nullptr, last);
		last->pNext = temp;
		last = temp;
		size++;
	}
}

void list::remove_first_elem() // работает
{
	list_elem* temp = head;
	if (size != 0 && size != 1)
	{
		head = head->pNext;
		delete temp;
		size--;
	}
	else if (size == 1)
	{
		delete temp;
		size--;
	}
}

void list::remove_all_list() // работает
{
	while (size)
	{
		remove_first_elem();
	}
}

void list::remove_by_index(int index) // работает
{
	if (size == 0)
	{
		std::cout << std::endl << "The list is empty" << std::endl;
		return;
	}
	else if (index > size || index <= 0)
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
		else if (index == size)
		{
			list_elem* temp = last;
			list_elem* temp_ = temp->pPrev;
			temp_->pNext = nullptr;
			last = temp_;
			delete temp;
		}
		else
		{
			if (index <= GetSize() / 2)
			{
				list_elem* temp = head;
				for (int i = 2; i < index; i++)
				{
					temp = temp->pNext;
				}
				list_elem* remove_elem = temp->pNext;
				list_elem* remove_elem_ = temp->pNext->pNext;
				temp->pNext = remove_elem_;
				remove_elem_->pPrev = temp;
				delete remove_elem;
			}
			else
			{
				list_elem* temp = last;
				for (int i = size; i > index + 1; i--)
				{
					temp = temp->pPrev;
				}
				list_elem* remove_elem = temp->pPrev;
				list_elem* remove_elem_ = temp->pPrev->pPrev;
				temp->pPrev = remove_elem_;
				remove_elem_->pNext = temp;
				delete remove_elem;
			}
			size--;
		}
	}
}

void list::add_to_any_place(int index, int data) // работает
{
	if (index <= 0 || index > size + 1)
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
			if (index <= GetSize() / 2)
			{
				list_elem* temp = head;
				for (int i = 1; i < index - 1; i++)
				{
					temp = temp->pNext;
				}
				list_elem* newlist_elem = new list_elem(data);
				list_elem* newlist_elem_ = temp->pNext;
				temp->pNext = newlist_elem;
				newlist_elem->pPrev = temp;
				newlist_elem->pNext = newlist_elem_;
				newlist_elem_->pPrev = newlist_elem;
			}
			else
			{
				list_elem* temp = last;
				for (int i = size; i > index; i--)
				{
					temp = temp->pPrev;
				}
				list_elem* newlist_elem = new list_elem(data);
				list_elem* newlist_elem_ = temp->pPrev;
				temp->pPrev = newlist_elem;
				newlist_elem->pNext = temp;
				newlist_elem->pPrev = newlist_elem_;
				newlist_elem_->pNext = newlist_elem;
			}
		}
	}
} 

void list::show_by_index(int index) // работает
{
	if (index <= 0)
	{
		std::cout << "Choose element from 1 to " << size << std::endl;
		return;
	}
	if (index == size + 1)
	{
		std::cout << std::endl << "List elments are located in the range from 1 to " << size << std::endl;
		return;
	}
	if (size != 0)
	{
		if (index <= GetSize() / 2)
		{
			int counter = 1;
			list_elem* temp = head;
			while (temp != nullptr)
			{
				if (counter == index)
				{
					std::cout << "[" << index << "]: " << temp->data << std::endl;
					break;
				}
				temp = temp->pNext;
				counter++;
			}
		}
		else
		{
			list_elem* temp = last;
			int counter = 0;
			int difference_size_and_index = size - index;
			while (1)
			{
				if (counter == difference_size_and_index)
				{
					std::cout << "[" << index << "]: " << temp->data << std::endl;
					break;
				}
				temp = temp->pPrev;
				counter++;
			}
		}
	}
	else
	{
		std::cout << "The list is empty\n";
	}
} 



int main()
{
	list x;
	x.push_front(1);
	x.push_front(2);
	x.push_front(3);
	x.push_front(4);
	x.push_front(5);
	x.push_front(6);
	x.show_all_list();
	x.remove_by_index(-1);
	x.show_all_list();
 
}
