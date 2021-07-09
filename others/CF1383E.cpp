/***************************************************************
	File name: CF1383E.cpp
	Author: ljfcnyali
	Create time: 2020年12月04日 星期五 10时55分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 1e9 + 7;

int n, m, f[maxn];
pii a[maxn];
char s[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    for ( int i = 1, j; i <= n; i = j + 1 ) 
    {
        j = i; while ( s[j + 1] == s[j] ) ++ j;
        a[++ m] = pii(s[i] - '0', j - i + 1);
    }
    f[1] = a[1].second;
    if ( a[1].first == 0 ) f[2] = a[2].second;
    REP(i, 2, m)
    {
        f[i] = (f[i] + f[i - 1] * a[i].second) % Mod;
        if ( a[i].first == 1 ) 
        {
            for ( int j = i + 2; j <= n; j += 2 ) 
                f[j] = (f[j] + f[i] * a[j].second) % Mod;
        }
        cout << f[i] << " ";
    }
    int ans = 0;
    REP(i, 1, m) if ( a[i].first >= a[m].first ) ans += f[i];
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
