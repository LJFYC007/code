#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 4e5 + 10;

int n, m;
namespace Subtask1
{
	map<string, bool> Map1, Map2;
	char s[maxn];
	int k, T;

	inline void Check()
	{
		REP(i ,1, n) cout << s[i]; cout << endl;
		exit(0);
	}

	inline void DFS(int x)
	{
		if ( x == n + 1 ) { Check(); return ; } 
		string t; if ( k <= x ) REP(i, x - k + 1, x - 1) t = t + s[i];
		string tt; if ( k < x ) REP(i, x - k, x - 1) tt = tt + s[i];
		REP(i, 0, m - 1)
		{
			s[x] = i + 'a';
			if ( k <= x && x <= T && Map1[t + s[x]] ) continue ; 
			if ( k + 1 <= x && Map2[tt + s[x]] ) continue ; 
			if ( k <= x && x <= T ) Map1[t + s[x]] = true;
			Map2[tt + s[x]] = true;
			DFS(x + 1);
			if ( k <= x && x <= T ) Map1[t + s[x]] = false;
			Map2[tt + s[x]] = false;
		}
	}

	inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r *= a; a *= a; b >>= 1; } return r; } 

	int main()
	{
		k = 1; while ( power(m, k) + k - 1 <= n ) ++ k; 
		-- k; T = power(m, k) + k - 1; DFS(1);
		return 0;
	}
}

unordered_map<string, int> Map;
map<int, int> Edge[maxn];
string b[maxn];
char s[maxn], lst[maxn];
int k, N, T, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], belong[maxn];
bool vis[maxn];
vector<int> ans[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; Edge[u][v] = e; }

inline void DFS1(int u, int t)
{
	for ( int i = Begin[u]; i; Begin[u] = i = Next[i] ) 
	{
		int v = To[i]; if ( vis[i] ) continue ; 
		vis[i] = true; DFS1(v, t); ans[t].push_back(W[i]);
	}
}

inline void DFS(int x)
{
	if ( x == k + 1 )
	{
		string t; REP(i, 1, k) t = t + s[i];
		Map[t] = ++ N; b[N] = t; return ; 
	}
	REP(i, 1, m) { s[x] = i + 'a' - 1; DFS(x + 1); } 
}

inline void DFS2(int x)
{
	if ( x == k + 2 )
	{
		string t; REP(i, 1, k) t = t + s[i];
		string T; REP(i, 2, k + 1) T = T + s[i];
		add(Map[t], Map[T], s[k + 1]); 
		return ; 
	}
	REP(i, 1, m) { s[x] = i + 'a' - 1; DFS2(x + 1); } 
}

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r *= a; a *= a; b >>= 1; } return r; } 

int main()
{
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	scanf("%d%d", &n, &m);
	if ( n <= m ) 
	{
		REP(i, 1, n) printf("%c", 'a' + i - 1); puts("");
		return 0; 
	}
	if ( m == 1 ) 
	{
		REP(i, 1, n) printf("%c", 'a'); puts("");
		return 0; 
	}

	if ( m != 2 ) return Subtask1 :: main();

	k = 1; while ( power(m, k) + k - 1 <= n ) ++ k; 
	-- k; T = power(m, k) + k - 1; 
	-- k; DFS(1); DFS2(1); DFS1(1, 1);
	reverse(ans[1].begin(), ans[1].end());
	REP(i, 1, k) lst[i] = b[1][i - 1];
	int len = k; for ( auto it : ans[1] ) lst[++ len] = it;

	++ k; N = e = 0; mem(Begin); mem(vis); Map.clear(); REP(i, 1, n) ans[i].clear();
	DFS(1); DFS2(1);

	REP(i, 1, len - k + 1) { string t; REP(j, 1, k) t = t + lst[i + j - 1]; belong[i] = Map[t]; }
	REP(i, 1, len - k) vis[Edge[belong[i]][belong[i + 1]]] = true;
	REP(i, 1, T - k + 1) DFS1(belong[i], i);	

	int num = T;
	REP(i, 1, T - k + 1) 
	{
		num += ans[i].size();
		if ( num >= n ) 
		{
			num = T; int nxt = i == T - k + 1 ? 1 : i + 1;
			REP(j, 1, k - 1) printf("%c", b[belong[nxt]][j - 1]);
			REP(j, i + 1, T - k + 1) printf("%c", b[belong[j]][k - 1]);
			REP(j, 1, i)
			{
				printf("%c", b[belong[j]][k - 1]);
				reverse(ans[j].begin(), ans[j].end());
				for ( auto it : ans[j] ) 
				{ 
					if ( num < n ) printf("%c", it); 
					++ num; 
				}
			}
			puts(""); return 0;
		}
	}
	return 0;
}
