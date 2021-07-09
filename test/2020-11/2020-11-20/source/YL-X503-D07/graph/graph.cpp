/***************************************************************
	File name: graph.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 17时14分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T;

inline int Solve(int n, vector<int> s)
{
    sort(s.begin(), s.end());
    while ( s.size() && s.back() > n - 1 ) s.pop_back();
    if ( !s.size() ) return n;
    if ( s[0] > n / 2 ) 
    {
        int x = 2 * s[0] - n; n -= x;
        for ( int i = 0; i < s.size(); ++ i ) s[i] -= x; 
        return Solve(n, s) + x;
    }
    int g = 0; 
    for ( int i = 0; i < s.size(); ++ i ) 
    {
        if ( s[i] <= n / 2 || s[i] + g <= n ) { g = __gcd(g, s[i]); continue ; }
        int N = g + n % g;
        vector<int> a; a.clear(); a.push_back(g);
        for ( int j = i; j < s.size(); ++ j ) a.push_back(N - (n - s[j]));
        return Solve(N, a);
    }
    return g; 
}

signed main()
{
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        int n, m; vector<int> s;
        scanf("%lld%lld", &n, &m);
        REP(i, 1, m) { int x; scanf("%lld", &x); s.push_back(x); }
        printf("%lld\n", Solve(n, s));
    }
    return 0;
}
