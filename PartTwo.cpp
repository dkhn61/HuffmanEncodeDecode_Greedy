//
// Team 2: Ara, Gadipudi, Koravi, Li on 02/12/22.
//
// Part two program for Huffman Coding
#include "utility.h"
using namespace std;

class PartTwo {

const string codeTableFile = "codetable.txt";

const string frequencyFile = "freq.txt";

const string codedFile = "coded.txt";

const string decodedFile = "decoded.txt";

public:
    map<char, string> codes;
    // A Huffman tree node
    struct MinHeapNode {

        // One of the input characters
        char data;

        // Frequency of the character
        unsigned freq;

        // Left and right child
        MinHeapNode *left, *right;

        MinHeapNode(char data, unsigned freq) {

            left = right = NULL;
            this->data = data;
            this->freq = freq;
        }
    };

// For comparison of two heap nodes (needed in min heap)
    struct compare {

        bool operator()(MinHeapNode *l, MinHeapNode *r) {
            return (l->freq > r->freq);
        }
    };

    void storeCodesInMap(struct MinHeapNode *root, string str) {

        if (!root)
            return;

        if (root->data != '$'){
            codes[root->data] = str;
        }

        storeCodesInMap(root->left, str + "0");
        storeCodesInMap(root->right, str + "1");
    }

    MinHeapNode * encoded_top;

// The main function that builds a Huffman Tree
    void HuffmanCodes() {
        struct MinHeapNode *left, *right, *top;

        // Create a min heap & inserts all characters of data[]
        priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;


        std::ofstream file(codeTableFile);
        std::stringstream ss;

                ifstream myfile2(frequencyFile);
                unsigned freq = 0;
                if (myfile2.is_open())

                {
                    std::string exp;
                    while(std::getline(myfile2, exp)) {
                        std::istringstream input(exp);
                        char mychar;
                            std::string token;
                            int space = exp.find(" " , 0);
                            if(exp[0] =='L' && exp[1]=='F'){
                                mychar = '\n';
                                    string sub = exp.substr(3);
                                    freq = stoi(sub);
                            }
                            else if (space == 0){
                                mychar = ' ';
                                    string sub = exp.substr(2);
                                    freq = stoi(sub);
                            }
                            else {
                                input >> token;
                                std::stringstream str_stream(token);
                                str_stream >> mychar;

                                input >> token;

                                freq = stoi(token);
                            }
                            if(freq != 0){
                                minHeap.push(new MinHeapNode(mychar, freq));
                            }


                    }

                }

        // Iterate while size of heap doesn't become 1
        while (minHeap.size() != 1) {

            // Extract the two minimum
            // freq items from min heap
            left = minHeap.top();
            minHeap.pop();

            right = minHeap.top();
            minHeap.pop();

            // A new internal node with frequency equal to the sum of the two nodes frequencies. Placing the two extracted node as left and right children
            // of this new node. Adding this node to the min heap, '$' is a special value for internal nodes, not used
            top = new MinHeapNode('$', left->freq + right->freq);

            top->left = left;
            top->right = right;

            minHeap.push(top);
        }

        // the Huffman codes in a map
        storeCodesInMap(minHeap.top(), "");

        for (std::map<char, string>::iterator  v = codes.begin(); v != codes.end(); v++){
          //  Writing the huffman codes as string
          if(v->first == '\n')
          {
              file << "LF" << ' ' << v->second << endl;
          }
          else file << v->first << ' ' << v->second << endl;
        }
        encoded_top = minHeap.top();
    }

    void decoding_for_PartB(struct MinHeapNode* root) {

        ifstream myfile(codedFile);
        std::ofstream file(decodedFile);
        std::stringstream ss;

        string ans = "";
        struct MinHeapNode *curr = root;

        if (myfile.is_open()) {
            char mychar;
            while (myfile) {
                mychar = myfile.get();
                if (mychar == '0')
                    curr = curr->left;
                else
                    curr = curr->right;

                // reached leaf node
                if (curr->left == NULL and curr->right == NULL) {
                    file << curr->data;
                    ans += curr->data;
                    curr = root;
                }
            }
            cout<<endl;
            cout << "Decode through file as per Part Three-B : -" << endl;
            cout << ans + '\0' << endl;
        }
    }

};