#include "SharedPtr.h"

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::SharedPtr() {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::SharedPtr(const SharedPtr& shared_ptr) {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::SharedPtr(ObjectType *m_object_) {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::~SharedPtr() {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>& SharedPtr<ObjectType, Dealloc>::operator=(const SharedPtr<ObjectType, Dealloc>& shared_ptr) {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
ObjectType* SharedPtr<ObjectType, Dealloc>::operator->() {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
const ObjectType* SharedPtr<ObjectType, Dealloc>::operator->() const {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
ObjectType& SharedPtr<ObjectType, Dealloc>::operator*() {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
const ObjectType& SharedPtr<ObjectType, Dealloc>::operator*() const {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
ObjectType& SharedPtr<ObjectType, Dealloc>::operator[](const int index_) {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
cons

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::operator ObjectType*() {
}t ObjectType& SharedPtr<ObjectType, Dealloc>::operator[](const int index_) const {
}

template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc>
SharedPtr<ObjectType, Dealloc>::operator ObjectType* const() const {
}
