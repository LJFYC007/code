/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年04月05日 星期一 09时03分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;
const int N = 2e9;

int n, ans, f[maxn], tot;
pii a[maxn];
struct node { int lson, rson, Min1, Min2; } Tree[maxn << 6];

#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
inline void Modify(int &root, int l, int r, int pos, int val1, int val2)
{
	if ( !root ) { root = ++ tot; Tree[root].Min1 = Tree[root].Min2 = INF; } 
	if ( l == r ) 
	{
		Tree[root].Min1 = min(Tree[root].Min1, val1);
		Tree[root].Min2 = min(Tree[root].Min2, val2);
		return ; 
	}
	int Mid = l + r >> 1; 
	if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val1, val2);
	else Modify(rs(root), Mid + 1, r, pos, val1, val2);
	Tree[root].Min1 = min(Tree[ls(root)].Min1, Tree[rs(root)].Min1);
	Tree[root].Min2 = min(Tree[ls(root)].Min2, Tree[rs(root)].Min2);
}

inline int Query1(int root, int l, int r, int L, int R)
{
	if ( !root ) return INF;
	if ( L <= l && r <= R ) return Tree[root].Min1;
	int Mid = l + r >> 1, ret = INF;
	if ( L <= Mid ) ret = min(ret, Query1(ls(root), l, Mid, L, R));
	if ( Mid < R ) ret = min(ret, Query1(rs(root), Mid + 1, r, L, R));
	return ret;
}

inline int Query2(int root, int l, int r, int L, int R)
{
	if ( !root ) return INF;
	if ( L <= l && r <= R ) return Tree[root].Min2;
	int Mid = l + r >> 1, ret = INF;
	if ( L <= Mid ) ret = min(ret, Query2(ls(root), l, Mid, L, R));
	if ( Mid < R ) ret = min(ret, Query2(rs(root), Mid + 1, r, L, R));
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) { scanf("%lld%lld", &a[i].first, &a[i].second); ans += a[i].second; } 
	sort(a + 1, a + n + 1); f[1] = 0;
	Tree[0].Min1 = Tree[0].Min2 = INF;
	int Root = 0; Modify(Root, 0, N, a[1].first + a[1].second, 0, -a[1].first - a[1].second);
	REP(i, 2, n)
	{
		f[i] = min(Query1(Root, 0, N, a[i].first, N), Query2(Root, 0, N, 0, a[i].first) + a[i].first);
		// REP(j, 1, i - 1) f[i] = min(f[i], f[j] + max(0ll, a[i].first - a[j].first - a[j].second));
		// cout << a[i].first << " " << f[i] << " " << a[i].first + a[i].second << endl; // " " << Query1(Root, 0, N, a[i].first, N) << endl;
		Modify(Root, 0, N, a[i].first + a[i].second, f[i], f[i] - a[i].first - a[i].second);
	}
	printf("%lld\n", ans + f[n]);
    return 0;
}
