#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int seed = 233;
const int Mod = 998244353;

int n, tot, pre[2510][maxn], suf[2510][maxn], sum;
int Begin[maxn * maxn], Next[maxn * maxn], To[maxn * maxn], e;
struct node
{
	int pos, l, r;
	node(int a = 0, int b = 0, int c = 0) { pos = a; l = b; r = c; }
} p[maxn * maxn];
map<int, pii> Map;
char s[2510][maxn];
vector<int> t;
bool vis[10010], use[10010];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
	if ( vis[u] ) return ; vis[u] = true; t.push_back(u); ++ sum;
	for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i]);
}

inline void Check()
{
	REP(j, 0, n - 1)
	{
		int num = 0;
		for ( int i = Begin[t[j]]; i; i = Next[i] )
		{
			if ( use[To[i]] ) continue ; use[To[i]] = true; ++ num;
		}
		for ( int i = Begin[t[j]]; i; i = Next[i] ) use[To[i]] = false;
		if ( num < (n - 1) * 2 ) return ;
	}
	puts("Yes");
	REP(i, 0, n - 1) { REP(j, p[t[i]].l, p[t[i]].r) printf("%c", s[p[t[i]].pos][j]); puts(""); }
	exit(0);
}

signed main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	scanf("%d", &n);
	REP(i, 1, n * (n - 1))
	{
		scanf("%s", s[i] + 1);
		int len = str(s[i] + 1); sum = 0;
		REP(j, 1, len)
		{
			sum = (sum * seed + s[i][j] - 'a' + 1) % Mod;
			if ( Map.count(sum) ) ++ Map[sum].second;
			else { Map[sum] = pii(++ tot, 1); p[tot] = node(i, 1, j); }
			pre[i][j] = sum;
		}
		sum = 0; int x = 1;
		for ( int j = len; j >= 1; -- j )
		{
			sum = (sum + (s[i][j] - 'a' + 1) * x) % Mod;
			x = x * seed % Mod;
			if ( Map.count(sum) ) ++ Map[sum].second;
			else { Map[sum] = pii(++ tot, 1); p[tot] = node(i, j, len); }
			suf[i][j] = sum;
		}
	}
	REP(i, 1, n * (n - 1))
	{
		int len = str(s[i] + 1);
		REP(j, 1, len - 1)
		{
			if ( Map[pre[i][j]].second >= (n - 1) * 2 )
			{
				int t = Map[pre[i][j]].first;
				printf("%d ", Map[pre[i][j]].second);
				REP(k, p[t].l, p[t].r) printf("%c", s[p[t].pos][k]); puts("");
			}
			if ( Map[pre[i][j]].second >= (n - 1) * 2 && Map[suf[i][j + 1]].second >= (n - 1) * 2 )
			{
				add(Map[pre[i][j]].first, Map[suf[i][j + 1]].first);
				add(Map[suf[i][j + 1]].first, Map[pre[i][j]].first);
			}
		}
	}
	REP(i, 1, tot)
	{
		if ( vis[i] ) continue ;
		sum = 0; t.clear();
		DFS(i);
		if ( sum != n ) continue ;
		Check();
	}
	puts("No");
	return 0;
}
