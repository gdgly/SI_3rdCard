#include "stdafx.h"
#include "CardReadBase.h"

template<class T>
CCardReadBase<T>::CCardReadBase()
{

};


template<class T>
CCardReadBase<T>::~CCardReadBase()
{
	if (t)
	{
		delete t;
		t=nullptr;
	}
};

template<class T>
T* CCardReadBase<T>::getInstance()
{
	if (t)
	{
		delete t;
	}
	t = new T();
	return t;
}