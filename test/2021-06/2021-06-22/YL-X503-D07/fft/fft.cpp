/***************************************************************
	File name: fft.cpp
	Author: ljfcnyali
	Create time: 2021年06月22日 星期二 08时17分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 998244353;
const int N = 1e9 + 2e5;

int k, m, a[maxn], Root, tot, ans;
struct node { int lson, rson, num[2], lazy; } Tree[maxn << 6];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % Mod; a = 1ll * a * a % Mod; b >>= 1; } return r; } 

inline int calc(LL n) 
{ 
	if ( n < 0 ) return 0; LL val = power(2, n);
	return (val * 4 + 3 * n * val + (n * n % Mod) * val - 1) % Mod;
}

inline int NewNode(int l, int r) { ++ tot; Tree[tot].num[0] = r - l + 1; return tot; }
inline void PushUp(int root) { REP(i, 0, 1) Tree[root].num[i] = (Tree[ls(root)].num[i] + Tree[rs(root)].num[i]) % Mod; }
inline void PushTag(int root, int l, int r, int val) { Tree[root].num[val] = r - l + 1; Tree[root].num[val ^ 1] = 0; Tree[root].lazy = val; }
inline void PushDown(int root, int l, int r)
{
	if ( Tree[root].lazy == -1 ) return ;
	int Mid = l + r >> 1;
	if ( !ls(root) ) ls(root) = NewNode(l, Mid); PushTag(ls(root), l, Mid, Tree[root].lazy);
	if ( !rs(root) ) rs(root) = NewNode(Mid + 1, r); PushTag(rs(root), Mid + 1, r, Tree[root].lazy);
	Tree[root].lazy = -1;
}

inline void Modify(int &root, int l, int r, int L, int R, int val)
{
	if ( !root ) root = NewNode(l, r);
	if ( L <= l && r <= R ) { PushTag(root, l, r, val); return ; } 
	int Mid = l + r >> 1; PushDown(root, l, r);
	if ( L <= Mid ) Modify(ls(root), l, Mid, L, R, val);
	if ( Mid < R ) Modify(rs(root), Mid + 1, r, L, R, val);
	PushUp(root);
}

inline int find(int &root, int l, int r, int L, int R, int val)
{
	if ( !root ) root = NewNode(l, r);
	if ( L <= l && r <= R ) 
	{
		if ( Tree[root].num[val] == 0 ) return -1;
		if ( l == r ) return l;
	}
	int Mid = l + r >> 1; PushDown(root, l, r);
	if ( L <= Mid ) { int x = find(ls(root), l, Mid, L, R, val); if ( x != -1 ) return x; }
	if ( Mid < R ) return find(rs(root), Mid + 1, r, L, R, val);
	return -1;
}

inline int Solve()
{
	int ret = ans, pos = find(Root, 0, N, 0, N, 1);
	ret = (ret - 1ll * (pos + 1) * power(2, pos + 1)) % Mod;
	return ret;
}

int main()
{
    freopen("fft.in", "r", stdin);
    freopen("fft.out", "w", stdout);
	scanf("%d%d", &k, &m);
	REP(i, 1, k)
	{
		int l, r; scanf("%d%d", &l, &r);
		Modify(Root, 0, N, l, r, 1);
		ans = (ans + calc(r) - calc(l - 1)) % Mod;
	}
	while ( m -- ) 
	{
		int op, x; scanf("%d%d", &op, &x);
		int pos = find(Root, 0, N, x, N, op);
		if ( pos != x ) 
		{
			if ( op == 0 ) ans = (ans - calc(pos - 1) + calc(x - 1)) % Mod;
			else ans = (ans + calc(pos - 1) - calc(x - 1)) % Mod;
			Modify(Root, 0, N, x, pos - 1, op);
		}
		if ( op == 0 ) ans = (ans + calc(pos) - calc(pos - 1)) % Mod;
		else ans = (ans - calc(pos) + calc(pos - 1)) % Mod;
		Modify(Root, 0, N, pos, pos, op ^ 1);
		printf("%d\n", (Solve() + Mod) % Mod);
	}
    return 0;
}
