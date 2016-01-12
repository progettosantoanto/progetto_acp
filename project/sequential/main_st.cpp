#include<iostream>
#include "vect.h"
#include "input.h"
#include "alloc.h"
#include "struct_sparse.h"
#include "timing.cpp"

int main(){
    timer t;
    t.start();
    const string filename("problem.csv");
    try{
        alloc parameters(filename);
        struct_sparse traffic_flow( parameters.get_M(), parameters.get_N(), filename);
        traffic_flow.play (parameters.get_it());
    } catch(exception &e) {
        cout<< "Error: "<<e.what()<<endl;
        return 1;
    }
    t.stop();

}
