#pragma once
#include <stdexcept>

template <class T> class Stack{
public:
	using sizetype = size_t;
	Stack() = default;
	Stack(const Stack&) = default;
	Stack(Stack&&) = default;
	Stack& operator=(const Stack&) = default;
	Stack& operator=(Stack&&) = default;
	~Stack();

	void push(const T&);
	void push(T&&);
	void pop() noexcept;
	const T& top() const;
	T&	top();
	//delegator to sort_
	void sort();

	//throw out_of_range, if stack doesn't contain equal element
	//const T& find(T&) const;
	T& find(const T& elem);

	void print();
	sizetype size() const noexcept;
	bool empty() const noexcept;
	void clear();

private:
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};
	sizetype counter = 0;
	Node* head = nullptr;

	template <class T1> void push_(T1&&);
	Node* getMiddleNode(Node*) const;
	Node* merge(Node* biggerHead, Node* smallerHead) const;
	Node* sort_(Node* head) const;

public:
	/*class BaseIterator {
	public:
		BaseIterator(Node* cur = nullptr);
		BaseIterator& operator++(); //move to the next node if it exists; else nothing
		bool operator==(BaseIterator& other) const; //if this or other iterator is at the nullptr position, throw invlid_argument 
		bool operator!=(BaseIterator&) const;		//if this or other iterator is at the nullptr position, throw invlid_argument 
	protected:
		Node *current;
	};

	class ConstIterator : public BaseIterator {
	public:
		using BaseIterator::BaseIterator;
		const T& operator*() const;
		ConstIterator& operator++();
	};*/
	class Iterator{
	public:
		Iterator(Node* cur = nullptr);
		T& operator*() const;
		Iterator& operator++(); //move to the next node if it exists; else nothing
		bool operator==(Iterator& other) const; //if this or other iterator is at the nullptr position, throw invlid_argument 
		bool operator!=(Iterator&) const;		//if this or other iterator is at the nullptr position, throw invlid_argument 
	private:
		Node *current;
	};

	//ConstIterator begin() const noexcept;
	Iterator begin() noexcept;
	//ConstIterator end() const noexcept;
	Iterator end() noexcept;

	void print_(Iterator begin, Iterator end);
	Iterator find_(const T& elem, Stack<T>& st);
};

template<class T> void Stack<T>::clear() {
	while (head) {
		pop();
	}
}

template<class T> Stack<T>::~Stack() {
	clear();
}

template<class T> bool Stack<T>::empty() const noexcept
{
	return (counter == 0);
}

template<class T> typename Stack<T>::sizetype Stack<T>::size() const noexcept{
	return counter;
}

//pre: T must override operator string
template<class T> void Stack<T>::print() {
	print_(begin(), end());
}

template<class T> template <class T1> void Stack<T>::push_(T1&& elem) {
	Node* newNode = new Node{ std::forward<T1>(elem), head, nullptr};
	if (head) head->prev = newNode;
	head = newNode;
	++counter;
}

template<class T> inline void Stack<T>::print_(Iterator begin, Iterator end)
{
	for (auto i = begin; i != end; ++i) {
		std::cout << std::string(*i) << std::endl;
	}
}
template<class T> void Stack<T>::push(const T& elem) {
	push_(elem);
}
template<class T> void Stack<T>::push(T&& elem) {
	push_(std::move(elem));
}

template <class T> void Stack<T>::pop() noexcept{
	if (!head) return;

	Node *tempHead = head->next;
	if (tempHead) tempHead->prev = nullptr;
	delete head;
	head = tempHead;
	--counter;
}

//pre: stack is nonempty, else throw
template <class T> const T& Stack<T>::top() const {
	if (!head) throw std::out_of_range("no elements in stack");
	return head->data;
}

//pre: stack is nonempty, else throw
template <class T> T& Stack<T>::top() {
	if (!head) throw std::out_of_range("no elements in stack");
	return head->data;
}

template <class T> void Stack<T>::sort() {
	head = sort_(head);
}

