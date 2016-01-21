#ifndef struct_matrix_h
#define struct_matrix_h

#include<iostream>
#include<algorithm>
#include "input.h"

class struct_matrix{

    unsigned int M;
    unsigned int N;
    vector<unsigned short int> s;


    public:
        struct_matrix( unsigned int M, unsigned int N, const string& filename): M(M),N(N),s(M*N) {
            unsigned int m(0),i(0);
            CSVRow row;
            ifstream file(filename);
            if(!file.good()) {
                throw runtime_error("unsuccessful file loading");
            }else{
                while(file >> row) {
                    if(m==0)
                        m+=1;
                    else {
                        for (int j=0; j<N; j++){
                            if(!row[j].empty()){
                                s[i+j] = stoi(row[j]);
                            }
                        }
                    m +=1;
                    i += N;
                    }
                }
            }
            file.close();
        }

        unsigned short int move_matrix_blue () {
            unsigned short int flag,changes(0);
            unsigned int i(0),eov(M*N);
            for(int j = 0; j < N; j++){
                i=j;
                flag = (s[i] == 0) && (s[i+eov-N] == 1);
                while(i < j+eov-N) {
                    if (s[i+N]==0) {
                        if (s[i] == 1){
                            s[i] = 0;
                            s[i+N] = 1;
                            i += 2*N;
                            if (changes==0)
                                changes=1;
                        }
                        else {
                            i += 2*N;
                        }
                    }else {
                        i += s[i+N]*N;
                    }
                }
                if (flag==1){
                    s[j]=1;
                    s[j+eov-N]=0;
                    if (changes==0)
                        changes=1;
                }
            }
        return changes;
        }

       unsigned short int move_matrix_red (){
            unsigned short int flag,changes(0);
            unsigned int i(0),j(0),eov(M*N);
            while( i < eov-N+1 ){
                j = i;
                flag = (s[j] == 0) && (s[j+N-1] == 2);
                while(j < i+N-1) {
                    if (s[j+1]==0) {
                        if (s[j] == 2){
                            s[j] = 0;
                            s[j+1] = 2;
                            j += 2;
                            if (changes==0)
                                changes=1;
                        }
                        else {
                            j += 2;
                        }
                    }else{
                    j += (3-s[j+1]);
                    }
                }
            if (flag==1){
                s[i]=2;
                s[i+N-1]=0;
                if (changes==0)
                    changes=1;
            }
        i += N;
        }
    return changes;
    }

    void output (unsigned int cont){
        unsigned int i(0), eov(M*N);
        ofstream out;
        out.open(to_string(cont)+".csv");
        while(i<eov){
            for (int j=0; j<N-1; j++)
                out << s[i+j] << ",";
            out<<s[i+N-1]<<endl;
            i += N;
            }
        out.close();
    }

    void play (vector <unsigned int>& iterations ) {
        unsigned int cont(0),changes1(1),changes2(1);
        if (*iterations.begin()==0) {
            output(0);
        }
        for (auto k = iterations.begin(); k != iterations.end(); ++k){
            while( cont<*k && changes1+changes2-changes1*changes2==1) {
                if(cont%2==0){
                    changes1=move_matrix_blue();
                }
                if(cont%2==1){
                    changes2=move_matrix_red();
                }
            cont++;
            }
            output(cont);
        }
    }
};

#endif
