#pragma once
#ifndef _MY_PAIR_
#define _MY_PAIR_

template <class T1, class T2>
struct Pair
{
	T1 first;
	T2 second;

	//constructor
	Pair() {}
	Pair(const T1& f, const T2& s) : first(f), second(s) {}
	Pair(const Pair<T1, T2>& p) : first(p.first), second(p.second) {}
	template<class T3, class T4>
	Pair(const T3& _first, const T4& _second) : first(_first), second(_second) {}

	//operator overload
	Pair& operator=(const Pair& p)
	{
		this->first = p.first;
		this->second = p.second;
		return *this;
	}
	bool operator==(const Pair<T1, T2>& p)
	{
		return first == p.first && second == p.second;
	}
	bool operator!=(const Pair<T1, T2>& p)
	{
		return first != p.first || second != p.second;
	}
};

template<class T1, class T2>
bool operator<(const Pair<T1, T2>& p, const Pair<T1, T2>& q)
{
	return p.first < q.first || (p.first == q.first && p.second < q.second);
}

template<class T1, class T2>
bool operator>(const Pair<T1, T2>& p, const Pair<T1, T2>& q)
{
	return p.first > q.first || (p.first == q.first && p.second > q.second);
}

template<class T1, class T2>
bool operator<=(const Pair<T1, T2>& p, const Pair<T1, T2>& q)
{
	return p.first <= q.first || (p.first == q.first && p.second <= q.second);
}

template<class T1, class T2>
bool operator>=(const Pair<T1, T2>& p, const Pair<T1, T2>& q)
{
	return p.first >= q.first || (p.first == q.first && p.second >= q.second);
}

template<class T1, class T2>
Pair<T1, T2> operator+(const Pair<T1, T2>& p, const Pair<T1, T2>& q)
{
	return Pair<T1, T2>(p.first + q.first, p.second + q.second);
}

template<class T1, class T2>
Pair<T1, T2> operator-(const Pair<T1, T2>& p, const Pair<T1, T2>& q)
{
	return Pair<T1, T2>(p.first - q.first, p.second - q.second);
}

#endif // !_MY_PAIR_