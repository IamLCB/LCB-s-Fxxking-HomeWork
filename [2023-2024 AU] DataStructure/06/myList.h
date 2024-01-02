#pragma once
#ifndef _MY_LIST_
#define _MY_LIST_

template <class Type>
struct ListNode
{
	Type data;
	ListNode<Type> *next, *prev;

	ListNode() : next(nullptr), prev(nullptr) {}//default constructor
	ListNode(Type _data,ListNode<Type>* _next = nullptr, ListNode<Type>* _prev = nullptr) : data(_data), next(_next), prev(_prev) {}//constructor with parameters

};

template <class Type>
class List
{
	typedef ListNode<Type>* _iterator;

private:
	//head
	ListNode<Type>* head;
	//tail
	ListNode<Type>* tail;
	int _size;

public:
	List();
	List(const List<Type>& v);//copy constructor
	~List();//destructor

	class iterator
	{
	private:
		_iterator ptr;
	public:
		iterator() : ptr(nullptr) {}//default constructor
		iterator(_iterator _ptr) : ptr(_ptr) {}//constructor with parameters
		iterator(Type dat) {//constructor with parameters
			dat = new ListNode<Type>;
			ptr->data = dat;
		}

		//operator overloading
		//read
		Type operator*() { return ptr->data; }
		//compare
		bool operator==(const iterator& v) { return this->ptr == v.ptr; }
		bool operator!=(const iterator& v) { return this->ptr != v.ptr; }
		bool operator<(const iterator& v) { return this->ptr < v.ptr; }
		bool operator>(const iterator& v) { return this->ptr > v.ptr; }
		bool operator<=(const iterator& v) { return this->ptr <= v.ptr; }
		bool operator>=(const iterator& v) { return this->ptr >= v.ptr; }
		//add and miuns
		List<Type>::iterator& operator++() {
			if (this->ptr != nullptr) 
				this->ptr = this->ptr->next;
			return *this;
		}
		List<Type>::iterator& operator++(int) {
			List<Type>::iterator temp = *this;
			++(*this);
			return temp;
		}
		List<Type>::iterator& operator--() {
			if (this->ptr != nullptr)
				this->ptr = this->ptr->prev;
			return *this;
		}
		List<Type>::iterator& operator--(int) {
			List<Type>::iterator temp = *this;
			--(*this);
			return temp;
		}
		int operator-(List<Type>::iterator v) {
			int dist = 0;
			while (v->ptr != this->ptr) {
				v++;
				dist++;
			}
			return dist;
		}
		//add and minus a num
		List<Type>::iterator& operator+(int num) {
			List<Type>::iterator old = (*this);
			for (int i = 0; i < num; ++i)
				++old;
			return old;
		}
		friend typename List<Type>::iterator operator+(int index, typename List<Type>::iterator data)
		{
			List<Type>::iterator old = data;
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		List<Type>::iterator& operator-(int num) {
			List<Type>::iterator old = (*this);
			for (int i = 0; i < num; ++i)
				--old;
			return old;
		}
		List<Type>::iterator& operator+=(int num) {
			for (int i = 0; i < num; ++i)
				++(*this);
			return *this;
		}
		List<Type>::iterator& operator-=(int num) {
			for (int i = 0; i < num; ++i)
				--(*this);
			return *this;
		}
		friend class List<Type>;
	};

	int size() const;//return size
	bool empty() const;//check if empty

	void push_back(const Type& data);//add element at the end
	void push_front(const Type& data);//add element at the beginning

	List<Type>::iterator find(const Type& data)const;//find element

	Type remove(List<Type>::iterator data);//remove element
	void remove_last();//remove last element
	void remove_first();//remove first element
	void clear();//clear list
	bool insert(List<Type>::iterator data, Type i);//insert element

	List<Type>::iterator begin();//return iterator to the beginning
	const List<Type>::iterator begin() const;//return iterator to the beginning

	List<Type>::iterator end();//return iterator to the end
	const List<Type>::iterator end() const;//return iterator to the end

