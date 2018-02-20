//----------------------------------------------------------------------------
// File:		ProjectDriver.cpp
// 
// Description: Test Driver for the CircularDoubleLinkedList class and it's
//				Derived Queue class
// 
// Programmer:  Anthony Waddell
//
// Functions:   main()
// 
// Environment: Hardware: PC, i7
//              Software: OS: Windows 10 
//              Compiles under Microsoft Visual C++ 2015
//-------------------------------------------------------------------------
#include <cstdlib>
#include <string>
#include <exception>
#include "CircularDoublyLinkedList.h"
#include "Queue.h"
using namespace std;
//---------------------------------------------------------------------------
//
// Function:	main()
// Title:		Using Cicular Double Linked Lists
// Description: This file contains function main() which tests the 
//				CircularDoublyLinkedList class, its scoped Iterator class,
//				and it's derived Queue class
//
// Programmer:	Anthony Waddell
// Date:		05-02-17
// Version:		1.0
// Environment: Hardware: PC, i7        
//				Software: OS: Windows 10 
//				Compiles under Microsoft Visual C++ 2015
// 
// Input:		user supplied elements to fill and test a Circular Doubly 
//				Linked List and it's inherited Queue
// Output:		Various operations performed on a Circular Doubly Linked
//				List and it's inherited queue class
// Calls:		Circular Doubly Linked List base class and it's derived 
//				Queue class
// Called By:	n/a
// Parameters:  None
// Returns:		EXIT_SUCCESS  upon successful execution
//
// History Log:	05-02-17 AW Began Project
//				05-22-17 AW Completed project
// Known Bugs:  N/A
//----------------------------------------------------------------------------

