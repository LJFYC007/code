/***************************************************************
	File name: P5495.cpp
	Author: ljfcnyali
	Create time: 2019年10月20日 星期日 20时03分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned int
typedef long long LL;

const int maxn = 2e7 + 10;

int n, b[maxn], ans, prime[maxn], tot, seed;
bool vis[maxn];

inline int Get() { seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5; return seed; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> seed;
    REP(i, 2, n) 
    {
        if ( !vis[i] ) prime[++ tot] = i;
        for ( int j = 1; j <= n && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) break ; 
        }
    }
    REP(i, 1, n) b[i] = Get();
    REP(i, 1, tot)
        for ( int j = 1; j * prime[i] <= n; ++ j ) 
            b[j * prime[i]] += b[j];
    REP(i, 1, n) ans ^= b[i];
    cout << ans << endl;
    return 0;
}
