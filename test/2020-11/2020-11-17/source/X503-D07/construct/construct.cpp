/***************************************************************
File name: construct.cpp
Author: ljfcnyali
Create time: 2020年11月17日 星期二 09时09分23秒
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
const int INF = 1e18;

int n, c, f[maxn], a[maxn], sum1[maxn], sum2[maxn], Stack[maxn], tot;

inline int Solve(int l, int r, int mx)
{
    int A = r - l - 1, B = -2 * (sum2[r - 1] - sum2[l]) - 2 * c, C = (sum1[r - 1] - sum1[l]) + c * a[l] + c * a[r];
    if ( l == 0 ) { B += c; C -= c * a[l]; }
    if ( r == n + 1 ) { B += c; C -= c * a[r]; }
    int t = round(-1.0 * B / 2 / A);
    t = max(t, mx); t = min(t, min(a[l], a[r]));
    return A * t * t + B * t + C;
}

signed main()
{
    freopen("construct.in", "r", stdin);
    freopen("construct.out", "w", stdout);
    scanf("%lld%lld", &n, &c);
    REP(i, 1, n) scanf("%lld", &a[i]); a[0] = a[n + 1] = INF;
    REP(i, 1, n) { sum1[i] = sum1[i - 1] + a[i] * a[i]; sum2[i] = sum2[i - 1] + a[i]; }
    Stack[1] = 0; tot = 1;
    REP(i, 1, n + 1)
    {
        f[i] = f[i - 1] + ((i != 1 && i != n + 1) ? c * abs(a[i] - a[i - 1]) : 0);
        while ( tot > 1 && a[Stack[tot]] <= a[i] ) 
        {
            f[i] = min(f[i], f[Stack[tot - 1]] + Solve(Stack[tot - 1], i, a[Stack[tot]]));
            -- tot;
        } 
        Stack[++ tot] = i;
    }
    printf("%lld\n", f[n + 1]);
    return 0;
}
