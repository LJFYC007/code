/***************************************************************
	File name: Manacher.cpp
	Author: ljfcnyali
	Create time: 2020年08月13日 星期四 15时22分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e7 + 10;

int n, f[maxn], ans;
char t[maxn], s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", t + 1);
    s[++ n] = '#'; REP(i, 1, str(t + 1)) { s[++ n] = t[i]; s[++ n] = '#'; }
    int MaxRight = 1, pos = 1; 
    REP(i, 1, n)
    {
        if ( i < MaxRight ) f[i] = min(f[2 * pos - i], MaxRight - i);
        else f[i] = 1;
        while ( i - f[i] >= 1 && i + f[i] <= n && s[i - f[i]] == s[i + f[i]] ) ++ f[i];
        if ( i + f[i] > MaxRight ) { MaxRight = i + f[i]; pos = i; }
    }
    REP(i, 1, n) ans = max(ans, f[i] - 1);
    printf("%d\n", ans);
    return 0;
}
