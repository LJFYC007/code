#include<bits/stdc++.h>
#define ll long long
#define lld long double
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 201000;
struct edge{int v,w;};
vector<edge> e[N];
vector<ll> f[N][2][2];
int n,p[N],sum[N],s[N],fa[N],hs[N],W[N],cnt,fw[N];
void merge(vector<ll>&p1,vector<ll>&p2,vector<ll>&P){
	P.push_back(0);
	for(int k1=1,k2=1;k1<p1.size()||k2<p2.size();)
		if(k2>=p2.size()||k1<p1.size()&&p1[k1]-p1[k1-1]>p2[k2]-p2[k2-1]) P.push_back(P.back()+p1[k1]-p1[k1-1]),k1++;
		else P.push_back(P.back()+p2[k2]-p2[k2-1]),k2++;
}
void build(int l,int r,int tag){
	if(l==r&&tag==0){
		swap(f[p[l]][0][0],f[p[l]][1][1]);
		f[p[l]][1][1].clear();
		f[p[l]][1][1].resize(max(f[p[l]][0][1].size()+1,f[p[l]][0][0].size()+0));
		for(int j=0;j<f[p[l]][1][1].size();j++) f[p[l]][1][1][j]=-1e15;
		for(int j=0;j<f[p[l]][0][1].size();j++)
			f[p[l]][1][1][j+1]=f[p[l]][0][1][j]+fw[p[l]];
		for(int j=0;j<f[p[l]][0][0].size();j++)
			f[p[l]][1][1][j]=max(f[p[l]][1][1][j],f[p[l]][0][0][j]);
		f[p[l]][0][1].clear();
		f[p[l]][1][0].clear();
	}
	if(r-l<1) return;
	int S=0;
	for(int i=l;i<=r;i++) S+=sum[i];
	for(int i=l,now=sum[l];i<r;i++,now+=sum[i])
		if(2*now+2*sum[i+1]>S){
			build(l,i,tag);build(i+1,r,tag);
			if(tag==1){
				vector<ll> now[2][2];
				for(int k1=0;k1<2;k1++)
					for(int k2=0;k2<2;k2++){
						vector<ll> P;
						merge(f[p[l]][k1][1],f[p[i+1]][1][k2],P);
						while(P.size()>now[k1][k2].size()) now[k1][k2].push_back(-1e15);
						for(int j=0;j<P.size();j++)
							now[k1][k2][j]=max(now[k1][k2][j],P[j]);
						P.clear();
						merge(f[p[l]][k1][0],f[p[i+1]][0][k2],P);
						if(l==i&&k1!=1||i+1==r&&k2!=1) continue;
						while(P.size()+1>now[k1][k2].size()) now[k1][k2].push_back(-1e15);
						for(int j=0;j<P.size();j++)
							now[k1][k2][j+1]=max(now[k1][k2][j+1],P[j]+W[p[i]]);
					}
				swap(now,f[p[l]]);
			}
			else{
				vector<ll> now[2],P;
				merge(f[p[l]][0][0],f[p[i+1]][0][0],P);
				while(P.size()>now[0].size()) now[0].push_back(-1e15);
				for(int j=0;j<P.size();j++)
					now[0][j]=max(now[0][j],P[j]);
				P.clear();
				merge(f[p[l]][0][0],f[p[i+1]][1][1],P);
				while(P.size()>now[1].size()) now[1].push_back(-1e15);
				for(int j=0;j<P.size();j++)
					now[1][j]=max(now[1][j],P[j]);
				P.clear();
				merge(f[p[l]][1][1],f[p[i+1]][0][0],P);
				while(P.size()>now[1].size()) now[1].push_back(-1e15);
				for(int j=0;j<P.size();j++)
					now[1][j]=max(now[1][j],P[j]);
				swap(f[p[l]][0][0],now[0]);
				swap(f[p[l]][1][1],now[1]);
			}
			return;
		}
}
void init(int x,vector<int>&V){
	cnt=0;
	for(int k:V) p[++cnt]=k,sum[cnt]=s[k];
	build(1,cnt,0);
	if(cnt) swap(f[x],f[p[1]]);
	if(f[x][0][0].size()<1) f[x][0][0].resize(1);
	if(f[x][1][1].size()<1) f[x][1][1].resize(1);
	f[x][0][1]=f[x][1][0]=f[x][0][0];
}
void dfs1(int x,int dad){
	s[x]=1;fa[x]=dad;
	for(auto v:e[x]) if(v.v!=dad){
		fw[v.v]=v.w;dfs1(v.v,x);s[x]+=s[v.v];
		if(!hs[x]||s[v.v]>s[hs[x]]) hs[x]=v.v,W[x]=v.w;
	}
}
void solve(int x){
	for(int y=x;y;y=hs[y]){
		vector<int> V; 
		for(auto v:e[y]){
			if(v.v!=fa[y]&&v.v!=hs[y]) solve(v.v),V.push_back(v.v);
		}
		init(y,V);
	}
	cnt=0;
	for(int y=x;y;y=hs[y]) p[++cnt]=y,sum[cnt]=s[y]-s[hs[y]];
	build(1,cnt,1);
}
int main(){
	freopen("accompany.in","r",stdin);
	freopen("accompany.out","w",stdout);
	int id,L,R;read(id);
	read(n);read(L);read(R);
	for(int i=1;i<n;i++){
		int x,y,z;read(x);read(y);read(z);
		e[x].push_back({y,z});
		e[y].push_back({x,z});
	}
	dfs1(1,0);
	solve(1);
	for(int i=L;i<=R;i++)
		if(i<f[1][1][1].size()) cout<<f[1][1][1][i]<<' ';
		else cout<<"- ";
	cout<<'\n';
	return 0;
}

