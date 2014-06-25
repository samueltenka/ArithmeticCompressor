#include "stdafx.h"
#include "Huffman.h"
#include <string>




BYTE Huffman::translate_mark()
{
	int c = 0;
	for(c; c < 256; c++)
	{
		// if frequency[c]/frequency[255] >= (mark-l)/(u-l)):
		if(frequency[c]*(u-l) >= (binary_mark-l)*frequency[255])
		{
			break;
		}
	}
	return c;	// this way, even if there's an error, still returns.
				// TODO: error-check!
}

bool Huffman::translation_is_determined()
{
	BYTE c = translate_mark();
	int l_count = c==0 ? 0 : frequency[c-1],
		u_count = frequency[c];
	// TODO: handle scaling stuff as in refine_interval!

	return l <= binary_mark-binary_jump && binary_mark+binary_jump < u;
}



// inefficient since lots of bits per translated character;
// turning loop "inside out" by going char-by-char instead of bit-by-bit
// might be faster.
string Huffman::produce(bool bit)
{
	string rtrn;
	while(translation_is_determined())	// TODO: for efficiency, 
										// use results of translate_mark() in
										// translation_is_determined()!
	{
		BYTE translated = translate_mark();
		rtrn += translated;
		refine_interval(translated);
		update_frequencies(translated);
	}

	move_mark(bit);

	return rtrn;
}

// TODO: clarify duality between this and coding.
