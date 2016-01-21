#ifndef struct_sparse_h
#define struct_sparse_h

#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "vect.h"
#include "input.h"

class struct_sparse{

    vect<vect<unsigned short int>> R;
    vect<vect<unsigned short int>> C;

    public:
        struct_sparse( unsigned int M, unsigned int N, ifstream& file): R(M),C(N) {
            unsigned int m(0),n(0),temp(0);
            CSVRow row;
            if(!file.good()) {
                cout<<"unsuccessful file loading";
                exit(1);
            }else{
                m = 0;
                while(file >> row) {
                        if(m==0)
                            m+=1;
                        else{
                            for(n = 0; n < row.size(); n++){
                                if (!row[n].empty()){
                                    temp = stoi(row[n]);
                                    if(temp==2)
                                        R[m-1].tail_add(n);
                                    if(temp==1)
                                        C[n].tail_add(m-1);
                                }
                            }
                            m +=1;
                        }
                    }
                }
                file.close();
        }
       unsigned int get_M (){
            return R.get_length();
        }
        unsigned int get_N (){
            return C.get_length();
        }
friend class move_sparse;
friend class output_sparse;
};

#endif
