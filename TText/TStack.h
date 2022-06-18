#pragma once
using namespace std;
#include<iostream>
#include <conio.h>
template <class T>
class TStack
{
private:
	T* arr;
	int size;
	int num;
public:
	TStack(int _size = 100);
	~TStack();
	TStack(const TStack<T>& st);
	TStack<T>& operator=(const TStack<T>& st);
	bool IsEmpty()const;
	bool IsFull()const;
	void Push(const T& a);
	T Pop();
	T Top();
	void Clear();
};

template <class T>
TStack<T>::TStack(int _size)
{
	if (_size <= 0)
	{
		char e[] = "Size cant be negative";
		throw e;
	}
	size = _size;
	arr = new T[size];
	num = -1;
}

template <class T>
TStack<T>::~TStack()
{
	delete[]arr;
}

template <class T>
TStack<T>::TStack(const TStack<T>& st)
{
	size = st.size;
	arr = new T[size];
	num = st.num;
	for (int i = 0; i <= num; i++)
	{
		arr[i] = st.arr[i];
	}
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& st)
{
	if (this != &st)
	{
		size = st.size;
		delete[]arr;
		arr = new T[size];
		num = st.num;
		for (int i = 0; i <= num; i++)
		{
			arr[i] = st.arr[i];
		}
	}
	return *this;
}

template <class T>
bool TStack<T>::IsEmpty()const {
	return num == -1;
}

template <class T>
bool TStack<T>::IsFull()const {
	return num == size - 1;
}

template <class T>
void TStack<T>::Push(const T& a) {
	if (IsFull())
	{
		char e[] = "Stack is Full";
		throw e;
	}
	else
	{
		arr[++num] = a;
	}
}

template <class T>
T TStack<T>::Pop() {
	if (IsEmpty())
	{
		char e[] = "Stack is Empty";
		throw e;
	}
	else
	{
		return arr[num--];
	}
}

template <class T>
T TStack<T>::Top() {
	if (IsEmpty())
	{
		char e[] = "Stack is Empty";
		throw e;
	}
	else
	{
		return arr[num];
	}
}

template <class T>
void TStack<T>::Clear() {
	num = -1;
}