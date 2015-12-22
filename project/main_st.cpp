#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "vect.h"
#include "input.h"
#include "alloc.h"
#include "struct_sparse.h"
#include "move_sparse.h"
#include "output_sparse.h"

int main(){

    ifstream file("problem.csv");
    if(!file.good()) {
        cout<<"unsuccessful file loading"<<endl;
        exit(1);
    }
    alloc parameters(file);
    file.open("problem.csv");
    struct_sparse traffic_flow( parameters.get_M(), parameters.get_N(), file);
    vector<unsigned int> iterations (parameters.get_it());
    unsigned int cont(0),changes1(1),changes2(1);
    move_sparse step(0);
    output_sparse output;
    for (auto k = iterations.begin(); k != iterations.end(); ++k){
        while( cont<*k && changes1+changes2-changes1*changes2==1) {
            if(cont%2==0){
                step(traffic_flow,"blue");
                changes1=step.get_changes();
            }
            if(cont%2==1){
                step(traffic_flow,"red");
                changes2=step.get_changes();
            }
        cont++;
        }
        ofstream out;
        out.open(to_string(*k)+".csv");
        output(traffic_flow,out);
        out.close();
    }

}
