/***************************************************************
	File name: CF587F.cpp
	Author: ljfcnyali
	Create time: 2021年05月03日 星期一 20时15分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int B = 1500;
const int maxn = 2e5 + 10;
const int maxm = 1e5 / B + 10;

int n, m, k, dfn[maxn], tot = 1, lst, cnt, size[maxn], l;
int p[maxn], c[maxn], a[maxn], id[maxn], f[maxn][maxm];
LL ans[maxn], g[maxn][maxm];
struct node { int Next[26], fa, len; } Tree[maxn];
vector<int> Edge[maxn]; vector<pii> Q[maxn];
string s[maxn]; 

inline int lowbit(int x) { return x & -x; } 
inline void modify(int pos, int val) { for ( int i = pos; i <= cnt; i += lowbit(i) ) c[i] += val; } 
inline int query(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; } 

inline void Extend(int c)
{
	int p = lst, cur = ++ tot; lst = cur; Tree[cur].len = Tree[p].len + 1;
	while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; } 
	if ( !p ) { Tree[cur].fa = 1; return ; } 
	int q = Tree[p].Next[c];
	if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; } 
	int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
	while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; } 
	Tree[q].fa = Tree[cur].fa = clone;
}

inline void DFS(int u)
{
	dfn[u] = ++ cnt; size[u] = 1;
	for ( auto v : Edge[u] ) 
	{
		DFS(v); size[u] += size[v]; 
		REP(j, 1, k) f[u][j] += f[v][j];
	} 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m); 
	REP(i, 1, n) { cin >> s[i]; lst = 1; for ( auto it : s[i] ) Extend(it - 'a'); }
	REP(i, 1, n) 
	{ 
		int x = 1; if ( s[i].length() > B ) id[i] = ++ k;
		for ( auto it : s[i] ) 
		{ 
			x = Tree[x].Next[it - 'a']; p[++ l] = x; 
			if ( s[i].length() > B ) ++ f[x][k];
		} 
		a[i] = l; 
	}
	REP(i, 2, tot) Edge[Tree[i].fa].push_back(i); DFS(1);
	REP(i, 1, n) REP(j, 1, k) g[i][j] = g[i - 1][j] + f[p[a[i]]][j];
	REP(i, 1, m) 
	{ 
		int l, r, k; scanf("%d%d%d", &l, &r, &k); 
		if ( id[k] ) ans[i] = g[r][id[k]] - g[l - 1][id[k]];
		else { Q[l - 1].push_back(pii(k, -i)); Q[r].push_back(pii(k, i)); }
	}
	REP(i, 1, n)
	{
		modify(dfn[p[a[i]]], 1); modify(dfn[p[a[i]]] + size[p[a[i]]], -1);
		for ( auto it : Q[i] ) 
		{
			int ret = 0;
			REP(j, 1, s[it.first].length()) ret += query(dfn[p[a[it.first - 1] + j]]);
			ans[abs(it.second)] += ret * (it.second < 0 ? -1 : 1);
		}
	}
	REP(i, 1, m) printf("%lld\n", ans[i]);
    return 0;
}
