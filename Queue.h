//-----------------------------------------------------------------------------
//   File: Queue.h
//
//   Class: queue
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Title:		queue Class
// Description:	This file contains the class definition for the derived 
//				queue class
//
// Programmer:	Anthony Waddell
// Date:		05-17-18
// Version:		1.0
// Environment: Hardware: PC, i7
//              Software: OS: Windows 10 
//              Compiles under Microsoft Visual C++ 2015
//
//   class queue:
//
//     Properties:
//			Inherited:
//				listelem *head -- front end of queue
//				listelem *tail -- back end of queue
//				unsigned m_size -- number of elements in the queue
//
//     Methods:
// 
//       inline: 
//				queue() : list<T>() {};
//					basic constructor
//				queue(size_t n_elements, T datum) : list<T>(n_elements, datum) 
//					{};
//					constuctor with parameters for size and elements
//				queue(const list& x) : list<T>(x) {};
//					copy constructor
//				queue(iterator b, iterator e) : list<T>(e, e) {};
//					constructor usign iterators
//				virtual unsigned getSize() const { return list<T>::getSize(); }
//					accessor for m_size
//				virtual iterator begin() const { return list<T>::begin(); }
//					accessor for *head
//				virtual iterator end() const { return list<T>::end(); }
//					accessor for *tail
//				virtual bool empty()const 
//					determines if queue is empty or not
//				{ return head == nullptr || tail == nullptr; }
//				virtual void release() { list<T>::release(); }
//					empties the queue
//				virtual ~queue() { list<T>::release(); }
//					destructor			
//				ostream& operator<<(ostream& sout, const queue<T>& x)
//					over-loaded output operator for queue
//
//       non-inline:
//				void push_back(T datum);
//					enque element to back of queue
//				T pop_front();
//					remove element from head of queue and return it's data
//
// History Log: AW began version 1.0 05-17-18
//				AW completed version 1.0 05-19-18
//-----------------------------------------------------------------------------
#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include <cstdlib>
#include <string>
#include <exception>
#include "CircularDoublyLinkedList.h"
using namespace std;

namespace AW_LIST
{
	template <class T>
	class queue : virtual protected list<T>

	{
	public:
		//constructors
		queue() : list<T>() {};
		queue(size_t n_elements, T datum) : list<T>(n_elements, datum) {};
		queue(const list& x) : list<T>(x) {};
		queue(iterator b, iterator e) : list<T>(b, e) {};

		//accessors for queue
		virtual unsigned getSize() const { return list<T>::getSize(); }
		virtual iterator begin() const { return list<T>::begin(); }
		virtual iterator end() const { return list<T>::end(); }

		//clearing
		virtual bool empty()const { return head == nullptr || tail == nullptr; }
		virtual void release() { list<T>::release(); }

		//enque and deque elements
		void push_back(T datum);
		T pop_front();

		//destructor
		virtual ~queue() { list<T>::release(); }
	};
	ostream& operator<<(ostream& sout, const list<class T>& x);

	//------------------------------------------------------------------------
	// Class:		Queue.h
	// Function:	template<class T> void queue<T>::push_back(T datum)
	// Title:		Inserts element at back of list<T>
	// Description: Inserts an element into the tail position of a queue<T>
	//
	// Programmer:	Anthony Waddell
	// Date:		05-17-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		T datum; the data to be inserted into the queue
	// Output:		N/A
	// Calls:		listelem(datum, tail, head); constructor
	//				empty()
	// Called By:	main()
	// Parameters:	T datum; the piece of data to be inserted into the queue
	// Returns:		void
	// History Log: 05-17-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template<class T>
	void queue<T>::push_back(T datum)
	{
		listelem* temp = new listelem(datum, tail, head);
		m_size++;
		if (!empty())
		{
			//link the new element to tail
			tail->next = temp;
			temp->prev = tail;
			//insert the new element at end
			tail = temp;
			tail->next = NULL;
		}
		else
		{
			//if list is empty
			head = tail = temp;
			head->next = NULL;
			head->prev = NULL;
			tail->next = NULL;
			tail->prev = NULL;
		}
	}

	//------------------------------------------------------------------------
	// Class:		Queue.h
	// Function:	template <class T> T queue<T>::pop_front()
	// Title:		Removes the *head element of the queue
	// Description: Removes the *head element of the queue and returns it's
	//				data
	//
	// Programmer:	Anthony Waddell
	// Date:		05-17-17
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
	//				opertor++
	// Called By:	main()
	// Parameters:	N/A
	// Returns:		T; the data contained in *head element
	// History Log: 05-17-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template <class T>
	T queue<T>::pop_front()
	{
		if (!getSize())
		{
			throw runtime_error("Empty queue");
			head = nullptr;
			tail = nullptr;
		}
		m_size--;
		T data = head->data;
		iterator temp = begin();
		temp++;
		delete head;
		head = temp;
		if (getSize()) //!empty()
		{
			head->prev = NULL;
		}
		else
		{
			tail = nullptr;
			head = nullptr; // empty at both ends
		}
		return data;
	}

	//------------------------------------------------------------------------
	// Class:		Queue.h
	// Function:	template <class T> 
	//				ostream& operator<<(ostream& sout, const queue<T>& x)
	// Title:		Overloaded output operator for queue 
	//				class
	// Description: Outputs elements of a queue to console
	//
	// Programmer:	Anthony Waddell
	// Date:		05-19-17
	// Version:		1.0
	//
	// Environment: Hardware: PC, i7
	//				Software: OS: Windows 10 
	//				Compiles under Microsoft Visual C++ 2015
	//
	// Input:		N/A
	// Output:		Elements of a queue to the designated output stream
	// Calls:		begin()
	//				end()
	//				getSize()
	// Called By:	main()
	// Parameters:	ostream& sout; the designated output stream
	//				const queue<T>& x; the queue to output
	// Returns:		a reference to sout
	// History Log: 05-19-17 AW Completed v 1.0
	//------------------------------------------------------------------------
	template <class T>
	ostream& operator<<(ostream& sout, const queue<T>& x)
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
}
#endif