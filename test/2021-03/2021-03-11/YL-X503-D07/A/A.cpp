#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define int long long

const int maxn = 4e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, W[maxn], s, t, id, sum, Max, ans, num, deg[maxn];
pii a[maxn];
map<int, int> Map;
vector<int> p;
bool vis[maxn], flag;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; ++ deg[u]; } 

inline void DFS1(int u, int fa)
{
	vis[u] = true; p.push_back(u); num += deg[u];
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( vis[v] ) { flag = true; s = u; t = v; id = i; } 
		else DFS1(v, u);
	}
}

inline void DFS2(int u, int id)
{
	vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( i == id || vis[v] ) continue ; 
		sum += W[i]; DFS2(v, id);
	}
}

inline void DFS3(int u, int fa)
{
	Max = max(Max, sum);
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		sum -= W[i]; sum += W[i ^ 1]; DFS3(v, u);
		sum += W[i]; sum -= W[i ^ 1];
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); Map[a[i].x] = Map[a[i].y] = true; } 
	for ( auto it : Map ) Map[it.first] = ++ m; 
	REP(i, 1, n) { add(Map[a[i].x], Map[a[i].y], a[i].x); add(Map[a[i].y], Map[a[i].x], a[i].y); } 

// 	REP(i, 1, n) cout << Map[a[i].x] << " " << Map[a[i].y] << endl;

	REP(i, 1, m) if ( !vis[i] ) 
	{
		p.clear(); flag = false; num = 0; DFS1(i, 0); sum = Max = 0;
//		cout << num << " " << p.size() << endl;
		if ( num > p.size() * 2 ) { puts("0"); return 0; } 
		if ( !flag ) 
		{ 
			for ( auto it : p ) vis[it] = false;
			DFS2(i, 0); DFS3(i, 0); 
		} 
		else 
		{ 
			for ( auto it : p ) vis[it] = false;
			sum = W[id ^ 1]; DFS2(s, id); Max = sum; 
			for ( auto it : p ) vis[it] = false;
			sum = W[id]; DFS2(t, id ^ 1); Max = max(Max, sum); 
		} 
		ans += Max;
	}

	printf("%lld\n", ans);
	return 0;
}
