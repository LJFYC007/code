/***************************************************************
	File name: P3765.cpp
	Author: ljfcnyali
	Create time: 2019年11月05日 星期二 20时36分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int unsigned int
typedef long long LL;

const int maxn = 1000010;

struct node { int lson, rson, val, size, rnd; } Tree[maxn];
stack<int> Rub;
int n, m, tot, Root[maxn], p[maxn], seed = 19491001;

inline int Rand()
{
    seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
    return seed;
}

inline int NewNode(const int val)
{
    register int x;
    if ( !Rub.empty() ) { x = Rub.top(); Rub.pop(); }
    else x = ++ tot;
    ls(x) = rs(x) = 0; Tree[x].size = 1; Tree[x].val = val; Tree[x].rnd = Rand();
    return x;
}

inline void PushUp(const int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }

inline void Merge(register int &root, const int a, const int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    if ( Tree[a].rnd <= Tree[b].rnd ) { root = a; Merge(rs(root), rs(root), b); }
    else { root = b; Merge(ls(root), a, ls(root)); }
    PushUp(root);
}

inline void Split(const int root, register int &a, register int &b, const int val)
{
    if ( !root ) { a = b = 0; return ; }
    if ( Tree[root].val <= val ) { a = root; Split(rs(a), rs(a), b, val); } 
    else { b = root; Split(ls(b), a, ls(b), val); }
    PushUp(root);
}

inline int Solve(int l, int r, int s)
{
    int a, b; const int len = (r - l + 1) >> 1, t = r - l + 1;
    REP(i, 1, 13)
    {
        const int x = p[l + (Rand() % t)];
        Split(Root[x], Root[x], a, l - 1);
        Split(a, a, b, r);
        if ( Tree[a].size > len ) s = x;
        Merge(a, a, b); Merge(Root[x], Root[x], a);
    }
    return s;
}

inline void Insert(const int x, const int val)
{
    int a, b; 
    Split(Root[x], Root[x], a, val - 1);
    b = NewNode(val);
    Merge(Root[x], Root[x], b); Merge(Root[x], Root[x], a);
}

inline void Del(const int x, const int val)
{
    int a, b;
    Split(Root[x], Root[x], a, val - 1); Split(a, a, b, val);
    Rub.push(a); 
    Merge(Root[x], Root[x], b);
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    read(n); read(m);
    REP(i, 1, n) { read(p[i]); Insert(p[i], i); } 
    REP(i, 1, m)
    {
        int l, r, s, k; read(l); read(r); read(s); read(k);
        s = Solve(l, r, s);
        printf("%d\n", s);
        REP(j, 1, k) { int x; read(x); Del(p[x], x); p[x] = s; Insert(p[x], x); }
    }
    printf("%d\n", Solve(1, n, -1));
    return 0;
}
