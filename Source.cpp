#include <iostream>
#include <string>



template <typename T>
class List {
private:
	
	template <typename T>
	class Node {
	public:
		Node* pNext;
		Node* pPrevious;
		T data;

		Node(T data = T(), Node* pNext = nullptr, Node* pPrevious = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrevious = pPrevious;
		}
	};
	
	int m_Size;
	Node<T>* m_Head;
	Node<T>* m_Tail;

public:
	List();
	~List();

	T& operator[](const int index);
	void push_back(T data);
	void push_front(T data);

	void pop_front();
	void pop_back();

	void clear();

	int get_Size() { return m_Size; }

	void insert(T data, int index);
	void remove_at(int index);

};

template<typename T>
List<T>::List()
{
	m_Size = 0;
	m_Head = nullptr;
	m_Tail = nullptr;
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->m_Head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}

	std::cerr << "Index doesn't exist!";
}

template<typename T>
void List<T>::push_back(T data)
{

	Node<T> *Temp = new Node<T>;
	Temp->pNext = NULL;
	Temp->data = data;
	// if list isn't empty
	if (m_Head != NULL) {
		Temp->pPrevious = m_Tail;
		m_Tail->pNext = Temp;
		m_Tail = Temp;
	} // If the first object doesn't exist
	else {
		Temp->pPrevious = NULL;
		m_Head = m_Tail = Temp;
	}

	m_Size++;
}

template<typename T>
void List<T>::push_front(T data)
{
	Node<T>* Temp = new Node<T>;
	Temp->pNext = m_Head;
	Temp->data = data;
	m_Head->pPrevious = Temp;

	m_Head = Temp;
	m_Size++;
}

template<typename T>
void List<T>::pop_front()
{

	Node<T>* Temp = m_Head;
	if (m_Head->pNext != nullptr) {
		m_Head = m_Head->pNext;
		m_Head->pPrevious = nullptr;
	}

	delete Temp;

	m_Size--;
}

template<typename T>
void List<T>::pop_back()
{

	Node<T>* Temp = m_Tail;
	if (m_Tail->pPrevious != nullptr) {
		m_Tail = m_Tail->pPrevious;
		m_Tail->pNext = nullptr;
	}

	delete Temp;

	m_Size--;
}


template<typename T>
void List<T>::clear()
{
	while (get_Size())
	{
		pop_front();
	}
}

template<typename T>
void List<T>::insert(T data, int index)
{

	int half_size = m_Size / 2;

		if (index == 0)
		{
			push_front(data);
		}
		else if (index > m_Size) {
			push_back(data);
		}
		else {

			if (index <= half_size) {
				Node<T>* previous = this->m_Head;
				for (int i = 0; i < index - 1; i++)  // встречается дважды (remove at)
				{
					previous = previous->pNext;
				}
				Node<T>* newNode = new Node<T>(data, previous->pNext, previous);
				previous->pNext = newNode;
				Node<T>* next = newNode->pNext;
				next->pPrevious = newNode;

				m_Size++;
			}
			else {
				Node<T>* Next = this->m_Tail;
				for (int i = m_Size; i > (index+1); i--)  // встречается дважды (remove at)
				{
					Next = Next->pPrevious;
				}
				Node<T>* newNode = new Node<T>(data, Next, Next->pPrevious);
				Next->pPrevious = newNode;
				Node<T>* Previous = newNode->pPrevious;
				Previous->pNext = newNode;

				m_Size++;
		}
	}
}

template<typename T>
void List<T>::remove_at(int index)
{
	int half_size = m_Size / 2;

	if (index == 0)
	{
		pop_front();
	}
	else if (index > m_Size) {
		pop_back();
	}
	else {
		if (index <= half_size) {
			Node<T>* previous = this->m_Head;
			for (int i = 0; i < index - 1; i++) // встречается дважды (insert)
			{
				previous = previous->pNext;
			}
			Node<T>* toDelete = previous->pNext;
			Node<T>* Next = toDelete->pNext;
			Next->pPrevious = previous;
			previous->pNext = Next;

			delete toDelete;
			m_Size--;
		}

		else {
			Node<T>* toDelete  = this->m_Tail;
			for (int i = m_Size; i > (index + 1); i--)  // встречается дважды (remove at)
			{
				toDelete = toDelete->pPrevious;
			}
			
			Node<T>* Previous = toDelete->pPrevious;
			Node<T>* Next = toDelete->pNext;
			Previous->pNext = Next;
			Next->pPrevious = Previous;


			delete toDelete;
			m_Size--;
		}

	}
}





int main() {

	List<int> test;

	test.push_back(0);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);


	test.insert(1, 1);
	test.insert(99, 4);
	std::cout << test[4];
	test.remove_at(4);
	std::cout << test.get_Size();

	return 0;
}

