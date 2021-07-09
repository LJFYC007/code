/***************************************************************
	File name: big.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 10时46分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, a[maxn], pre[maxn], suf[maxn], tot = 1;
struct node { int son[2]; } Tree[maxn * 30];
pii ans;

inline pii operator + (pii a, pii b) { return pii(a.first, a.second + b.second); }

inline int calc(int x) { return ((x * 2 / (1 << n)) + x * 2) % (1 << n); }

inline void Insert(int x)
{
    int p = 1;   
    for ( int i = n; i >= 1; -- i ) 
    {
        int c = (x >> i - 1) & 1;
        if ( !Tree[p].son[c] ) Tree[p].son[c] = ++ tot;
        p = Tree[p].son[c];
    }
}

inline pii DFS(int p, int dep)
{
    if ( !p ) return pii(-INF, 0);
    if ( dep == 0 )
    {
        if ( Tree[p].son[0] && Tree[p].son[1] ) return pii(0, 2); 
        if ( !Tree[p].son[0] && !Tree[p].son[1] ) return pii(-INF, 0);
        return pii(1, 1); 
    }
    if ( Tree[p].son[0] && Tree[p].son[1] ) 
    {
        pii x = DFS(Tree[p].son[0], dep - 1);
        pii y = DFS(Tree[p].son[1], dep - 1);
        if ( x.first > y.first ) return x;
        if ( x.first < y.first ) return y;
        return x + y;
    }
    int y = Tree[p].son[0] + Tree[p].son[1];
    pii x = DFS(y, dep - 1); x.first += 1 << dep; 
    return x;
}

int main()
{
    freopen("big.in", "r", stdin);
    freopen("big.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if ( n == 0 ) { puts("0\n1"); return 0; }
    REP(i, 1, m) scanf("%d", &a[i]);
    REP(i, 1, m) pre[i] = pre[i - 1] ^ a[i];
    for ( int i = m; i >= 1; -- i ) suf[i] = suf[i + 1] ^ a[i];
    Insert(suf[1]);
    REP(i, 1, m) Insert(calc(pre[i]) ^ suf[i + 1]);
    ans = DFS(1, n - 1);
    printf("%d\n%d\n", ans.first, ans.second);
    return 0;
}
