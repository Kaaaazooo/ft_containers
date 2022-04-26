#include "test.hpp"


template <class Cont>
int	member_type(void)
{
	NAMESPACE::map<int, int>::key_type					a;
	//NAMESPACE::map<int, int>::mapped_type				x;
	NAMESPACE::map<int, int>::value_type				b;
	NAMESPACE::map<int, int>::size_type					c;
	NAMESPACE::map<int, int>::difference_type			d;
	NAMESPACE::map<int, int>::key_compare				e;
	//NAMESPACE::map<int, int>::value_compare			x;
	NAMESPACE::map<int, int>::allocator_type			f;
	//NAMESPACE::map<int, int>::reference				x;
	//NAMESPACE::map<int, int>::const_reference			x;
	NAMESPACE::map<int, int>::pointer					g;
	NAMESPACE::map<int, int>::const_pointer				h;
	NAMESPACE::map<int, int>::iterator					i;
	NAMESPACE::map<int, int>::const_iterator			j;
	NAMESPACE::map<int, int>::reverse_iterator			k;
	NAMESPACE::map<int, int>::const_reverse_iterator	l;

	return 1;
	(void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h;(void)i;(void)j;(void)k;(void)l;
}

template <class Cont>
void	capacity(void)
{
	std::cout << std::endl << std::setw(48) << "empty/size/max_size: " << std::endl;
	Cont	c;

	std::cout << c.size() << std::endl;
	std::cout << c.max_size() << std::endl;

	ms_insert(c, 19);

	std::cout << c.empty() << std::endl;
	std::cout << c.max_size() << std::endl;

	ms_erase(c);
	std::cout << c.size() << std::endl;

	for (int i = 0; i < 8; ++i)
		ms_insert(c, 1);

	std::cout << c.size() << std::endl;
	std::cout << c.empty() << std::endl;
}

template <class Cont>
static void	comp_op(void)
{
	std::cout << std::endl << std::setw(18) << "compare operator:" << std::endl;
	Cont	c;
	Cont	c2;

	all_compare(c, c2);

	ms_insert(c, 12);
	ms_insert(c, 68);
	ms_insert(c2, 86);
	all_compare(c, c2);

	c.swap(c2);
	all_compare(c, c2);

	c2.erase(c2.begin());
	all_compare(c, c2);
}

template <class Cont>
static void	assign_op(void)
{
	std::cout << std::endl << std::setw(18) << "assignation operator:" << std::endl;
	Cont	c;
	Cont	c2;

	ms_insert(c, 99);
	ms_insert(c, 9);

	c2 = c;
	printInfo(c2);

	c.erase(c.begin());
	printInfo(c2);
}

template <class Cont>
int	all_operator(void)
{
	std::cout << std::endl << std::setw(48) << "operator:" << std::endl;
	assign_op<Cont>();
	comp_op<Cont>();
	return 1;
}

template <class Cont>
int	test_clear(void)
{
	std::cout << std::endl << std::setw(48) << "clear:" << std::endl;
	clear<Cont>(ms_insert, ms_erase);
	return 1;
}

template <class Cont>
static void	_find_count(Cont& c, int key)
{
	ms_print_it(c.find(key));
	std::cout << c.count(key) << std::endl;
}

template <class Cont>
void	find_count(int size)
{
	std::cout << std::endl << std::setw(48) << "find_count: (size = " << size << ")" << std::endl;
	if (size < 0)
		size = 8;
	Cont	c;

	for (int i = 0; i < size; ++i)
		ms_insert(c, i);
	_find_count((const Cont)c, size - 1);
	_find_count(c, 1);
	_find_count(c, size / 2);
	_find_count(c, 0);
}

void	ms_lst_push(std::list<int>& lst, int value)
{
	lst.push_back(value);
}

void	ms_lst_push(std::list<NAMESPACE::pair<const int, int> >& lst, int value)
{
	lst.push_back(NAMESPACE::pair<const int, int>(value, value));
}

void	ms_print_it(std::set<int>::const_iterator it)
{
	std::cout << *it << std::endl;
	(void)it;
}

void	ms_print_it(NAMESPACE::map<int, int>::const_iterator it)
{
	std::cout << it->first << " . " << it->second << std::endl;
	(void)it;
}

void	ms_print_it(NAMESPACE::map<int, int>::iterator it)
{
	std::cout << it->first << " . " << it->second << std::endl;
	(void)it;
}

void test_map()
{
	std::cout << std::setw(48) << "map" << std::endl;

	typedef NAMESPACE::map<int, int> Cont;
	member_type<Cont>();
	capacity<Cont>();
	all_operator<Cont>();
	test_clear<Cont>();
	insert<Cont>(-1);
	erase<Cont>(-1);
	find_count<Cont>(-1);
	range_bound<Cont>(-1);

	std::cout << std::endl << std::setw(48) << "compare:" << std::endl;
	insert<NAMESPACE::map<int, int, std::greater<int> > >(-1);
}
