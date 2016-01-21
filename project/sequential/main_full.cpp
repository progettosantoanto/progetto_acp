#include<iostream>
#include"struct_matrix.h"
#include"timing.cpp"
#include"alloc.h"

int main(){
    timer t;
    t.start();
    const string filename("problem.csv");
    try{
        alloc parameters(filename);
        struct_matrix traffic_flow( parameters.get_M(), parameters.get_N(), filename);
        traffic_flow.play (parameters.get_it());
    } catch(exception &e) {
        cout<< "Error: "<<e.what()<<endl;
        return 1;
    }
    t.stop();

}
