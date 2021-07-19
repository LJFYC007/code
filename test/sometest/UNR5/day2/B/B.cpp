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
const int M = (1 << 30) - 2;

int n, m, q, f[maxn], b[maxn], MaxBit[maxn];
u128 a[maxn], p[128], c[maxn];
struct node { int op, l, r; u128 v; } Q[maxn];
struct Segment
{
	struct Node { int sum; } Tree[maxn << 2];
#define lson root << 1
#define rson root << 1 | 1
	
	inline void PushUp(int root) { Tree[root].sum = (Tree[lson].sum & M) + (Tree[rson].sum & M); } 
	inline void PushDown(int root)
	{
		if ( Tree[root].sum != 1 ) return ;
		Tree[lson].sum = Tree[rson].sum = 1; Tree[root].sum = 0;
	}

	inline void Build(int root, int l, int r)
	{
		if ( l == r ) { Tree[root].sum = b[l] << 1; return ; } 
		int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);	
		PushUp(root);
	}

	inline int Query(int root, int l, int r, int L, int R)
	{
		if ( !(Tree[root].sum & M) || (L <= l && r <= R) ) return Tree[root].sum >> 1; 
		int Mid = l + r >> 1, ret = 0; PushDown(root);
		if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
		if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
		return ret;
	}

	inline void Modify(int root, int l, int r, int pos, int val)
	{
		if ( l == r ) { Tree[root].sum = val << 1; return ; } 
		int Mid = l + r >> 1; PushDown(root);
		if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
		else Modify(rson, Mid + 1, r, pos, val);
		PushUp(root);
	}

	inline void Delete(int root, int l, int r, int L, int R)
	{
		if ( !(Tree[root].sum & M) ) return ; 
		if ( L <= l && r <= R ) { Tree[root].sum = 1; return ; } 
		int Mid = l + r >> 1; PushDown(root);
		if ( L <= Mid ) Delete(lson, l, Mid, L, R);
		if ( Mid < R ) Delete(rson, Mid + 1, r, L, R);
		PushUp(root);
	}
} Seg[128];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); } 
inline int lowbit(int x) { return x & -x; } 
inline void modify(int pos, u128 val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] += val; } 
inline u128 query(int pos) { u128 ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &q); REP(i, 1, n) a[i] = read(); 
	REP(i, 1, n + 1) f[i] = i;
	p[0] = 1; REP(i, 1, 127) p[i] = p[i - 1] * 2;
	bool flag = false;
	REP(i, 1, q)
	{
		int op, l, r; u128 v; scanf("%d%d%d", &op, &l, &r); Q[i] = {op, l, r};
		if ( op == 1 ) Q[i].v = read(); 
		if ( op == 2 ) { Q[i].v = read(); flag = true; } 
	}

	if ( !flag ) 
	{
		REP(i, 1, n) modify(i, a[i]);
		REP(i, 1, q)
		{
			if ( Q[i].op == 1 ) 
			{
				if ( Q[i].v == 1 ) continue ; 
				int x = find(Q[i].l);
				while ( x <= Q[i].r ) 
				{
					modify(x, -a[x]); a[x] /= Q[i].v; modify(x, a[x]);
					if ( !a[x] ) f[x] = x + 1;
					x = find(x + 1);
				}
			}
			if ( Q[i].op == 3 ) 
			{
				u128 ans = query(Q[i].r) - query(Q[i].l - 1);
				output(ans); putchar('\n');
			}
		}
		return 0;
	}

	REP(i, 1, n) MaxBit[i] = 127;
	REP(i, 0, 127) 
	{
		REP(j, 1, n) b[j] = (a[j] >> i) & 1;
		Seg[i].Build(1, 1, n);
	}
	REP(i, 1, q)
	{
		if ( Q[i].op == 1 ) 
		{
			if ( Q[i].v == 1 ) continue ; 
			int x = find(Q[i].l);
			while ( x <= Q[i].r ) 
			{
				a[x] = 0; 
				REP(j, 0, MaxBit[x]) if ( Seg[j].Query(1, 1, n, x, x) ) a[x] += p[j];
				a[x] /= Q[i].v;
				bool ttt = false;
				for ( int j = MaxBit[x]; j >= 0; -- j ) 
					if ( (a[x] >> j) & 1 ) { MaxBit[x] = j; ttt = true; break ; } 
					else Seg[j].Modify(1, 1, n, x, 0);
				if ( !ttt ) MaxBit[x] = -1;
				REP(j, 0, MaxBit[x]) Seg[j].Modify(1, 1, n, x, (a[x] >> j) & 1);
				if ( !a[x] ) f[x] = x + 1;
				x = find(x + 1);
			}
		}
		if ( Q[i].op == 2 ) 
		{
			REP(j, 0, 127) if ( !((Q[i].v >> j) & 1) )
				Seg[j].Delete(1, 1, n, Q[i].l, Q[i].r);
		}
		if ( Q[i].op == 3 ) 
		{
			u128 ans = 0;
			REP(j, 0, 127) ans += p[j] * Seg[j].Query(1, 1, n, Q[i].l, Q[i].r);
			output(ans); putchar('\n');
		}
	}
    return 0;
}
