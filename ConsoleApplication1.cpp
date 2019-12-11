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
	Tree_Elem(Tree_Elem* left = nullptr, Tree_Elem* right = nullptr,Tree_Elem* prev = nullptr)
	{
		data = 0;
		key = 0;
		this->left = left;
		this->right = right;
		this->prev = prev;

	}
	~Tree_Elem() {}
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
	

};

Tree_Elem* tree = nullptr;
Tree_Elem* tree1 = nullptr;

Tree::Tree()
{
	head = nullptr;
	size = 0;
}

Tree::~Tree()
{
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
		cout << "Tree is empty" << endl;
	}
}

void Tree::delete_all_branch()
{
	Tree_Elem* temp = head;
	Tree_Elem* temp_prev;
	while (temp != nullptr)
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
			delete temp;
			temp = temp_prev;
		}
		else
		{
			delete temp;
		}

	}
}

int main()
{

	Tree x;
	x.add_elem(20, 1);
	x.add_elem(19, 2);
	x.add_elem(21, 3);
	x.show_all_elem();
	x.delete_all_branch();
	x.show_all_elem();

}
}


