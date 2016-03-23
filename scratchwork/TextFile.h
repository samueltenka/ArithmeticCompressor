class TextFile
{
private:
	int length;
	char* data;

	int index;

public:
	TextFile();
	TextFile(char* filename);
	void read_from(char* filename);
	void write_to(char* filename);
	void clear_data();
	~TextFile();

	void display();

	bool is_at_end();
	char next();
};
