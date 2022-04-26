#include "test.hpp"

static int	member_type(void)
{
	NAMESPACE::stack<int>::container_type	a;
	NAMESPACE::stack<int>::value_type		b;
	NAMESPACE::stack<int>::size_type		c;

	return 1;
	(void)a;(void)b;(void)c;
}

typedef	foo<std::string>	t_foo;
typedef	std::deque<t_foo>	t_deq;

static void	cont_constructor(void)
{
	NAMESPACE::stack<t_foo, t_deq>		s((t_deq()));

	s.push(t_foo());
	s.push(t_foo());
	s.pop();
	s.push(t_foo());
	printInfo(s);
}

static void	copy_constructor(void)
{
	NAMESPACE::stack<int>		s;

	for (int i = 0; i < 8; ++i)
		s.push((i * 12) >> 1);

	NAMESPACE::stack<int>		s_cpy(s);
	printInfo(s_cpy);
}

static int	constructor(void)
{
	std::cout << std::endl << std::setw(48) << "constructor:" << std::endl;
	cont_constructor();
	copy_constructor();
	return 1;
}

static int	empty(void)
{
	std::cout << std::endl << std::setw(48) << "empty:" << std::endl;
	NAMESPACE::stack<int>	s;

	std::cout << s.empty() << std::endl;	
	s.push(101);
	std::cout << s.empty() << std::endl;	
	s.pop();
	std::cout << s.empty() << std::endl;	
	return 1;
}

static void	comp_op(void)
{
	std::cout << std::endl << std::setw(18) << "compare operator:" << std::endl;
	NAMESPACE::stack<int>	s;
	NAMESPACE::stack<int>	s2;

	s.push(68);
	s2.push(86);

	all_compare(s, s2);

	s2.pop();

	all_compare(s, s2);
}

static void	assign_op(void)
{
	std::cout << std::endl << std::setw(18) << "assignation operator:" << std::endl;
	NAMESPACE::stack<int>	s;
	NAMESPACE::stack<int>	s2;

	s.push(99);
	s.push(99);
	s.pop();

	s2 = s;
	s.pop();
	printInfo(s2);
}

static int	all_operator(void)
{
	std::cout << std::endl << std::setw(48) << "operator:" << std::endl;
	assign_op();
	comp_op();
	return 1;
}

void test_stack()
{
	std::cout << std::endl << std::setw(24) << "STACK" << std::endl;
	member_type();
	constructor();
	empty();
	comp_op();
	assign_op();
	all_operator();
}
