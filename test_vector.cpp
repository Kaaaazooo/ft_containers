#include "test.hpp"

int	member_type(void)
{
	NAMESPACE::vector<int>::value_type				a;
	NAMESPACE::vector<int>::allocator_type			b;
	NAMESPACE::vector<int>::size_type				c;
	NAMESPACE::vector<int>::difference_type			d;
//	NAMESPACE::vector<int>::reference				e;
//	NAMESPACE::vector<int>::const_reference			f;
	NAMESPACE::vector<int>::pointer					g;
	NAMESPACE::vector<int>::const_pointer			h;
	NAMESPACE::vector<int>::iterator				i;
	NAMESPACE::vector<int>::const_iterator			j;
	NAMESPACE::vector<int>::reverse_iterator		k;
	NAMESPACE::vector<int>::const_reverse_iterator	l;

	return 1;
	(void)a;(void)b;(void)c;(void)d;(void)g;(void)h;(void)i;(void)j;(void)k;(void)l;
}

typedef foo<int>								t_foo;
typedef NAMESPACE::vector<t_foo>::const_iterator	t_cfit;
typedef NAMESPACE::vector<int>::iterator		t_it;
typedef NAMESPACE::vector<int>::const_iterator	t_const_it;

static void	iterator_arrow(void)
{
	NAMESPACE::vector<t_foo>	v;
	v.push_back(t_foo(1));

	t_cfit	cfit = --v.end();

	std::cout << cfit->getValue() << std::endl;
}

static int	iterator(void)
{
	std::cout << std::endl << std::setw(48) << "iterator:" << std::endl;
	NAMESPACE::vector<int>	v;
	t_it	it = v.begin();

	for (int i = 0; i < 8; ++i)
		v.push_back(i);

	std::cout << *(v.begin() + 4) << std::endl;
	std::cout << v.end() - v.begin() << std::endl;
	std::cout << *(v.end() - 1) << std::endl;

	t_it	ite = v.end();

	for (it = v.begin(); it != ite - 4; ++it) 
		*it = 42;
	printInfo(v);

	for (it = v.end() - 1; it != v.begin(); --it) 
		*it = -2;
	printInfo(v);

	iterator_arrow();
	all_compare(v.begin(), --v.end());
	return 1;
}

typedef foo<int>										t_foo;
typedef NAMESPACE::vector<t_foo>::const_reverse_iterator		t_cfrit;
typedef NAMESPACE::vector<int>::reverse_iterator		t_rit;
typedef NAMESPACE::vector<int>::const_reverse_iterator	t_const_rit;

static void	r_iterator_arrow(void)
{
	NAMESPACE::vector<t_foo>	v;
	v.push_back(t_foo(1));

	t_cfrit	cfrit = --v.rend();

	std::cout << cfrit->getValue() << std::endl;
}

static int	r_iterator(void)
{
	std::cout << std::endl << std::setw(48) << "reverse_iterator:" << std::endl;
	NAMESPACE::vector<int>	v;
	t_rit	rit = v.rbegin();

	for (int i = 0; i < 8; ++i)
		v.push_back(i);

	std::cout << *(v.begin() + 4) << std::endl;
	std::cout << v.begin() - v.end() << std::endl;

	t_rit	rite = v.rend();

	for (rit = v.rbegin(); rit != rite - 4; ++rit) 
		*rit = 42;
	printInfo(v);

	for (rit = v.rend() - 1; rit != v.rbegin(); --rit) 
		*rit = -2;
	printInfo(v);

	r_iterator_arrow();
	all_compare(v.rbegin(), --v.rend());
	return 1;
}

static void	inputItConstructor(void)
{
	std::list<int>	lst;

	for (int i = 0; i < 12; ++i)
		lst.push_back(i);

	NAMESPACE::vector<int>	inputItC(lst.begin(), lst.end());
	printInfo(inputItC);
}

static void	copyConstructor(void)
{
	NAMESPACE::vector<int>	c;

	for (int i = 0; i < 12; ++i)
		c.push_back(i);

	printInfo(c);
	NAMESPACE::vector<int>	copyC(c);
	std::cout << "LA DIFF EST ICI" << std::endl;
	printInfo(copyC);
}

static int	constructor(void)
{
	std::cout << std::endl << std::setw(48) << "constructor: " << std::endl;
	NAMESPACE::vector<int>	defaultC = NAMESPACE::vector<int>();
	printInfo(defaultC);

	NAMESPACE::vector<int>	allocC((std::allocator<int>()));
	printInfo(allocC);

	NAMESPACE::vector<int>	sizeC(12, 19);
	printInfo(sizeC);

	inputItConstructor();
	copyConstructor();
	return 1;
}

