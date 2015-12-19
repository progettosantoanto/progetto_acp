#include<stdlib.h>
#include<iostream>
#include<memory>
#include<algorithm>
#include<ostream>
#include<fstream>
#include<math.h>
#include "clvect.h"

using namespace std;

class structure {
    vect<vect<unsigned short int>> R;
    vect<vect<unsigned short int>> C;

    public:
        structure( vect<vect<unsigned short int>> R, vect<vect<unsigned short int>> C ) {
            unsigned int m( R.get_length() );
            for (int i=0; i<m; i++){
                structure::R.tail_add(R[i]);
            }
            unsigned int n( C.get_length() );
            for (int i=0; i<m; i++){
                structure::C.tail_add(C[i]);
            }
        };
};
