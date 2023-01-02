//
// Team 2: Ara, Gadipudi, Koravi, Li on 02/12/22.
//
#include "utility.h"

class PartThree{

const string filename = "clear.txt";

const string codedFile = "coded.txt";

const string filename_read_codes = "codetable.txt";

public:
    void partThreeA(){
        ifstream myfile(filename);
        std::ofstream file(codedFile);
        std::stringstream ss;

        if (myfile.is_open())
        {
            char mychar;
            while ( myfile ) {
                mychar = myfile.get();
                string str;
                str+=mychar;
                ifstream myfile2(filename_read_codes);
                if (myfile2.is_open())

                {
                    std::string exp;
                    while(std::getline(myfile2, exp)){

                        std::istringstream input(exp);
                        int space = exp.find(" " , 0);

                        std::string token;

                        if(str == " " && space == 0){

                            // cout << str << ":";
                            input >> token;
                            //cout << " "<< token;
                            file << token;
                            break;

                        }
                        else if(str == "\n"){
                            // cout << str << ":";
                            input >> token;
                            input >> token;
                            //cout << " "<< token;
                            file << token;
                            break;
                        }
                        while (!input.eof ())
                        {
                            input >> token;
                            if (token == str){
                                input >> token;
                                //writing to coded.txt file
                                file << token;
                                break;
                            }
                        }
                        if(token == str) break;
                    }

                }
                else{
                    cout << "unable to find input file" <<endl;
                    exit(1);
                }

            }
            myfile.close();
        }
        else{
            cout << "unable to find input file" <<endl;
            exit(1);
        }
    }


};