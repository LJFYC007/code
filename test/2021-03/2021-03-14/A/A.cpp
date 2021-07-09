/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年03月14日 星期日 08时58分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define k first
#define b second
typedef long long LL;

const int maxn = 1e4 + 10;
const int INF = 1e18;
const int N = 1e6;

int n, k, h[maxn], f[maxn][110], Root[110], tot;
struct node { int lson, rson; pii line; } Tree[maxn << 7];

inline int F(pii l, int pos) { return pos * l.k + l.b; } 

inline void Modify(int &root, int l, int r, pii x)
{
	if ( !root ) { root = ++ tot; Tree[root].line = x; return ; } 
	int Mid = (l + r) >> 1;
	if ( F(Tree[root].line, Mid) > F(x, Mid) ) swap(Tree[root].line, x);
	if ( l == r ) return ; 
	if ( x.k > Tree[root].line.k ) Modify(ls(root), l, Mid, x);
	else Modify(rs(root), Mid + 1, r, x);
}

inline int Query(int root, int l, int r, int pos)
{
	if ( !root ) return INF;
	if ( l == r ) return F(Tree[root].line, pos);
	int Mid = l + r >> 1, ret = F(Tree[root].line, pos);
	if ( pos <= Mid ) ret = min(ret, Query(ls(root), l, Mid, pos));
	else ret = min(ret, Query(rs(root), Mid + 1, r, pos));
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &k);
	REP(i, 1, n) scanf("%lld", &h[i]);
	Modify(Root[0], 1, N, pii(- 2 * h[1], h[1] * h[1]));
	REP(i, 1, n) for ( int j = k; j >= 1; -- j ) 
	{
		f[i][j] = Query(Root[j - 1], 1, N, h[i]) + h[i] * h[i];
		Modify(Root[j], 1, N, pii(-2 * h[i + 1], h[i + 1] * h[i + 1] + f[i][j]));
	}
	printf("%lld\n", f[n][k]);
    return 0;
}
