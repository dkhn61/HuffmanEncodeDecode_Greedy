/*
Team 2: Ara, Gadipudi, Koravi, Li
*/
#include "utility.h"
#include <unordered_map>
#include <bitset>

class PartFourB {

const string inputfile = "codedalt.txt";

const string outputfile = "decodedalt.txt";

const string tablefile = "codetable.txt";

public:
    void bit_level_decoding() {
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
        unordered_map<string, string> codetable;
        string chr;
        string code;
        while (getline(t_stream, chr, ' ')) {
            if (chr == "") {
                chr = " ";
                getline(t_stream, code, ' ');
                getline(t_stream, code);
            } else {
                getline(t_stream, code);
            }

            //cout << chr << " " << code << endl;
            codetable[code] = chr;
        }

        //decode the input file into the output file, without pulling the input file into memory
        char ch;
        int bit = 0;
        int ascii;
        //bitset<7> bits;
        string curr = "";
        string bitstring;
        fstream file(outputfile, fstream::in | fstream::out | fstream::trunc);
        int xxxx = 0;
        cout << "Decoded bit level as per Part FOUR-B : -" << endl;
        while (in_stream >> ch) {
            //the encoding is in high ascii characters to avoid carriage return, vertical tab, backspace, etc.
            bitset<7> bits(((int) ch) - 128);
            bitstring = bits.to_string();
            //cout << "bitstring " <<  bitstring << endl;
            for (int i = 0; i < 7; i++) {
                curr += bitstring[i];
                //cout << curr << endl;
                auto c = codetable.find(curr);
                if (c == codetable.end()) {
                    continue;
                }
                cout << to_string(xxxx++) << " " << c->second;
                if (c->second == "LF") {
                    file << (char) 10;
                } else {
                    file << c->second;
                }
                curr = "";
            }
        }
        file.close();
    }
};