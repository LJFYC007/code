/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2020年11月29日 星期日 17时03分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t, n, p, k, a[maxn];
    cin >> t >> n >> p >> k;
    REP(i, 1, n) scanf("%1d", &a[i]);
    int x, y; cin >> x >> y;
    int ans = 2e9;
    for ( int i = n; i > n - k; -- i )
    {
        int ans2 = 0;
        for ( int j = i; j >= p; j -= k ) 
        {
            if ( a[j] == 0 ) ans2 += x;
            ans = min(ans, ans2 + (j - p) * y);
        }
    }
    cout << ans << endl;
    return 0;
}
