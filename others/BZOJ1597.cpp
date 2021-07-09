/***************************************************************
    File name: BZOJ1597.cpp
    Author: ljfcnyali
    Create time: 2019年06月26日 星期三 21时24分29秒
***************************************************************/
#include<bits/stdc++.h>
  
using namespace std;
  
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;
  
const int maxn = 500010;
  
LL q[maxn], s, t, n, a[maxn], b[maxn], cnt, f[maxn];
struct node 
{
    LL x, y;
} p[maxn];
  
inline int cmp(node a, node b)
{
    return a.x > b.x || (a.x == b.x && a.y > b.y);
}
  
inline int cmp1(node a, node b)
{
    return a.x > b.x || (a.x == b.x && a.y < b.y);
}
  
inline double js(int j, int k)
{
    return ((double)f[j] - f[k]) / (a[k + 1] - a[j + 1]);
}
  
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld%lld", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1, cmp);
    REP(i, 2, n)
        if ( p[i - 1].x >= p[i].x && p[i - 1].y >= p[i].y )
        {
            p[i] = p[i - 1];
            p[i - 1].x = p[i - 1].y = -1;
        }
    sort(p + 1, p + n + 1, cmp1);
    REP(i, 1, n)
    {
        if ( p[i].x == -1 && p[i].y == -1 ) continue ;
        a[++ cnt] = p[i].x; b[cnt] = p[i].y;
    }
    n = cnt;
    s = t = 1;
    REP(i, 1, n)
    {
        while ( s < t && js(q[s + 1], q[s]) < b[i] ) ++ s;
        f[i] = f[q[s]] + 1LL * a[q[s] + 1] * b[i];
        while ( s < t && js(q[t], q[t - 1]) > js(i, q[t]) ) -- t;
        q[++ t] = i;
    }
    printf("%lld\n", f[n]);
    return 0;
}
