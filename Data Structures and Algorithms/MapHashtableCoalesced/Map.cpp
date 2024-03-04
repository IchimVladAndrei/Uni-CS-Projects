#include "Map.h"
#include "MapIterator.h"

int Map::hash(TKey k) const
{
	return abs(k) % this->m;
}
//Theta(1)

void Map::get_first_empty()
{
	this->first_empty += 1;
	while (this->first_empty < this->m && this->elements[this->first_empty] != NULL_TELEM)
		this->first_empty += 1;
}//BC: Theta(1) when first empty is on the first bucket
//WC: Theta(capacity): when we have the first empty on the last bucket


void Map::resize_rehash()
{
	int start_length = this->length;
	int start_m = this->m;
	this->m = this->m * 2;
	auto start_elements = new TElem[start_m];
	for (int i = 0; i < start_m; i++) {
		start_elements[i] = this->elements[i];

	}
	delete[] this->elements;
	this->elements = new TElem[this->m];
	delete[] this->next;
	this->next = new int[this->m];

	for (int i = 0; i < this->m; i++) {
		this->elements[i] = NULL_TELEM;
		this->next[i] = -1;
	}
	this->first_empty = 0;
	for (int i = 0; i < start_m; i++) {
		if (start_elements[i] != NULL_TELEM)
			add(start_elements[i].first, start_elements[i].second);

	}
	this->length = start_m;
	delete[] start_elements;
}
//Theta(capacity)
Map::Map() {
	this->m = 13;
	this->elements = new TElem[this->m];
	this->next = new int[this->m];
	for (int i = 0; i < this->m; i++) {
		this->elements[i] = NULL_TELEM;
		this->next[i] = -1;
	}
}
//Theta(capacity)

Map::~Map() {
	delete[] this->next;
	delete[] this->elements;
}
//Theta(1)

TValue Map::add(TKey c, TValue v) {
	TValue k = NULL_TVALUE;
	TElem temp;
	temp.first = c;
	temp.second = v;
	int hash_result = this->hash(c);
	if (this->elements[hash_result] == NULL_TELEM)
	{
		if (hash_result == first_empty)
			this->get_first_empty();
		this->elements[hash_result] = temp;
		this->next[hash_result] = -1;
		this->length++;
		//return NULL_TVALUE;
	}
	else {
		if (this->first_empty == this->m)
			this->resize_rehash();
		int current = hash_result;
		while (this->next[current] != -1 && this->elements[current].first != c) {
			current = this->next[current];
		}
		if (this->elements[current].first == c) {
			/*TValue aux = this->elements[current].second*/;
			k = this->elements[current].second;
			this->elements[current].second = v;
			//return aux;
		}

		else if (this->next[current] == -1) {
			this->elements[first_empty] = temp;
			this->next[this->first_empty] = -1;
			this->next[current] = this->first_empty;
			this->get_first_empty();
			this->length++;
		}
		
	}
	return k;
}
//BC:Theta(1): when we add on an empty bucket
//WC:Theta(nrElements): when all but one bucket are full
//TOTAL:O(nrElements)

	TValue Map::search(TKey c) const {

		int hash_result = this->hash(c);
		int current = hash_result;
		while (this->next[current] != -1 && this->elements[current].first != c)
			current = this->next[current];
		if (this->elements[current].first == c)
			return this->elements[current].second;
		return NULL_TVALUE;
	}//BC:Theta(1): if the key is alone in the bucket
	//WC:Theta(nrElements):if the key is linked to others
	//TOTAL:O(1)

	TValue Map::remove(TKey c) {
		TValue aux;
		int hash_result = this->hash(c);
		int current = hash_result;
		int prev = -1;
		while (current != -1 && this->elements[current].first != c)
		{
			prev = current;
			current = this->next[current];
		} //find the key to be removed, set its previous as well

		if (current == -1)
			return NULL_TVALUE;  //key doesnt exist
		else {
			//finding another key that hashes to current
			aux = this->elements[current].second;
			bool solved = false;  //becomes true when nothing hashes to current
			do {
				int pos = this->next[current]; //first pos to be checked
				int prev_pos = current;
				while (pos != -1 && this->hash(this->elements[pos].first) != current)
				{
					prev_pos = pos;
					pos = this->next[pos];
				}
				if (pos == -1)
					solved = true;
				else {//moves the element to the position to be deleted from
					this->elements[current] = this->elements[pos];
					prev = prev_pos; 
					current = pos;
				}

			} while (!solved);
			//remove key from position current
			if (prev == -1) {
				int i = 0;
				//check if current has any previous element
				while (i < this->m && prev == -1)
					if (this->next[i] == current) {
						prev = i;
					}
					else {
						i++;
					}

			}


			if (prev != -1)
				this->next[prev] = this->next[current];
			this->length--;
			this->elements[current] = NULL_TELEM;
			this->next[current] = -1;
			if (this->first_empty > current)
				this->first_empty = current;
		}
		return aux;
	}
	//BC:Theta(1):we remove a key that is alone in a bucket
	//WC:Theta(nrElems):we remove a key that has links to a lot more elements
	//TOTAL:O(nrElems):

	int Map::size() const {
		return this->length;
	}//Theta(1)

	bool Map::isEmpty() const {
		if (this->length == 0)
			return true;
		return false;
	}//Theta(1)

	MapIterator Map::iterator() const {
		return MapIterator(*this);
	}
	//Theta(1)
	void Map::replace(TKey k, TValue oldValue, TValue newValue)
	{
		int current = this->hash(k);
		while (this->next[current] != -1 && this->elements[current].first != k)
			current = this->next[current];
		if (this->elements[current].first == k && this->elements[current].second == oldValue)
			this->elements[current].second = newValue;
	}//BC:Theta(1): if the key (bucket) is alone in the bucket
	//WC:Theta(nrElements):if the key is linked to others 
	//TOTAL=O(nrElements)


