#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <iomanip>
#include <list>
#include <stack>
#include <set>
#include <vector>
#include <map>

#include "utils.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"

#ifndef NAMESPACE
#define NAMESPACE std
#endif



template <class T>
void	ms_insert(std::set<int, T>& c, typename std::set<int, T>::iterator it, int val)
{ c.insert(it, val); }

template <class T>
void	ms_insert(NAMESPACE::map<int, int, T>& c, typename NAMESPACE::map<int, int, T>::iterator it, int val)
{ c.insert(it, NAMESPACE::pair<int, int>(val, val)); }

template <class T>
void	ms_insert(std::set<int, T>& c, int val)
{ c.insert(val); }

template <class T>
void	ms_insert(NAMESPACE::map<int, int, T>& c, int val)
{ c.insert(NAMESPACE::pair<int, int>(val, val)); }

void	ms_lst_push(std::list<int>& lst, int value);
void	ms_lst_push(std::list<NAMESPACE::pair<const int, int> >& lst, int value);

void	ms_print_it(std::set<int>::const_iterator it);
void	ms_print_it(NAMESPACE::map<int, int>::const_iterator it);
void	ms_print_it(NAMESPACE::map<int, int>::iterator it);

template <class Cont>
void	ms_erase(Cont& c)
{ c.erase(c.begin()); }


template <typename T>
class	foo
{
	private:
		T	value;
	public:
		foo(const T& value = T()) : value(value) {}
		~foo(void) {}
		T getValue(void) const { return this->value; }
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, const foo<T>& bar) { return o << bar.getValue(); }

template <typename T>
bool	operator<(const foo<T> &lhs, const foo<T> &rhs) { return lhs.getValue() < rhs.getValue(); }

	template <class T>
static void	all_compare(T lhs, T rhs)	
{
	std::cout << (lhs == rhs) << std::endl;
	std::cout << (lhs != rhs) << std::endl;
	std::cout << (lhs < rhs) << std::endl;
	std::cout << (lhs <= rhs) << std::endl;
	std::cout << (lhs > rhs) << std::endl;
	std::cout << (lhs >= rhs) << std::endl;
}

	template <class T, class U>
void printInfo(NAMESPACE::stack<T, U>& s)
{
	std::cout << "size: " << s.size() << std::endl;
	while (s.size())
	{
		std::cout << s.top() << std::endl;
		s.pop();
	}
}

	template <class Cont>
