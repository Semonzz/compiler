#include "Head.h"

#define CAPACITY 100000

HashTable::HashTable() {};

HashTable::HashTable(long long size){
		this->sz = size;
		this->items = new HT_item[sz];
		this->cnt = 0;
}

HashTable::~HashTable(){
		delete[] items;
}

void HashTable::Show(){
		for (long long i = 0; i<this->cnt; i++) this->items[i].Show();
}

int HashTable::hashFunc(const char* key) {
		int res = 0;
		for (int i = 0; i<sizeof(key); i++) res +=int(key[i]);
		return res % CAPACITY;
}

void HashTable::resize(){
		long long newSz = this->sz*2+1;
		HT_item* newArr = new HT_item[newSz];
		//memcpy(newArr, this->items, this->sz);
		this->items = newArr;
		this->sz = newSz;
}

void HashTable::insert(const char* key, const char* value){
		HT_item newItem(key, value);
		int ind = hashFunc(key);
		while(ind>=this->sz) this->resize();
		items[ind] = newItem;
}
		