static int	capacity(void)
{
	std::cout << std::endl << std::setw(48) << "capacity/max_size/empty/reserve: " << std::endl;
	NAMESPACE::vector<int>	v;

	std::cout << v.max_size() << std::endl;

	v.reserve(2);

	std::cout << v.capacity() << std::endl;
	std::cout << v.empty() << std::endl;
	std::cout << v.max_size() << std::endl;

	for (int i = 0; i < 10; ++i)
		v.push_back(int());

	std::cout << v.capacity() << std::endl;
	std::cout << v.empty() << std::endl;

	try
	{
		//v.reserve(4611686018427387903);
		//v.reserve(-1);
		std::cout << v.capacity() << std::endl;
	}
	catch (const std::exception& e)
	{ std::cout << e.what() << std::endl; }

	v.reserve(0);
	std::cout << v.capacity() << std::endl;
	std::cout << v.empty() << std::endl;
	return 1;
}

static void	at(NAMESPACE::vector<int> v, int index)
{ std::cout << v.at(index) << std::endl; }

static void	op_at_assign(NAMESPACE::vector<int> v, int index)
{ v[index] = 12; }

static void	op_at(NAMESPACE::vector<int> v, int index)
{ std::cout << v[index] << std::endl; }

static int access(void)
{
	std::cout << std::endl << std::setw(48) << "access:" << std::endl;
	NAMESPACE::vector<int>	v;

	for (int i = 0; i < 3; ++i)
		v.push_back(i);

	access_test(v, at, 1);
	access_test(v, op_at_assign, 0);
	access_test(v, op_at, 0);
	std::cout << v.front() << std::endl;
	std::cout << v.back() << std::endl;

	v.pop_back();
	v.erase(v.begin());
	std::cout << v.front() << std::endl;
	std::cout << v.back() << std::endl;

	return 1;
}

static void	comp_op(void)
{
	std::cout << std::endl << std::setw(18) << "compare operator:" << std::endl;
	NAMESPACE::vector<int>	v;
	NAMESPACE::vector<int>	v2;

	v.push_back(68);
	v2.push_back(86);
	all_compare(v, v2);

	v.swap(v2);
	all_compare(v, v2);

	v2.pop_back();
	all_compare(v, v2);

	std::cout << NAMESPACE::lexicographical_compare(v.begin(), v.end(), v2.begin(), v2.end()) << std::endl;
	std::cout << NAMESPACE::lexicographical_compare(v.begin(), v.end(), v2.begin(), v2.end(), std::greater<int>()) << std::endl;
	std::cout << NAMESPACE::equal(v2.begin(), v2.end(), v.begin()) << std::endl;
	std::cout << NAMESPACE::equal(v2.begin(), v2.end(), v.begin(), std::equal_to<int>()) << std::endl;
}

static void	assign_op(void)
{
	std::cout << std::endl << std::setw(18) << "assignation operator:" << std::endl;
	NAMESPACE::vector<int>	v;
	NAMESPACE::vector<int>	v2;

	v.push_back(99);
	v.push_back(99);
	v.push_back(99);
	v.push_back(99);
	v.push_back(99);

	v2 = v;
	v.pop_back();
	printInfo(v2);
}

static int	all_operator(void)
{
	std::cout << std::endl << std::setw(48) << "operator:" << std::endl;
	assign_op();
	std::cout << "aa" << std::endl;
	comp_op();
	std::cout << "aa" << std::endl;
	return 1;
}

static void	erase_one(int size)
{
	std::cout << std::endl << std::setw(18) << "erase_one:" << std::endl;
	NAMESPACE::vector<int>	c;

	for (int i = 0; i < size; ++i)
		c.push_back(i);
	printInfo(c);

	for (t_it it = c.begin(); it != c.end(); ++it)
		c.erase(it);
	printInfo(c);
}

static void	erase_it(int size)
{

	std::cout << std::endl << std::setw(18) << "erase_it:" << std::endl;
	NAMESPACE::vector<int>	c;

	for (int i = 0; i < size; ++i)
		c.push_back(i);
	printInfo(c);

	if (size > 3)
	{
		c.erase(++c.begin(), --(c.end()));
		printInfo(c);
	}

	if (size > 1)
	{
		c.erase(++(++c.begin()), c.end());
		printInfo(c);
	}

	if (size > 0)
	{
		c.erase(++c.begin(), c.end());
		printInfo(c);
	}
	c.erase((c.begin()), c.end());
	printInfo(c);

}

