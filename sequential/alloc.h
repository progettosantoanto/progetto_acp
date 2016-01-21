#ifndef alloc_h
#define alloc_h

#include<iostream>
#include<algorithm>
#include"input.h"

using namespace std;

class alloc{
    unsigned int M;
    unsigned int N;
    vector <unsigned int> it;
    float sparsity;
    public:

        alloc(const string& filename) {
            unsigned int n (0), m (0), n1 (0), num_0 (0), num_cars (0);
            int temp;
            try {
                ifstream file(filename);
                if( !file.good() ) {
                    throw runtime_error("unsuccessful file loading");
                }else{
                CSVRow row;
                while(file >> row) {
                    if(m == 0){
                        try {
                            for(int i = 0; i < row.size(); i++){
                                if ( !row[i].empty() ){
                                    temp = stoi(row[i]);
                                    if (temp < 0)
                                        throw runtime_error("negative iterations");
                                    it.push_back(temp);
                                }
                            }
                            if ( it.empty() ) {
                                throw runtime_error("empty file");
                            }
                            sort(it.begin(),it.end());
                            it.erase(unique(it.begin(),it.end()), it.end());
                            m += 1;
                        } catch ( runtime_error& e) {
                            cerr << "Exception occurred in the first line: " << e.what() << endl;
                        }
                    }else {
                        n1 = 0;
                        for(int i = 0; i < row.size(); i++){
                            if (!row[i].empty()){
                                n1 += 1;
                                if (row[i] == "0") {
                                    num_0 += 1;
                                } else if ( (row[i] == "1") || (row[i] == "2") ){
                                    num_cars += 1;
                                } else {
                                    throw runtime_error ("data is not a 0,1,2 valued matrix");
                                }
                            }
                        }
                    if( n1 != n && m>1) {
                        throw runtime_error ("data is not a matrix");
                    }
                    n = n1;
                    m += 1;
                    }
                }
            }
                if (m == 1){
                    throw runtime_error ("empty matrix");
                }
            file.close();
            } catch ( exception &e ) {
                cerr << "Exception occurred: " << e.what() << endl;
            }
            M = m-1;
            N = n;
            sparsity = (float) num_0 / (num_0 + num_cars);
        }

        unsigned int get_M(){
            return M;
        }

        unsigned int get_N(){
            return N;
        }

        vector<unsigned int>& get_it(){
            return it;
        }

        float get_sparsity() {
            return sparsity;
        }

};

#endif
