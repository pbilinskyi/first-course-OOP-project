#pragma once
#include <stdexcept>

template <class T> class Stack{
public:
	using sizetype = size_t;
	Stack() = default;
	Stack(const Stack&) = delete;
	Stack(Stack&&) = delete;
	Stack& operator=(const Stack&) = delete;
	Stack& operator=(Stack&&) = delete;
	~Stack();

	void push(const T&);
	void push(T&&);
	void pop() noexcept;
	const T& top() const;
	T&	top();
	template<class Identificator> const T& find(Identificator&) const;
	template<class Identificator> T& find(Identificator&);

	//delegator to sort_
	void sort();

	void print() const;
	sizetype size() const noexcept;
	bool empty() const noexcept;
	void clear();

private:
	struct Node {
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};
	sizetype counter = 0;
	Node* head = nullptr;
	template <class T1> void push_(T1&&);

	Node* getMiddleNode(Node*) const;
	Node* merge(Node* biggerHead, Node* smallerHead) const;
	Node* sort_(Node* head) const;
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
template<class T> void Stack<T>::print() const{
	Node *temp = head;
	while (temp) {
		std::cout << temp->data << " ";
		temp = temp->next;
	}
}

template<class T> template <class T1> void Stack<T>::push_(T1&& elem) {
	
	Node* newNode = new Node{ std::forward<T1>(elem), head, nullptr};
	if (head) head->prev = newNode;
	head = newNode;
	++counter;
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

template<class T> template<class Identificator> const T& Stack<T>::find(Identificator& field) const {
	//plug
	return top();
}

template<class T> template<class Identificator> T& Stack<T>::find(Identificator& field){
	//plug
	return top();
}

