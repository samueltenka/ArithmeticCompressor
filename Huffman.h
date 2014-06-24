#include "stdafx.h"
#include <iostream>
#include "Huffman.h"
using namespace std;


void HuffmanCoder::reset_frequencies()
{
	for(int c = 0; c <= 256; c++)
	{
		cumulative_freqs[c] = c;
	}
}

void HuffmanCoder::reset_intervals()
{
	lower = 0;
	upper = DETAIL;
	thresh = DETAIL/2;
	bin_inc = DETAIL/4;
}

HuffmanCoder::HuffmanCoder()
{
	reset_frequencies();
	reset_intervals();
}


void HuffmanCoder::update_frequencies(char chr)
{
	for(int c = static_cast<int>(chr)+1; c <= 256; c++) // start at chr's __successor__
	{
		cumulative_freqs[c] += 1;
	}
}


void HuffmanCoder::interval_to_binary(string* coded)
{
	bool is_0, is_1;
	while(	(is_0 = (upper < thresh)) ||
			(is_1 = (lower > thresh)))
	{
		if(is_0)
		{
			(*coded) += '0';
			thresh -= bin_inc;
			bin_inc /= 2;
		}
		else // is_1
		{
			(*coded) += '1';
			thresh += bin_inc;
			bin_inc /= 2;
		}

		while(bin_inc < BIN_DETAIL)
		{
			scale_and_shift();
		}
	}
}


void HuffmanCoder::scale_and_shift()
{
	// scale intervals
	lower *= 2;	// these scalings can be done on the order of 64 times for long long ints, right?
	upper *= 2;	// but minus 16, since everybody's at least on the order of 2^16, so really can only scale ~48 times.
	thresh *= 2;
	bin_inc *= 2;

	// shift them back to avoid overflow
	thresh -= lower;
	bin_inc -= 0; // since this is a vector, not a point.
	upper -= lower;
	lower -= lower; // TO OPTIMIZE:	lower==0 and upper==length, right? so can parameterize just in terms of length!
					//				except when this while loop is completely skipped... so maybe it's ok the way it is:
					//				it reshifts when the intervals get big, but otherwise doesn't worry
}


void HuffmanCoder::char_to_interval(char c) // optimized for clarity instead of speed, but yay for pretty good compilers!
{
	int l = cumulative_freqs[c], u = cumulative_freqs[c+1];
	int count = u-l;
	int total_count = cumulative_freqs[256];

	// ensure appropriately large intervals:
	long long int length;
	while(count*(length=upper-lower) < DETAIL*total_count)	// subinterval size will be (count/total_count)*length, so
															// this reads "while subinterval size < DETAIL:"
	{
		scale_and_shift();
	}

	// then modify intervals:
	thresh = thresh; // thresh is fixed, and the others slide until they exceed thresh
	upper = u*length/total_count + lower;
	lower = l*length/total_count + lower;
}


string HuffmanCoder::encode(string plain)
{
	string coded = "";
	reset_frequencies();
	reset_intervals();

	for(int i = 0; i < plain.length(); i++)
	{
		if(i%1000 == 0)
		{
			cout << i << endl;
		}
		char encode_me = plain[i];
		char_to_interval(encode_me);
		
		interval_to_binary();
		
		update_frequencies(encode_me);
	}

	return coded;
}

string HuffmanCoder::decode(string coded)
{
	string plain = "";
	reset_frequencies();
	reset_intervals();

	for(int i = 0; i < plain.length(); i++)
	{
		if(i%1000 == 0)
		{
			cout << i << endl;
		}
		char encode_me = plain[i];
		char_to_interval(encode_me);
		
		interval_to_binary();
		
		update_frequencies(encode_me);
	}

	return plain;
}
