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

	// ======= ADD CODE HERE IF NEEDED =========
				
public:
	////////////////////////////////////////////
	// Constructors & destructor
	////////////////////////////////////////////
	
	SharedPtr();
	explicit SharedPtr(ObjectType *m_object_);
	SharedPtr(const SharedPtr& shared_ptr);
	~SharedPtr();

	////////////////////////////////////////////
	// Assignment operator
	////////////////////////////////////////////
	
	SharedPtr& operator=(const SharedPtr& shared_ptr);
	
	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	// operator*

	ObjectType* operator->();
	const ObjectType* operator->() const;

	ObjectType& operator*();
	const ObjectType& operator*() const;
	
	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	ObjectType& operator[](const int index_);

	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	const ObjectType& operator[](const int index_) const;

	////////////////////////////////////////////
	// Type casting operators
	////////////////////////////////////////////
	// operator ObjectType const*() const
	// operator ObjectType*()
	
	operator ObjectType*();
	operator ObjectType* const() const;
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::SharedPtr() {
    m_ref_counter = new int(0);
    m_object = nullptr;
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::SharedPtr(ObjectType *m_object_) {
    m_ref_counter = new int(1);
    m_object = m_object_;
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::SharedPtr(const SharedPtr& shared_ptr) {
    m_ref_counter = shared_ptr.m_ref_counter;
    m_object = shared_ptr.m_object;
    *m_ref_counter++;
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::~SharedPtr() {
    *m_ref_counter--;
    if (*m_ref_counter == 0) {
        Dealloc(m_object);
        delete m_ref_counter;
    }
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>& SharedPtr<ObjectType, Dealloc>::operator=(const SharedPtr<ObjectType, Dealloc>& shared_ptr) {
    m_ref_counter = shared_ptr.m_ref_counter;
    m_object = shared_ptr.m_object;
    *m_ref_counter++;
	return *this;
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
ObjectType* SharedPtr<ObjectType, Dealloc>::operator->() {
    return m_object;
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
const ObjectType* SharedPtr<ObjectType, Dealloc>::operator->() const {
    return m_object;
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
ObjectType& SharedPtr<ObjectType, Dealloc>::operator*() {
    return *m_object;
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
const ObjectType& SharedPtr<ObjectType, Dealloc>::operator*() const {
    return *m_object;
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
ObjectType& SharedPtr<ObjectType, Dealloc>::operator[](const int index_) {
    return *(m_object + index_);
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
const ObjectType& SharedPtr<ObjectType, Dealloc>::operator[](const int index_) const {
    return *(m_object + index_);
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::operator ObjectType*() {
    return m_object;
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::operator ObjectType* const() const {
    return m_object;
}

#endif
