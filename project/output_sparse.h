#ifndef output_sparse_h
#define output_sparse_h

#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "vect.h"
#include "input.h"

class output_sparse{

public:
    ofstream operator () (struct_sparse& S, ofstream& out){
    unsigned int N(S.C.get_length()),M(S.R.get_length());

    int lr;
    for(int i=0;i<M;i++){
        lr = S.R[i].get_length();
        if(lr==0){
            for(int j=0;j<N-1;j++)
                out<<S.C[j].search(i)<<",";
            out<<S.C[N-1].search(i);
            }
        else if(lr==1){
            for(int j=0;j<S.R[i][0];j++)
                out<<S.C[j].search(i)<<",";
            if (S.R[i][0]!=N-1) {
                out<<2<<",";
                for(int j=S.R[i][0]+1;j<N-1;j++)
                    out<<S.C[j].search(i)<<",";
                out<<S.C[N-1].search(i);
            }
            else
                out<<2;
        }
        else{
            for(int j=0;j<S.R[i][0];j++)
                out<<S.C[j].search(i)<<",";
            for(int r=0;r<lr-1;r++){
                out<<2<<",";
                for(int j=S.R[i][r]+1;j<S.R[i][r+1];j++)
                    out<<S.C[j].search(i)<<",";
            }
            if (S.R[i][lr-1]!=N-1){
                out<<2<<",";
                for(int j=S.R[i][lr-1]+1;j<N-1;j++)
                    out<<S.C[j].search(i)<<",";
                out<<S.C[N-1].search(i);
                }
            else
                out<<2;
		}
        out<<endl;
    }
    out.close();
}

};

#endif
