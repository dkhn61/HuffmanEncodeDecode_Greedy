#include "utility.h"
#include "PartOne.cpp"
#include "PartThree.cpp"
#include "PartTwo.cpp"
#include "PartFourA.cpp"
#include "PartFourB.cpp"
#define SIZE 128

int main() {

    PartOne p1;
    PartTwo p2;
    PartThree p3;
    int freq[SIZE]= {0 };
    p1.partOneFreqCounting(freq);

    for(int i=0 ; i< 128; i++)
    {
        cout <<  freq[i]  << " ";
    }
    cout<<endl;
    p1.partOneAsciiSort(freq);

    p2.HuffmanCodes();
    p3.partThreeA();
    p2.decoding_for_PartB(p2.encoded_top);

    PartFourA four_a;
    four_a.bit_level_encoding();
    PartFourB four_b;
    four_b.bit_level_decoding();

    return 0;
}


