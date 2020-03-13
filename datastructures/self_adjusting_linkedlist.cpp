#include<iostream> 
using namespace std;




struct Node
{
	int data;
	Node* next;
	Node(int val)
	{
		data = val;
		next = NULL;
	}
};


bool isempty(Node* head)
{
	if (!head) return false;
	return true;
}




Node* add(Node* head, int data)
{
	Node* newNode = new Node(data);
	if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		newNode->next = head;
		head = newNode;
	}
	return head;
}


void print(Node* head)
{
	Node* curr = head;
	while (curr)
	{
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << endl;
}


Node* modify(Node* head, int key)
{

	if (head == NULL)
	{
		cout << "linkedlist is empty" << endl;
	}
	else
	{
		Node* prev = head;
		Node* curr = head;

		while (curr and curr->data != key)
		{
			prev = curr;
			curr = curr->next;
		}
		if (curr == NULL)
		{
			cout << "no key found" << endl;
			return head;
		}
		prev->next = curr->next;

		// if there is single element
		if (curr != head)curr->next = head;
		head = curr;
	}
	return head;
}




int main()
{

	Node* head = NULL;
	cout << "----------------" << endl;
	cout << "\n1.append  \n2.modify \n3.display \n4.exit" << endl;
	int ch;
	while (true)
	{
		cout << "enter choice" << endl;
		cin >> ch;

		if (ch == 1)
		{
			cout << "enter value" << endl;
			int val;
			cin >> val;
			head=add(head,val);
		}
		else if (ch == 2)
		{
			cout << "enter node no to be added at front" << endl;
			int no;
			cin >> no;
			head = modify(head, no);
		}
		else if (ch == 3)
		{
			print(head);
			cout << endl;
		}
		else break;

	}
	return 0;
}
