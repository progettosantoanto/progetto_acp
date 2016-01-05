#ifndef STRUCT_MATRIXBIS_H_H
#define STRUCT_MATRIXBIS_H_H

#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "input.h"

class struct_matrixBIS{

    unsigned int M;
    unsigned int N;
    vector<unsigned short int> s;
    vector<unsigned int> it;
    float sparsity;

    public:

       struct_matrixBIS(ifstream& file, ifstream& file2) {
            unsigned int n (0), m (0), n1 (0), numel_0 (0), numel_1 (0), numel_2 (0);
            if(!file.good()) {
                exit(1);
            }else{
            CSVRow row;
            while(file >> row) {
                if(m == 0){
                    it = read_first(row);
                    if(it.empty()){
                        //cout<<"empty file"<<endl;
                        exit(1);
                    }
                m += 1;
                }
                else {
                    n1 = 0;
                    for(int i = 0; i < row.size(); i++){
                        if (!row[i].empty()){
                            n1 += 1;
                        if (row[i] == "0")
                           numel_0 += 1;
                        else if (row[i] == "1")
                            numel_1 += 1;
                        else if (row[i] == "2")
                            numel_2 += 1;
                        else {
                            //cout<< "data is not a 0,1,2 valued matrix"<<endl;
                            exit(1);
                            }
                        }
                    }
                if( n1 != n && m>1) {
                    //cout<<"data is not a matrix"<<endl;
                    exit(1);
                }
                n = n1;
                m += 1;
                }
            }
        }
                if (m == 1){
                    //cout<<"empty matrix";
                    exit(1);
                }
        file.close();
        struct_matrixBIS::M = m-1;
        struct_matrixBIS::N = n;
        float zeros(numel_0);
        sparsity = zeros / (numel_0+numel_1+numel_2);
        vector<unsigned short int> s(M*N);
        m=0; n=0;
        unsigned int temp(0), i(0);
        CSVRow row2;
            if(!file2.good()) {
                cout<<"unsuccessful file loading";
                exit(1);
            }else{
                while(file2 >> row2) {
                    if(m==0)
                        m+=1;
                    else {
                        for (int j=0; j<N; j++){ //scorro le colonne di una riga
                            if(!row2[j].empty()){
                                s[i+j] = stoi(row2[j]);
                            }
                        }
                    m +=1;
                    i += N;
                    }
                }
            }
            file2.close();
        struct_matrixBIS::s = s;
        }

       vector<unsigned int> get_it(){
            return it;
        }

      vector<unsigned short int> get_s(){
            return s;
        }

        unsigned short int move_matrix_blue ( ) {
            unsigned short int flag,changes(0);
            unsigned int i(0), j(0),eov(M*N);
            for(int j = 0; j < N; j++){
                i=j;
                flag = (s[i] == 0) && (s[i+eov-N] == 1);//si accende solo se devo spostare l'elemento
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
                    s[i]=1;
                    s[i+eov-N]=0;
                    if (changes==0)
                        changes=1;
                }
            }
        return changes;
        }

       unsigned short int move_matrix_red ( ){
            unsigned short int flag,changes(0);
            unsigned int i(0), j(0),eov(M*N);
            while( i < eov-N+1 ){
                j = i;
                flag = (s[j] == 0) && (s[j+N-1] == 2) ; //si accende solo se devo spostare l'elemento
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
                s[j]=2;
                s[j+N-1]=0;
                if (changes==0)
                    changes=1;
            }
        i += N;
        }
    return changes;
    }

    void output_mat (ofstream& out){
          unsigned int i(0), eov(M*N);
            while(i<eov){
                for (int j=0; j<N-1; j++)
                    out << s[i+j] << ",";
                out<<s[i+N-1]<<endl;
                i += N;
            }
            out.close();
        }

};

#endif // STRUCT_MATRIXBIS_H_H
