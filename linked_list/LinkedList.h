#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#pragma once

template <typename T>
class LinkedList
{
public:

	/*======Data_Node======*/

	class Node
	{
	public:
		Node(const T& _data);
		T data;
		Node* next;
		Node* prev;
	};

	/*======BEHAVOIRS======*/
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	/*======INSERTION_OPERATIONS======*/
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, int count);
	void AddNodesTail(const T* data, int count);

	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	/*======REMOVAL_OPERATIONS======*/
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	/*======ACCESSORS======*/
	unsigned int NodeCount() const;

	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	Node* GetNode(unsigned int index);
	const Node* GetNode(unsigned int index) const;

	Node* Find(const T& data);
	const Node* Find(const T& data) const;
	void FindAll(std::vector<Node*>& outData, const T& value) const;

	/*======OPERATORS======*/
	T& operator[](unsigned int index);
	const T& operator[](unsigned int index) const;
	const LinkedList& operator=(const LinkedList& rhs);
	bool operator==(const LinkedList& rhs) const;

	/*======CONSTRUCTION/DESTRUCTION======*/
	LinkedList();
	LinkedList(const LinkedList& list);
	~LinkedList();

private:

	Node* head;
	Node* tail;
	unsigned int nodeCount;
};

/*======BEHAVOIRS======*/

