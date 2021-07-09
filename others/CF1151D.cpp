/***************************************************************
	File name: CF1151D.cpp
	Author: ljfcnyali
	Create time: 2019年08月30日 星期五 15时16分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 100010;
const int INF = 500000000;

struct node
{
    int a, b, c;
    bool operator < (const node &x) { return c > x.c; }
} a[maxn];

int n, ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) 
    {
        scanf("%lld%lld", &a[i].a, &a[i].b);
        a[i].c = a[i].a - a[i].b;
    }
    sort(a + 1, a + n + 1);
    REP(i, 1, n) ans += a[i].a * (i - 1) + a[i].b * (n - i);
    printf("%lld\n", ans);
    return 0;
}
