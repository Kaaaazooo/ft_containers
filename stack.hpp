#ifndef STACK_HPP
# define STACK_HPP
# include <memory>
# include <deque>

namespace ft {

	template <class T, class Container = std::deque<T> >
		class stack{
			public:
				typedef Container container_type;
				typedef typename Container::value_type value_type;
				typedef typename Container::size_type size_type;
				typedef typename Container::reference reference;
				typedef typename Container::const_reference const_reference;

			protected:
				Container c;

			public:
				explicit stack(const Container& cont = Container()) : c(cont) {}
				~stack(void) {}
//
//				stack& operator=( const stack& other ) {
//					c = other.c;
//					return *this;
//				}
//
				bool empty() const					{ return c.empty(); }

				size_type size()  const				{ return c.size(); }

				const_reference   top() const		{ return c.back(); }

				void push(const value_type& value)	{ c.push_back(value); }

				void pop()							{ c.pop_back(); }

				template <class Tf, class ContainerF>
					friend bool operator>= (const stack<Tf,ContainerF>& lhs, const stack<Tf,ContainerF>& rhs);
				template <class Tf, class ContainerF>
					friend bool operator>  (const stack<Tf,ContainerF>& lhs, const stack<Tf,ContainerF>& rhs);
				template <class Tf, class ContainerF>
					friend bool operator<= (const stack<Tf,ContainerF>& lhs, const stack<Tf,ContainerF>& rhs);
				template <class Tf, class ContainerF>
					friend bool operator<  (const stack<Tf,ContainerF>& lhs, const stack<Tf,ContainerF>& rhs);
				template <class Tf, class ContainerF>
					friend bool operator!= (const stack<Tf,ContainerF>& lhs, const stack<Tf,ContainerF>& rhs);
				template <class Tf, class ContainerF>
					friend bool operator== (const stack<Tf,ContainerF>& lhs, const stack<Tf,ContainerF>& rhs);

		};

	template <class T, class Container>
		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c == rhs.c;
		}

	template <class T, class Container>
		bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c != rhs.c;
		}

	template <class T, class Container>
		bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c < rhs.c;
		}

	template <class T, class Container>
		bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c <= rhs.c;
		}

	template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c > rhs.c;
		}

	template <class T, class Container>
		bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs.c >= rhs.c;
		}
}

#endif
