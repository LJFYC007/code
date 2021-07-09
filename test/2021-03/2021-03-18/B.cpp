/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月18日 星期四 15时13分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 998244353;

int N, m, a[maxn], ret1, ret2, ret3;
struct node { int sum1, sum2, sum3, len, lazy; } Tree[maxn << 2];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 

inline void PushUp(int root)
{
	Tree[root].sum1 = (Tree[lson].sum1 + Tree[rson].sum1) % Mod;
	Tree[root].sum2 = Tree[lson].sum2 * Tree[rson].sum2 % Mod;
	Tree[root].sum3 = (Tree[lson].sum3 * Tree[rson].sum2 + Tree[rson].sum3 * Tree[lson].sum2) % Mod;
}

inline void PushTag(int root, int val)
{
	Tree[root].lazy = Tree[root].lazy * val % Mod;
	Tree[root].sum1 = Tree[root].sum1 * val % Mod;
	int x = power(val, Tree[root].len - 1);
	Tree[root].sum3 = Tree[root].sum3 * x % Mod;
	x = x * val % Mod; Tree[root].sum2 = Tree[root].sum2 * x % Mod;
}

inline void PushDown(int root)
{
	if ( Tree[root].lazy == 1 ) return ; 
	PushTag(lson, Tree[root].lazy);
	PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = 1;
}

inline void Build(int root, int l, int r)
{
	Tree[root].len = r - l + 1; Tree[root].lazy = 1;
	if ( l == r ) { Tree[root].sum1 = Tree[root].sum2 = a[l]; Tree[root].lazy = Tree[root].sum3 = 1; return ; } 
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r); PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

inline void Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) 
	{
		ret3 = (ret3 * Tree[root].sum2 + ret2 * Tree[root].sum3) % Mod;
		ret2 = ret2 * Tree[root].sum2 % Mod; ret1 = (ret1 + Tree[root].sum1) % Mod;
		return ; 
	} 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Query(lson, l, Mid, L, R);
	if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &N, &m); REP(i, 1, N) scanf("%lld", &a[i]);
	Build(1, 1, N);
	while ( m -- ) 
	{
		int op, l, r, k; scanf("%lld%lld%lld%lld", &op, &l, &r, &k);
		if ( op == 1 ) { Modify(1, 1, N, l, r, k); continue ; }
		ret1 = 0; ret2 = 1; ret3 = 0; Query(1, 1, N, l, r);
		int ans = 0, n = r - l + 1;
		if ( (n - 1 - k) % 2 == 0 ) ++ ans;
		if ( k == 1 ) ans = (ans + sgn(n - 1) * ret2) % Mod;
		if ( k == 2 ) ans = (ans + sgn(n) * ret3 + sgn(n - 1) * ret1 * ret2) % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
