/***************************************************************
	File name: H.cpp
	Author: ljfcnyali
	Create time: 2020年07月27日 星期一 13时44分10秒
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
const int Delta = 1000;

int n, ans;

inline int f(int x)
{
    int ret = 0;
    while ( x ) { ret += x % 10; x /= 10; }
    return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n;
    REP(i, 0, n) REP(j, i, n) if ( f(i) > f(j) ) ++ ans;
    cout << ans << endl;
    return 0;
}
