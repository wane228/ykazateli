#include <iostream>
#include <vector>

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
	void add_elem(unsigned int key, int data);
	void show_all_elem(Tree_Elem* head);
	void show_all_elem1() {	show_all_elem(head); cout << endl;}
	void delete_all_tree();
	Tree_Elem* find_by_key(unsigned int key);
	void delete_by_key(unsigned int key);
	void show_by_key(unsigned int key);
};



Tree::Tree()
{
	head = nullptr;
	size = 0;
}
Tree::~Tree()
{
	delete_all_tree();
}
void Tree::add_elem(unsigned int key, int data)
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
			if (key == temp->key)
			{
				temp->data = NewElem->data;
				break;
			}
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


void Tree::show_all_elem(Tree_Elem* temp)
{
		cout << temp->data << " ";
		if (temp->left != nullptr)
		{
			show_all_elem(temp->left);
		}
		if (temp->right != nullptr)
		{
			show_all_elem(temp->right);
		}
		
}





void Tree::delete_all_tree()
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
		size--;
	}
}

Tree_Elem* Tree::find_by_key(unsigned int key)
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

void Tree::delete_by_key(unsigned int key)
{
	Tree_Elem* rem_elem = find_by_key(key);

	if (rem_elem != nullptr)
	{
		if (rem_elem != head)
		{
			Tree_Elem* rem_elem_prev = rem_elem->prev;
			Tree_Elem* rem_elem_left = rem_elem->left;
			Tree_Elem* rem_elem_right = rem_elem->right;
			Tree_Elem* temp;
			if (rem_elem_left != nullptr && rem_elem_right != nullptr)
			{
				if (rem_elem_prev->right == rem_elem)
				{
					rem_elem_prev->right = rem_elem_right;
					rem_elem_right->prev = rem_elem_prev;
				}
				if (rem_elem_prev->left == rem_elem)
				{
					rem_elem_prev->left = rem_elem_right;
					rem_elem_right->prev = rem_elem_prev;
				}
				temp = rem_elem_right;
				while (temp->left != nullptr)
				{
					temp = temp->left;
				}
				temp->left = rem_elem_left;
				rem_elem_left->prev = temp;
				delete rem_elem;
			}
			else if (rem_elem_right == nullptr && rem_elem_left != nullptr)
			{
				if (rem_elem_prev->right == rem_elem)
				{
					rem_elem_prev->right = rem_elem_left;
					rem_elem_left->prev = rem_elem_prev;
				}
				if (rem_elem_prev->left == rem_elem)
				{
					rem_elem_prev->left = rem_elem_left;
					rem_elem_left->prev = rem_elem_prev;
				}
				delete rem_elem;
			}
			else if (rem_elem_right != nullptr && rem_elem_left == nullptr)
			{
				if (rem_elem_prev->right == rem_elem)
				{
					rem_elem_prev->right = rem_elem_right;
					rem_elem_right->prev = rem_elem_prev;
				}
				if (rem_elem_prev->left == rem_elem)
				{
					rem_elem_prev->left = rem_elem_right;
					rem_elem_right->prev = rem_elem_prev;
				}
				delete rem_elem;
			}
			else if (rem_elem_left == nullptr && rem_elem_right == nullptr)
			{
				if (rem_elem_prev->right == rem_elem)
				{
					rem_elem_prev->right = nullptr;
				}
				if (rem_elem_prev->left == rem_elem)
				{
					rem_elem_prev->left = nullptr;
				}
				delete rem_elem;
			}
			size--;
		}
		else if (rem_elem == head)
		{
			Tree_Elem* rem_elem_left = rem_elem->left;
			Tree_Elem* rem_elem_right = rem_elem->right;
			Tree_Elem* temp;
			if (rem_elem_left != nullptr && rem_elem_right != nullptr)
			{
				head = rem_elem_right;
				rem_elem_right->prev = nullptr;
				temp = rem_elem_right;
				while (temp->left != nullptr)
				{
					temp = temp->left;
				}
				temp->left = rem_elem_left;
				rem_elem_left->prev = temp;
				delete rem_elem;
			}
			else if (rem_elem_right == nullptr && rem_elem_left != nullptr)
			{
				head = rem_elem_left;
				rem_elem_left->prev = nullptr;
				delete rem_elem;
			}
			else if (rem_elem_right != nullptr && rem_elem_left == nullptr)
			{
				head = rem_elem_right;
				rem_elem_right->prev = nullptr;
				delete rem_elem;
			}
			else if (rem_elem_left == nullptr && rem_elem_right == nullptr)
			{
				delete rem_elem;
			}
			size--;
		}
	}
	else
	{
		cout << "Elemet not found!!!" << endl;
	}

}

void Tree::show_by_key(unsigned int key)
{
	Tree_Elem* temp = find_by_key(key);
	if (temp != nullptr)
	{
		cout << temp->key << "||" << temp->data << endl;
	}
	else
	{
		cout << "Elemet not found!!!" << endl;
	}
}




int main()
{
	Tree x;
	x.add_elem(0, 1);
	x.show_all_elem1();
	x.delete_by_key(10);
	x.show_all_elem1();
}

