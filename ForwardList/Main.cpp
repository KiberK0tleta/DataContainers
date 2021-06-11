#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

template<typename T>class Iterator;
template<typename T>class ForwardList;

template<typename T>

class Element
{
	T Data;           //Значение элемента
	Element<T>* pNext;    //Указатель на следующий элемент
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		//cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		//cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
};
template<typename T>
int Element<T>::count = 0; //Инициализация стат переменной

template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr)
	{
		this->Temp = Temp;
		//cout << "IConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		//cout << "IDestructor:\t" << this << endl;
	}
	//--------------------operators--------------------//
	Iterator<T>& operator++()
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
	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	Element<T>*& operator->()
	{
		return Temp;
	}
	Element<T>* get_currend_address()
	{
		return Temp;
	}


	const T& operator*()const
	{
		return Temp->Data;
	}
	T& operator*()
	{
		return Temp->Data;
	}
	//-------------------------------------------------//
};


template<typename T>
class ForwardList
{
	Element<T>* Head;
	int size;
public:
	Iterator<T> getHead()
	{
		return Head;
	}
	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<T> il):ForwardList()
	{
		//il - контейнер такой же как ForwardList у любого контейнера есть методы begin() и end() которые возвращают указатели на начало и конец контейнеров 
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it); // it итератор который проходит по il
		}
	}
	ForwardList(const ForwardList<T>& other)
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
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element<T>* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyAssigment:\t" << this << endl;
		return *this;

	}
	//---------------------------------------------//
	void push_front(T Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		//Element* New = new Element(Data);
		Element<T>* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	void pop_front()
	{
		Element<T>* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(T Data, int index)
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}
		//Element* New = new Element(Data);
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
			if (Temp->pNext == nullptr)break;
		}
		//New->pNext = Temp->pNext;
		Temp->pNext = new Element<T>(Data,Temp->pNext);
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
		Element<T>* Temp = Head;
		for (int i = 0; i <index-1; i++)
		{
			Temp = Temp->pNext;
			Element<T>* to_del = Temp->pNext;
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
		for (Iterator<T> Temp = Head; Temp != nullptr; ++Temp)
			//cout << Temp.get_currend_address()<< tab <<Temp->Data << tab<<Temp->pNext<<endl;
			cout << *Temp << tab;
		cout << endl;
		cout << "Кол-во эл в списку: " << size << endl;
		cout << "Общее Кол-во эл в списку: " << Element<T>::count << endl;
	}
};


#define BASE_CHECK
#define ITRATOR_CHACK
#define RANGE_BASED_LIST



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
#ifndef RANGE_BASED_LIST
	ForwardList<int> list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // !RANGE_BASED_LIST

	ForwardList<double> list = { 2.5,3.14,8.3,5.4,7.2 };
	for (double i : list)
	{
		cout << i << tab;
	}

}