#include<iostream>
using namespace std;


// circular queue with linked list


//  two operation performed on circular LL
// 1) enqueue -> insert a new element at rear(back)
// 2) dequeue -> delete a element at front



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


Node* front;
Node* rear;



void enqueue(int data)
{
	Node* newNode = new Node(data);
	if (rear == NULL)
	{
		rear = newNode;
		front = rear;
		rear->next = front;
	}
	rear->next = newNode;
	rear = newNode;
	rear->next = front;
}


void print_queue()
{
	if (rear == NULL)
	{
		cout << "empty " << endl;
		return;
	}
	Node* temp = front;
	while (temp->next != front)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << temp->data << endl;
}


void dequeue()
{
	if (front == NULL)
	{
		cout << "queue is empty " << endl;
	}
	else if (rear != front)
	{
		cout << "remove " << front->data << endl;
		Node* curr = front;
		front = front->next;
		rear->next = NULL;
		delete(curr);
		rear->next = front;
	}
	else
	{
		cout << "remove " << front->data << endl;
		front = NULL;
		rear = NULL;
	}

}


int main()
{
	front = NULL;
	rear = NULL;

	// enqueue(10);
	// enqueue(20);
	// // enqueue(30);
	// // enqueue(40);


	// print_queue();

	// dequeue();
	// dequeue();
	// dequeue();
	// enqueue(20);

	// print_queue();

	cout << "----------------" << endl;
	cout << "\n1.enqueue  \n2.dequeue \n3.display\n4.exit" << endl;
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
			enqueue(val);
		}
		else if (ch == 2)
		{
			dequeue();
		}
		else if (ch == 3)
		{
			cout << "queue contents is" << endl;
			print_queue();
			cout << endl;
		}
		else break;

	}


	return 0;
}
