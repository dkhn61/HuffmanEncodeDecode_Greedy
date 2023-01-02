//
// Team 2: Ara, Gadipudi, Koravi, Li on 02/12/22.
//
#include "utility.h"
#define SIZE 128

class PartOne{

const string filename = "clear.txt";

public:
    void partOneFreqCounting(int * freq){
        ifstream myfile(filename);

        if (myfile.is_open())
        {
            char mychar;
            while ( myfile ) {
                mychar = myfile.get();
                //std::cout << mychar;
                int N =  static_cast <int>(mychar);
                ++freq[N];
            }
            myfile.close();
        }
        else{
            cout << "unable to find input file" <<endl;
            exit(1);
        }
    }

    void partOneAsciiSort(int * freq){

        string fileToWrite = "freq.txt";
        std::ofstream file(fileToWrite);
        std::stringstream ss;

        if (file.is_open())
        {
            for(int i=0; i< SIZE; i++)
            {
                // char charvalue = static_cast <char>(i);
                char charvalue = char(i);
                if(i == 10) file << "LF" << " " << freq[i] << endl;

                else file << charvalue << " " << freq[i] << endl;

            }

        }
        else std::cout << "unable to find freq.txt file to write the frequency counts !\n";


    }
};