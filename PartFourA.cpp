/*
Team 2: Ara, Gadipudi, Koravi, Li
*/
#include "utility.h"
#include <bitset>
class PartFourA {

const string inputfile = "clear.txt";

const string outputfile = "codedalt.txt";

const string tablefile = "codetable.txt";

public:

void bit_level_encoding()
{
	//default to the file being in the same directory and called this
	string ifilename = inputfile;
	string tfilename = tablefile;

	fstream in_stream(ifilename);
	if (in_stream.fail()) {
		std::cout << "Error message: No " << ifilename << " file.";
		exit(1);
	}

	fstream t_stream(tfilename);
	if (t_stream.fail()) {
		std::cout << "Error message: No " << tfilename << " file.";
		exit(1);
	}

	//Read the codetable file
	string codetable[128];
	string chr;
	string code;
	while (getline(t_stream, chr,' ')) {
		if (chr == "") {
			chr = ' ';
			getline(t_stream, code, ' ');
			getline(t_stream, code);
		}
		else {
			getline(t_stream, code);
		}

		//cout << chr << " " << code << endl;
		if (chr == "LF") {
			codetable[10] = code;
		}
		else {
			codetable[(int)chr[0]] = code;
		}
	}

	//encode the input file into the output file, without pulling the input file into memory
	char ch;
	int bit = 6;
	bitset<7> bits;
	char ascii;
	fstream file(outputfile, fstream::in | fstream::out | fstream::trunc);
	while (in_stream >> noskipws >> ch) {
		code = codetable[(int)ch];

		for (int i = 0; i < code.length(); i++) {
			if (bit < 0) {
				ascii = char(bits.to_ulong() + 128);  //the encoding is in high ascii characters to avoid carriage return, vertical tab, backspace, etc.
				//cout << "a:" << ascii << " " << bits.to_string() << " " << bits.to_ulong() << " " << bit << endl;
				file << ascii;
				bits.reset();
				bit = 6;
			}

			bits.set(bit--, code[i] == '1');
			//cout << "b:" << bit << " i:" << i << " o:" << code[i] << endl;
		}
	}

	//take care of possible last character trouble
	ascii = char(bits.to_ulong() + 128);
	file << ascii;
	//cout << "z: " << bit << " " << ascii << " " << bits.to_ulong() << " " << bits.to_string() << endl;
	file.close();

}
};