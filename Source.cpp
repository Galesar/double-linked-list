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
	void clear();

	int get_Size() { return m_Size; }


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
void List<T>::clear()
{
	while (get_Size())
	{
		pop_front();
	}
}




int main() {

	List<int> test;

	int arr_size;
	std::cin >> arr_size;
	std::cout << std::endl;
	for (int i = 0; i < arr_size; i++)
	{
		test.push_back(rand() % 10);
	} 

	for (int i = 0; i < test.get_Size(); i++) {
		std::cout << test[i] << std::endl;
	}

	test.pop_front();

	std::cout << "\n\n\n";

	for (int i = 0; i < test.get_Size(); i++) {
		std::cout << test[i] << std::endl;
	}

	test.clear();
	
	test.get_Size();
	if (test.get_Size() != 0) {
		for (int i = 0; i < test.get_Size(); i++) {
			std::cout << test[i] << std::endl;
		}
	}
	else {
		std::cout << "Array is empty";
	}

	return 0;
}