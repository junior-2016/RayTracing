#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#define DEFULT_CAPCITY 10
template<class T>
class DynamicArray
{
private:
	T*data;
	int size;
	int capcity;
public:
	DynamicArray();
	DynamicArray(int cap);
	~DynamicArray();
	bool append(T object);
	bool truncate();
	void clear() { size = 0; }
	int length()const { return size; }
	bool empty()const { return size == 0; }
	T& operator[](int index) { return data[index]; }
	const T& operator[](int index) const { return data[index]; }

};
template<class T>
DynamicArray<T>::DynamicArray()
{
	size = 0;
	capcity = DEFULT_CAPCITY;
	data = new T[capcity];
}
template<class T>
DynamicArray<T>::DynamicArray(int cap)
{
	size = 0;
	capcity = cap;
	data = new T[capcity];
}
template<class T>
DynamicArray<T>::~DynamicArray()
{
	size = 0;
	delete[]data;
}
template<class T>
bool DynamicArray<T>::append(T object)
{
	if (size >= capcity)
	{
		T * temp = data;
		capcity *= 2;
		data = new T[capcity];
		for (int i = 0;i < size;i++) data[i] = temp[i];
		delete[]temp;
		data[size++] = object;
		return true;
	}
	data[size++] = object;
	return true;
}
template<class T>
bool DynamicArray<T>::truncate()//将空间利用率提高为100%
{
	if (size < capcity)
	{
		T *temp = data;
		capcity = size;
		if (!(data = new T[capcity])) return false;
		for (int i = 0;i < size;i++) data[i] = temp[i];
		delete[] temp;
	}
	return true;
}
#endif // !DYNAMIC_ARRAY_H