template<class T> T& Stack<T>::find(const T& elem){
	
	Iterator i = find_(elem, *this);
	return *i;
}

template <class T> typename Stack<T>::Node* Stack<T>::sort_(Node* head) const{
	if ((!head)||(!head->next)) return head;
	else {
		Node* median = getMiddleNode(head);
		if (median->prev) {
			median->prev->next = nullptr;
			median->prev = nullptr;
		}
		head = sort_(head);
		median = sort_(median);
		return merge(head, median);
	}
}

template <class T> typename Stack<T>::Node* Stack<T>::getMiddleNode(Node* head) const {
	Node *p1 = head;
	Node *p2 = head;
	while ((p1) && (p1->next)) {
		p1 = p1->next->next;
		p2 = p2->next;
	}
	return p2;
}

template <class T> typename Stack<T>::Node* Stack<T>::merge(Node* biggerHead, Node* smallerHead) const  {
	Node *tempHead, *result;
	if (smallerHead->data > biggerHead->data) {
		tempHead = biggerHead;
		biggerHead = smallerHead;
		smallerHead = tempHead;
	}

	result = biggerHead;

	while ((biggerHead) && (smallerHead)) {
		while ((biggerHead->next) && (biggerHead->next->data >= smallerHead->data))
			biggerHead = biggerHead->next;

		tempHead = smallerHead;
		if (!(biggerHead->next)) {
			biggerHead->next = smallerHead;
			smallerHead->prev = biggerHead;
			biggerHead = nullptr;
		}
		else {
			while ((tempHead->next) && (tempHead->next->data >= biggerHead->next->data))
				tempHead = tempHead->next;

			Node* nextSmallerHead = tempHead->next;

			tempHead->next = biggerHead->next;
			biggerHead->next->prev = tempHead;
			biggerHead->next = smallerHead;
			smallerHead->prev = biggerHead;

			smallerHead = nextSmallerHead;
			biggerHead = tempHead->next;

		}

	}

	return result;
}

//template<class T> typename Stack<T>::ConstIterator Stack<T>::begin() const noexcept { return ConstIterator(head); }
template<class T> typename Stack<T>::Iterator Stack<T>::begin() noexcept { return Iterator(head); }
//template<class T> typename Stack<T>::ConstIterator Stack<T>::end() const noexcept { return ConstIterator(nullptr); }
template<class T> typename Stack<T>::Iterator Stack<T>::end() noexcept { return Iterator(nullptr); }

template<class T> typename Stack<T>::Iterator Stack<T>::find_(const T& elem, Stack<T>& st)
{
	Iterator i = st.begin();
	Iterator end = st.end();
	while ((i != end) && (*i != elem)) ++i;
	return i;
}

//stack::Iterator
template <class T> Stack<T>::Iterator::Iterator(Node* cur) : current (cur) {}
template <class T> typename  Stack<T>::Iterator& Stack<T>::Iterator::operator++(){
	if (current) current = current->next;
	return *this;
}

template <class T> bool Stack<T>::Iterator::operator==(Iterator& other) const{
	//if ((!other.current) || (!this->current)) return 
	return (this->current == other->current);
}

template <class T> bool Stack<T>::Iterator::operator!=(Iterator& other) const{	
	return (this->current != other.current);
}

/*Stack::ConstIterator
template<class T>
inline const T & Stack<T>::ConstIterator::operator*() const
{
	if (BaseIterator::current) return BaseIterator::current->data;
	else throw std::out_of_range("iterator at the nullptr position");
}

template<class T>
inline typename Stack<T>::ConstIterator& Stack<T>::ConstIterator::operator++()
{
	BaseIterator::operator++();
	return *this;
}
*/

//Stack::Iterator
template<class T>
inline T & Stack<T>::Iterator::operator*() const
{
	if (current) return current->data;
	else throw std::out_of_range("iterator at the nullptr position");
}

/*template<class T>
inline typename Stack<T>::Iterator& Stack<T>::Iterator::operator++()
{
	BaseIterator::operator++();
	return *this;
}*/
