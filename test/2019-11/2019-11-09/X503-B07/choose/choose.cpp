/***************************************************************
	File name: choose.cpp
	Author: ljfcnyali
	Create time: 2019年11月09日 星期六 08时52分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 100010;
const int Mod = 1e9 + 7;

int a[maxn], b[maxn], n, ans, pre[maxn], suf[maxn], f[maxn];

signed main()
{
    freopen("choose.in", "r", stdin);
    freopen("choose.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 2, n) scanf("%lld", &b[i]);
    f[0] = 1; f[1] = a[1] + b[2];
    REP(i, 2, n) f[i] = (f[i - 1] * (a[i] + b[i] + b[i + 1]) - f[i - 2] * b[i]) % Mod;
    printf("%lld\n", (f[n] + Mod) % Mod);
    return 0;
    REP(i, 2, n) { a[i - 1] += b[i]; a[i] += b[i]; }
    pre[0] = 1; REP(i, 1, n) pre[i] = pre[i - 1] * a[i] % Mod;
    suf[n + 1] = 1; for ( int i = n; i >= 1; -- i ) suf[i] = suf[i + 1] * a[i] % Mod;
    ans = pre[n];
    REP(i, 2, n)
    {
        int ret = pre[i - 2] * suf[i + 1] % Mod;
        ans = (ans - ret * b[i]) % Mod;
    }
    ans = (ans + Mod) % Mod;
    printf("%lld\n", ans);
    return 0;
}
