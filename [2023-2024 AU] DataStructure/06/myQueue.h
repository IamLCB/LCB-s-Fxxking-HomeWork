#ifndef _MY_QUEUE_
#define _MY_QUEUE_

#include "myList.h"

template<class Type>
class Queue
{
private:
	//�ڲ�����һ������
	List<Type> data;

public:
	//���캯��
	//Ĭ�Ϲ��캯��
	Queue();

	//�ж϶����Ƿ�Ϊ��
	inline bool empty()const;
	//���ض��д�С
	inline int size()const;

	//���
	void push(const Type& i);
	//����
	void pop();

	//��ȡ����Ԫ��
	const Type& front()const;
	Type& front();
};

//Ĭ�Ϲ��캯��
template<class Type>
Queue<Type>::Queue()
{

}

//�ж϶����Ƿ�Ϊ��
template<class Type>
inline bool Queue<Type>::empty()const
{
	return this->data.empty();
}

//���ض��д�С
template<class Type>
inline int Queue<Type>::size()const
{
	return this->data._size;
}

//���
template<class Type>
void Queue<Type>::push(const Type& i)
{
	this->data.push_back(i);
}

//����
template<class Type>
void Queue<Type>::pop()
{
	this->data.erase_first();
}

//��ȡ����Ԫ��
template<class Type>
const Type& Queue<Type>::front()const
{
	return this->data.head->next->data;
}

template<class Type>
Type& Queue<Type>::front()
{
	return this->data.head->next->data;
}

#endif // !_MY_QUEUE_

