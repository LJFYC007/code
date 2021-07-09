/***************************************************************
	File name: aminusb.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月29日 星期日 08时13分57秒
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
const int Mod = 998244353;

int T, n, a[maxn];

signed main()
{
    freopen("aminusb.in", "r", stdin);
    freopen("aminusb.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n);
        REP(i, 1, n) scanf("%lld", &a[i]);
        printf("%lld\n", (a[1] - a[2] + Mod) % Mod);
    }
    return 0;
}
