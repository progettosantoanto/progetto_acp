#include<iostream>
#include<ostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<memory>
#include<algorithm>
#include "clvect.h"

using namespace std;

class move{
    unsigned short int changes;
    public:

    move (unsigned short int changes=0):changes(changes){};

    unsigned short int get_changes(){
        return changes;
        }

    vect<vect<int>>& operator () (vect<vect<int>>& C, vect<vect<int>>& R) {
    int N(C.get_length()), M(R.get_length()), l;
    unsigned short int flag;
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
    }
};
