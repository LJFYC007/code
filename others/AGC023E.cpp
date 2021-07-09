/***************************************************************
	File name: AGC023E.cpp
	Author: ljfcnyali
	Create time: 2021年01月15日 星期五 20时25分38秒
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

const int maxn = 1e6 + 10;
const int Mod = 1e9 + 7;

int n, a[maxn], b[maxn], c[maxn], s[maxn], val, t[maxn];
struct node { int lazy, sum; } Tree[maxn << 2];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r ; } 

inline void PushTag(int root, int val ) { Tree[root].lazy = Tree[root].lazy * val % Mod; Tree[root].sum = Tree[root].sum * val % Mod; } 

inline void PushDown(int root) 
{
    if ( Tree[root].lazy == 1) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy); 
    Tree[root].lazy = 1; 
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    if ( l == r ) { Tree[root].sum = val; return ; } 
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    Tree[root].sum = (Tree[lson].sum + Tree[rson].sum) % Mod;
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret % Mod;
}

inline void INIT() { REP(i, 1, n * 4) { Tree[i].lazy = 1; Tree[i].sum = 0; } }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) { c[i] = a[i]; ++ s[a[i]]; } 
    sort(c + 1, c + n + 1);
    REP(i, 1, n) s[i] += s[i - 1]; REP(i, 1, n) { b[i] = s[a[i]] --; t[b[i]] = i; } 
    val = 1; REP(i, 1, n) val = val * (c[i] - i + 1) % Mod;
    
    int ret = 0; INIT();
    for ( int i = n; i >= 1; -- i ) 
    {
        if ( i < n ) 
        {
            PushTag(Tree[1].lazy, (c[i + 1] - i - 1) * power(c[i + 1] - i, Mod - 2) % Mod);
            int x = t[i + 1];
            Modify(1, 1, n, x, power(a[x] - b[x] + 1, Mod - 2));
        }
        int x = t[i]; ret = (ret + (a[x] - b[x]) * Query(1, 1, n, x + 1, n)) % Mod;
    }

    INIT();
    REP(i, 1, n)
    {
        if ( i > 1 ) 
        {
            PushTag(Tree[1].lazy, (c[i - 1] - i + 1) * power(c[i - 1] - i + 2, Mod - 2) % Mod);
            int x = t[i - 1];
            Modify(1, 1, n, x, (a[x] - b[x]) % Mod);
        }
        int x = t[i]; ret = (ret - power(a[x] - b[x] + 1, Mod - 2) * Query(1, 1, n, x + 1, n)) % Mod;
    }

    INIT();
    REP(i, 1, n) 
    {
        if ( i > 1 ) Modify(1, 1, n, t[i - 1], 2);
        ret = (ret + Query(1, 1, n, t[i] + 1, n)) % Mod;
    }
    ret = ret * power(2, Mod - 2) % Mod;
    ret = ret * val % Mod;
    printf("%lld\n", (ret + Mod) % Mod);
    return 0;
}
