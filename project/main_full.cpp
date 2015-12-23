#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include"output_matrix.h"
#include"move_matrix.h"

int main(){

    ifstream file("0.csv");
    if(!file.good()) {
        cout<<"unsuccessful file loading"<<endl;
        exit(1);
    }
    alloc parameters(file);
    file.open("problem.csv");
    unsigned int M(parameters.get_M()), N(parameters.get_N());
    unsigned short int s( M*N );
    // creo una classe struct_full
    vector<unsigned int> iterations (parameters.get_it());
    unsigned int cont(0),changes1(1),changes2(1);
    move_matrix step(0);
    output_matrix output;
    for (auto k = iterations.begin(); k != iterations.end(); ++k){
        while( cont<*k && changes1+changes2-changes1*changes2==1) {
            if(cont%2==0){
                step(s,"blue",M,N);
                changes1=step.get_changes();
            }
            if(cont%2==1){
                step(s,"red",M,N);
                changes2=step.get_changes();
            }
        cont++;
        }
        ofstream out;
        out.open(to_string(*k)+".csv");
        output(s,M,N,out);
        out.close();
    }

}
