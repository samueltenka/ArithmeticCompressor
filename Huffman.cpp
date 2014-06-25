#include "stdafx.h"
#include "Huffman.h"
#include <string>



Huffman::Huffman()
{
	binary_mark = MIN_INTERVAL_LENGTH/2;
	binary_jump = MIN_INTERVAL_LENGTH/4;
	l = 0; u = MIN_INTERVAL_LENGTH;

	for(int i = 0; i < 256; i++)
	{
		frequency[i] = i+1;
	}
}



bool Huffman::mark_is_accurate()
{
	return l<=binary_mark && binary_mark<u;
}

void Huffman::rescale()
{
	binary_mark *= 2;
	binary_jump *= 2;
	u *= 2;
	l *= 2;
	//PRINTL("binjmp", binary_jump)

	binary_mark -= l;
	u -= l;
	l -= l; // shift the interval: [u, l] --> [0, u-l]
}

void Huffman::rescale_as_needed()
{
	while(	binary_jump < MIN_JUMP_LENGTH ||
			u-l < MIN_INTERVAL_LENGTH)
	{
		rescale();
	}
}


char Huffman::split_binary()
{
	int direction = binary_mark<l ? +1 : -1;
	binary_mark += direction * binary_jump;
	binary_jump /= 2;

	return direction==+1 ? '1' : '0';
}

string Huffman::refine_binary()
{
	string rtrn;
	while(!mark_is_accurate())
	{
		rtrn += split_binary(); // a single halving of detail
		rescale_as_needed();
	}
	return rtrn;
}



void Huffman::update_frequencies(unsigned char c)
{
	for(int i = c; i <= 256; i++)
	{
		frequency[i] += 1;
	}
}

void Huffman::refine_interval(unsigned char c)
{
	int l_count = c==0 ? 0 : frequency[c-1],
		u_count = frequency[c];
	int total = frequency[255];

	while((u-l) * total < MIN_INTERVAL_LENGTH * (u_count-l_count)) // if length*prob < MIN_INT_LEN
	{
		rescale();
	}

	long long int length = u-l;
	long long int old_l = l;
	l = old_l + length * l_count/total;
	u = old_l + length * u_count/total;

	rescale_as_needed();
}

string Huffman::eat(unsigned char c)
{
	refine_interval(c);
	update_frequencies(c);	// needs to be after, since decoder needs to first process
							// interval to figure out character and from there how
							// to update frequency table.

	return refine_binary(); // get rtrn string from this!!
}

// i'd sorta like it more symmetrical:
//
// the refine interval part would be
// while(mark_is_accurate())
// {
//   . . .
// }



void Huffman::check()
{
	if(	binary_jump <= 0 ||
		u <= l)
	{
		PRINTL("bm", binary_mark);
		PRINTL("bj", binary_jump);
		PRINTL("u", u);
		PRINTL("l", l);
		char l; cin >> l;
	}
}