int main(void)
{
	using AW_LIST::list;
	using AW_LIST::queue;

	try
	{
		list<int> intList;
		list<int> parameterList(5, 5);
		list<int> copyList(parameterList);
		list<int> iteratorList(copyList.end(), copyList.begin());
		list<int> iteratorOperatorList;
		for (int i = 0; i < 10; i++)
			iteratorOperatorList.push_back(i);
		queue<int> intQueue;
		queue<int> parameterQueue(10, 1);
		queue<int> copyQueue(parameterQueue);
		queue<int> iteratorQueue(copyQueue.end(), copyQueue.begin());
		queue<int> iteratorOperatorQueue;
		for (int i = 0; i < 10; i++)
			iteratorOperatorQueue.push_back(i);

		//----------- Circular Doubly Linked List Testing --------------------

		//Test the basic constructor and getSize() on a list
		cout << "Test of basic constructor: intList" << intList << endl;
		cout << "intList contains: " << intList.getSize() << " elements.";

		//Test that head and tail in an empty list are null pointers
		cout << "intLists head and tail are both: ";
		if (intList.begin() == NULL && intList.end() == NULL)
			cout << "nullptrs." << endl << endl;

		//Test of push_front() and push_back() to fill a list
		for (int i = 0; i < 10; i++)
		{
			if (i % 2 == 0)
				intList.push_back(i);
			else
				intList.push_front(i);
		}
		cout << "Test of push_front() and push_back()" << endl;
		cout << "intList: " << intList << endl;
		cout << "tail->next points to " << intList.end()->next->data << ", "
			<< "the data contained in the head element." << endl;
		cout << "head->previous points to " << intList.begin()->prev->data <<
			", the data contained in the tail element." << endl << endl;

		//Test of front() and back() on a list
		cout << "Test of front() annd back()" << endl
			<< "head contains: " << intList.front() << " and  tail contains "
			<< intList.back() << endl << endl;

		//Test of operator[] and operator= on a list
		cout << "Test of operator[] and  operator=" << endl
			<< "The data in the fifth element of the list is "
			<< intList[4] << endl;
		intList[4] = 6;
		cout << "The data in the fifth element of the list is now "
			<< intList[4] << endl << endl;

		//Test of pop_front() and pop_back() to remove elements from list
		cout << "Test of pop_front() and pop_back()" << endl;
		cout << "Using pop_front(), the first five elements of the list are: "
			<< endl;
		for (int i = 0; i < 5; i++)
			cout << intList.pop_front() << " ";
		cout << endl << endl << "intList now contains: " << intList << endl;
		cout << "Using pop_back(), the last five elements of the list are: "
			<< endl;
		for (int i = 0; i < 5; i++)
			cout << intList.pop_back() << " ";
		cout << endl << endl << "intList now contains " << intList.getSize() <<
			" elements" << endl;
		cout << "intList is now an empty list whose head and tail elements" <<
			" are ";
		if (intList.begin() == NULL && intList.end() == NULL)
			cout << "nullptrs." << endl << endl;

		//Test of constructor with parameters on a list
		cout << "Test of constructor with parameters for size and data" <<
			endl << "parameterList: " << parameterList << endl;

		//Test of copy constructor on a list
		cout << "Test of copy constructor" << endl;
		cout << "copyList is a copy of paramaterList" << endl;
		cout << "copyList: " << copyList << endl;

		//Test of iterator constructor on a list
		cout << "Test of iterator constructor" << endl;
		cout << "iteratorList is constructed using the begin() and end()" <<
			" of copyList" << endl;
		cout << "iteratorList: " << iteratorList << endl;

		//Test of release() and empty()
		cout << "Test of release() and empty() on iteratorList" << endl;
		iteratorList.release();
		cout << "iteratorList: " << iteratorList;
		if (iteratorList.empty())
			cout << "iteratorList's head and tail are null pointers now." <<
			endl << endl;

		//------------------- Iterator Class Testing -------------------------

		//Test of iterator class functions
		list<int>::iterator testIt = iteratorOperatorList.begin();
		cout << "Test of iterator class functions on iteratorOperatorList"
			<< endl << "iteratorOperatorList: " << iteratorOperatorList;
		cout << "testIt is equal to iteratorOperatorList[0]" << endl;
		cout << "Test of -> operator on testIt: " <<
			(testIt)->data << endl;
		cout << "Test of testIt++ operator on testIt: " <<
			(testIt++)->data << endl;
		cout << "testIt now points to " << testIt->data << endl;
		cout << "Test of ++testIt operator on testIt: " <<
			(++testIt)->data << endl;
		cout << "testIt now points to " << testIt->data << endl;
		cout << "Test of testIt-- operator on testIt: " <<
			(testIt--)->data << endl;
		cout << "testIt now points to " << testIt->data << endl;
		cout << "Test of --testIt operator on testIt: " <<
			(--testIt)->data << endl;
		cout << "testIt now points to " << testIt->data << endl << endl;

		//---------------------- Queue Class Testing -------------------------

		//Test of basic queue constructor and getSize()
		cout << "Test of basic constructor: intQueue" << intQueue << endl;
		cout << "intQueue contains: " << intQueue.getSize() << " elements. ";

		//Test that head and tail in an empty queue are null pointers
		//Test of begin() and end()
		cout << "intQueue's head and tail are both: ";
		if (intQueue.begin() == NULL && intQueue.end() == NULL)
			cout << "nullptrs." << endl;

		//Test of push_back() to fill a queue
		for (int i = 0; i < 10; i++)
		{
			intQueue.push_back(i);
		}
		cout << "Test of push_back() on a queue" << endl;
		cout << "intQueue: " << intQueue << endl;
		cout << "tail->prev points to " << intQueue.end()->prev->data << endl;
		if (intQueue.end()->next == NULL)
			cout << "tail->next points to null" << endl;
		cout << "head->next points to " << intQueue.begin()->next->data
			<< endl;
		if (intQueue.begin()->prev == NULL)
			cout << "head->prev points to null" << endl << endl;

		//Test of constructor with parameters on a queue
		cout << "Test of constructor with parameters for size and data" <<
			endl << "parameterQueue: " << parameterQueue << endl;

		//Test of copy constructor on a queue
		cout << "Test of copy constructor" << endl;
		cout << "copyQueue is a copy of paramaterQueue" << endl;
		cout << "copyQueue: " << copyQueue << endl;

		//Test of iterator constructor on a queue
		cout << "Test of iterator constructor" << endl;
		cout << "iteratorQueue is constructed using the begin() and end()" <<
			" of copyQueue" << endl;
		cout << "iteratorQueue: " << iteratorQueue << endl;

		//Test of pop_front() to remove elements from queue
		cout << "Test of pop_front() on a queue" << endl;
		cout << "Using pop_front(), the first ten elements of the queue areendl			<< :" 
;
		for (int i = 0; i < 10; i++)
			cout << intQueue.pop_front() << " ";
		cout << endl << endl << "intQueue now contains: " << intQueue << endl;
		cout << "intQueue is now an empty queue whose head and tail " <<
			"elements are ";
		if (intQueue.begin() == NULL && intQueue.end() == NULL)
			cout << "nullptrs." << endl << endl;
	}
	catch (exception e)
	{
		cerr << "program terminated: " << e.what() << endl;
		cin.get();
		return EXIT_FAILURE;
	}
	cout << "Press <ENTER> to continue";
	cin.get();
	return EXIT_SUCCESS;
}
