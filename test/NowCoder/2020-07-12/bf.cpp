#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T f=0,x=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
namespace run{

	typedef pair<int,int> P;
	const int N=109;P ed[N];
	int n,m,d[N],deg[N];
	int main(){
	//	int T=read<int>();
	//	while(T--){
		while(~scanf("%d%d",&n,&m)){	
			for(int i=1;i<=n;i++) d[i]=read<int>();
			for(int i=1;i<=m;i++){
				int u=read<int>(),v=read<int>();
				ed[i]=P(u,v);
			}
			int peg=0;
			for(int i=0;i<(1<<m);i++){
				for(int j=1;j<=n;j++) deg[j]=0;
				for(int j=0;j<m;j++)
					if((i>>j)&1){
						deg[ed[j+1].first]++;
						deg[ed[j+1].second]++;
					}
				int fla=1;
				for(int j=1;j<=n;j++)
					if(d[j]^deg[j]){fla=0;break;}
				if(fla){peg=1;break;}
			}
			if(peg==1) puts("Yes");
			else puts("No");
		}
		return 0;
	}
}
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
	return run::main();
}
