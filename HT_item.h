class HT_item{
private:
		char* key;
		char* value;
public:
		HT_item();
		HT_item(char* key, char* value);
		HT_item(const char* key, const char* value);

		void Show();

		~HT_item();
};
