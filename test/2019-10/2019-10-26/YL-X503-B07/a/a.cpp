/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年10月26日 星期六 08时06分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;
const int N = 2e7 + 10;

int n, m, v[maxn], l[maxn], r[maxn], sum[N];

signed main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld%lld%lld", &v[i], &l[i], &r[i]);
    REP(i, 1, n - 1) REP(j, i + 1, n)
    {
        sum[l[i] + l[j]] = (sum[l[i] + l[j]] + v[i] * v[j]) % Mod;
        sum[l[i] + r[j] + 1] = (sum[l[i] + r[j] + 1] - v[i] * v[j]) % Mod;
        sum[r[i] + l[j] + 1] = (sum[r[i] + l[j] + 1] - v[i] * v[j]) % Mod;
        sum[r[i] + r[j] + 2] = (sum[r[i] + r[j] + 2] + v[i] * v[j]) % Mod;
    }
    REP(i, 1, N - 10) sum[i] = (sum[i] + sum[i - 1]) % Mod;
    REP(i, 1, N - 10) sum[i] = (sum[i] + sum[i - 1]) % Mod;
    REP(i, 1, m) { int x; scanf("%lld", &x); printf("%lld\n", (sum[x] + Mod) % Mod); }
    return 0;
}
