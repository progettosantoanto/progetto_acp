#ifndef struct_sparse_h
#define struct_sparse_h

#include<iostream>
#include "vect.h"
#include "input.h"

class struct_sparse{

    vect<vect<unsigned short int>> R;
    vect<vect<unsigned short int>> C;

    public:
        struct_sparse( unsigned int M, unsigned int N, const string& filename): R(M),C(N) {
            unsigned int m(0),n(0),temp(0);
            CSVRow row;
            ifstream file(filename);
            if(!file.good()) {
                throw runtime_error("unsuccessful file loading");
            }else{
                m = 0;
                while(file >> row) {
                        if(m==0)
                            m+=1;
                        else{
                            for(n = 0; n < row.size(); n++){
                                if (!row[n].empty()){
                                    temp = stoi(row[n]);
                                    if(temp==2)
                                        R[m-1].tail_add(n);
                                    if(temp==1)
                                        C[n].tail_add(m-1);
                                }
                            }
                            m +=1;
                        }
                    }
                }
                file.close();
        }

    unsigned short int move_blue () {
        unsigned short int flag,changes(0);
        unsigned int l;
        unsigned int N(C.get_length()), M(R.get_length());
        for(int j = 0; j < N; j++){
			l = C[j].get_length();
			if(l==1 && l<M){
				if(!R[(C[j][0]+1)%M].search(j)){
					C[j][0]=(C[j][0]+1)%M;
					if(changes==0)
						changes=1;
				}
			}
			if(l>1){
				flag=C[j][0]==0 && C[j][l-1]==M-1;
				for(int i=0;i<l-flag;i++){
					if(mod_dist(C[j][i+1],C[j][i],M)>1 && !R[(C[j][i]+1)%M].search(j)){
						C[j][i]=(C[j][i]+1)%M;
						if(changes==0)
							changes=1;
						if(C[j][i]==0)
							C[j].last_first();
					}
				}
			}
		}
		return changes;
    }

    unsigned short int move_red () {
        unsigned short int flag,changes(0);
        unsigned int l;
        unsigned int N(C.get_length()), M(R.get_length());
        for(int i=0;i<M;i++){
			l = R[i].get_length();
			if(l==1 && l<N){
				if(!C[(R[i][0]+1)%N].search(i)){
					R[i][0]=(R[i][0]+1)%N;
					if(changes==0)
						changes=1;
				}
			}
			if(l>1){
				flag=R[i][0]==0 && R[i][l-1]==N-1;
				for(int j=0;j<l-flag;j++){
					if(mod_dist(R[i][j+1],R[i][j],N)>1 && !C[(R[i][j]+1)%N].search(i)){
						R[i][j]=(R[i][j]+1)%N;
						if(changes==0)
							changes=1;
						if(R[i][j]==0)
							R[i].last_first();
					}
				}
			}
		}
		return changes;
    }

    void output (unsigned int cont){
        unsigned int N(C.get_length()),M(R.get_length());
        ofstream out;
        out.open(to_string(cont)+".csv");
        int lr;
        for(int i=0;i<M;i++){
            lr = R[i].get_length();
            if(lr==0){
                for(int j=0;j<N-1;j++)
                    out<<C[j].search(i)<<",";
                out<<C[N-1].search(i);
                }
            else if(lr==1){
                for(int j=0;j<R[i][0];j++)
                    out<<C[j].search(i)<<",";
                if (R[i][0]!=N-1) {
                    out<<2<<",";
                    for(int j=R[i][0]+1;j<N-1;j++)
                        out<<C[j].search(i)<<",";
                    out<<C[N-1].search(i);
                }
                else
                    out<<2;
            }
            else{
                for(int j=0;j<R[i][0];j++)
                    out<<C[j].search(i)<<",";
                for(int r=0;r<lr-1;r++){
                    out<<2<<",";
                    for(int j=R[i][r]+1;j<R[i][r+1];j++)
                        out<<C[j].search(i)<<",";
                }
                if (R[i][lr-1]!=N-1){
                    out<<2<<",";
                    for(int j=R[i][lr-1]+1;j<N-1;j++)
                        out<<C[j].search(i)<<",";
                    out<<C[N-1].search(i);
                    }
                else
                    out<<2;
            }
            out<<endl;
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
                    changes1=move_blue();
                }
                if(cont%2==1){
                    changes2=move_red();
                }
            cont++;
            }
            output(cont);
        }
    }
};

#endif
