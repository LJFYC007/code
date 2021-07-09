/***************************************************************
	File name: x.cpp
	Author: ljfcnyali
	Create time: 2019年08月08日 星期四 08时41分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

int n, m, ans, last;

struct node
{
    int l, r;
    bool operator < (const node &a) const { return r < a.r; }
} a[maxn];

int main()
{
    freopen("x.in", "r", stdin);
    freopen("x.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { int x, y; scanf("%d%d", &x, &y); a[i].l = x - y; a[i].r = x + y; }
    sort(a + 1, a + n + 1);
    int last = -0x3f3f3f3f;
    REP(i, 1, n)
        if ( last < a[i].l ) { ++ ans; last = a[i].r; }
    printf("%d\n", ans);
    return 0;
}
