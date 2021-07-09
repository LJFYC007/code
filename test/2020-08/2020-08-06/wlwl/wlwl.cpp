/***************************************************************
	File name: wlwl.cpp
	Author: ljfcnyali
	Create time: 2020年08月06日 星期四 08时56分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int __int128
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, p, a[maxn], g, ans;
vector<int> prime, t;
map<int, bool> Map;
map<int, int> f;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % p; a = a * a % p; b >>= 1; } return r; }

inline void Get(int x)
{
    REP(i, 2, 1000000)
    {
        if ( x % i != 0 ) continue ;
        prime.push_back(i);
        while ( x % i == 0 ) x /= i;
    }
    if ( x > 1 ) prime.push_back(x);
}

inline int Find(int x)
{
    x %= p; int ret = p - 1;
    for ( auto i : prime ) while ( ret % i == 0 && power(x, ret / i) == 1 ) ret /= i;
    return ret;
}

inline void DFS(int x)
{
    if ( Map.count(x) ) return ; Map[x] = true; 
    for ( auto i : prime ) if ( ((p - 1) / x) % i == 0 ) DFS(x * i);
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("wlwl.in", "r", stdin);
    freopen("wlwl.out", "w", stdout);
    read(n); read(p); Get(p - 1); DFS(1);
    REP(i, 1, n) 
    {
        read(a[i]); a[i] = Find(a[i]);
        f[a[i]] = (f[a[i]] + a[i]) % p;
    }
    for ( auto i : Map ) t.push_back(i.first); 
    sort(t.begin(), t.end()); reverse(t.begin(), t.end());
    for ( auto i : prime ) for ( auto j : t ) if ( j % i == 0 ) f[j / i] = (f[j / i] + f[j]) % p;
    for ( auto i : t ) f[i] = f[i] * f[i] % p;
    reverse(t.begin(), t.end());
    for ( auto i : prime ) for ( auto j : t ) if ( j % i == 0 ) f[j / i] = (f[j / i] - f[j]) % p;
    for ( auto i : t ) ans = (ans + f[i] * power(i * i % p, p - 2)) % p;
    printf("%lld\n", (LL)((ans + p) % p));
    return 0;
}
