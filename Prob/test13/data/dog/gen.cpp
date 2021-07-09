#include<bits/stdc++.h>
#define enter putchar('\n')
#define space putchar(' ')
#define N 500010
#define int long long
#define re register
#define fr(i,a,b) for(int i(a),end##i(b);i<=end##i;i++)
#define fd(i,a,b) for(int i(a),end##i(b);i>=end##i;i--)
using namespace std;
void generate(int &x,int &y){
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

const int lim=1000000000,L=100000000;

int a[N],tot;

struct data{
	int fi,se,th;
	data(const int X=0,const int Y=0,const int Z=0):fi(X),se(Y),th(Z){}
}p[N];

signed main(){
	freopen("dog4_12.in","w",stdout);
	srand(time(0)+(unsigned long long)new char);
	int q=1000000,Q=500000,O=rand()%Q+1;
	cout<<q<<endl;
	for(re int i=1;i<=Q;++i)
	printf("%lld %lld %lld\n",1,i,1),++tot;
	for(re int i=Q+1;i<=q;++i){
		int opt=(rand()&1)||(i==1);
		if(opt==1){
			int X=rand()%Q+1;
			X=271;
			int Y=rand()%2+1;
			tot-=a[X];
			tot+=Y;
			a[X]=Y;
			printf("%lld %lld %lld\n",opt,X,Y);
		}
		else{
			int X=1ll*rand()*rand()%tot+1;
			printf("%lld %lld\n",opt+2,X);
		}
	}
	return 0;
}
