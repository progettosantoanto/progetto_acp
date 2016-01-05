#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include"struct_matrixBIS.h"
#include"input.h"

int main(){

    ifstream file("problemino.csv"),file2("problemino.csv");
    if(!file.good()) {
        cout<<"unsuccessful file loading"<<endl;
        exit(1);
    }
    struct_matrixBIS traffic_flow(file,file2);
    vector<unsigned int> iterations (traffic_flow.get_it());
    unsigned short int cont(0),changes1(1),changes2(1);

    for (auto k = iterations.begin(); k != iterations.end(); ++k){
        cout<<*k<<endl;
        while( cont<*k && changes1+changes2-changes1*changes2==1) {
            cout<<cont<<endl;
            if(cont%2==0){
                changes1 = traffic_flow.move_matrix_blue();
            }
            else{
                changes2 = traffic_flow.move_matrix_red();
            }
            cont++;
            cout<<changes1<<","<<changes2<<endl;
        }
        ofstream out;
        out.open(to_string(*k)+".csv");
        traffic_flow.output_mat(out);
    }
}
