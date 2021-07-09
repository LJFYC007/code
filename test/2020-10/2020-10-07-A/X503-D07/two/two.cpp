/***************************************************************
	File name: two.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 14时55分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, q, ans;
priority_queue<int, vector<int>, greater<int> > a[maxn];

int main()
{
    freopen("two.in", "r", stdin);
    freopen("two.out", "w", stdout);
    scanf("%d%d", &n, &q);
    REP(i, 1, n) { int m, k; scanf("%d%d", &m, &k); a[m].push(k); }
    ans = n;
    while ( q -- ) 
    {
        int op, x, t; scanf("%d%d%d", &op, &x, &t);
        if ( op == 1 ) { a[x].push(t); ++ ans; printf("%d\n", ans); continue ; }
        REP(i, x - sqrt(t), x + sqrt(t))
        {
            if ( i < 1 || i > 100000 || a[i].empty() ) continue ; 
            int it = a[i].top();
            while ( it + (i - x) * (i - x) <= t ) 
            {
                a[i].pop(); -- ans;
                if ( a[i].empty() ) break ; 
                it = a[i].top();
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
