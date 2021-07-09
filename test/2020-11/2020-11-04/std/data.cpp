#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#define N 1000005
#define ll long long
using namespace std;
int n;
int f[N],ai[N],bi[N],nx[N],fa[N],la[N];
int s1[N],s2[N],t1[N],t2[N];
struct pl{int a,b,id;};
struct cmp{bool operator()(pl A,pl B){return (ll)A.a*B.b>(ll)A.b*B.a;}};
priority_queue<pl,vector<pl>,cmp>q;
int get(int x){
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}
int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	scanf("%d",&n);
	for(int i=2;i<=n;i++) scanf("%d",&f[i]);
	for(int i=1;i<=n;i++) la[i]=i;
	for(int i=1;i<=n;i++) scanf("%d%d",&ai[i],&bi[i]),s1[i]=ai[i],s2[i]=bi[i];
	for(int i=2;i<=n;i++){
		pl tmp;tmp.a=ai[i];tmp.b=bi[i];tmp.id=i;
		q.push(tmp);
	}
	for(int i=1;i<=n;i++) fa[i]=i;
	while(!q.empty()){
		pl tmp=q.top();q.pop();
//		cout<<tmp.a<<" "<<tmp.b<<" "<<tmp.id<<endl;
		if(tmp.a!=ai[tmp.id]||tmp.b!=bi[tmp.id]) continue;
		int ti=get(tmp.id),tk=f[ti];tk=get(tk);
		nx[la[tk]]=ti;la[tk]=la[ti];
		ai[tk]+=ai[ti];bi[tk]+=bi[ti];fa[ti]=tk;
		tmp.a=ai[tk];tmp.b=bi[tk];tmp.id=tk;
		if(tk!=1) q.push(tmp);
	}
	int tmp=1,tot=0;
	while(tmp!=0){tot++;t1[tot]=s1[tmp];t2[tot]=s2[tmp];tmp=nx[tmp];}
	for(int i=tot;i>=1;i--) t1[i]+=t1[i+1];ll ans=0;
	for(int i=1;i<=tot;i++) ans+=(ll)t2[i]*t1[i+1];printf("%lld\n",ans);
	return 0;
}
