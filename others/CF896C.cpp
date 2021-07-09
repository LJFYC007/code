/***************************************************************
	File name: CF896C.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 20时03分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

struct node 
{
    int l, r, val;
    node(const int L, const int R, const int Val) { l = L; r = R; val = Val; }
    bool operator < (const node &a) const { return l < a.l; }
} ;
set<node> Set;
vector<pii> f;
int n, m, seed, vmax, mod, a[maxn];

inline int Rand() { int ret = seed; seed = (seed * 7 + 13) % Mod; return ret; }

inline int power(int a, int b) 
{ 
    int r = 1; 
    while ( b ) 
    { 
        if ( b & 1 ) r = r * a % mod; 
        a = a * a % mod; b >>= 1; 
    } 
    return r; 
}

inline auto Split(int x)
{
    auto it = -- Set.upper_bound(node(x, 0, 0));
    if ( it -> l == x ) return it;
    int l = it -> l, r = it -> r, val = it -> val;
    Set.erase(it);
    Set.insert(node(l, x - 1, val)); Set.insert(node(x, r, val));
    return Set.lower_bound(node(x, 0, 0));
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> m >> seed >> vmax;
    REP(i, 1, n) a[i] = Rand() % vmax + 1;
    for ( int i = 1; i <= n; ++ i )
    {
        int L = i, R = i;
        while ( a[R] == a[L] ) ++ R;
        i = R - 1; Set.insert(node(L, i, a[i]));
    }
    while ( m -- ) 
    {
        int opt = Rand() % 4 + 1, l = Rand() % n + 1, r = Rand() % n + 1, x;
        if ( l > r ) swap(l, r);
        if ( opt == 3 ) x = Rand() % (r - l + 1) + 1; else x = Rand() % vmax + 1;
        auto itr = Split(r + 1), itl = Split(l);
        if ( opt == 1 ) for ( ; itl != itr; ) 
        { 
            int L = itl -> l, R = itl -> r, v = itl -> val + x;
            auto it = itl; ++ itl; Set.erase(it); Set.insert(node(L, R, v));
        }
        if ( opt == 2 ) { Set.erase(itl, itr); Set.insert(node(l, r, x)); }
        if ( opt == 3 ) 
        {
            f.clear();
            for ( ; itl != itr; ++ itl ) f.push_back(pii(itl -> val, itl -> r - itl -> l + 1));
            sort(f.begin(), f.end());
            for ( auto i : f ) { x -= i.second; if ( x <= 0 ) { printf("%lld\n", i.first); break ; } }
        }
        if ( opt == 4 )
        {
            mod = Rand() % vmax + 1; int ans = 0;
            for ( ; itl != itr; ++ itl ) 
            {
                int len = itl -> r - itl -> l + 1; len %= mod;
                ans = (ans + len * power(itl -> val % mod, x)) % mod;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
