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

	//string lorem = "Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, \
				   totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. \
				   Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, \
				   sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. \
				   Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, \
				   sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. \
				   Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? \
				   Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, \
				   vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?";

	// compress it
	string shorter;
	Huffman H;
	PRINTL("lorem ~#pages", lorem.length()/(6*500));
	for(int n = 0; n < lorem.length(); n++)
	{
		//if(n>205634) //n%205635 == 0)
		//{
		//	PRINT(n)
		//	H.X = true;
		//}
		shorter += H.eat(lorem[n]);
	}
	PRINT("YEAH!")
	//PRINTL("shorter", shorter)
	PRINTL("lorem bits", lorem.length()*8);
	PRINTL("shorter bits", shorter.length());

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
