#include "Head.h"

HT_item::HT_item(){
		key = nullptr;
		value = nullptr;
}

HT_item::HT_item(char* key, char* value){
		this->key = new char[sizeof(key)];
		this->value = new char[sizeof(value)];
		strcpy(this->value, value);
		strcpy(this->key, key);
}

HT_item::HT_item(const char* key, const char* value){
		this->key = new char[sizeof(key)];
		this->value = new char[sizeof(value)];
		strcpy(this->value, value);
		strcpy(this->key, key);
}

void HT_item::Show(){
		std::cout<<key<<"    "<<value<<"\n";
}

HT_item::~HT_item(){
		delete[] key;
		delete[] value;
}

char* HT_item::getKey(){
		return this->key;
}

void HT_item::operator=(HT_item &other){
		this->key = new char[sizeof(other.getKey())];
		this->value = new char[sizeof(other.value)];
		strcpy(this->key, other.key);
		strcpy(this->value, other.value);
}
