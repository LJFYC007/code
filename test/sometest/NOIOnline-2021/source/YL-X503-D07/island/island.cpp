/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月27日 星期六 09时14分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e5 + 10;
const int N = 24;
const int INF = 0x3f3f3f3f;

int n, m, k, a[maxn], b[maxn], ans[maxn], Root[maxn], tot;
pii p[maxn];
struct node 
{ 
	int id, c, d; 
	bool operator < (const node &a) const { return d < a.d; } 
} ;
struct NODE { int son[2], sum; } Trie[maxn << 6];
vector<node> Tree[maxn << 2];

inline int NewNode() { ++ tot; Trie[tot].son[0] = Trie[tot].son[1] = Trie[tot].sum = 0; return tot; } 

inline int Insert1(int p, int val, int x)
{
	int q = NewNode(); Trie[q] = Trie[p]; ++ Trie[q].sum;
	if ( !x ) return q; int c = (val >> x - 1) & 1; 
	Trie[q].son[c] = Insert1(Trie[q].son[c], val, x - 1);
	return q;
}

inline int Query1(int p, int val, int x)
{
	int ret = 0;
	for ( int i = N - 1; i >= 0; -- i ) 
	{
		if ( !p ) return ret;
		int c = (val >> i) & 1; 
		if ( (x >> i) & 1 ) 
		{
			ret += Trie[Trie[p].son[c]].sum;
			p = Trie[p].son[c ^ 1];
		}
		else p = Trie[p].son[c];
	}
	ret += Trie[p].sum; return ret;
}

inline int Query2(int val)
{
	int ret = 0, p = 1;
	for ( int i = N - 1; i >= 0; -- i ) 
	{
		int c = (val >> i) & 1;
		p = Trie[p].son[c];
		if ( !p ) return ret;
		ret += Trie[p].sum;
	}
	return ret;
}

inline void Modify(int root, int l, int r, int L, int R, node val)
{
	if ( L <= l && r <= R ) { Tree[root].push_back(val); return ; } 
	int Mid = l + r >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
}

inline void Solve(int root, int l, int r)
{
	k = 0; REP(i, l, r) p[++ k] = pii(b[i], a[i]); sort(p + 1, p + k + 1);	
	sort(Tree[root].begin(), Tree[root].end()); tot = 0; Root[k + 1] = NewNode();
	for ( int i = k; i >= 1; -- i ) Root[i] = Insert1(Root[i + 1], p[i].second, N);	
	int now = 1;
	for ( int i = 0; i < Tree[root].size(); ++ i ) 
	{
		while ( Tree[root][i].d > p[now].first && now <= k ) ++ now;
		ans[Tree[root][i].id] += Query1(Root[now], Tree[root][i].c, Tree[root][i].d);
	}

	tot = 0; NewNode(); now = 0; p[k + 1].first = INF;
	REP(i, 1, k)
	{
		int pos = 1;
		for ( int j = N - 1; j >= 0; -- j ) 
		{
			int c = (p[i].second >> j) & 1;
			if ( !Trie[pos].son[0] ) Trie[pos].son[0] = NewNode();
			if ( !Trie[pos].son[1] ) Trie[pos].son[1] = NewNode();
			if ( (p[i].first >> j) & 1 )
			{
				++ Trie[Trie[pos].son[c]].sum;
				pos = Trie[pos].son[c ^ 1];
			}
			else pos = Trie[pos].son[c];
		}
		++ Trie[pos].sum;

		while ( now < Tree[root].size() && Tree[root][now].d <= p[i + 1].first )
		{
			if ( Tree[root][now].d > p[i].first )
				ans[Tree[root][now].id] += Query2(Tree[root][now].c);
			++ now; 	
		}
	}

	// for ( auto it : Tree[root] ) REP(i, 1, k) if ( it.d <= p[i].first ) 
		// ans[it.id] += (it.c ^ p[i].second) <= it.;

	if ( l == r ) return ; 
	int Mid = l + r >> 1; Solve(lson, l, Mid); Solve(rson, Mid + 1, r);
}

int main()
{
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
	scanf("%d%d", &n, &m); REP(i, 1, n) scanf("%d%d", &a[i], &b[i]);
	REP(i, 1, m) { int l, r, c, d; scanf("%d%d%d%d", &l, &r, &c, &d); Modify(1, 1, n, l, r, {i, c, d}); }
	Solve(1, 1, n);
	// cerr << Trie[0].son[0] << " " << Trie[0].son[1] << " " << Trie[0].sum << endl;
	REP(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}
