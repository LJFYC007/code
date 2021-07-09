#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T f=0,x=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
#define int long long
namespace run{
	const int N=309,inf=1e15;
	int dist[N][N],n,m,Q,e[N][N];
	int main(){
		n=read<int>(),m=read<int>(),Q=read<int>();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++) dist[i][j]=e[i][j]=inf;
			dist[i][i]=e[i][i]=0;
		}

		for(int i=1;i<=m;i++){
			int u=read<int>(),v=read<int>(),w=read<int>();
			e[u][v]=e[v][u]=min(e[u][v],w);
		}
		for(int i=1;i<=Q;i++){
			int opt=read<int>();
			if(opt==1){
				int x=read<int>();
				for(int i=1;i<=n;i++) dist[x][i]=dist[i][x]=e[i][x];
				for(int i=1;i<=n;i++)
					for(int j=1;j<=n;j++) dist[i][j]=min(dist[i][j],dist[i][x]+dist[x][j]);
			}else{
				int x=read<int>(),y=read<int>();
				printf("%lld\n",dist[x][y]>=inf?-1:dist[x][y]);
			}
		}
		return 0;
	}
}
#undef int
int main(){
	freopen("route.in","r",stdin);
	freopen("route.out","w",stdout);
	return run::main();
}
