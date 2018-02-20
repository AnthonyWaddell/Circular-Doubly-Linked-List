//-----------------------------------------------------------------------------
//   File: list.cpp
//
//   Class: list
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Title:		list Class
// Description: This file contains the class definition for list, with a test driver
//
// Programmer:	Object Oriented Programming Using C++, Edition 2 By Ira Pohl
//				modified by Paul Bladek
//				modified by Anthony Waddell
// 
// Date:		original: Summer 1996
//				current: 05-17-18				
// Version:		1.10
// Environment: Hardware: PC, i7
//              Software: OS: Windows 10 
//              Compiles under Microsoft Visual C++ 2015
//
// class list:
//
//     Properties:
//       listelem *head -- front end of list
//       listelem *tail -- back end of list
//       unsigned m_size -- number of elements in the list
//
//     Methods:
// 
//       inline: 
//         list();
//				construct the empty list
//         list(size_t n_elements, T datum);
//				create a list of a specific size, all elements the same
//         ~list() { release(); };
//				destructor
//         unsigned getSize()const;
//				accessor for m_size
//         iterator begin()const;;
//				returns address of first element
//         iterator end()const;
//				returns address of last element
//         T& front()const;
//				returns first element data
//         T& back()const;
//				returns last element data
//         bool empty()const;
//				true if no elements in list, false if not
//
//       non-inline:
//         list(const list& x);
//				copy constructor
//         list(iterator b, iterator e);
//				constructor using iterators
//         void push_front(T datum);
//				insert element at front of list
//         T pop_front();
//				removes front element and returns the data from that element
//         void push_back(T datum);
//				insert element at back of list 
//         T pop_back();
//				removes back element and returns the data from that element
//         void release();
//				removes all items from list
//         list operator=(const list & rlist)
//				returns a copy of rlist
//         T& operator[](int index);
//				for l-value
//         const T& operator[](int index)const;
//				for r-value
//
//    Public Nested Structures:
//
//      struct listelem -- list cell
//
//        properties:
//          T data -- the actual datum
//          listelem *next -- forward link
//          listelem *prev -- backward link
//        constructor:
//          listelem(T c, listelem* p, listelem* n, listelem* p) -- struct constructor
//
//     class iterator
//        Public Methods
// 
//           inline: 
//            listelem* operator->() -- same as for pointer
//            T& operator*() -- same as for pointer
//            operator listelem*() -- conversion
//            iterator(listelem* p = nullptr) -- constructor
// 
//           non-inline: 
//            iterator operator++() -- pre-increment
//            iterator operator--() -- pre-decrement
//            iterator operator++(int) -- post-increment
//            iterator operator--(int) -- post-decrement
// 
//        Private Properties
//            listelem* ptr -- current listelem or NULL
//
// History Log:
//				summer, 1996 original  IP completed version 1.0 
//				May 11, 2000,  PB  completed version 1.01 
//				March 8, 2002, PB  completed version 1.02 
//				April 10, 2003, PB  completed version 1.03 
//				April 30, 2003, PB  completed version 1.04 
//				May 10, 2005, PB  completed version 1.05 
//				April 15, 2008, PB  completed version 1.06
//				April 20, 2010, PB completed version 1.07 
//				April 15, 2011, PB completed version 1.09 
//				AW completed version 1.10 05-22-17
//-----------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>

using namespace std;
namespace AW_LIST
{

	template <class T>
	class list

	{
	public:

		// forward declarations
		struct listelem;
		class iterator;

		// constructors
		list() : head(nullptr), tail(nullptr), m_size(0) {}
		list(size_t n_elements, T datum);
		list(const list& x);
		list(iterator b, iterator e);

		//destructor
		~list() { release(); }

		//accessors for listelem
		virtual unsigned getSize() const { return m_size; }
		virtual iterator begin() const { return head; }
		virtual iterator end() const { return tail; }

		void push_front(T datum);
		T pop_front();
		void push_back(T datum);
		T pop_back();
		T& front() const { return head->data; }
		T& back() const { return tail->data; }
		virtual bool empty()const { return head == nullptr || tail == nullptr; }
		void release();
		list operator=(const list & rlist);
		T& operator[](int index);
		const T& operator[](int index) const;