	List<Type>& operator=(const List<Type>& v);//operator =

};

//default constructor
template <class Type>
List<Type>::List() {
	head = new ListNode<Type>();
	tail = head;
	_size = 0;
}

//copy constructor
template <class Type>
List<Type>::List(const List<Type>& v) {
	head = new ListNode<Type>();
	tail = head;
	_size = 0;
	for (auto i = v.begin(); i != v.end(); i++) 
		this->push_back(*i);
}

template <class Type>
bool List<Type>::empty() const {
	return tail == head;
}

template <class Type>
void List<Type>::push_back(const Type& data) {

	if (empty()) {
		ListNode<Type>* newNode = new ListNode<Type>(data, nullptr, head);

		head->next = newNode;
		tail = newNode;
	}
	else {
		ListNode<Type>* newNode = new ListNode<Type>(data, nullptr, tail);

		tail->next = newNode;
		tail = newNode;
	}
	_size++;
}

template <class Type>
void List<Type>::push_front(const Type& data) {
	if (empty()) {
		ListNode<Type>* newNode = new ListNode<Type>(data, nullptr, head);

		head->next = newNode;
		tail = newNode;
	}
	else {
		ListNode<Type>* newNode = new ListNode<Type>(data, head->next, head);

		head->next->prev = newNode;
		head->next = newNode;
	}
	_size++;
}

template <class Type>
int List<Type>::size() const {
	return _size;
}

template <class Type>
typename List<Type>::iterator List<Type>::begin() {
	return List<Type>::iterator(this->head->next);
}

template <class Type>
const typename List<Type>::iterator List<Type>::begin() const {
	return List<Type>::iterator(this->head->next);
}

template <class Type>
typename List<Type>::iterator List<Type>::end() {
	return List<Type>::iterator(this->tail->next);
}

template <class Type>
const typename List<Type>::iterator List<Type>::end() const {
	return List<Type>::iterator(this->tail->next);
}

template <class Type>
Type List<Type>::remove(List<Type>::iterator data) {
	ListNode<Type>* temp = data.ptr;
	Type value = temp->data;

	if (temp == tail) {
		tail = temp->prev;
		tail->next = nullptr;
	}
	else {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}

	delete temp;
	return value;

}

template <class Type>
bool List<Type>::insert(List<Type>::iterator data, Type i) {
	ListNode<Type>* temp = data.ptr;
	temp->prev->next = new ListNode<Type>(i, temp, temp->prev);//new node
	temp->prev = temp->prev->next;
	return true;
}

template <class Type>
void List<Type>::remove_last() {
	if (!empty()) {
		ListNode<Type>* toDel = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete toDel;
	}
	else {
		throw("List is empty!");
	}
	return;
}

template <class Type>
void List<Type>::remove_first() {
	if (!empty()) {
		ListNode<Type>* toDel = head->next;
		if (toDel == tail) {
			tail = head;
			head->next = nullptr;
			delete toDel;
		}
		else {
			head->next = toDel->next;
			toDel->next->prev = head;
			delete toDel;
		}

	}
	else {
		throw("List is empty!");
	}
	return;
}

template <class Type>
void List<Type>::clear() {
	this->_size = 0;
	List<Type>::iterator it = this->begin();
	while (it.ptr != nullptr){
		ListNode<Type>* toDel = it.ptr;
		it++;
		delete toDel;
	}
	this->tail = this->head;
	this->head->next = nullptr;
}

template <class Type>
List<Type>::~List() {
	this->clear();
	delete this->head;
}

template <class Type>
typename List<Type>::iterator List<Type>::find(const Type& data)const {
	for (auto i = this->begin(); i != this->end(); i++) {
		if (*i == data)return i;
	}
	return this->end();
}

//operator overload
//operator =
template <class Type>
List<Type>& List<Type>::operator=(const List<Type>& v) {
	this->clear();
	for (auto i = v.begin(); i != v.end(); i++)
		this->push_back(*i);

	return *this;
}

#endif // !_MY_LIST_