#include <iostream>

using namespace std;

class Tree_Elem
{
public:
	int key;
	int data;
	Tree_Elem* left;
	Tree_Elem* right;
	Tree_Elem* prev;
	Tree_Elem(Tree_Elem* left = nullptr, Tree_Elem* right = nullptr, Tree_Elem* prev = nullptr)
	{
		data = 0;
		key = 0;
		this->left = left;
		this->right = right;
		this->prev = prev;
	}
	~Tree_Elem()
	{
		data = 0;
		key = 0;
		left = nullptr;
		right = nullptr;
		prev = nullptr;
	}
};



class Tree
{
private:
	Tree_Elem* head;
	int size;
public:
	Tree();
	~Tree();
	void add_elem(int key, int data);
	void show_all_elem();
	void delete_all_branch();
	Tree_Elem* findByIndex(int key);
	void delete_by_key(int key);
};



Tree::Tree()
{
	head = nullptr;
	size = 0;
}
Tree::~Tree()
{
	delete_all_branch();
}
void Tree::add_elem(int key, int data)
{
	Tree_Elem* NewElem = new Tree_Elem();
	NewElem->data = data;
	NewElem->key = key;
	if (head == nullptr)
	{
		head = NewElem;
	}
	else
	{
		Tree_Elem* temp = head;
		while (temp != nullptr)
		{
			if (key > temp->key)
			{
				if (temp->right != nullptr)
				{
					temp = temp->right;
				}
				else
				{
					break;
				}
			}
			if (key < temp->key)
			{
				if (temp->left != nullptr)
				{
					temp = temp->left;
				}
				else
				{
					break;
				}
			}
		}
		NewElem->prev = temp;
		if (key > temp->key)
		{
			temp->right = NewElem;
		}
		if (key < temp->key)
		{
			temp->left = NewElem;
		}
	}
	size++;
}


void Tree::show_all_elem()
{
	Tree_Elem* temp = head;
	if (head != nullptr)
	{
		cout << head->key << "||" << head->data << " ";
		temp = temp->left;
		while (temp != nullptr)
		{
			cout << temp->key << "||" << temp->data << " ";
			temp = temp->left;
		}
		temp = head;
		temp = temp->right;
		while (temp != nullptr)
		{
			cout << endl << temp->key << "||" << temp->data << " ";
			temp = temp->right;
		}
	}
	else
	{
		cout << endl << "Tree is empty" << endl;
	}
}

void Tree::delete_all_branch()
{
	Tree_Elem* temp = head;
	Tree_Elem* temp_prev;
	while (head != nullptr)
	{
		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		if (temp->right != nullptr)
		{
			temp = temp->right;
			continue;
		}
		if (temp->prev != nullptr)
		{
			temp_prev = temp->prev;
			if (temp_prev->left == temp)
			{
				temp_prev->left = nullptr;
			}
			if (temp_prev->right == temp)
			{
				temp_prev->right = nullptr;
			}
			delete temp;
			temp = temp_prev;
		}
		else
		{
			head = nullptr;
			delete temp;
		}
	}
	size = 0;
}

Tree_Elem* Tree::findByIndex(int key)
{
	Tree_Elem* temp = head;
    if (head != nullptr) {
		while (temp != nullptr) 
		{
			if (key == temp->key) 
			{
				break;
			}
			else if (key > temp->key) 
			{
				if (temp->right != nullptr)
				{
					temp = temp->right;
				}
				else
				{
					temp = nullptr;
					break;
				}
			}
			else if (key < temp->key)
			{
				if (temp->left != nullptr) 
				{
					temp = temp->left;
				}
				else
				{
					temp = nullptr;
					break;
				}
			}
		}
		return temp;
	}
	
}

void Tree::delete_by_key(int key)
{
	Tree_Elem* dell_elem = findByIndex(key);
	Tree_Elem* dell_elem_prev = dell_elem->prev;
	Tree_Elem* dell_elem_left = dell_elem->left;
	Tree_Elem* dell_elem_right = dell_elem->right;
	Tree_Elem* temp;

	if (dell_elem_left != nullptr && dell_elem_right != nullptr)
	{
		dell_elem_prev->right = dell_elem_right;
		temp = dell_elem_right;
		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		temp->left = dell_elem_left;
	}
	else if (dell_elem_right == nullptr)
	{

	}
}


int main()
{
	Tree x;
	x.add_elem(20, 1);
	x.add_elem(19, 2);
	x.add_elem(21, 3);
	x.show_all_elem();
	//x.delete_all_branch();
	//x.show_all_elem();
	cout << endl << x.findByIndex(21)->data;
}
