/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月19日 星期一 11时10分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

typedef __uint128_t u128;
inline u128 read() {
    static char buf[100]; scanf("%s", buf);
    u128 res = 0;
    for(int i = 0;buf[i];++i)
        res = res << 4 | (buf[i] <= '9' ? buf[i] - '0' : buf[i] - 'a' + 10);
    return res;
}
inline void output(u128 res) {
    if(res >= 16)
        output(res / 16);
    putchar(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
}

const int maxn = 3e5 + 10;
const u128 M = -1;

int n, m, q; u128 a[maxn];
struct node { int len; u128 sum[20], lazy; } Tree[maxn << 2];
#define lson root << 1
#define rson root << 1 | 1

inline void PushUp(int root) 
{ 
	u128 c = 0; 
	REP(i, 0, Tree[root].len)
	{
		u128 x = Tree[lson].sum[i] & Tree[rson].sum[i];
		u128 y = (Tree[lson].sum[i] ^ x) | (Tree[rson].sum[i] ^ x);
		u128 z = y & c;
		Tree[root].sum[i] = (y ^ z) | (c ^ z);	
		c = x | z;
	}
} 

inline void PushTag(int root, u128 val)
{
	Tree[root].lazy &= val;
	REP(i, 0, Tree[root].len) Tree[root].sum[i] &= val;
}

inline void PushDown(int root)
{
	if ( Tree[root].lazy == M ) return ;
	PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = M;
}

inline void Build(int root, int l, int r)
{
	Tree[root].lazy = M;
	if ( l == r ) { Tree[root].sum[0] = a[l]; return ; } 
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);	
	Tree[root].len = Tree[lson].len + 1; PushUp(root);
}

inline u128 Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) 
	{
		u128 ret = 0;
		REP(i, 0, Tree[root].len) ret += Tree[root].sum[i] * (1 << i);
		return ret;
	}
	int Mid = l + r >> 1; u128 ret = 0; PushDown(root);
	if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
	if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
	return ret;
}

inline void Modify(int root, int l, int r, int L, int R, u128 val)
{
	if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

inline void Fuck(int root, int l, int r, u128 val)
{
	bool flag = false;
	REP(i, 0, Tree[root].len) if ( Tree[root].sum[i] ) flag = true;
	if ( !flag ) return ;
	if ( l == r ) { Tree[root].sum[0] /= val; return ; } 
	int Mid = l + r >> 1; PushDown(root);
	Fuck(lson, l, Mid, val); Fuck(rson, Mid + 1, r, val);
	PushUp(root);
}

inline void Delete(int root, int l, int r, int L, int R, u128 val)
{
	if ( L <= l && r <= R ) 
	{ 
		Fuck(root, l, r, val);
		return ;
	} 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Delete(lson, l, Mid, L, R, val);
	if ( Mid < R ) Delete(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &q); REP(i, 1, n) a[i] = read(); 
	Build(1, 1, n);
	REP(i, 1, q)
	{
		int op, l, r; u128 v; scanf("%d%d%d", &op, &l, &r); 
		if ( op == 1 ) 
		{
			v = read(); if ( v == 1 ) continue ; 
			Delete(1, 1, n, l, r, v);
		}
		if ( op == 2 ) Modify(1, 1, n, l, r, read());
		if ( op == 3 ) { output(Query(1, 1, n, l, r)); putchar('\n'); }
	}
    return 0;
}
