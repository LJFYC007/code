/***************************************************************
    File name: B.cpp
    Author: ljfcnyali
    Create time: 2020年07月11日 星期六 16时33分57秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;
 
const int maxn = 1e3 + 10;
 
int q, n, k, f[maxn][maxn][10];
 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % 2; a = a * a % 2; b >>= 1; } return r; }

inline int lowbit(int x) { return x & -x; }
 
inline int Check(int k, vector<int> a)
{
    int sum = 0;
    REP(i, 1, 20) sum += a[i] * i;
    if ( k == 0 ) return 1;
    if ( lowbit(sum) != k || sum == k ) return 0;
    return 1;
}
 
inline int DFS(int k, vector<int> a)
{
    if ( k < 0 ) return 0;
    int ret = 0;
    REP(i, 1, n) if ( a[i] > 1 ) 
    {
        int x = a[i]; -- a[i];
        ret += DFS(k - i, a);
        -- a[i]; ++ a[i * 2];
        ret += DFS(k, a);
        return ret % 2;
    }
    printf("%d %d\n", k, Check(k, a));
    REP(i, 1, 10) printf("%d ", a[i]); puts("");
    return Check(k, a);
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%lld", &q);
    while ( q -- ) 
    {
        scanf("%lld%lld", &n, &k);
        vector<int> a; a.resize(21); REP(i, 0, n) a[i] = 0; a[1] = n;
        printf("%lld\n", DFS(k, a) % 2);
    }
    return 0;
}
