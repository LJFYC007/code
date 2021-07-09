/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年10月14日 星期一 07时53分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

int a, b, c, x, y, n;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> c >> a >> b;
    REP(i, 0, 100000)
        if ( (c - b * i) % a == 0 ) 
        {
            x = (c - b * i) / a, y = i;
            if ( x < 0 || y < 0 ) continue ;
            if ( x + y <= n ) { cout << x << " " << y << " " << n - x - y << endl; return 0; }
        }
    puts("-1");
    return 0;
}
