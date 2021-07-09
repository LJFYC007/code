/*************************************************************************
	> File Name: game.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2020年11月18日 星期三 14时01分44秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define N 1210

using namespace std;

inline int max(int x,int y){return (x>y?x:y);}

inline int min(int x,int y){return (x<y?x:y);}

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

int n,T;

const int lim=35;

struct matrix{
	bool mat[N][N];
	matrix(){memset(mat,0,sizeof(mat));return;}
	inline bool * operator [] (const int a){return mat[a];}
	matrix operator * (const matrix &a)const{
		matrix C;
		for(re int i=1;i<=n;++i)
			for(re int k=1;k<=n;++k)		if(mat[i][k])
				for(re int j=1;j<=n;++j)
				C.mat[i][j]^=(mat[i][k]&a.mat[k][j]);
		return C;
	}
	matrix operator + (const matrix &a)const{
		matrix C;
		for(re int j=1;j<=n;++j)
			for(re int k=1;k<=n;++k)		if(a.mat[k][j])
				for(re int i=1;i<=n;++i)
				C.mat[i][j]^=(mat[i][k]&a.mat[k][j]);
		return C;
	}
}I[lim+1],U,A;

inline bool get01(){
	char c=getchar();
	while(c!='0' && c!='1') c=getchar();
	return (c-48);
}

inline void Input(){
	n=read(),T=read();
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=n;++j)
		A[i][j]=get01();
	
	for(re int i=1;i<=n;++i) U[i][i]=1;
	for(re int i=1;i<=n;++i){
		if(i^1) I[0][i][i-1]=1;
		if(i^n) I[0][i][i+1]=1;
	}
	for(re int i=1;i<=lim;++i) I[i]=I[i-1]*I[i-1],cerr<<i<<endl;
	return;
}

inline void solve(){
	for(re int i=lim;~i;--i)if(T>=(1ll<<i)) A=A+I[i],A=I[i]*A,T-=(1<<i);
	
	/*A=A*U;
	A=U*A;*/
	
	for(re int i=1;i<=n;++i){
		for(re int j=1;j<=n;++j)
		putchar(A[i][j]+'0');enter;
	}
	
	return;
}

int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	Input();
	solve();
	return 0;
}
