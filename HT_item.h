#pragma once

class HT_item{
private:
		char* key;
		char* value;
public:
		HT_item();
		HT_item(char* key, char* value);
		HT_item(const char* key, const char* value);

		char* getKey();

		void operator=(HT_item &other);

		void Show();

		~HT_item();
};
