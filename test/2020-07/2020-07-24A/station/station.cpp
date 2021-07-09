/***************************************************************
	File name: station.cpp
	Author: ljfcnyali
	Create time: 2020年07月24日 星期五 14时38分14秒
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

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int n, m, sum;
struct node { int sum; } Tree[maxn << 2];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Modify(int root, int l, int r, int pos, int val) 
{
    Tree[root].sum += val; if ( l == r ) return ; 
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
}

inline int Query(int root, int l, int r, int x)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1;
    if ( x <= Tree[lson].sum ) return Query(lson, l, Mid, x);
    else return Query(rson, Mid + 1, r, x - Tree[lson].sum);
}

signed main()
{
    freopen("station.in", "r", stdin);
    freopen("station.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { int x; scanf("%lld", &x); sum += x; Modify(1, 1, n, i, x); }
    int ans = 0;
    REP(i, 1, m)
    {
        int pos, val; scanf("%lld%lld", &pos, &val); sum += val; 
        Modify(1, 1, n, pos, val);
        ans = (ans + power(19260817, i) * Query(1, 1, n, (sum + 1) / 2)) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
