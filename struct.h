#include<stdlib.h>
#include<iostream>
#include<memory>
#include<algorithm>
#include<ostream>
#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "clvect.h"
#include "input.h"
#include<vector>

using namespace std;

class structure {
    vect<vect<unsigned short int>> R;
    vect<vect<unsigned short int>> C;
    vector<unsigned int> it;

    public:
        structure( ifstream& file ): file(file) {
            CSVRow row, row2;
            unsigned int n1 (0), numel_0 (0), numel_1 (0), numel_2 (0), temp(0);
            if(!file.good()) {
                cout<<"unsuccessful file loading"<<endl;
                return 1; //exception
            }else{
                R.n = 0;
                while(file >> row) {
                    if(R.n == 0){
                        it = read_first(row);
                        if(it.empty()){
                            cout<<"empty file"<<endl;
                            return 1; //exception
                        }
                        R.n += 1;
                    }
                    else {
                        n1 = 0;
                        R.tail_add(vect<unsigned short int> r);
                        for(int i = 0; i < row.size(); i++){
                            if (!row[i].empty()){
                                if (n1==0) {
                                    C.tail_add(vect<unsigned short int> c);
                                    C.n += 1;
                                    }
                                n1 += 1;
                                temp = stoi (row[i]);
                                if (temp == "0")
                                    numel_0 += 1;
                                else if (temp == "1")
                                    numel_1 += 1;
                                    C[C.n].tail_add(i);
                                    C[C.n].n += 1;
                                else if (temp == "2")
                                    numel_2 += 1;
                                    R[R.n].tail_add(i);
                                    R[R.n].n += 1;
                                else {
                                    cout<< "data is not a 0,1,2 valued matrix"<<endl;
                                    return 1; //exception
                                }
                            }
                        }
                        if( n1 != C.n && R.n>1) {
                            cout<<"data is not a matrix"<<endl;
                            return 1; //exception
                        }
                        C.n = n1;
                        R.n += 1;
                    }
                }
            }

            if (m == 1){
                    cout<<"empty matrix";
                    return 1; //exception
            }
            file.close();
            R.n = R.n - 1;
        }
};