void printInfo(const Cont& c)
{
	std::cout << "size: " << c.size() << std::endl;
	std::cout << "capacity: " << c.capacity() << std::endl;
	std::cout << "max_size: " << c.max_size() << std::endl;
	for (typename Cont::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << *it << std::endl;
}

	template <class T, class U>
void printInfo(const NAMESPACE::map<T, T, U>& c)
{
	std::cout << "size: " << c.size() << std::endl;
	std::cout << "max_size: " << c.max_size() << std::endl;
	for (typename NAMESPACE::map<T, T>::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << it->first << " . " << it->second << std::endl;
}

template <class Cont>
int	access_test(Cont c, void (*f)(Cont, int), typename Cont::size_type more)
{
	for (typename Cont::size_type i = 0; i < c.size() + more; ++i)
	{
		try
		{ f(c, i); }
		catch (const std::exception& e)
		{ std::cout << e.what() << std::endl; }
	}
	return 1;
}

template <class Cont>
static void	it_insert(int size)
{
	std::cout << std::endl << std::setw(18) << "it_insert:" << std::endl;
	std::list<typename Cont::value_type>	lst;

	for (int i = 0; i < size; ++i)
		ms_lst_push(lst, i);

	Cont	c;

	c.insert(lst.begin(), lst.begin());
	printInfo(c);

	c.insert(lst.begin(), ++lst.begin());
	printInfo(c);

	c.insert(lst.begin(), lst.end());
	printInfo(c);
}

template <class Cont>
static void	hint_insert(int size)
{
	std::cout << std::endl << std::setw(18) << "hint_insert:" << std::endl;
	Cont	c;

	ms_insert(c, c.begin(), 0);
	printInfo(c);

	for (int i = 0; i < size; ++i)
		ms_insert(c, ++c.begin(), i);
	printInfo(c);

	ms_insert(c, --c.end(), 5);
	printInfo(c);
}

template <class Cont>
static void	value_insert(int size)
{
	std::cout << std::endl << std::setw(18) << "value_insert:" << std::endl;
	Cont	c;

	ms_insert(c, 0);
	printInfo(c);

	for (int i = 0; i < size; i += 2)
		ms_insert(c, i);
	printInfo(c);

	for (int i = 1; i < size; i += 2)
		ms_insert(c, i);
	printInfo(c);
}

template <class Cont>
static void	it_erase(int size)
{
	std::cout << std::endl << std::setw(18) << "it_erase:" << std::endl;
	Cont	c;

	for (int i = 0; i < size; ++i)
		ms_insert(c, i);
	printInfo(c);

	c.erase(c.begin(), ++(++c.begin()));
	printInfo(c);

	c.erase(++c.begin(), ++c.begin());
	printInfo(c);

	c.erase(--c.end(), c.end());
	printInfo(c);

	c.erase(c.begin(), c.end());
	printInfo(c);
}

template <class Cont>
static void	one_it_erase(int size)
{
	std::cout << std::endl << std::setw(18) << "one_it_erase:" << std::endl;
	Cont	c;

	for (int i = 0; i < size; ++i)
		ms_insert(c, i);
	printInfo(c);

	c.erase(c.begin());
	printInfo(c);

	c.erase(++c.begin());
	printInfo(c);

	c.erase(--c.end());
	printInfo(c);

	for (unsigned long i = 0; i < c.size(); ++i)
		c.erase(c.begin());
	printInfo(c);
}

template <class Cont>
void	clear(void (*insert)(Cont&, int), void (*erase)(Cont&))
{
	Cont	c;

	c.clear();
	for (int i = 0; i < 2; ++i)
		insert(c, i);
	printInfo(c);

	erase(c);
	c.clear();
	printInfo(c);

	for (int i = 0; i < 8; ++i)
		insert(c, i);
	printInfo(c);

	c.clear();
	printInfo(c);
}


template <class Cont>
static void	value_erase(int size)
{
	std::cout << std::endl << std::setw(18) << "value_erase:" << std::endl;
	Cont	c;

	for (int i = 0; i < size; ++i)
		ms_insert(c, i);
	printInfo(c);

	c.erase(size - 1);
	printInfo(c);

	c.erase(size / 2);
	printInfo(c);

	c.erase(1);
	printInfo(c);

	for (unsigned long i = 0; i < c.size(); ++i)
		c.erase(i);
	printInfo(c);
}

template <class Cont>
int	erase(int size)
{
	if (size < 0)
		size = 12;
	std::cout << std::endl << std::setw(48) << "erase: (size = " << size << ")" << std::endl;
	one_it_erase<Cont>(size);
	it_erase<Cont>(size);
	value_erase<Cont>(size);
	return 1;
}

template <class Cont>
int	insert(int size)
{
	if (size < 0)
		size = 12;
	std::cout << std::endl << std::setw(48) << "erase: (size = " << size << ")" << std::endl;
	it_insert<Cont>(size);
	hint_insert<Cont>(size);
	value_insert<Cont>(size);
	return 1;
}

template <class T>
static void	equal_print(NAMESPACE::pair<T, T> p)
{
	ms_print_it(p.first);
	ms_print_it(p.second);
}

template <class Cont>
static void	_range_bound(Cont c, int key)
{
	ms_print_it(c.lower_bound(key));
	ms_print_it(c.upper_bound(key));
	equal_print(c.equal_range(key));
}

template <class Cont>
void	range_bound(int size)
{
	std::cout << std::endl << std::setw(48) << "range_bound: (size = " << size << ")" << std::endl;
	if (size < 0)
		size = 8;
	Cont	c;

	for (int i = 0; i < size; ++i)
		ms_insert(c, i);
	_range_bound((const Cont)c, size / 2);
	ms_print_it(c.lower_bound(size - 2));
	ms_print_it(c.upper_bound(1));
}

void test_stack(void);
void test_vector(void);
void test_map(void);

#endif
