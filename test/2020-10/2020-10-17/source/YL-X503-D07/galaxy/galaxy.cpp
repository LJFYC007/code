/***************************************************************
	File name: galaxy.cpp
	Author: ljfcnyali
	Create time: 2020年10月17日 星期六 16时45分10秒
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

int n, q, a[maxn], c[2][maxn], num;
double preans;

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val, int op) { for ( int i = pos; i <= n; i += lowbit(i) ) c[op][i] += val; }

inline int get(int pos, int op) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[op][i]; return sum; }

inline void Solve()
{
    double ans = preans;
    int sum = 0;
    REP(i, 1, n) c[0][i] = c[1][i] = 0;
    REP(i, 1, n) 
    {
        ans += num * (i - 1 - get(a[i], 0)) - (n - i + 1) * (sum - get(a[i], 1));
        add(a[i], 1, 0); add(a[i], i, 1); sum += i;
    }
    printf("%.6lf\n", ans / num);
}

signed main()
{
    freopen("galaxy.in", "r", stdin);
    freopen("galaxy.out", "w", stdout);
    scanf("%lld%lld", &n, &q);
    REP(i, 1, n) scanf("%lld", &a[i]);
    num = n * (n + 1) / 2;
    REP(i, 1, n) preans += 0.25 * (n - i + 1) * i * (i - 1);
    Solve();
    while ( q -- ) 
    {
        int x, y; scanf("%lld%lld", &x, &y);
        swap(a[x], a[y]); Solve();
    }
    return 0;
}
