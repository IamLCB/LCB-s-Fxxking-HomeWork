#pragma once
#ifndef _MY_VECTOR_
#define _MY_VECTOR_

#define VECTOR_DEFAULT_SIZE 5 //������С

template<class Type>
class Vector
{
	typedef Type* Pointer;
	typedef Pointer _iterator;

private:
	//���ݴ�С
	int _size;
	//��ǰ����
	int _capacity;
	//����
	Type* _elements;

	//��dataָ���и���[low,high)��һ������
	Type* copyFrom(Type* data, int low, int high, int size = 0);

	//����Ԫ������
	void expand();
public:
	//���캯��
	Vector();//Ĭ�Ϲ��캯��
	Vector(int size);//��ʼ��С�Ĺ��캯��
	Vector(const Vector& v);//���ƹ��캯��
	Vector(int sz, Type data)
	{
		this->_size = sz;
		this->_capacity = (_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;

		//����ռ�
		this->_elements = new Type[_capacity];
		if (_elements == nullptr)
			;
		for (int i = 0; i < sz; ++i)
			this->_elements[i] = data;
	}

	//��������
	~Vector();

	//��������
	class iterator
	{
	private:
		_iterator data;//һ��ָ��
	public:
		typedef Type value_type;
		//Ĭ�Ϲ��캯��
		iterator() :data(nullptr) {};
		//���캯��
		iterator(_iterator datas) :data(datas) {};

		//���������
		//�����ݲ���
		Type& operator*()
		{
			return *data;
		}
		//�Ƚ������
		inline bool operator==(const iterator& v)const
		{
			return this->data == v.data;
		}
		inline bool operator<(const iterator& v)const
		{
			return this->data < v.data;
		}
		inline bool operator>(const iterator& v)const
		{
			return this->data > v.data;
		}
		inline bool operator>=(const iterator& v)const
		{
			return this->data >= v.data;
		}
		inline bool operator<=(const iterator& v)const
		{
			return this->data <= v.data;
		}
		inline bool operator!=(const iterator& v)const
		{
			return this->data != v.data;
		}
		//���������
		inline Vector<Type>::iterator& operator++()
			//ǰ������
		{
			this->data++;
			return (*this);
		}
		Vector<Type>::iterator operator++(int)
			//��������
		{
			Vector<Type>::iterator old = (*this);
			++(*this);
			return old;
		}
		//�Լ������
		inline Vector<Type>::iterator& operator--()
			//ǰ���Լ�
		{
			this->data--;
			return (*this);
		}
		Vector<Type>::iterator operator--(int)
			//�����Լ�
		{
			Vector<Type>::iterator old = (*this);
			--(*this);
			return old;
		}
		//�����һ����
		Vector<Type>::iterator operator+(int index)
		{
			Vector<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//ǰ����һ����
		friend typename Vector<Type>::iterator operator+(int index, typename Vector<Type>::iterator data)
		{
			typename Vector<Type>::iterator old = data;
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//���ȥһ����
		Vector<Type>::iterator operator-(int index)
		{
			Vector<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i)
				--old;
			return old;
		}
		//�Լ�
		Vector<Type>::iterator& operator+=(int index)
		{
			for (int i = 0; i < index; ++i)
				++(*this);
			return (*this);
		}
		//�Լ�
		Vector<Type>::iterator& operator-=(int index)
		{
			for (int i = 0; i < index; ++i)
				--(*this);
			return (*this);
		}
		friend int operator-(const Vector<Type>::iterator& i, const Vector<Type>::iterator& j)
		{
			return i.data - j.data;
		}
	};



	//������С
	inline int size()const;
	//�ж������Ƿ�Ϊ��
	inline bool empty()const;

	//β����������
	void push_back(const Type data);
	//ɾ������
	Type pop_back();
	//��ָ��������ǰ��������
	bool insert(const Vector<Type>::iterator place, Type item);
	//ɾ��ָ��������������
	bool erase(const Vector<Type>::iterator place);
	//�������
	void clear();
	//��ָ����Χ�ڲ������ݣ�������λ������Ӧ�ĵ�����

	//ͳһ��ֵ
	void fillData(const Type data);

	//����ָ��λ�õ�һϵ�к���
	//��ʼλ�õ�����
	inline Vector<Type>::iterator begin();
	inline const Vector<Type>::iterator begin()const;
	//���λ�õ�����
	inline Vector<Type>::iterator end();
	inline const Vector<Type>::iterator end()const;
	//��ȡ���һ��Ԫ�صĵ�����
	inline Vector<Type>::iterator last();
	inline const Vector<Type>::iterator last()const;

	//��һ������
	Type& front()const
	{
		return this->_elements[0];
	}

	//���������
	//ȡ�±������������[]
	inline Type& operator[](int i);
	//�Ⱥ������
	Vector<Type>& operator=(const Vector<Type>& v);

	void resize(int sz)
	{
		while (this->_size < sz)
		{
			if (this->_size == this->_capacity)
				this->expand();

			_size++;
		}

		while (this->_size > sz)
		{
			_size--;
		}
	}

};

//Ĭ�Ϲ��캯��
template<class Type>
Vector<Type>::Vector()
{
	this->_capacity = VECTOR_DEFAULT_SIZE;
	this->_size = 0;
	//����Ĭ��������С����ռ�
	this->_elements = new Type[_capacity];
}

//������ʼ��С�Ĺ��캯��
template<class Type>
Vector<Type>::Vector(int size)
{
	this->_size = size;
	this->_capacity = (_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;

	//����ռ�
	this->_elements = new Type[_capacity];
	if (_elements == nullptr)
		;
}

//���ƹ��캯��
template<class Type>
Vector<Type>::Vector(const Vector& v)
{


	this->_size = v._size;
	this->_capacity = v._capacity;

	//Ԫ��һһ����
	this->_elements = copyFrom(v._elements, 0, _size, _capacity);
}

//��dataָ���и���[low,high)��һ������
template<class Type>
Type* Vector<Type>::copyFrom(Type* data, int low, int high, int size)
{
	if (size == 0)
		size = high - low;

	//����ռ�
	Type* newData = new Type[size];

	//һһ����
	for (int i = low; i < high; ++i)
		newData[i] = data[low + i];

	return newData;
}

//��ȡ����Ԫ�ظ���
template<class Type>
inline int Vector<Type>::size()const
{
	return this->_size;
}

//����Ԫ������
template<class Type>
void Vector<Type>::expand()
{
	this->_capacity += VECTOR_DEFAULT_SIZE;

	Type* oldElements = this->_elements;

	//����
	this->_elements = copyFrom(this->_elements, 0, _size, _capacity);

	delete[] oldElements;
}

//��������
template<class Type>
void Vector<Type>::push_back(const Type data)
{
	//�ж�����
	if (this->_size == this->_capacity)
		this->expand();

	this->_elements[_size++] = data;
}

//ȡ�±������������[]
template<class Type>
inline Type& Vector<Type>::operator[](int i)
{
	if (i < 0 || i >= _size)
		;

	return _elements[i];
}

//ɾ������
template<class Type>
Type Vector<Type>::pop_back()
{
	if (_size == 0)
		;

	//�������һ������
	return _elements[--_size];
}

//������������ʼλ��
template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::begin()
{
	return _size > 0 ? typename Vector<Type>::iterator(&_elements[0]) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline const typename Vector<Type>::iterator Vector<Type>::begin()const
{
	return _size > 0 ? typename Vector<Type>::iterator(&_elements[0]) :
		typename Vector<Type>::iterator();
}

//�������������λ��
template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::end()
{
	return _size > 0 ? ++(typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline const typename Vector<Type>::iterator Vector<Type>::end()const
{
	return _size > 0 ? ++(typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::last()
{
	return _size > 0 ? (typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline const typename Vector<Type>::iterator Vector<Type>::last()const
{
	return _size > 0 ? (typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

//ǰ�ü�һ����
template<class Type>
typename Vector<Type>::iterator operator+(int index, typename Vector<Type>::iterator data)
{
	typename Vector<Type>::iterator old = data;
	for (int i = 0; i < index; ++i)
		++old;
	return old;
}

//�ж������Ƿ�Ϊ��
template<class Type>
inline bool Vector<Type>::empty()const
{
	return this->_size == 0;
}

//��ָ��������ǰ��������
template<class Type>
bool Vector<Type>::insert(const typename Vector<Type>::iterator place, Type item)
{
	//��ǰ��¼λ��(expand��λ�÷����仯)
	auto places = place;
	int j = places - this->begin();

	//�ж��Ƿ���Ҫ����
	if (this->_size == this->_capacity)
		this->expand();

	//��place�����������Ԫ�����κ���һλ
	int i;

	for (i = _size - 1; i >= j; --i)
		this->_elements[i + 1] = this->_elements[i];

	//��������Ԫ��
	this->_elements[i + 1] = item;
	this->_size++;

	return true;
}

//ɾ��ָ��������������
template<class Type>
bool Vector<Type>::erase(const typename Vector<Type>::iterator place)
{
	//��ȡplace���±�λ��
	int index = place - this->begin();

	if (index < 0 || index >= this->_size)
		return false;

	while (index < this->_size - 1)
	{
		this->_elements[index] = this->_elements[index + 1];
		++index;
	}

	this->_size--;

	return true;
}

//�������
template<class Type>
void Vector<Type>::clear()
{
	//�������Ԫ��
	delete[] _elements;

	//����Ĭ�Ϲ��캯��
	this->_capacity = VECTOR_DEFAULT_SIZE;
	this->_size = 0;
	//����Ĭ��������С����ռ�
	this->_elements = new Type[_capacity];
}

//��������
template<class Type>
Vector<Type>::~Vector()
{
	//�������Ԫ��
	delete[] _elements;
}

//���صȺ������
template<class Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type>& v)
{
	//��ֹ���ҵ���
	if (v._elements == this->_elements)
		return *this;
	this->clear();
	//һ��һ�����ĸ��ƹ�ȥ
	for (auto i = v.begin(); i != v.end(); ++i)
		this->push_back(*i);

	return *this;
}

//ͳһ��ֵ
template<class Type>
void Vector<Type>::fillData(const Type data)
{
	for (auto i = begin(); i != end(); ++i)
		*i = data;
}


#endif // !_MY_VECTOR_

	