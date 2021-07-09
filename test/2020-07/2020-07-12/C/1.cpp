#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
#define int long long
namespace run{
	const int N=2e6+9,inf=1e18;
	char s[N];int ans=0;
	namespace AC{
		int c[26][N],fa[N],val[N],num,dep[N];
		inline void insert(int len,int v){
			int now=0;
			for(int i=1;i<=len;i++){
				int &cur=c[s[i]-'a'][now];
				if(!cur) cur=++num;
				now=cur;
			}
			val[now]+=v;
		}

		int f[N],g[N],st[N],top;
		queue<int> q;
		inline void build(){
			for(int i=0;i<26;i++)
				if(c[i][0]) q.push(c[i][0]),dep[c[i][0]]=1;
			while(!q.empty()){
				int u=q.front();q.pop();
				val[u]+=val[fa[u]],f[u]+=val[u];
			//	cout<<fa[u]<<" "<<u<<endl;
				for(int i=0;i<26;i++){
					if(c[i][u]) fa[c[i][u]]=c[i][fa[u]],q.push(c[i][u]),f[c[i][u]]=f[u],dep[c[i][u]]=dep[u]+1;
					else c[i][u]=c[i][fa[u]];
				}
			}
		}
		inline void bfs(){	
			q.push(0);
			while(!q.empty()){
				int u=q.front();q.pop();
				st[++top]=u;
				for(int i=0;i<26;i++)
					if(dep[c[i][u]]==dep[u]+1){
						int a=fa[c[i][u]],tmp=u,v=c[i][u];
						g[v]=max(g[v],g[tmp]+val[a]);
						tmp=fa[tmp],q.push(v);
						if(tmp==0) continue;
						do{
							if(c[i][tmp]==a) break;
							g[v]=max(g[v],max(f[tmp],g[tmp])+val[a]);
							tmp=fa[tmp];
						}while(1);
					}
			}
		}
		inline void find(int len){
			for(int i=1;i<=top;i++)
				g[st[i]]=max(g[st[i]],g[fa[st[i]]]),f[st[i]]=max(f[st[i]],f[fa[st[i]]]);
			int now=0;
			for(int i=1;i<=len;i++){
				now=c[s[i]-'a'][now];
				ans=max(ans,max(g[now],f[now]));
			}
		}
	}using namespace AC;
	int n,m;
	int main(){
		n=read<int>(),m=read<int>();
		for(int i=1;i<=n;i++)
			scanf("%s",s+1),insert(strlen(s+1),read<int>());
		scanf("%s",s+1),insert(strlen(s+1),0);

		build(),g[0]=0;
		for(int i=1;i<=num;i++) g[i]=-inf;
		bfs();
	//	for(int i=1;i<=num;i++) cout<<g[i]<<" ";cout<<endl;
		find(strlen(s+1));
		printf("%lld\n",ans);
		return 0;
	}
}
#undef int
int main(){
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	return run::main();
}
