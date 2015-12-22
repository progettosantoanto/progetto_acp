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

#define maxr 300
#define maxc 300

typedef  int mat[maxr][maxc];

class output_matrix
{
    public:
        ofstream operator () (mat s, unsigned int M, unsigned int N, ofstream& out) {

            for(int i=0;i<M;i++){
                for(int j=0;j<N-1;j++){
                    out << s[i][j] << ",";
                }
            out<<s[i][N-1]<<endl;
            }
            out.close();
        }

};

#endif // OUTPUT_MATRIX_H
