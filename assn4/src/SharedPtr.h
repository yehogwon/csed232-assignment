#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <iostream>
#include <cassert>

template<typename ObjectType>
void Deallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Object" << std::endl;
	delete ptr;
}

template<typename ObjectType>
void ArrayDeallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Array" << std::endl;
	delete[] ptr;
}

template<typename T>
using DeallocatorFuncType = void (T*);

// SharedPtr
template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc = Deallocator<ObjectType> >
class SharedPtr
{
private:
	ObjectType* m_object;
	int* m_ref_counter;

	/**
	 * @brief Decrease the reference counter and check if there is no reference to the object. If so, deallocate the object. This function is called when a SharedPtr instance is destructed or assigned to another one. 
	*/
	void clear_() {
		if (m_ref_counter && --(*m_ref_counter) == 0) {
			delete m_ref_counter;
			Dealloc(m_object);
		}
	}
				
public:
	////////////////////////////////////////////
	// Constructors & destructor
	////////////////////////////////////////////
	
	// Constructor without arguments -> directing nullptr and setting the reference counter to 0
	SharedPtr() : m_ref_counter(nullptr), m_object(nullptr) { }

	// Assuming it is the first time that m_object_ is directed by a SharedPtr
	explicit SharedPtr(ObjectType *m_object_) : m_ref_counter(new int(1)), m_object(m_object_) { }
	
	// copy constructor
	SharedPtr(const SharedPtr &shared_ptr) : m_ref_counter(shared_ptr.m_ref_counter), m_object(shared_ptr.m_object) {
		if (m_ref_counter != nullptr) // If this SharedPtr is not directed to nullptr, increase the reference counter
			(*m_ref_counter)++;
	}
	
	~SharedPtr() {
		// When SharedPtr is destructed, check the reference status. i.e., if there is no reference other than this SharedPtr, deallocate the object. (simply call clear_())
		clear_();
	}

	////////////////////////////////////////////
	// Assignment operator
	////////////////////////////////////////////
	
	SharedPtr& operator=(const SharedPtr &shared_ptr) {
		clear_(); // This SharedPtr is about to be assigned to another SharedPtr, so decrease the reference counter and check if there is no reference to the object. If so, deallocate the object. 
		m_ref_counter = shared_ptr.m_ref_counter; // Copy the reference counter
		m_object = shared_ptr.m_object; // Copy the object
		if (m_ref_counter != nullptr) // If this SharedPtr is not directed to nullptr, increase the reference counter
			(*m_ref_counter)++;
		return *this;
	}
	
	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	// operator*

	ObjectType* operator->() {
		return m_object; // give the address of the object
	}

	const ObjectType* operator->() const {
		return m_object; // give the address of the object
	}

	ObjectType& operator*() {
		return *m_object; // give the object (as a reference)
	}
	const ObjectType& operator*() const {
		return *m_object; // give the object (as a reference)
	}
	
	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	ObjectType& operator[](const int index_) {
		return *(m_object + index_); // return the index_(th) element of the array (Notice that array and pointer are equivalent)
	}

	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	const ObjectType& operator[](const int index_) const {
		return *(m_object + index_); // return the index_(th) element of the array (Notice that array and pointer are equivalent)
	}

	////////////////////////////////////////////
	// Type casting operators
	////////////////////////////////////////////
	// operator ObjectType const*() const
	// operator ObjectType*()
	
	operator ObjectType*() {
		return m_object; // casting to ObjectType*
	}

	operator const ObjectType*() const {
		return m_object; // casting to ObjectType* (const version)
	}
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif
