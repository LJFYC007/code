/***************************************************************
	File name: time.cpp
	Author: ljfcnyali
	Create time: 2019年10月21日 星期一 09时43分22秒
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
const int N = 100000;
const int INF = 1000000000000;

int n, a[maxn], c[maxn][2], num, ans, suf[maxn], pre[maxn];

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val, int opt)
{
    for ( int i = pos; i <= N; i += lowbit(i) )
        c[i][opt] += val;
}

inline int get(int pos, int opt)
{
    int sum = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i][opt];
    return sum;
}

inline void Solve()
{
    REP(i, 1, n)
    {
        pre[i] = i - 1 - get(a[i], 0);
        add(a[i], 1, 0);
    }
    for ( int i = n; i >= 1; -- i )
    {
        suf[i] = n - i - get(a[i], 1);
        add(a[i], 1, 1);
    }
    REP(i, 1, n) ans += min(suf[i], pre[i]);
}

signed main()
{
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    Solve();
    printf("%lld\n", ans);
    return 0;
}
