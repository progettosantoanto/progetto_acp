#ifndef alloc_h
#define alloc_h

#include<iostream>
#include<algorithm>

using namespace std;

class alloc{
    unsigned int M;
    unsigned int N;
    vector<unsigned int> it;
    float sparsity;
    public:

        alloc(const string& filename) {
            unsigned int n (0), m (0), n1 (0), numel_0 (0), numel_1 (0), numel_2 (0), temp;
            ifstream file(filename);
            if(!file.good()) {
                throw runtime_error("unsuccessful file loading");
            }else{
            CSVRow row;
            while(file >> row) {
                if(m == 0){
                    for(int i = 0; i < row.size(); i++){
                        if (!row[i].empty()){
                            temp = stoi(row[i]);
                            if (temp<0)
                                throw runtime_error("negative iterations");
                            it.push_back(temp);
                        }
                    }
                    if(it.empty()){
                        throw runtime_error("empty file");
                    }
                    sort(it.begin(),it.end());
                    it.erase(unique(it.begin(),it.end()), it.end());
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
                    throw runtime_error("empty matrix");
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
