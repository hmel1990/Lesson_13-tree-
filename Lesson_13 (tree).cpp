#include <iostream>
using namespace std;

class Tree
{
public:
	struct Node // one element of the tree
	{
		int value; // useful data

		Node* parent = nullptr;
		Node* right = nullptr;
		Node* left = nullptr;

		void ShowNode() const
		{
			cout << value << ", ";
		}
		int ShowValueNode() const
		{
			return value;
		}

	};

private:
	Node* root = nullptr;
	// int count;

public:
	bool IsEmpty() const
	{
		return root == nullptr;
	}

	Tree() {} // так как в классе есть явно объявленный конструктор копирования, приходится и конструктор без параметров явно делать :)

	~Tree()
	{
		Clear();
	}

private:
	void ShowTree(Node* element) const
	{
		if (element != 0)
		{
			ShowTree(element->left);
			element->ShowNode();
			ShowTree(element->right);
		}
	}

public:
	void ShowTree() const
	{
		cout << "\n";
		ShowTree(root);
		cout << "\n";
	}

private:
	Node* GetRoot() const
	{
		return root;
	}

	int GetCount(Node* element, int count) const
	{
		if (element != 0)
		{
			count = GetCount(element->left, count);
			count++;
			count = GetCount(element->right, count);
		}
		return count;
	}

public:
	int GetCount() const
	{
		int count = 0;
		count = GetCount(root, count);
		return count;
	}

private:
	void Clear(Node* element)
	{
		if (element != nullptr)
		{
			Clear(element->left);
			Clear(element->right);
			delete element;
			element = nullptr;
		}
	}

public:
	void Clear()
	{
		if (!IsEmpty())
		{
			Clear(root);
			root = nullptr;
		}
	}

	Node* FindNode(int value) const
	{
		if (IsEmpty())
			return nullptr;

		Node* f = root;
		while (true)
		{
			if (value < f->value)
			{
				if (f->left != nullptr)
					f = f->left;
				else
					break;
			}
			else if (value > f->value)
			{
				if (f->right != nullptr)
					f = f->right;
				else
					break;
			}
			else
				return f;
		}
		return nullptr;
	}

	void AddNode(int value)
	{
		if (FindNode(value))
			return;

		Node* n = new Node;
		n->value = value;
		Node* parent = nullptr;
		if (IsEmpty())
		{
			root = n;
			root->parent = parent;
		}
		else
		{
			Node* p = root;
			while (p != nullptr)
			{
				parent = p;
				if (n->value > p->value)
					p = p->right;
				else
					p = p->left;
			}
			if (n->value < parent->value)
				parent->left = n;
			else
				parent->right = n;
			n->parent = parent;
		}
	}

	Tree& operator = (const Tree& original)
	{
		if (!IsEmpty())
			Clear();

		AddNode(original.root->value);
		Copy(original.root);
		return *this;
	}

	Tree(const Tree& original)
	{
		AddNode(original.root->value);
		Copy(original.root);
	}

	void Copy(Node* element)
	{
		if (element->left != nullptr)
			AddNode(element->left->value);

		if (element->right != nullptr)
			AddNode(element->right->value);

		if (element->left != nullptr)
			Copy(element->left);

		if (element->right != nullptr)
			Copy(element->right);
	}

	void DeleteNode(int value)
	{
		Node* d = FindNode(value);
		if (d == nullptr)
			return;

		Node* parent = d->parent;
		if (d == root && GetCount() == 1)
		{
			Clear();
			return;
		}
		if (d->left == nullptr && d->right == nullptr)
		{
			if (parent->left == d)
				parent->left = nullptr;
			else
				parent->right = nullptr;
			delete d;
			return;
		}
		if (d->left == nullptr && d->right != nullptr)
		{
			if (parent->left == d)
			{
				parent->left = d->right;
			}
			else
			{
				parent->right = d->right;
			}
			d->right->parent = parent;
			delete d;
			return;
		}

		if (d->left != nullptr && d->right == nullptr)
		{
			if (parent->left == d)
			{
				parent->left = d->left;
			}
			else
			{
				parent->right = d->left;
			}
			d->left->parent = parent;
			delete d;
			return;
		}
		if (d->left != nullptr && d->right != nullptr)
		{
			Node* r = d->right;
			if (r->right == nullptr && r->left == nullptr)
			{
				d->value = r->value;
				d->right = nullptr;
				delete r;
			}
			else if (r->left != nullptr)
			{
				Node* p = r->left;
				while (p->left != nullptr)
					p = p->left;
				d->value = p->value;
				if (p->right == nullptr)
					p->parent->left = nullptr;
				else
					p->parent->left = p->right;
				delete p;
			}
			else
			{
				d->value = r->value;
				d->right = r->right;
				delete r;
			}
		}
	}
	//_____________________________________________________________________________________________________________________________________

private:

	void AddToTemp(Node* element, int *temp, int &count_element)
	{
		if (element != 0)
		{
			AddToTemp(element->left, temp, count_element);
			temp[count_element++] = element->ShowValueNode();
			AddToTemp(element->right, temp, count_element);
		}

	}


	void BalancedTree(Node* element, int SIZE) 
	{
		int count_element = 0;
		int* temp = new int[SIZE];
		AddToTemp(element, temp, count_element);

		for (int i = 0; i < SIZE; i++)
		{
			cout << "\n";
			cout << temp[i];
		}
	
		Clear (root);
		BuildBalancedTree(temp, SIZE);
		delete[]temp;

	}

	Node* BuildBalancedTree(int* temp,  int SIZE, int start = 0) {
		if (start > SIZE) return nullptr;

		int mid = (start + SIZE) / 2;
		Node *tree = new Node();
		tree->value = temp[mid];

		tree->left = BuildBalancedTree(temp, mid - 1, start);
		tree->right = BuildBalancedTree(temp, SIZE, mid + 1);

		return tree;
	}





public:
	void BalancedTree(int SIZE) 
	{
		BalancedTree(root, SIZE);
	}

//private:
//	void ShowValueNode() const
//	{
//		return value;
//	}

};

int main()
{
	setlocale(0, "UKR");

	const int SIZE = 25;
	int ar[SIZE] = { // в начале и в конце массива - сотки
		100, 50, 25, 10, 5,
		15, 35, 27, 40, 75,
		60, 90, 300, 200, 150,
		250, 500, 400, 350, 370,
		700, 800, 750, 900, 100
	};

	Tree bt;
	for (int i = 0; i < SIZE; i++)
		bt.AddNode(ar[i]);
	bt.ShowTree();
	bt.BalancedTree(SIZE);
	


	//cout << "\n" << bt.GetCount() << "\n";
	//// 24 элемента, потому что вторая сотка не добавилась

	//Tree bt2 = bt;

	//bt2.ShowTree();

	//Tree bt3;
	//for (int i = 0; i < 10; i++)
	//	bt3.AddNode(rand() % 100);
	//bt3.ShowTree();

	//bt3 = bt2;
	//cout << "\n" << bt3.GetCount() << "\n";

	//Tree::Node* f = bt.FindNode(750);
	//if (f)
	//	cout << "\nзначение 750 найдено!\n";

	//bt.DeleteNode(750);
	//bt.ShowTree();

	//bt.DeleteNode(700);
	//bt.ShowTree();

	//bt.DeleteNode(500);
	//bt.ShowTree();

	//bt.DeleteNode(25);
	//bt.ShowTree();
}