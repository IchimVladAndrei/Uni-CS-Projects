#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->current = 0;
	while (this->current <= map.m && this->map.elements[this->current] == NULL_TELEM)
		this->current++;
	this->first_element = this->current;
}
//BC: Theta(1), WC: Theta(capacity) , TOTAL: O(capacity)

void MapIterator::first() {
	this->current = 0;
	while (this->current <= map.m && this->map.elements[this->current] == NULL_TELEM)
		this->current++;
	this->first_element = this->current;
}
//BC: Theta(1) when current is the the first element
//WC: Theta(capacity): when we have the first element on the last bucket
//TOTAL: O(capacity)

void MapIterator::next() {
	if (this->current >= this->map.m)
		throw exception();
	this->current++;
	while (this->current <= this->map.m && this->map.elements[this->current] == NULL_TELEM)
		this->current++;
}
//BC: Theta(1) when next is the the first element
//WC: Theta(capacity): when we have the next element on the last bucket
//TOTAL: O(capacity)


TElem MapIterator::getCurrent(){
	if (this->current >= this->map.m)
		throw exception();

	return this->map.elements[this->current];
}
//Theta(1)


bool MapIterator::valid() const {
	if (this->current < this->map.m)
		return true;
	return false;
}
//Theta(1)


