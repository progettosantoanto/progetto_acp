#include<iostream>
#include "vect.h"
#include "input.h"
#include "alloc.h"
#include "struct_sparse.h"
#include "timing.h"

int main(){
    timer t;
    t.start();
    const string filename("problem.csv");
    alloc parameters(filename);
    //cout << parameters.get_sparsity() << endl;
    struct_sparse traffic_flow( parameters.get_M(), parameters.get_N(), filename);
    traffic_flow.play (parameters.get_it());
    t.stop();
}
