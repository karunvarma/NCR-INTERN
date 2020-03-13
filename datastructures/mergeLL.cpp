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

Node* insert(Node* head1, Node* head2, int pos)
{
	Node* prev = head1;
	Node* curr = head1;
	int cnt = 1;
	while (cnt < pos)
	{
		prev = curr;
		curr = curr->next;
		cnt++;
	}
	if (prev)
	{
		cout << "prev " << prev->data << endl;
	}
	if (curr)
	{
		cout << "curr" << curr->data << endl;
	}
	Node* last = head2;
	while (last->next != NULL)
	{
		last = last->next;
	}

	if (last)
	{
		cout << "last" << last->data << endl;
	}
	
	
	if (pos == 1)
	{
		last->next = curr;
		return head2;
	}
	else
	{
		prev->next = head2;
		last->next = curr;
	}
	
	return  head1;
}




int main()
{

	Node* head1 = NULL;
	Node* head2 = NULL;

	int n1, n2;

	cout << "enter list1 size" << endl;
	cin >> n1;
	for (int i = 0; i < n1; i++)
	{
		int data;
		cin >> data;
		head1 = add(head1, data);
	}
	print(head1);

	cout << "enter list2 size" << endl;
	cin >> n2;
	for (int i = 0; i < n2; i++)
	{
		int data;
		cin >> data;
		head2 = add(head2, data);
	}
	print(head2);

	
		cout << "enter pos" << endl;
		int pos;
		cin >> pos;

		if (pos > n1)
		{
			cout << "invalid pos" << endl;
			return 0;
		}

		Node* merge = NULL;


		merge = insert(head1, head2, pos);

		print(merge);

	


	return 0;
}
