#pragma once

#include "Head.h"

class HashTable{
private:
		HT_item* items;
		long long sz, cnt;
public:
		HashTable();
		HashTable(long long size);
		void Show();
		void insert(const char* key, const char* value);
		~HashTable();
private:
		int hashFunc(const char* key);
		void resize();
};