static int	erase(int size)
{
	if (size < 0)
		size = 12;
	std::cout << std::endl << std::setw(48) << "erase: (size = " << size << ")" << std::endl;
	erase_one(size);
	erase_it(size);
	return 1;
}

static int	inputItAssign(void)
{
	std::list<std::string>	strLst;
	NAMESPACE::vector<std::string>	strV;

	for (int i = 0; i < 5; ++i)
		strLst.push_back("a");

	strV.assign(strLst.begin(), strLst.end());
	printInfo(strV);
	return 1;
}

static int	inputItAssign2(int size)
{
	std::list<int>	lst;

	for (int i = 0; i < size; ++i)
		lst.push_back(i);

	NAMESPACE::vector<int>	inputItC;

	inputItC.assign(lst.begin(), lst.end());
	printInfo(inputItC);
	return 1;
}

static int	assign(int size)
{
	if (size < 0)
		size = 19;
	std::cout << std::endl << std::setw(48) << "assign: (size = " << size << ")" << std::endl;
	NAMESPACE::vector<int>	c;

	c.assign(size, 42);
	printInfo(c);
	std::cout << "OK" << std::endl;

	inputItAssign();
	inputItAssign2(size);
	return 1;
}

static void	one_insert(int size)
{
	NAMESPACE::vector<foo<int> >	v;	

	std::cout << std::endl << std::setw(18) << "one_insert:" << std::endl;
	for (int i = 0; i < size; ++i)
		v.insert(v.begin(), foo<int>(12));
	printInfo(v);
}

static void	count_insert(int size)
{
	NAMESPACE::vector<int>	v;	

	std::cout << std::endl << std::setw(18) << "count_insert:" << std::endl;
	v.insert(v.end(), 1, 9);
	printInfo(v);
	v.insert(--v.end(), size, 12);
	printInfo(v);
}

static void	it_insert(int size)
{
	std::list<int>			lst;
	NAMESPACE::vector<int>	v;	

	std::cout << std::endl << std::setw(18) << "it_insert:" << std::endl;
	for (int i = 0; i < size; ++i)
		lst.push_back(i);
	v.insert(v.begin(), lst.begin(), lst.end());
	printInfo(v);
}

static int	insert(int size)
{
	if (size < 0)
		size = 12;	
	std::cout << std::endl << std::setw(48) << "insert: (size = " << size << ")" << std::endl;
	one_insert(size);
	it_insert(size);
	count_insert(size);
	return 1;
}

static void	one_insert2(int size)
{
	NAMESPACE::vector<foo<int> >	v;	

	std::cout << std::endl << std::setw(18) << "one_insert:" << std::endl;
	for (int i = 0; i < size; ++i)
		v.insert(v.begin(), foo<int>());
	printInfo(v);
}

static void	count_insert2(int size)
{
	NAMESPACE::vector<foo<int> >	v;	

	std::cout << std::endl << std::setw(18) << "count_insert:" << std::endl;
	v.insert(v.end(), 1, foo<int>());
	printInfo(v);
	v.insert(--v.end(), size, foo<int>());
	printInfo(v);
}

static void	it_insert2(int size)
{
	std::list<foo<int> >			lst;
	NAMESPACE::vector<foo<int> >	v;	

	std::cout << std::endl << std::setw(18) << "it_insert:" << std::endl;
	for (int i = 0; i < size; ++i)
		lst.push_back(foo<int>());
	v.insert(v.begin(), lst.begin(), lst.end());
	printInfo(v);
}

static int	insert2(int size)
{
	if (size < 0)
		size = 12;	
	std::cout << std::endl << std::setw(48) << "insert2: (size = " << size << " )" << std::endl;
	one_insert2(size);
	count_insert2(size);
	it_insert2(size);
	return 1;
}

static int	resize(int size)
{
	if (size < 0)
		size = 9;
	std::cout << std::endl << std::setw(48) << "resize: (size = " << size << ")" << std::endl;
	NAMESPACE::vector<int>	v;	
	v.resize(size, 19);
	printInfo(v);

	v.resize(size + 2);
	printInfo(v);

	v.resize(0);
	printInfo(v);

	v.resize(3);
	printInfo(v);
	return 1;
}

void test_vector()
{
	std::cout << std::setw(24) << "VECTOR" << std::endl;
	member_type();
	iterator();
	r_iterator();
	constructor();
	capacity();
	access();
	all_operator();
	erase(-1);
	assign(-1);
	insert(-1);
	insert2(-1);
	resize(-1);
}
