/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年10月20日 星期日 17时03分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 1e9 + 7;

int f[200010], n, m;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> m;
    f[1] = 1; f[2] = 2;
    REP(i, 3, n + m) f[i] = (f[i - 1] + f[i - 2]) % Mod;
    cout << (2 * (f[n] + f[m] - 1)) % Mod << endl;
    return 0;
}
