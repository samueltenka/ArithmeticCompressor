// Compressor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Huffman.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


#define PAUSE {char l; cin >> l;}


int _tmain(int argc, _TCHAR* argv[])
{
	// load a very large file
	string lorem;
	ifstream myfile("C:\\Users\\Sam\\Desktop\\Compressor\\GenesisAsciified.txt");
	while(myfile)
	{
		lorem += myfile.get();
	}
	myfile.close();
	//string lorem = "why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there \
				   why hello there why hello there why hello there why hello there why hello there";

	// compress it
	string shorter;
	Huffman H;
	for(int n = 0; n < lorem.length(); n++)
	{
		if(n%1000 == 0)
			PRINT(n)
		shorter += H.eat(lorem[n]);
	}
	PRINT("YEAH!")
	//PRINTL("shorter", shorter)
	PRINTL("lorem length", lorem.length()*8);
	PRINTL("shorter length", shorter.length());

	// write


	PAUSE
	return 0;
}










/*	ifstream gen_in("C:\\Users\\Sam\\Desktop\\Compressor\\Genesis.txt");
	ofstream gen_out("C:\\Users\\Sam\\Desktop\\Compressor\\GenesisAsciified.txt");
	for(int i = 0; gen_in; i++)
	{
		gen_out.put(gen_in.get());
	}
	gen_out.close();
	gen_in.close();
*/
