//List.h:
//--------
#ifndef LIST_H
#define LIST_H

#include <assert.h>

enum bool{false, true};

//----------------------------------------------------------------------
//  class list
//      arbitrary size lists of elements
//      permits insertion and removal only
//      from the front of the list
//----------------------------------------------------------------------

template <class T> class link;

template <class T> class list
{
public:
    // constructors
    list();
	 ~list();

    // operations
	 void          Add(T value);
    T             FirstElement() const;
	 virtual bool  Includes(T value) const;
    int           IsEmpty() const;
	 void          RemoveFirst();
	 T             RemoveandReturnFirst();    //ohad & liat
	 virtual void  Clear();
	 T					ReturnValue(T v);             //for Puzzle usage

protected:
    // data field
    link<T> *     first;
};


//----------------------------------------------------------------------
//  class link
//      facilitator for operations on lists
//      maintains a single element for the linked list class
//----------------------------------------------------------------------

template <class T> class link
{
public:
	 // constructor
    link(T linkValue, link * nextPtr);
    link(const link &);

    // data areas
    T         value;
    link *    next;
};


//----------------------------------------------------------------------
//  class doubleEndedList
//      a variation on lists - can add elements to end
//      as well as to front
//----------------------------------------------------------------------

template <class T> class doubleEndedList : public list<T> {
public:
    // constructors
    doubleEndedList ();

    // override the following methods from class list
    virtual void    Add (T value);
	 virtual void    Clear ();
	 virtual void    RemoveFirst ();
	 virtual   T     RemoveandReturnFirst();  //change the "last" ptr as well

    // add a new element to the end of the list
    void        AddToEnd (T value);

protected:
    // data area -- link to end
    link<T> * last;
};



//----------------------------------------------------------------------
//  class list implementation
//----------------------------------------------------------------------

template <class T> list<T>::list() : first(NULL)
{
    // no further initialization
}



template <class T> list<T>::~list()
{
    Clear();
}

template <class T> void list<T>::Clear()
{
    // empty all elements from the list
    link<T> * next;

    for (link<T> * p=first; p != NULL; p=next)
    {
    // delete the element pointed to by p
		next=p->next;
      p->next=NULL;
      delete p;
	 }

    // mark that the list contains no elements
    first=NULL;
}



template <class T> void list<T>::Add(T val)
{
    // Add a new value to the front of a linked list
    first=new link<T>(val, first);
    assert(first != NULL);
}


template <class T> T list<T>::FirstElement() const
{
    // return first value in list
    assert(first != NULL);
	 return first->value;
}



template <class T> bool list<T>::Includes(T v) const
{
	 // loop to test each element
	 for (link<T> * p=first; p!=NULL ; p=p->next)
		  if (v == p->value)
				return true;

	 // not found
	 return false;
}



template <class T> int list<T>::IsEmpty() const
{
	 // test to see if the list is empty
	 // list is empty if the pointer to the first link is null
	 return first == NULL;
}



template <class T> void list<T>::RemoveFirst()
{
	 // make sure there is a first element
	 assert(first != NULL);

	 // save pointer to the removed node
	 link<T> * p=first;

	 // reassign the first node
	 first=  p->next;

	 // recover memory used by the first element
	 delete p;
}

template <class T> T list<T>::RemoveandReturnFirst()
{
	 // make sure there is a first element
	 assert(first != NULL);

	 // save pointer to the removed node
	 link<T> * p=first;

	 T temp = p->value;  //so we can return it

	 // reassign the first node
	 first=  p->next;

	 // recover memory used by the first element
	 delete p;
	 return temp;
}


template <class T> T list<T>::ReturnValue(T v)
{
// loop to test each element
	 for (link<T> * p=first; p!=NULL ; p=p->next)
		  if (v == p->value)
				return p->value;

	 // not found
	 return NULL;
}

//----------------------------------------------------------------------
//  class link implementation
//----------------------------------------------------------------------

template <class T> link<T>::link(T val, link<T> * nxt)
	 : value(val), next(nxt)
{
	 // create and initialize a new link field
}

template <class T> link<T>::link(const link<T> & source)
	 : value(source.value), next(source.next)
{
}


//----------------------------------------------------------------------
//  class doubleEndedList implementation
//----------------------------------------------------------------------

template <class T> doubleEndedList<T>::doubleEndedList()
	 : list<T>()
{
    last = NULL;
}

template <class T> void doubleEndedList<T>::Add(T val)
{   // add an element to the front of a double ended list
    // only need to handle addition to empty list

    if (IsEmpty()) {
        list<T>::Add(val);
		  last=first;
        }
    else
        list<T>::Add(val);
}

template <class T> void doubleEndedList<T>::AddToEnd(T val)
{
	 // add a new element to the end of a double ended list
    // if there is an end, add to it

    if (last != NULL) {
        last->next = new link<T>(val,NULL);
		  last = last->next;
    }

	 // otherwise, just add to front
    else
        Add(val);
}

template <class T> void doubleEndedList<T>::RemoveFirst()
{
	 // remove the first element from double ended list
	 // invoke the method from list to do the work

	 list<T>::RemoveFirst();

	 // only do something different if we removed last element

	 if (IsEmpty())
		  last = NULL;
}

template <class T> void doubleEndedList<T>::Clear()
{   
    // delete all values from collection
    // invoke the list method to do the actual work

    list<T>::Clear();

    // then set the pointer to the last element to zero
    
    last = NULL;
}

template <class T> T doubleEndedList<T>::RemoveandReturnFirst()
{
	 T temp = list<T>::RemoveandReturnFirst();

	 // only do something different if we removed last element

	 if (IsEmpty())
		  last = NULL;

	 return temp;
}
#endif