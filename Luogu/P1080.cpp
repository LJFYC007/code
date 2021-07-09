/***************************************************************
	File name: P1080.cpp
	Author: ljfcnyali
	Create time: 2019年06月17日 星期一 15时13分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1010;

struct node
{
    LL a, b;
} a[maxn];

LL n;
LL ans, sum;

inline int cmp(node x, node y)
{
    return (x.a * x.b) < (y.a * y.b);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &a[0].a, &a[0].b);
    REP(i, 1, n) scanf("%lld%lld", &a[i].a, &a[i].b);
    sum = a[0].a;
    sort(a + 1, a + n + 1, cmp);
    REP(i, 1, n)
    {
        ans = max(ans, sum / a[i].b);
        sum *= a[i].a; 
    }
    printf("%lld\n", ans);
    return 0;
}
