/***************************************************************
	File name: pigeons.cpp
	Author: ljfcnyali
	Create time: 2021年05月05日 星期三 10时32分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define fa(x) Tree[x].fa
#define ls(x) Tree[x].son[0]
#define rs(x) Tree[x].son[1]
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, ans;
struct node { int son[2], fa, tag, sum[2][2], val; } Tree[maxn];

inline bool IsRoot(int x) { return ls(fa(x)) != x && rs(fa(x)) != x; } 
inline int calc(int x) { return x * x; }
inline int Get(int x, int o) { return Tree[x].sum[0][o] + Tree[x].sum[1][o]; }
inline void PushUp(int root) 
{ 
	REP(o, 0, 1) Tree[root].sum[0][o] = Get(ls(root), o ^ 1) + Get(rs(root), o ^ 1);
	++ Tree[root].sum[0][0];
} 
inline void PushTag(int root) { swap(ls(root), rs(root)); Tree[root].tag ^= 1; }
inline void PushDown(int root)
{
    if ( !Tree[root].tag ) return ; Tree[root].tag = 0;
    if ( ls(root) ) PushTag(ls(root)); if ( rs(root) ) PushTag(rs(root));
}
inline void Rotate(int x)
{
    int y = fa(x), z = fa(y), k = rs(y) == x, w = Tree[x].son[!k];
    if ( !IsRoot(y) ) Tree[z].son[rs(z) == y] = x; 
    fa(x) = z; fa(y) = x; if ( w ) fa(w) = y;
    Tree[x].son[!k] = y; Tree[y].son[k] = w;
    PushUp(y); PushUp(x);
}
inline void Maintain(int x) { if ( !IsRoot(x) ) Maintain(fa(x)); PushDown(x); } 
inline void Splay(int x)
{
	Maintain(x);
    while ( !IsRoot(x) ) 
    {
        int y = fa(x), z = fa(y);
        if ( !IsRoot(y) ) Rotate((ls(y) == x) ^ (ls(z) == y) ? x : y);
        Rotate(x);
    }
}
inline void Access(int root) 
{ 
	for ( int x = 0; root; x = root, root = fa(root) ) 
	{ 
		Splay(root); 
		REP(o, 0, 1) 
		{
			Tree[root].sum[1][o] += Get(rs(root), o ^ 1) - Get(x, o ^ 1);
			Tree[root].val += calc(Get(rs(root), o)) - calc(Get(x, o));
		}
		rs(root) = x; PushUp(root); 
	} 
}
inline void MakeRoot(int x) { Access(x); Splay(x); PushTag(x); }
inline int FindRoot(int x) { Access(x); Splay(x); while ( ls(x) ) x = ls(x); Splay(x); return x; } 
inline void Link(int u, int v) 
{ 
	MakeRoot(u); if ( FindRoot(v) == u ) return ; 
	MakeRoot(v);
	REP(o, 0, 1) ans += Get(u, o) * Get(v, o ^ 1);
	REP(o, 0, 1) { Tree[v].sum[1][o] += Get(u, o ^ 1); Tree[v].val += calc(Get(u, o)); }
	fa(u) = v; PushUp(v);
} 
inline void Split(int u, int v) { MakeRoot(u); Access(v); Splay(v); }
inline void Cut(int u, int v) 
{ 
	Split(u, v); 
	if ( fa(u) == v && ls(v) == u ) 
	{
		REP(o, 0, 1) { Tree[v].sum[1][o] -= Get(u, o ^ 1); Tree[v].val -= calc(Get(u, o)); }
		REP(o, 0, 1) ans += Get(u, o) * Get(v, o ^ 1);
		fa(u) = ls(v) = 0; PushUp(v);
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("pigeons.in", "r", stdin);
    freopen("pigeons.out", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m); ans = n;
	REP(i, 1, n) Tree[i].sum[0][0] = 1;
	while ( m -- ) 
	{
		int op, x, y; scanf("%lld%lld%lld", &op, &x, &y);
		if ( op == 1 ) Link(x, y); else Cut(x, y);
		printf("%lld\n", ans);
	}
    return 0;
}