template <typename T>
void LinkedList<T>::PrintForward() const
{
	Node* currObj = head;
	while (currObj != nullptr)
	{
		std::cout << currObj->data << std::endl;
		currObj = currObj->next;
	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const
{
	Node* currObj = tail;
	while (currObj != nullptr)
	{
		std::cout << currObj->data << std::endl;
		currObj = currObj->prev;
	}
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
	if (node == nullptr)
	{
		std::cout << std::endl;
		return;
	}

	std::cout << node->data << std::endl;
	PrintForwardRecursive(node->next);
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	if (node == nullptr)
	{
		std::cout << std::endl;
		return;
	}

	std::cout << node->data << std::endl;
	PrintReverseRecursive(node->prev);
}

/*======INSERTION_OPERATIONS======*/

template <typename T>
void LinkedList<T>::AddHead(const T& data)
{
	// add node to the head of list
	Node* obj = new Node(data);

	obj->next = head;

	if (head != nullptr)
	{
		head->prev = obj;
	}

	head = obj;

	if (nodeCount == 0)
	{
		tail = head;
	}

	nodeCount += 1;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data)
{
	// add node to the tail of the list
	if (nodeCount == 0)
	{
		AddHead(data);
	}
	else
	{
		Node* obj = new Node(data);

		tail->next = obj;
		obj->prev = tail;
		tail = obj;

		nodeCount += 1;
	}
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, int count)
{
	for (int i = count - 1; i >= 0; --i)
	{
		AddHead(data[i]);
	}

	nodeCount += count;
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, int count)
{
	for (int i = 0; i < count; ++i)
	{
		AddTail(data[i]);
	}

	nodeCount += count;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data)
{
	Node* obj = new Node(data);

	Node* before = node;
	Node* after = before->next;

	obj->next = after;
	obj->prev = before;

	before->next = obj;
	after->prev = obj;

	nodeCount += 1;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data)
{
	Node* obj = new Node(data);

	Node* after = node;
	Node* before = node->prev;

	obj->next = after;
	obj->prev = before;

	before->next = obj;
	after->prev = obj;

	nodeCount += 1;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{
	if (index > nodeCount)
	{
		throw std::out_of_range("Error: index out of range");
	}
	else if (index == nodeCount)
	{
		AddTail(data);
	}
	else if (index == 0)
	{
		AddHead(data);
	}
	else
	{
		Node* obj = new Node(data);
		Node* before = head;

		for (unsigned int i = 0; i < index - 1; ++i)
		{
			before = before->next;
		}

		Node* after = before->next;

		obj->next = after;
		obj->prev = before;

		before->next = obj;
		after->prev = obj;

		nodeCount += 1;
	}
}

/*======REMOVAL_OPERATIONS======*/

template <typename T>
bool LinkedList<T>::RemoveHead()
{
	if (nodeCount == 0)
	{
		return false;
	}

	Node* temp = head;
	head = head->next;

	delete temp;
	nodeCount -= 1;

	if (head != nullptr)
	{
		head->prev = nullptr;
	}

	return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail()
{
	if (nodeCount == 0)
	{
		return false;
	}

	if (tail == head)
	{
		RemoveHead();
	}
	else
	{
		Node* temp = tail;
		tail = tail->prev;
		tail->next = nullptr;

		delete temp;
		nodeCount -= 1;
	}

	return true;
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data)
{
	unsigned int count = 0;

	Node* temp = head;
	while (temp != nullptr)
	{
		if (temp->data == data)
		{
			Node* del = temp;
			Node* before = del->prev;
			Node* after = del->next;

			before->next = after;
			after->prev = before;

			delete del;
			count += 1;
			nodeCount -= 1;

			temp = after;
		}
		else
		{
			temp = temp->next;
		}
	}

	return count;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
	// remove data node at specific index
	if (index > nodeCount - 1 || nodeCount == 0)
	{
		return false;
	}
	else if (index == nodeCount - 1)
	{
		RemoveTail();
		return true;
	}
	else if (index == 0)
	{
		RemoveHead();
		return true;
	}
	else
	{
		Node* del = GetNode(index);

		Node* before = del->prev;
		Node* after = del->next;

		before->next = after;
		after->prev = before;

		delete del;
		nodeCount -= 1;

		return true;
	}
}

template <typename T>
void LinkedList<T>::Clear()
{
	Node* temp = head;

	while (temp != nullptr)
	{
		Node* del = temp;
		temp = temp->next;
		delete del;
	}

	head = nullptr;
	tail = nullptr;
	nodeCount = 0;
}

/*======ACCESSORS======*/

template <typename T>
unsigned int LinkedList<T>::NodeCount() const
{
	return nodeCount;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
	return tail;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
	if (index > nodeCount - 1)
	{
		throw std::out_of_range("Error: index out of range");
	}

	Node* toReturn = head;

	for (unsigned int i = 0; i < index; ++i)
	{
		toReturn = toReturn->next;
	}

	return toReturn;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
	if (index > nodeCount - 1)
	{
		throw std::out_of_range("Error: index out of range");
	}

	Node* toReturn = head;

	for (int i = 0; i < index; ++i)
	{
		toReturn = toReturn->next;
	}

	return toReturn;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
	Node* toReturn = head;

	while (toReturn != nullptr)
	{
		if (toReturn->data == data)
		{
			return toReturn;
		}

		toReturn = toReturn->next;
	}

	return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const
{
	Node* toReturn = head;

	while (toReturn != nullptr)
	{
		if (toReturn->data == data)
		{
			return toReturn;
		}

		toReturn = toReturn->next;
	}

	return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(std::vector<Node*>& outData, const T& value) const
{
	Node* toReturn = head;

	while (toReturn != nullptr)
	{
		if (toReturn->data == value)
		{
			outData.push_back(toReturn);
		}

		toReturn = toReturn->next;
	}
}

/*======OPERATORS======*/

template <typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
	// modify operator to return specific node of list
	if (index > nodeCount - 1)
	{
		throw std::out_of_range("Error: index out of range");
	}

	Node* toReturn = head;

	for (int i = 0; i < index; ++i)
	{
		toReturn = toReturn->next;
	}

	return toReturn->data;
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	// modify operator to return specific node of list
	if (index > nodeCount - 1)
	{
		throw std::out_of_range("Error: index out of range");
	}

	Node* toReturn = head;

	for (int i = 0; i < index; ++i)
	{
		toReturn = toReturn->next;
	}

	return toReturn->data;
}


template <typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs)
{
	// equals operator
	this->Clear();

	Node* originalData = rhs.head;
	AddHead(originalData->data);

	originalData = originalData->next;
	while (originalData != nullptr)
	{
		AddTail(originalData->data);
		originalData = originalData->next;
	}

	return *this;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList& rhs) const
{
	if (this->nodeCount != rhs.nodeCount)
	{
		return false;
	}
	else
	{
		Node* list1 = this->head;
		Node* list2 = rhs.head;

		while (list1 != nullptr)
		{
			if (list1->data != list2->data)
			{
				return false;
			}

			list1 = list1->next;
			list2 = list2->next;
		}

		return true;
	}
}

/*======CONSTRUCTION/DESTRUCTION======*/

template <typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	nodeCount = 0;
}


template <typename T>
LinkedList<T>::LinkedList(const LinkedList& list)
{
	// copy constructor
	head = nullptr;
	tail = nullptr;
	nodeCount = 0;

	Node* originalData = list.head;
	AddHead(originalData->data);

	originalData = originalData->next;
	while (originalData != nullptr)
	{
		AddTail(originalData->data);
		originalData = originalData->next;
	}
}


template <typename T>
LinkedList<T>::~LinkedList()
{
	// destructor
	this->Clear();
}

template <typename T>
LinkedList<T>::Node::Node(const T& _data)
{
	data = _data;
	next = nullptr;
	prev = nullptr;
}