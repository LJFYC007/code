/***************************************************************
	File name: P4168.cpp
	Author: ljfcnyali
	Create time: 2019年09月11日 星期三 16时33分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 210;
const int maxm = 40010;

int p[maxn][maxn], f[maxn][maxm], sum[maxm];
int n, m, h[maxm], id[maxm], num, block, ans;
struct node
{
    int id, val;
    bool operator < (const node &a) const { return val < a.val; }
} a[maxm];

inline int Solve1(int l, int r)
{
    REP(i, l, r) sum[h[i]] = 0;
    int Max = 0, k = 0;
    REP(i, l, r)
    {
        ++ sum[h[i]];
        if ( sum[h[i]] > Max || (sum[h[i]] == Max && id[h[i]] < k) ) { Max = sum[h[i]]; k = id[h[i]]; }
    }
    return k;
}

inline int Solve2(int L, int R)
{
    int x = (L - 1) / block + 1;
    int y = (R - 1) / block + 1;
    int l = x * block, r = y * block - block + 1;
    int k = p[x + 1][y - 1], Max = f[y - 1][k] - f[x][k];
    k = id[k];
    REP(i, L, l) sum[h[i]] = 0; REP(i, r, R) sum[h[i]] = 0;
    REP(i, L, l) ++ sum[h[i]];
    REP(i, r, R) ++ sum[h[i]];
    REP(i, L, l)
    {
        int K = sum[h[i]] + f[y - 1][h[i]] - f[x][h[i]];
        if ( K > Max || (K == Max && id[h[i]] < k) ) { Max = K; k = id[h[i]]; }
    }
    REP(i, r, R)
    {
        int K = sum[h[i]] + f[y - 1][h[i]] - f[x][h[i]];
        if ( K > Max || (K == Max && id[h[i]] < k) ) { Max = K; k = id[h[i]]; }
    }
    return k;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m); block = sqrt(n);
    REP(i, 1, n) { scanf("%lld", &a[i].val); a[i].id = i; }
    sort(a + 1, a + n + 1);
    REP(i, 1, n) { if ( a[i].val != a[i - 1].val ) ++ num; h[a[i].id] = num; id[num] = a[i].val; }
    REP(i, 1, n)
    {
        if ( (i - 1) / block != (i - 2) / block )
            REP(j, 1, num) f[(i - 1) / block + 1][j] = f[(i - 2) / block + 1][j];
        ++ f[(i - 1) / block + 1][h[i]];
    }
    num = (n - 1) / block + 1;
    REP(i, 1, num)
    {
        int l = (i - 1) * block + 1;
        mem(sum);
        int Max = 0, k = 0, K = 0;
        REP(j, l, n)
        {
            ++ sum[h[j]];
            if ( sum[h[j]] > Max || (sum[h[j]] == Max && id[h[j]] < K) ) { Max = sum[h[j]]; k = h[j]; K = id[h[j]]; }
            if ( j % block == 0 ) p[i][j / block] = k;
        }
    }
    REP(i, 1, m)
    {
        int l, r; scanf("%lld%lld", &l, &r);
        l = (l + ans - 1) % n + 1;
        r = (r + ans - 1) % n + 1;
        if ( l > r ) swap(l, r);
        int L = (l - 1) / block + 1, R = (r - 1) / block + 1;
        if ( L == R || L + 1 == R ) ans = Solve1(l, r);
        else ans = Solve2(l, r);
        printf("%lld\n", ans);
    }
    return 0;
}
