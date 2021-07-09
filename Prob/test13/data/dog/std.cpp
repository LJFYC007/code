/*************************************************************************
	> File Name: std.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2020年12月30日 星期三 10时26分40秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define int long long
#define N 1110010
#define fi first
#define se second
#define mp make_pair

using namespace std;

const int lim=30;

inline int max(int x,int y){return (x>y?x:y);}

inline int min(int x,int y){return (x<y?x:y);}

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

int n,q,a[N],A[N];

bool flag;

struct data{
	int S,Q,W,len;
	data(const int X=0,const int Y=0,const int Z=0,const int P=0):S(X),Q(Y),W(Z),len(P){}
	inline int Gval(){
		return S-Q;//len-mod
	}
}O;

/*inline void pushup(int x){
	T[x]=T[ls]+T[rs];
	if(Len[ls]>=lim){
		Q[x]=Q[rs];
		if(W[rs]<=Q[ls])	++Q[x],W[x]=inf;
		else				W[x]=(W[rs]-Q[ls]==1?W[ls]:inf);
	}
	else{
		Q[x]=Q[rs]+(Q[ls]>>Len[rs]);
		Q[ls]&=(len[rs]-1);
		W[x]=(W[rs]+len[rs]-Q[ls]<<Len[ls])+W[ls];
		if(W[x]>len[x])		W[x]-=len[x];
		else				++Q[x];
	}
	return;
}*/

int Cnt;

inline data operator + (data A,data B){

	if(!A.len) return B;

	/*if(A.S || B.S)
	cout<<A.S<<" "<<A.Q<<" "<<A.W<<" "<<A.len<<endl,
	cout<<B.S<<" "<<B.Q<<" "<<B.W<<" "<<B.len<<endl,Cnt=1;*/
	
	data C;
	C.S=A.S+B.S;
	C.len=A.len+B.len;
	C.len=min(C.len,lim);
	C.Q=B.Q+(A.Q>>B.len);
	A.Q&=(1ll<<B.len)-1;
	C.W=(B.W+(1ll<<B.len)-1-A.Q<<A.len)+A.W;
	if(C.W<=(1ll<<A.len+B.len))	++C.Q;

	//if(C.W>(1ll<<C.len)) C.W-=(1ll<<C.len);

	if(C.W>(1ll<<A.len+B.len)) C.W-=(1ll<<A.len+B.len);

	C.W=min(C.W,(1ll<<C.len));

	if(Cnt)
	cout<<C.S<<" "<<C.Q<<" "<<C.W<<" "<<C.len<<endl,
	enter;

	Cnt=0;

	return C;
}

struct Segment_Tree{
	#define ls (x<<1)
	#define rs (x<<1|1)
	data T[N<<2];
	int U[N<<2];
	inline void pushup(int x){
		T[x]=T[ls]+T[rs];
		U[x]=U[ls]+U[rs];
		return;
	}
	void build(int x,int l,int r){
		T[x].S=T[x].Q=0;T[x].W=2;
		T[x].len=r-l+1;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(x);
		return;
	}
	void change(int x,int l,int r,int y,int val){
		if(l==r) {
			T[x].S=val;T[x].Q=(val>>1);T[x].W=2-(val&1);	U[x]=val*l;
			return;
		}
		int mid=(l+r)>>1;
		if(y<=mid)	change(ls,l,mid,y,val);
		else		change(rs,mid+1,r,y,val);
		pushup(x);
		return;
	}
	int query(int x,int l,int r,int val,data F){
		if(l==r){
			//cout<<l<<" "<<r<<endl;
			//flag=1;

			int r1=F.Q+a[l],r2;
			F=F+T[x];
			r2=F.S-val;
			//cerr<<l<<" "<<r1<<" "<<r2<<" "<<F.Q<<endl;
			//assert(r2*2+1>=r1);
			assert(F.Gval()>=val);
			if(r1==r2*2+1)
			return U[x]-r2*(l+1);
			else
			return U[x]-r2*l-(r1-r2);
		}
		int mid=(l+r)>>1;
		if(val<=(F+T[ls]).Gval())	return query(ls,l,mid,val,F);
		else						return F=F+T[ls],query(rs,mid+1,r,val,F)+U[ls];
	}
}tree;

inline void Input(){
	q=read();n=1001000;
	tree.build(1,1,n);
	return;
}

inline void solve(){
	int opt,X,Y,cnt=0;
	for(re int I=1;I<=q;++I){
		opt=read();
		if(opt==1){
			X=read(),Y=read();
			if(X^1)
			tree.change(1,1,n,X,Y);
			a[X]=Y;
		}
		else{
			++cnt;
			//cout<<cnt<<endl;
			X=read();
			X-=a[1];
			if(X>0) 
			printf("%lld\n",tree.query(1,1,n,X,O)+a[1]);
			else
			printf("%lld\n",X+a[1]);
		}
	}
	/////////////////////////////////////////////////////*//////////////
	return;
}

signed main(){
	freopen("dog4_12.in","r",stdin);
	freopen("dog4_12.out","w",stdout);
	Input();
	solve();
	return 0;
}
