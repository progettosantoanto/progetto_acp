#ifndef OUTPUT_MATRIX_H
#define OUTPUT_MATRIX_H

#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "vect.h"
#include "input.h"

class output_matrix
{
    public:
        void operator () (unsigned short int s[], unsigned int M, unsigned int N, ofstream& out) {
            unsigned int i=0, eov(M*N);
            while(i<eov){
                for (int j=0; j<N-1; j++)
                    out << s[i+j] << ",";
                out<<s[i+N-1]<<endl;
                i += N;
            }
            out.close();
        }

};

#endif // OUTPUT_MATRIX_H
