#ifndef SORT_H
#define SORT_H
#include<iostream>
using namespace std;
template<class T>
class sort
{
public:
	static void insertSort(T * array, int size)
	{
		for (int i = 1;i < size;i++)
		{
			T key = array[i];
			int j = i - 1;
			while (j>=0&&array[j]>key)
			{
				array[j + 1] = array[j];
				j -= 1;
			}
			array[j + 1] = key;
		}
	}
};
#endif // !SORT_H

