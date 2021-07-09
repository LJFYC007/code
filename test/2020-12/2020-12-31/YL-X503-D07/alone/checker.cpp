#include<cstdio>
#include<bitset>
#include<algorithm>
#include<vector>
#define fo(x,a,b) for(int x=(a),_e=(b);x<=_e;x++)
#define fd(x,a,b) for(int x=(a),_e=(b);x>=_e;x--)
#define ww printf
#define pb push_back

using namespace std;
typedef long long ll;
const int N=100005;
int n,m,ans,q[N],ty;
bool vis[N],c[N];
vector<int> E[N];

void Fail(){
	puts("Format error.");
	fclose(stdin);
	exit(0);
}

void WA(){
	puts("Yout Output is not correct.");
	fclose(stdin);
	exit(0);
}

int main(int argc,char* argv[]){
	int x,y;
	freopen(argv[1],"r",stdin);
	scanf("%d",&ty);
	scanf("%d %d",&n,&m);
	fo(i,1,m) scanf("%d %d",&x,&y), E[x].pb(y), E[y].pb(x);

	freopen(argv[2],"r",stdin);
	scanf("%d",&ans);
	if(ans>n) Fail();
	fo(i,1,ans) {
		if(!(~scanf("%d",&x))) Fail();
		if(x<1 || x>n) Fail();
		if(vis[x]) Fail();
		vis[x]=true;
		q[i]=x, c[x]=true;
	}
	fo(i,1,n) vis[i]=false;
	fo(o,1,ans) {
		x=q[o];
		int cnt=0;
		for(int go:E[x]) {
			if(c[go]) ++cnt, ww("%d %d\n",x,go);
		}
		if(ty==1 && cnt || ty==2 && cnt<ans-1) WA();
		// ww("%d : suc\n",x);
	}

	puts("OK");
	fclose(stdin);
	return 0;
}