	protected:
		listelem *head;
		listelem *tail;
		unsigned m_size;

	public:
		struct listelem
		{
			T data;
			listelem *next;
			listelem *prev;
			listelem(T datum, listelem* p, listelem* n) :
				data(datum), prev(p), next(n) {} 
		};

		// scoped within class list !
		class iterator
		{
		public:
			iterator(listelem* p = nullptr) : ptr(p) {}
			iterator operator++();
			iterator operator--();
			iterator operator++(int);
			iterator operator--(int);
			listelem* operator->() const { return ptr; }
			T& operator*() const { return ptr->data; }
			operator listelem*() const { return ptr; }
		private:
			listelem* ptr; //current listelem or nullptr
		};
	};

	ostream& operator<<(ostream& sout, const list<class T>& x);

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template<class T> list<T>::list(size_t n_elements, T datum)
	//				:m_size(0), head(nullptr), tail(nullptr)
	// Title:		Constructor
	// Description: Constructs a list object of size: n_elements with elements 
	//				of type: datum
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		listelem(datum, tail, head); constructor
	//				push_front(datum)
	// Called By:	main()
	// Parameters:	size_t n_elements; the number of elemetns in the list
	//				T datum; the type of element
	// Returns:		list<T>; the list of elements
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T> list<T>::list(size_t n_elements, T datum)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		if (n_elements <= 0)
			throw out_of_range("Empty list");
		for (size_t i = 0; i < n_elements; ++i)
			push_front(datum);
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template<class T> list<T>::list(const list<T>& x)
	//				: m_size(0), head(nullptr), tail(nullptr)
	// Title:		Copy constructor
	// Description: Constructs a list<T> object using a reference to another
	//				list object.
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		push_back(datum)
	//				begin()
	//				empty()
	// Called By:	main()
	// Parameters:	const list<T>& x; the list to copy
	// Returns:		list<T>; the list of copied elements
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	list<T>::list(const list<T>& x) : m_size(0), head(nullptr), tail(nullptr)
	{
		if (!x.empty())
		{
			list::iterator r_it = x.begin();
			while (r_it != x.end())
				push_back(*r_it++);
			list::iterator end = x.end();
			push_back(*end);
		}
		else
		{
			head = NULL;
			tail = NULL;
			m_size = 0;
		}
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template <class T> list<T>::list(iterator b, iterator e)
	//				: m_size(0), head(nullptr), tail(nullptr)
	// Title:		Copy constructor
	// Description: Constructs a list<T> object that is a copy of another
	//				list, using iterators
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		push_front(datum)  
	// Called By:	main()
	// Parameters:	iterator b; the point to copy from
	//				iterator e; the point to copt to one before
	// Returns:		list<T>; the list of copied elements from b to e
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template <class T> list<T>::list(iterator b, iterator e)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		while (b != e)
			push_front(*b--);
		push_front(*b);
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template <class T> void list<T>::release()
	// Title:		Clears list
	// Description: Clears list of elements
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		pop_front() 
	// Called By:	main()
	// Parameters:	N/A
	// Returns:		void
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template <class T>
	void list<T>::release()
	{
			while (getSize())
				pop_front();
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template <class T> ostream& operator<<
	//				(ostream& sout, const list<T>& x)
	// Title:		Overloaded output operator for CircularDoubleLinkedList 
	//				class
	// Description: Outputs elements of a list to console
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		elements of a Circular Doubly Linked List to the
	//				designated output stream
	// Calls:		begin()
	//				end()
	//				getSize()
	// Called By:	main()
	// Parameters:	ostream& sout; the designated output stream
	//				const list<T>& x; the list to output
	// Returns:		a reference to sout
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template <class T>
	ostream& operator<<(ostream& sout, const list<T>& x)
	{
		list<T>::iterator p = x.begin(); 
		sout << "(";
		int size = x.getSize();
		if (size > 1)
		{
			while (p != x.end())
			{
				sout << *p;
				if (p != x.end())
					sout << ", ";
				++p;
			}
			sout << *x.end();
		}
		else if (p != nullptr)
		{
			sout << *p;
		}
		sout << ")\n";
		return sout;
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template<class T> void list<T>::push_front(T datum)
	// Title:		Inserts element at front of list<T>
	// Description: Insertst an element into the head position of a list<T>
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		T datum; the data to be inserted into the list
	// Output:		N/A
	// Calls:		empty()
	// Called By:	main()
	//				operator=(const list<T> & rlist); = operator
	//				list(size_t n_elements, T datum); constructor
	//				list(const list<T>& x); constructor
	//				list(iterator b, iterator e); constructor
	// Parameters:	T datum; the piece of data to be inserted into the list
	// Returns:		void
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	void list<T>::push_front(T datum)
	{
		listelem* temp = new listelem(datum, tail, head);
		m_size++;
		if (!empty())// was a nonempty list
		{
			//link the beginning of the list
			head->prev = temp;
			//insert the new element at front
			head = temp;
			//link the end of the list to the beginning
			head->prev = tail;
			tail->next = head;
		}
		else
		{
			// if it was an empty list
			head = tail = temp;
			head->next = tail;
			head->prev = tail;
			tail->next = head;
			tail->prev = head;
		}
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template<class T> void list<T>::push_back(T datum)
	// Title:		Inserts element at back of list<T>
	// Description: Inserts an element into the tail position of a list<T>
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		T datum; the data to be inserted into the list
	// Output:		N/A
	// Calls:		listelem(datum, tail, head); constructor
	//				empty()
	// Called By:	main()
	// Parameters:	T datum; the piece of data to be inserted into the list
	// Returns:		void
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	void list<T>::push_back(T datum)
	{
		listelem* temp = new listelem(datum, tail, head);
		m_size++;
		if (!empty())
		{
			//link the end the list
			tail->next = temp;
			temp->prev = tail;
			//insert the new element at end
			tail = temp;
			//link the end of the list to the beginning
			head->prev = tail;
			tail->next = head;
		}
		else
		{
			//if list is empty
			head = tail = temp;
			head->next = tail;
			head->prev = tail;
			tail->next = head;
			tail->prev = head;
		}
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template <class T> list<T> list<T>::operator=
	//				(const list<T> & rlist)
	// Title:		Overloaded = operator
	// Description: Returns a copy of a list<T>
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		begin()
	//				release()
	//				push_front()
	// Called By:	main()
	// Parameters:	const list<T> & rlist; the list to be copied
	// Returns:		*this; a list<T> object that is a copy of rlist
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template <class T>
	list<T> list<T>::operator=(const list<T> & rlist)
	{
		if (&rlist != this)
		{
			list::iterator r_it = rlist.begin();
			release();
			while (r_it != 0)
				push_front(*r_it++);
		}
		return *this;
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template<class T> typename inline list<T>::iterator 
	//				list<T>::iterator::operator++()
	// Title:		Overloaded pre-increment operator
	// Description: Increments an iterator in a list and returns next position
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		N/A
	// Called By:	main()
	//				ostream& operator<<
	// Parameters:	N/A
	// Returns:		*this; pointer to next element in list<T>
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	typename inline list<T>::iterator list<T>::iterator::operator++()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->next;
		return *this;
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template<class T> typename list<T>::iterator 
	//				list<T>::iterator::operator++(int)
	// Title:		Overloaded post-increment operator
	// Description: Returns current position in list<T> and increments iterator
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		N/A
	// Called By:	main()
	//				operator=
	//				pop_front()
	// Parameters:	int; amount to be incremented
	// Returns:		temp; current position in list<T> before incrementing
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	typename list<T>::iterator list<T>::iterator::operator++(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->next;
		return temp;
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template<class T> typename list<T>::iterator 
	//				list<T>::iterator::operator--()
	// Title:		Overloaded pre-decrement operator
	// Description: decrements iterator and returns previous element in list<T>
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		N/A
	// Called By:	main()
	// Parameters:	N/A
	// Returns:		*this; previous position in list<T>
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	typename list<T>::iterator list<T>::iterator::operator--()
	{
		if (ptr == nullptr)
			throw runtime_error("empty list");
		ptr = ptr->prev;
		return *this;
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template<class T> typename list<T>::iterator 
	//				list<T>::iterator::operator--(int)
	// Title:		Overloaded post-decrement operator
	// Description: Returns current position in list<T> and decrements iterator 
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		N/A
	// Called By:	main()
	//				pop_back()
	// Parameters:	int; the amount to be decremented
	// Returns:		temp; the current position in the list before decrementing
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	typename list<T>::iterator list<T>::iterator::operator--(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->prev;
		return temp;
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template <class T> T list<T>::pop_front()
	// Title:		Returns data from head
	// Description: Removes the first element in the list and returns it's data
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		begin()
	//				empty()
	//				operator++()
	// Called By:	main()
	//				release()
	// Parameters:	N/A
	// Returns:		T data; the data contained in the first element of the
	//				list
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template <class T>
	T list<T>::pop_front()
	{
		if (!getSize())
		{
			throw runtime_error("Empty list");
			head = nullptr;
			tail = nullptr;
		}
		m_size--;
		T data = head->data;
		iterator temp = begin();
		temp++;
		delete head;
		head = temp;
		if (getSize())
		{
			head->prev = tail;
			tail->next = head;
		}
		else
		{
			tail = nullptr;
			head = nullptr;
		}
		return data;
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template<class T> T list<T>::pop_back()
	// Title:		Returns data from tail
	// Description: Removes the last element in the list and returns it's data
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		end()
	//				empty()
	//				operator--()
	// Called By:	main()
	// Parameters:	N/A
	// Returns:		T data; the data contained in the last element of the
	//				list
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	T list<T>::pop_back()
	{

		if (!getSize())
		{
			throw runtime_error("Empty list");
			head = nullptr;
			tail = nullptr;
		}
		m_size--;
		T data = tail->data;
		iterator temp = end();
		temp--;
		delete tail;
		tail = temp;
		if (getSize()) //!empty()
		{
			head->prev = tail;
			tail->next = head;
		}
		else
		{
			tail = nullptr;
			head = nullptr;
		}
		return data;
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template <class T> T& list<T>::operator[](int index)
	// Title:		Returns a reference to data at index
	// Description: Finds element at index and returns a reference to the
	//				l-value of that element
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		getSize()
	//				begin()
	//				operator++()
	//				end()
	//				operator--()
	// Called By:	main()
	// Parameters:	N/A
	// Returns:		T&; a reference to the l-value in list<T>
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template <class T>
	T& list<T>::operator[](int index)
	{
		iterator it;
		if (index >= 0)
		{
			if (index >= static_cast<int>(getSize()))
				throw out_of_range("index out-of-range");
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		else
		{
			if (index < -(static_cast<int>(getSize())))
				throw out_of_range("index out-of-range");
			it = end();
			for (int i = -1; i > index; i--)
				it--;
		}
		return *it;
	}

	//------------------------------------------------------------------------
	// Class:		CircularDoublyLinkedLIst.h
	// Function:	template <class T> const T& list<T>::operator[](int index)
	//				const
	// Title:		Returns a reference to data at index
	// Description: Finds element at index and returns a reference to the
	//				r-value of that element
	//
	// Programmer:	Anthony Waddell
	// Date:		05-11-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		N/A
	// Calls:		getSize()
	//				begin()
	//				operator++()
	//				end()
	//				operator--()
	// Called By:	main()
	// Parameters:	N/A
	// Returns:		T&; a reference to the r-value in list<T>
	// History Log: 05-11-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template <class T>
	const T& list<T>::operator[](int index)const
	{
		iterator it;
		if (index >= 0)
		{
			if (index >= static_cast<int>(getSize()))
				throw out_of_range("index out-of-range");
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		else
		{
			if (index < -(static_cast<int>(getSize())))
				throw out_of_range("index out-of-range");
			it = end();
			for (int i = -1; i > index; i--)
				it--;
		}
		return *it;
	}
} // end namespace AW_LIST

