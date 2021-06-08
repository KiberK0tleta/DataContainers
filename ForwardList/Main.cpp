#include<iostream>
using namespace std;
#define tab "\t"

class Element
{
	int Data;           //Значение элемента
	Element* pNext;    //Указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0; //Инициализация стат переменной

class ForwardList
{
	Element* Head;
	int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other)
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)
		{
			pop_front();
		}
		cout << "LDestructor:\t" << this << endl;
	}
	//---------------------------------------------//
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
		size++;
	}
	void pop_front()
	{
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Data, int index)
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
			if (Temp->pNext == nullptr)break;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void erase(int index)
	{
		if (index > size)return;
		if(index==0)
		{
			pop_front();
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i <index-1; i++)
		{
			Temp = Temp->pNext;
			Element* to_del = Temp->pNext;
			Temp->pNext = Temp->pNext->pNext;
			delete to_del;
			size--;
		}
	}


	void print()
	{
		Element* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Кол-во эл в списку: " << size << endl;
		cout << "Общее Кол-во эл в списку: " << Element::count << endl;
	}
};


#define BASE_CHECK




void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();

#ifndef BASE_CHECK
	int value;
	int index;
	cout << "value:"; cin >> value;
	cout << "index: "; cin >> index;
	list.insert(value, index);
	list.print();

	/*cout << "list2" << endl;
	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();*/
	cout << "index Удал эл: "; cin >> index;
	list.erase(index);
	list.print();
#endif // !BASE_CHECK
	ForwardList list2 = list;
	list2.print();
}