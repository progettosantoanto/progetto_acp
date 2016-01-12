#ifndef alloc_h
#define alloc_h

#include<iostream>
#include<vector>
#include "vect.h"
#include "input.h"

using namespace std;

class alloc{
    unsigned int M;
    unsigned int N;
    vector<unsigned int> it;
    float sparsity;
    public:

        alloc(ifstream& file) {
            unsigned int n (0), m (0), n1 (0), numel_0 (0), numel_1 (0), numel_2 (0);
            if(!file.good()) {
                exit(1);
            }else{
            CSVRow row;
            while(file >> row) {
                if(m == 0){
                    it = read_first(row);
                    if(it.empty()){
                        //cout<<"empty file"<<endl;
                        exit(1);
                    }
                m += 1;
                }
                else {
                    n1 = 0;
                    for(int i = 0; i < row.size(); i++){
                        if (!row[i].empty()){
                            n1 += 1;
                        if (row[i] == "0")
                           numel_0 += 1;
                        else if (row[i] == "1")
                            numel_1 += 1;
                        else if (row[i] == "2")
                            numel_2 += 1;
                        else {
                            //cout<< "data is not a 0,1,2 valued matrix"<<endl;
                            exit(1);
                            }
                        }
                    }
                if( n1 != n && m>1) {
                    //cout<<"data is not a matrix"<<endl;
                    exit(1);
                }
                n = n1;
                m += 1;
                }
            }
        }
                if (m == 1){
                    //cout<<"empty matrix";
                    exit(1);
                }
        file.close();
        M = m-1;
        N = n;
        float zeros(numel_0);
        sparsity = zeros / (numel_0+numel_1+numel_2);
        }



        unsigned int get_M(){
            return M;
        }

        unsigned int get_N(){
            return N;
        }

        vector<unsigned int> get_it(){
            return it;
        }

        float get_sparsity(){
            return sparsity;
        }

};

#endif
