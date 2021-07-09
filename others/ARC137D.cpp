/***************************************************************
	File name: AtCoder137D.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 15时43分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

int n, m, ans;
struct node
{
    int a, b;
    bool operator < (const node &x) const { return a < x.a; }
} a[maxn];

priority_queue<int> Q;

int main()
{
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d%d", &a[i].a, &a[i].b);
    sort(a + 1, a + n + 1);
    int now = 1;
    for ( int i = n; i >= 1; -- i )
    {
        while ( now <= n && i + a[now].a - 1 <= m ) Q.push(a[now ++].b);
        if ( !Q.empty() ) { ans += Q.top(); Q.pop(); }
    }
    printf("%d\n", ans);
    return 0;
}
