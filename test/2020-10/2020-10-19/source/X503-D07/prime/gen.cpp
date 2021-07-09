#include<bits/stdc++.h>
#define fr(i,a,b) for(int i(a),end##i(b);i<=end##i;i++)
#define fd(i,a,b) for(int i(a),end##i(b);i>=end##i;i--)
using namespace std;
int n=6,q=10;
int generate(int &x,int &y){
	if(rand()%10==0){
		if(rand()%2)x=3,y=2;
		else x=2,y=3;
	}
	else if(rand()%5==0){
		if(rand()%2)x=1,y=0;	
		else x=0,y=1;
	}
	else x=rand()%9,y=rand()%9;
	if(rand()%2)x=-x;
	if(rand()%2)y=-y;
}
int main(){
	freopen("prime.in","w",stdout);
	srand(time(0)+(unsigned long long)new char);
	printf("%d %d\n",n,q);
	fr(i,1,n){
		int x,y;generate(x,y);
		printf("%d %d\n",x,y);
	}
	while(q--){
		int op=rand()%3+1,l=rand()%n+1,r=rand()%n+1;
		if(!q)op=3;
		if(l>r)swap(l,r);
		if(op==1||op==2){
			int x,y;generate(x,y);
			printf("%d %d %d %d %d\n",op,l,r,x,y);	
		}
		else printf("%d %d %d\n",op,l,r);
	}
	return 0;
}
