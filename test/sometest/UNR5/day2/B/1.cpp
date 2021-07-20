/*
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC target("avx") 
*/
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

char buf[1 << 20], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)

typedef __uint128_t u128;
inline u128 read() {
	u128 res=0;char c=gc();
	while((c>'9'||c<'0')&&(c>'f'||c<'a'))c=gc();
	while(('0'<=c&&c<='9')||('a'<=c&&c<='f')){
		res=res<<4|(c<='9'?c-'0':c-'a'+10);
		c=gc();
	}
    return res;
}
inline void output(u128 res) {
    if(res >= 16)
        output(res / 16);
    putchar(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
}
inline void READ(int &x)
{
	char c = gc(); x = 0;
	while ( c < '0' || c > '9' ) c = gc();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = gc(); } 
}

const int maxn = 3e5 + 10;
const u128 M = -1;

int n, m, q; u128 a[maxn], ans;
struct node { int len; vector<u128> sum; u128 lazy; bool ccc; } Tree[maxn << 2];
#define lson root << 1
#define rson root << 1 | 1

inline void PushUp(int root) 
{ 
	if ( Tree[root].ccc ) return ;
	u128 c = 0; Tree[root].len = max(Tree[lson].len, Tree[rson].len);
	Tree[root].sum.resize(Tree[root].len + 1);
	for ( register int i = 0; i <= Tree[root].len; ++ i ) 
	{
		const u128 X = Tree[lson].len >= i ? Tree[lson].sum[i] : 0;
		const u128 Y = Tree[rson].len >= i ? Tree[rson].sum[i] : 0;
		const u128 y = X ^ Y;
		Tree[root].sum[i] = y ^ c; c = (X & Y) | (y & c); 
	}
	if ( c ) Tree[root].sum.push_back(c), ++ Tree[root].len;
	else while ( Tree[root].len >= 0 && !Tree[root].sum[Tree[root].len] ) { -- Tree[root].len; Tree[root].sum.pop_back(); }
	if ( Tree[root].len == -1 ) Tree[root].ccc = true;
} 

inline void PushTag(int root, const u128 val)
{
	if ( Tree[root].ccc ) return ;
	Tree[root].lazy &= val; for ( register int i = 0; i <= Tree[root].len; ++ i ) Tree[root].sum[i] &= val;
	while ( Tree[root].len >= 0 && !Tree[root].sum[Tree[root].len] ) { -- Tree[root].len; Tree[root].sum.pop_back(); }
	if ( Tree[root].len == -1 ) Tree[root].ccc = true;
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
	if ( l == r ) { Tree[root].sum.push_back(a[l]); return ; } 
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);	
	PushUp(root);
}

inline void Query(int root, int l, int r, int L, int R)
{
	if ( Tree[root].ccc ) return ;
	if ( L <= l && r <= R ) 
	{
		int x = 1;
		for ( register int i = 0; i <= Tree[root].len; ++ i ) { ans += Tree[root].sum[i] * x; x <<= 1; } 
		return ;
	}
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Query(lson, l, Mid, L, R);
	if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
}

inline void Modify(int root, int l, int r, int L, int R, const u128 val)
{
	if ( Tree[root].ccc ) return ;
	if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

inline void Fuck(int root, int l, int r, const u128 val)
{
	if ( Tree[root].ccc ) return ;
	if ( l == r ) { Tree[root].sum[0] /= val; return ; } 
	int Mid = l + r >> 1; PushDown(root);
	Fuck(lson, l, Mid, val); Fuck(rson, Mid + 1, r, val);
	PushUp(root);
}

inline void Delete(int root, int l, int r, int L, int R, const u128 val)
{
	if ( Tree[root].ccc ) return ;
	if ( L <= l && r <= R ) { Fuck(root, l, r, val); return ; } 
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
	READ(n); READ(q); REP(i, 1, n) a[i] = read(); 
	Build(1, 1, n);
	REP(i, 1, q)
	{
		int op, l, r; u128 v; READ(op); READ(l); READ(r);
		if ( op == 1 ) 
		{
			v = read(); if ( v == 1 ) continue ; 
			Delete(1, 1, n, l, r, v);
		}
		if ( op == 2 ) Modify(1, 1, n, l, r, read());
		if ( op == 3 ) { ans = 0; Query(1, 1, n, l, r); output(ans); putchar('\n'); }
	}
    return 0;
}
