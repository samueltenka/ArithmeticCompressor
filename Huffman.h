#include <iostream>
using namespace std;

#define PRINT(X) {cout << X << endl;}
#define PRINTL(L, X) {cout << L << ": " << X << endl;}

#define MIN_INTERVAL_LENGTH 65536
#define MIN_JUMP_LENGTH (MIN_INTERVAL_LENGTH/4)


// actually arithmetic compressor
class Huffman
{
private:
	int frequency[256];	// c.d.f. up to i, inclusive.
						// so frequency[255] = total count

	// arithmetic interval info:
	long long int binary_mark;
	long long int binary_jump;
	long long int l, u;

	bool mark_is_accurate();
	void rescale();
	void rescale_as_needed();

	char split_binary();
	string refine_binary();

	void update_frequencies(unsigned char c);
	void refine_interval(unsigned char c);
	
	void check();
public:
	Huffman();

	string eat(unsigned char c);
};
