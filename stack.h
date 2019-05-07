#ifndef STACK_TEMPLATE_
#define STACK_TEMPLATE_

#include <cstddef> // for size_t
#include <utility> // for move and so on

template <class T> class Stack {
public:
    using sizetype=size_t;
    using elem_t=T;
	Stack()=default;
    Stack(const Stack&)=delete;
    Stack(Stack&&)=delete;
	Stack& operator=(const Stack&)=delete;
	Stack& operator=(Stack&&)=delete;
	~Stack();

	void push(T&& elem);
	void push(const T& elem);
	void pop(); //pre: stack is not empty, else throw
	inline T& top(); //pre: stack is not empty, else throw
    inline const T& top() const; //pre: stack is not empty, else throw

	sizetype size() const noexcept;
	bool empty() const noexcept;
	void clear() noexcept;

protected:
	struct Node {T data; Node *next;} ;
    Node *head=nullptr;
	sizetype count=0;

	template <class T1> void push_(T1&& elem);

    class BaseIterator{
    public:
		BaseIterator(Node *current=nullptr) noexcept;
		BaseIterator& operator ++(); //move to next node if current node exist; else nothing
        bool operator ==(const BaseIterator&) const noexcept;
        bool operator !=(const BaseIterator&) const noexcept;
	protected:
		Node *current;
	};
public:

    class const_iterator:public BaseIterator{
	public:
	    using BaseIterator::BaseIterator;
		const T& operator*() const;	 //current data element if exist; else throw(out_of_range)
		const_iterator& operator ++(); //move to next node if current node exist; else nothing
	};
    class iterator:public BaseIterator{
	public:
	    using BaseIterator::BaseIterator;
		T& operator*() const;	     //current data element if exist; else throw(out_of_range)
		iterator& operator ++(); //move to next node if current node exist; else nothing
	};

	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;
	iterator begin() noexcept;
	iterator end() noexcept;
};

///implementation
#include <stdexcept>
///cleaning
template<class T> Stack<T>::~Stack(){clear();}
template<class T> void Stack<T>::clear() noexcept{
	Node* tmp;
	while (head) {
		tmp=head->next;
		delete head;
		head=tmp;
	}
	count=0;
}
///
template<class T> template<class T1> void Stack<T>::push_(T1&& elem){
     head=new Node{std::forward<T1>(elem), head};
	 ++count;
}

template<class T> void Stack<T>::push(const T& elem){
  push_(elem);
}
template<class T> void Stack<T>::push(T&& elem){
    push_(std::move(elem));
}
template<class T> void Stack<T>::pop(){
    if (!head) throw std::out_of_range("There are no elements in stack!");
	Node* tmp=head->next; delete head; head=tmp; --count;
}
template<class T> T& Stack<T>::top(){
    if (!head) throw std::out_of_range("There are no elements in stack!");
    return head->data;
}
template<class T> const T& Stack<T>::top()const{
    if (!head) throw std::out_of_range("There are no elements in stack!");
    return head->data;
}
///
template<class T> typename Stack<T>::sizetype  Stack<T>::size()const noexcept{return count;}
template<class T> bool Stack<T>::empty()const noexcept{return size()==0;}

///added for version with iterator
template<class T> typename Stack<T>::const_iterator Stack<T>::begin() const noexcept{return const_iterator(head);}
template<class T> typename Stack<T>::const_iterator Stack<T>::end() const noexcept{return const_iterator();}
template<class T> typename Stack<T>::iterator Stack<T>::begin() noexcept{return iterator(head);}
template<class T> typename Stack<T>::iterator Stack<T>::end() noexcept{return iterator();}

///Stack::BaseIterator
template<class T> Stack<T>::BaseIterator::BaseIterator(Node *c)noexcept:current(c){}
template<class T> typename Stack<T>::BaseIterator& Stack<T>::BaseIterator::operator ++(){
	if (current) current=current->next;
	return *this;
}
template<class T> bool Stack<T>::BaseIterator::operator ==(const BaseIterator& other) const noexcept{
	return current==other.current;
}
template<class T> bool Stack<T>::BaseIterator::operator !=(const BaseIterator& other) const noexcept{
	return current!=other.current;
}
///Stack::const_iterator
template<class T> const T& Stack<T>::const_iterator::operator*() const{
	if (BaseIterator::current)
        return BaseIterator::current->data;
    else
        throw std::out_of_range("wrong iterator position");
}
template<class T> typename Stack<T>::const_iterator& Stack<T>::const_iterator::operator ++(){
	BaseIterator::operator++();
	return *this;
}

///Stack::iterator
template<class T> T& Stack<T>::iterator::operator*() const{
	if (BaseIterator::current)
        return BaseIterator::current->data;
    else
        throw std::out_of_range("wrong iterator position");
}
template<class T> typename Stack<T>::iterator& Stack<T>::iterator::operator ++(){
	BaseIterator::operator++();
	return *this;
}

///List
template <class T> class List:public Stack<T> {
public:
    using elem_t=typename Stack<T>::elem_t;
    typename Stack<T>::const_iterator find(const T&) const; //first occurence or end()
    typename Stack<T>::iterator find(const T&); //first occurence or end()
};

template <class T> auto find_(T&& li, const typename std::remove_cv_t<std::remove_reference_t<T>>::elem_t &data){
    auto tmp=li.begin(), end_=li.end();
	while (tmp!=end_ && *tmp!=data) ++tmp;
	return tmp;
}
template<class T> typename Stack<T>::const_iterator List<T>::find(const T& data) const {
    return find_(*this, data);
}
template<class T> typename Stack<T>::iterator List<T>::find (const T& data){
    return find_(*this, data);
}

/// embedded class sample

template<class T> class A{
	class B;
};
template<class T> class A<T>::B{};


#endif // STACK_TEMPLATE_
