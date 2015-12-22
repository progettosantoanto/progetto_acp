#ifndef move_sparse_h
#define move_sparse_h

#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "vect.h"
#include "struct_sparse.h"

using namespace std;

class move_sparse{
    unsigned short int changes;
    public:

    move_sparse (unsigned short int changes=0):changes(changes){};

    unsigned short int get_changes(){
        return changes;
        }

    void operator () (struct_sparse S, string car) {
    unsigned short int flag;
    unsigned int l;
    unsigned int N(S.C.get_length()), M(S.R.get_length());
    if (car=="blue") {

    for(int j = 0; j < N; j++){
			l = S.C[j].get_length();
			if(l==1 && l<M){
				if(!S.R[(S.C[j][0]+1)%M].search(j)){
					S.C[j][0]=(S.C[j][0]+1)%M;
					if(changes==0)
						changes=1;
				}
			}
			if(l>1){
				flag=S.C[j][0]==0 && S.C[j][l-1]==M-1;
				for(int i=0;i<l-flag;i++){
					if(mod_dist(S.C[j][i+1],S.C[j][i],M)>1 && !S.R[(S.C[j][i]+1)%M].search(j)){
						S.C[j][i]=(S.C[j][i]+1)%M;
						if(changes==0)
							changes=1;
						if(S.C[j][i]==0)
							S.C[j].last_first();
					}
				}
			}
		}
    }

   else if (car=="red") {

        for(int i=0;i<M;i++){
			l = S.R[i].get_length();
			if(l==1 && l<N){
				if(!S.C[(S.R[i][0]+1)%N].search(i)){
					S.R[i][0]=(S.R[i][0]+1)%N;
					if(changes==0)
						changes=1;
				}
			}
			if(l>1){
				flag=S.R[i][0]==0 && S.R[i][l-1]==N-1;
				for(int j=0;j<l-flag;j++){
					if(mod_dist(S.R[i][j+1],S.R[i][j],N)>1 && !S.C[(S.R[i][j]+1)%N].search(i)){
						S.R[i][j]=(S.R[i][j]+1)%N;
						if(changes==0)
							changes=1;
						if(S.R[i][j]==0)
							S.R[i].last_first();
					}
				}
			}
		}
}
else
    exit(1);
}
friend class struct_sparse;
};

#endif
