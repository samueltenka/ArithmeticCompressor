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
	while(	binary_jump < MIN_JUMP_LENGTH ||
			u-l < MIN_INTERVAL_LENGTH)
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
		rescale();
	}
	return rtrn;
}



void Huffman::update_frequencies(char c)
{
	for(int i = c; i <= 256; i++)
	{
		frequency[i] += 1;
	}
}

void Huffman::refine_interval(char c)
{
	int l_count = frequency[c],
		u_count = frequency[c+1];
	int total = frequency[255];

	long long int length = u-l;
	long long int old_l = l;
	l = old_l + length * l_count/total;
	u = old_l + length * u_count/total;
	// TODO: above might yield l==u, no detail.
	// so need to write a check whether
	// should scale up first. and act on it!
	// NOTE: rescale scales based on present
	// but need to scale based on future!

	rescale();
}

string Huffman::eat(char c)
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
