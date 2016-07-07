#include <iostream>
#include <sstream>
#include <fstream>
#include <string> 
#include <stdlib.h>
#include "bitChar.cpp"
using namespace std;


int main()
{
	ofstream outf("Sample.dat");
	ifstream inf("Sample.dat");

	string enCoded = "101000001010101010";

	//write to file
	cout << enCoded << endl ; //print  101000001010101010
	bitChar bchar;
	bchar.setBITS(enCoded);
	bchar.insertBits(outf);

	//read from file
	string decoded =bchar.readByBits(inf);
	cout << decoded << endl ; //print 101000001010101010000000
	return 0;
}
