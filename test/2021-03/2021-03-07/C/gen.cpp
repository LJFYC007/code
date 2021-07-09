
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
	typedef pair<int,int> P;
	const int lim=26;
	map<P,int> mp;
	int vis[26];
	int main(){
		srand(time(0));

		int n=2500,m=1,Q=5000;
		cout<<n<<" "<<m<<" "<<Q<<endl;
		for(int i=2;i<=n;i++){
			int p=rand()%(i-1)+1;
			p=i-1;
			cout<<i<<" "<<p<<" ";
			for(int j=0;j<lim;j++) vis[j]=0;
			vis[rand()%lim]=1;
			for(int j=0;j<lim;j++) vis[j]|=(rand()%2==1);
			for(int j=0;j<lim;j++) if(vis[j]|1) cout<<(char)('a'+j);
			cout<<endl;
		}
		for(int i=1;i<=m;i++){
			int len=40;
			for(int j=1;j<=len;j++){
				cout<<(char)(rand()%lim+'a');
			}
			cout<<endl;
		}
		for(int i=1;i<=Q;i++){
			int u=rand()%n+1,v=rand()%n+1;
			while(u==v) v=rand()%n+1;
			u=1,v=n;
			cout<<u<<" "<<v<<endl;
		}
		return 0;
	}
}
#undef int
int main(){
	freopen("input.txt","w",stdout);
	return run::main();
}
