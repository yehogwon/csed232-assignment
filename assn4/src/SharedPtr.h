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

	void clear_() {
		if (--(*m_ref_counter) == 0) {
			delete m_ref_counter;
			Dealloc(m_object);
		}
	}
				
public:
	////////////////////////////////////////////
	// Constructors & destructor
	////////////////////////////////////////////
	
	SharedPtr() : m_ref_counter(new int(0)), m_object(nullptr) { }

	// Assuming it is the first time that m_object_ is directed by a SharedPtr
	explicit SharedPtr(ObjectType *m_object_) : m_ref_counter(new int(1)), m_object(m_object_) { }
	
	SharedPtr(const SharedPtr &shared_ptr) : m_ref_counter(shared_ptr.m_ref_counter), m_object(shared_ptr.m_object) {
		if (m_ref_counter != nullptr)
			(*m_ref_counter)++;
	}
	
	~SharedPtr() {
		clear_();
	}

	////////////////////////////////////////////
	// Assignment operator
	////////////////////////////////////////////
	
	SharedPtr& operator=(const SharedPtr &shared_ptr) {
		clear_();
		m_ref_counter = shared_ptr.m_ref_counter;
		m_object = shared_ptr.m_object;
		if (m_ref_counter != nullptr)
			(*m_ref_counter)++;
		return *this;
	}
	
	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	// operator*

	ObjectType* operator->() {
		return m_object;
	}

	const ObjectType* operator->() const {
		return m_object;
	}

	ObjectType& operator*() {
		return *m_object;
	}
	const ObjectType& operator*() const {
		return *m_object;
	}
	
	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	ObjectType& operator[](const int index_) {
		return *(m_object + index_);
	}

	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	const ObjectType& operator[](const int index_) const {
		return *(m_object + index_);
	}

	////////////////////////////////////////////
	// Type casting operators
	////////////////////////////////////////////
	// operator ObjectType const*() const
	// operator ObjectType*()
	
	operator ObjectType*() {
		return m_object;
	}

	operator const ObjectType*() const {
		return m_object;
	}
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif
