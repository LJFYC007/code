#include <bits/stdc++.h>

#define re register
#define enter putchar('\n')
#define space putchar(' ')
#define M 1050000
#define N 310
#define vec vector<int>

using namespace std;

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

int n,K,s=N-2,t=N-1;

int a[N][N],siz[N];

vec to[N];

int p[N],v[N],ret;

int P[N];

void dfs(int x){
	if(x==n+1){if(ret%K==0) puts("Yes"),exit(0);return;}
	for(re int i=1;i<=n;++i)if(!v[i] && ~a[x][i]){
		p[x]=i;v[i]=1,ret+=a[x][i];
		dfs(x+1);
		p[x]=v[i]=0,ret-=a[x][i];
	}
	return;
}

int ver[M],nex[M],head[N],e[M],nu;

int d[N],cur[N],cs,Val;

queue<int> q;

inline void add(int x,int y,int z){
	ver[++nu]=y,nex[nu]=head[x],head[x]=nu;e[nu]=z;
	ver[++nu]=x,nex[nu]=head[y],head[y]=nu;e[nu]=0;
	return;
}

bool bfs(){
	int x,y;
	++cs;
	while(!q.empty()) q.pop();
	q.push(s);
	d[s]=0;cur[s]=head[s];v[s]=cs;
	while(!q.empty()){
		x=q.front();q.pop();
		for(re int i=head[x];i;i=nex[i])if(e[i] && v[ver[i]]!=cs){
			y=ver[i];
			d[y]=d[x]+1;
			v[y]=cs;
			cur[y]=head[y];
			if(y==t) return 1;
			q.push(y);
		}
	}
	return 0;
}

int Dfs(int x,int flow){
	int ret=flow,y,k;
	if(x==t) return flow;
	for(re int i=cur[x];i && ret;i=nex[i])if(e[i]){
		cur[x]=i;
		y=ver[i];
		if(v[y]==cs && d[y]==d[x]+1){
			//cerr<<x<<" "<<y<<" "<<ret<<endl;
			k=Dfs(y,min(ret,e[i]));
			if(!k) d[y]=0;
			e[i]-=k;
			e[i^1]+=k;
			ret-=k;
		}
	}
	return flow-ret;
}

bool vis[N];

inline bool Find(int x,int tar){
	int y;
	vis[x]=1;
	for(re int i=head[x];i;i=nex[i])if(ver[i]!=P[x] && ver[i]!=s && ver[i]!=t){
		y=ver[i];
		if(y==tar) return Val-=a[x][P[x]-n],Val+=a[x][y-n],P[y]=x,P[x]=y,1; 
	}
	for(re int i=head[x];i;i=nex[i])if(ver[i]!=P[x] && !vis[P[ver[i]]] && ver[i]!=s && ver[i]!=t){
		y=ver[i];
		bool k=Find(P[y],tar);
		if(k) return Val-=a[x][P[x]-n],Val+=a[x][y-n],P[y]=x,P[x]=y,1;
	}
	return 0;
}

inline void Input(){
	n=read(),K=read();
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=n;++j){
			a[i][j]=read();
			if(~a[i][j]) to[i].push_back(j),++siz[i];
		}
	return;
}

inline void solve(){
	srand((unsigned)time(NULL));
	if(n<=10){
		dfs(1);
		//cerr<<mx<<endl;
		puts("No");
		return;
	}
	else{
		for(re int i=1;i<=n;++i) add(s,i,1);
		for(re int i=1;i<=n;++i) add(i+n,t,1);
		for(re int i=1;i<=n;++i)
			for(re int j=1;j<=n;++j)if(~a[i][j])
			add(i,j+n,1);

		int ans=0;
		while(bfs())	ans+=Dfs(s,19260817);
		//cerr<<ans<<endl;
		if(ans!=n)		return puts("No"),void();

		for(re int i=1;i<=n;++i){
			for(re int j=head[i];j;j=nex[j])if(!e[j] && j!=s && j!=t){
				//cerr<<i<<" "<<ver[j]<<endl;
				P[i]=ver[j];
				P[ver[j]]=i;
				Val+=a[i][ver[j]-n];
				break;
			}
		}

		for(re int I=1;I<=3e5;++I){
			//cerr<<I<<endl;
			if(Val%K==0)	return puts("Yes"),void();
			int x=rand()%n+1;
			Find(x,P[x]);

			for(re int i=0;i<=n*2;++i) vis[i]=0;

			/*int CH=0;
			for(re int i=1;i<=n;++i) CH+=a[i][P[i]-n];
			assert(CH==Val);*/
		}
		puts("No");
	}
	return;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
	nu=1;
	Input();
	solve();
	return 0;
}
