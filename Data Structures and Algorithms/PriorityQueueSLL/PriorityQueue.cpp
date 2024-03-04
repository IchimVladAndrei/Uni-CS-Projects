#include "PriorityQueue.h"
#include <exception>
using namespace std;

PriorityQueue::PriorityQueue(Relation r) {
	this->size = 0;
	this->rel = r;
	this->head = nullptr;
}
//theta(1)


void PriorityQueue::push(TElem e, TPriority p) {
	node* new_node = new node;
	new_node->info.first = e;
	new_node->info.second = p;
	new_node->next = nullptr;
//allocate new node

	if (this->size == 0)
		this->head = new_node;
	//to add the head
	else {
		node* current = this->head;
		node* previous = nullptr;
		while (current != nullptr) {
			previous = current;
			current = current->next;
		}
		previous->next = new_node;
	}
	
	this->size++;
}
//BC:theta(1), we have to just add the node head 
//WC:theta(size), we have to add any other node
//T:O(size)


Element PriorityQueue::top() const {
	if (this->size == 0)
		throw exception();
	node* current = this->head;
	node* elem = current;
	while (current != nullptr) {
		if (this->rel(current->info.second, elem->info.second))
			elem = current;
		current = current->next;
	}
	return elem->info;
}
//theta(size), we have to visit every node

Element PriorityQueue::pop() {
	if (this->size == 0)
		throw exception();
	node* current = this->head;
	node* previous = nullptr;
	Element highest = top();
	while (current != nullptr && !(current->info.first == highest.first && current->info.second == highest.second)) {
		previous = current;
		current = current->next;
	}
	if (current == this->head)
		this->head = current->next;
	else
		previous->next = current->next;
	this->size--;
	return current->info;
}
//BC:theta(1) we only have to pop the head 
//WC:theta(size); we have to visit every node otherwise
//T:O(size)

bool PriorityQueue::isEmpty() const {
	if (this->size == 0)
		return true;
	return false;
}
//theta(1)

PriorityQueue::~PriorityQueue() {
	node* temp;
	while (this->head != nullptr) {
		temp = this->head->next;
		delete this->head;
		this->head = temp;
	}
}//theta(size) we have to visit every node


bool PriorityQueue::search(TElem elem) const
{
	if (this->size == 0)
		throw exception();

	node* current = this->head;
	while (current != nullptr) {
		if (current->info.first == elem)
			return true;
		current = current->next;
	}
	return false;
}
//theta(size)