#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#define N 1000005
#define ll long long
#define mod 1000000007
using namespace std;
int n,fi,cnt,ans=1;
int head[N],si[N],t[N],fc[N],ny[N];
struct pl{int v,nex;}e[2*N];
void add(int a,int b){cnt++;e[cnt].v=b;e[cnt].nex=head[a];head[a]=cnt;}
int C(int a,int b){
	if(a<0||b<a) return 0;
	return (ll)fc[b]*ny[a]%mod*ny[b-a]%mod;
}
void dfs(int a,int fa){
	int i=head[a];
	while(i!=0){
		if(e[i].v!=fa){
			dfs(e[i].v,a),si[a]+=si[e[i].v],t[a]+=t[e[i].v];
			ans=(ll)ans*C(si[e[i].v],si[a])%mod*C(t[e[i].v],t[a])%mod;
		}
		i=e[i].nex;
	}
	t[a]--;si[a]++;
}
int po(int a,int b){
	int an=1;
	while(b!=0){
		if(b&1) an=(ll)an*a%mod;
		a=(ll)a*a%mod;b=(b>>1);
	}
	return an;
}
int get(){
	char ch;int v=0;
	while(!isdigit(ch=getchar()));v=ch-48;
	while(isdigit(ch=getchar())) v=(v<<1)+(v<<3)+ch-48;
	return v;
} 
int main()
{
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	n=get();fc[0]=ny[0]=1;
	for(int i=1;i<=n;i++) fc[i]=(ll)fc[i-1]*i%mod;ny[n]=po(fc[n],mod-2);
	for(int i=n-1;i>=1;i--) ny[i]=(ll)ny[i+1]*(i+1)%mod;
	for(int i=2;i<=n;i++) fi=get(),add(i,fi),add(fi,i);
	for(int i=1;i<=n;i++) t[i]=get();
	dfs(1,0);printf("%d\n",ans);
	return 0;
}
