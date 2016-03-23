#include "stdafx.h"
#include "TextFile.h"
#include <iostream> // for TextFile::display and debugging
#include <fstream>
using namespace std;


TextFile::TextFile()
{
}

TextFile::TextFile(char* filename)
{
	read_from(filename);
}

void TextFile::read_from(char* filename)
{
	clear_data();

	length = 0;
	ifstream myfile(filename);
	while(myfile)
	{
		myfile.get();
		length++;
	}
	myfile.close();
	data = new char[length];
	length -= 1; // since last character is EOF, automatically included.

	myfile.open(filename);
	for(int i = 0; myfile; i++)
	{
		data[i] = myfile.get();
	}
	myfile.close();
}
void TextFile::write_to(char* filename)
{
	ofstream myfile(filename);
	for(int i = 0; i < length; i++)
	{
		myfile.put(data[i]);
	}
	myfile.close();
}


void TextFile::clear_data()
{
	delete[] data;
}

TextFile::~TextFile()
{
	clear_data();
}


void TextFile::display()
{
	cout << length << endl;
	for(int i = 0; i < length; i++)
	{
		cout << data[i];
	}
	cout << endl << "*" << endl;
}


bool TextFile::is_at_end()
{
	return index==length;
}
char TextFile::next()
{
	return data[index++];
}
