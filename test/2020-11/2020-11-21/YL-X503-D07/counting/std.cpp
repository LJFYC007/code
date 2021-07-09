/*************************************************************************
	> File Name: counting.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2020年11月21日 星期六 11时09分52秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define int long long
#define N 140100
#define M 330
#define K 18
#define count(x) __builtin_popcount(x)

using namespace std;

const int mod=998244353,in2=499122177,lim=31;

inline int max(int x,int y){return (x>y?x:y);}

inline int min(int x,int y){return (x<y?x:y);}

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

int n,m,A,B,P,a[N],U,T,tot;

int p[M],ip[M],C[M][M];

int f[K][K][K];

int G[2][N][K][K];

inline int Pow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=1ll*ans*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ans;
}

inline int in(int X){return Pow(X,mod-2);}

inline int add(int x){
	if(x<0) return x+mod;
	return (x>=mod?x-mod:x);
}

inline void pre(){
	p[0]=ip[0]=1;
	for(re int i=1;i<M;++i)
	p[i]=1ll*p[i-1]*2%mod,
	ip[i]=1ll*ip[i-1]*in2%mod;
	C[0][0]=1;
	for(re int i=1;i<M;++i){
		C[i][0]=1;
		for(re int j=1;j<M;++j)
		C[i][j]=add(C[i-1][j-1]+C[i-1][j]);
	}
	return;
}

struct Matrix{
	int mat[M][M];
	inline int * operator [] (const int a){return mat[a];}
	Matrix(){memset(mat,0,sizeof(mat));}
	Matrix operator * (const Matrix &a)const{
		Matrix C;
		for(re int i=0;i<tot;++i)
			for(re int k=0;k<tot;++k)if(mat[i][k])
				for(re int j=0;j<tot;++j)
				C.mat[i][j]=(C.mat[i][j]+mat[i][k]*a.mat[k][j])%mod;
		return C;
	}
	inline void clear(){memset(mat,0,sizeof(mat));return;}
	inline void print(){/*
		for(re int i=0;i<tot;++i){
			for(re int j=0;j<tot;++j)
			cout<<mat[i][j]<<" ";enter;
		}
		enter;*/
		return;
	}
}I[lim+1],O;

//在这里

//我用0~n表示变为1的

//0~n*(n+1)表示变为0的

inline int mp(int X,int Y){
	return X*(n+1)+Y;
}

inline void Input(){
	n=read();m=read();A=read();B=read();
	P=A*in(B)%mod;
	U=(1<<n);
	tot=(n+1)*(n+1);
	for(re int i=0;i<U;++i)	a[i]=read();

	for(re int i=0;i<=n;++i){
		I[0].clear();
		for(re int j=0;j<=n-i;++j){//转移出去的位数中，外面有几个是1
			for(re int k=0;k<=i;++k){//重合的，有几个是1
				for(re int u=0;u<=j;++u){
					for(re int v=0;v<=k;++v){
						I[0][mp(u,v)][mp(j,k)]=(I[0][mp(u,v)][mp(j,k)]+(mod-P+1)*ip[n-u-v]%mod*C[n-i-u][j-u]%mod*C[i-v][k-v])%mod;
					}
				}
				for(re int u=j;u<=n-i;++u){
					for(re int v=k;v<=i;++v){
						I[0][mp(u,v)][mp(j,k)]=(I[0][mp(u,v)][mp(j,k)]+P*ip[u+v]%mod*C[u][j]%mod*C[v][k])%mod;
					}
				}
			}
		}

		for(re int j=1;j<=lim;++j)
		I[j]=I[j-1]*I[j-1];

		O.clear();
		O[0][mp(0,i)]=1;
		
		for(re int j=lim;~j;--j)if(m>>j&1)
		O=O*I[j];

		for(re int j=0;j<=n;++j)
			for(re int k=0;k<=n;++k)
			f[i][j][k]=O[0][mp(j,k)]*in(C[n-i][j])%mod*in(C[i][k])%mod;
		//enter;
	}
	return;
}

inline void solve(){
	int T=0,cnt,ret=0;
	for(re int i=0;i<U;++i){
		cnt=count(i);
		for(re int j=0;j<=n;++j)
			for(re int k=0;k<=cnt;++k)
			G[T][i][j][k]=(__int128)f[cnt][j][cnt-k]*a[i]%mod;
		//enter;
	}

	for(re int I=0;I<n;++I){
		T^=1;
		for(re int i=0;i<U;++i)
		if(i>>I&1)
		for(re int j=0;j<=n-I;++j)
			for(re int k=0;k<=n-I-j;++k)
			G[T][i][j][k]=add(G[T^1][i][j][k]+G[T^1][i^(1<<I)][j+1][k])%mod;
		
		else
		for(re int j=0;j<=n-I;++j)
			for(re int k=0;k<=n-I-j;++k)
			G[T][i][j][k]=add(G[T^1][i][j][k]+G[T^1][i^(1<<I)][j][k+1])%mod;
	}
	
	for(re int i=0;i<U;++i)
	printf("%lld ",G[T][i][0][0]);enter;
	return;
}

signed main(){
	freopen("counting.in","r",stdin);
	freopen("counting1.out","w",stdout);
	pre();
	Input();
	solve();
	return 0;
}
