#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
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
		//cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		//cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};
int Element::count = 0; //Инициализация стат переменной

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr)
	{
		this->Temp = Temp;
		//cout << "IConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		//cout << "IDestructor:\t" << this << endl;
	}
	//--------------------operators--------------------//
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	Element*& operator->()
	{
		return Temp;
	}
	Element* get_currend_address()
	{
		return Temp;
	}
	int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
	//-------------------------------------------------//
};



class ForwardList
{
	Element* Head;
	int size;
public:
	Iterator getHead()
	{
		return Head;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il):ForwardList()
	{
		//il - контейнер такой же как ForwardList у любого контейнера есть методы begin() и end() которые возвращают указатели на начало и конец контейнеров 
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it); // it итератор который проходит по il
		}
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
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//--------------------operators--------------------//
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyAssigment:\t" << this << endl;
		return *this;

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
		/*while (Temp != nullptr)
		Element* Temp = Head;
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for (Iterator Temp = Head; Temp != nullptr; ++Temp)
			//cout << Temp.get_currend_address()<< tab <<Temp->Data << tab<<Temp->pNext<<endl;
			cout << *Temp << tab;
		cout << endl;
		cout << "Кол-во эл в списку: " << size << endl;
		cout << "Общее Кол-во эл в списку: " << Element::count << endl;
	}
};


#define BASE_CHECK
#define ITRATOR_CHACK



void main()
{
//-------------------------------------------------------//
	setlocale(LC_ALL, "");
#ifndef BASE_CHECK
	int n;
	cout << "Размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list = list;
	list.print();
#endif // !BASE_CHECK

#ifndef ITRATOR_CHACK
	for (Iterator it = list.getHead(); it != nullptr; it++)
	{
		*it = rand() % 100;
	}

	list.print();
#endif // !ITRATOR_CHACK

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
	ForwardList list2 = list;
	list2.print();
#endif // !BASE_CHECK
//-------------------------------------------------------//
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

}