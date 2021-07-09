/***************************************************************
	File name: dissolution.cpp
	Author: ljfcnyali
	Create time: 2021年01月21日 星期四 09时36分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 4e6 + 10;
const int INF = 1e18;

int n, g[maxn], N1, N2, p1[maxn], p2[maxn], f[maxn], s[maxn], c[4][maxn], ans, A[maxn], B[maxn];
map<int, int> Map1, Map2;
pii a[maxn], b[maxn];

inline int lowbit(int x) { return x & -x; }

inline void add(int op, int pos, int val) { for ( int i = pos; i <= (op <= 1 ? N1 : N2); i += lowbit(i) ) c[op][i] = max(c[op][i], val); } 

inline int query(int op, int pos) { int sum = -INF; for ( int i = pos; i > 0; i -= lowbit(i) ) sum = max(sum, c[op][i]); return sum; } 

inline int Dis(int x, int y) { return max(abs(p1[A[x]] - p1[A[y]]), abs(p2[B[x]] - p2[B[y]])); }

inline void Modify(int i)
{
    int val = f[i] - s[i]; -- i;
    add(0, N1 - A[i] + 1, val + p1[A[i]]);
    add(1, A[i], val - p1[A[i]]);
    add(2, N2 - B[i] + 1, val + p2[B[i]]);
    add(3, B[i], val - p2[B[i]]);
}

signed main()
{
    freopen("dissolution.in", "r", stdin);
    freopen("dissolution.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { int x, y; scanf("%lld%lld", &x, &y); a[i] = pii(x + y, i); b[i] = pii(x - y, i); }
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
    REP(i, 1, n) { if ( a[i].first != a[i - 1].first ) p1[++ N1] = a[i].first; A[a[i].second] = N1; }
    REP(i, 1, n) { if ( b[i].first != b[i - 1].first ) p2[++ N2] = b[i].first; B[b[i].second] = N2; }

    REP(i, 2, n) { g[i] = Dis(i - 1, i); f[i] = f[i - 1] + g[i - 1]; s[i] = s[i - 1] + g[i]; } 
    REP(i, 0, max(N1, N2)) REP(j, 0, 3) c[j][i] = -INF;

    Modify(2);
    REP(i, 3, n) 
    {
        int Max = 0;
        Max = max(Max, query(0, N1 - A[i] + 1) - p1[A[i]]);
        Max = max(Max, query(1, A[i]) + p1[A[i]]);
        Max = max(Max, query(2, N2 - B[i] + 1) - p2[B[i]]);
        Max = max(Max, query(3, B[i]) + p2[B[i]]);
        f[i] = max(f[i], Max + s[i - 1]);
        Modify(i);
    }

    int sum = 0;
    for ( int i = n; i >= 2; -- i ) { ans = max(ans, f[i] + sum); sum += g[i]; } 
    printf("%lld\n", ans);
    return 0;
}
