/***************************************************************
	File name: div.cpp
	Author: ljfcnyali
	Create time: 2019年07月11日 星期四 08时35分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

LL n, m, a[210], ans[210], p[100010], cnt;
map<LL, int> Map;

int main()
{
    freopen("div.in", "r", stdin);
    freopen("div.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) 
    {
        scanf("%lld", &a[i]);
        LL x = a[i];
        for ( LL j = 1; j * j <= a[i]; ++ j )
        {
            if ( x % j == 0 ) 
            { 
                if ( j <= n ) { ++ Map[j]; if ( Map[j] == 1 ) p[++ cnt] = j; }
                if ( j * j != x && (x / j) <= n ) 
                {
                    ++ Map[x / j]; 
                    if ( Map[x / j] == 1 ) p[++ cnt] = x / j;
                }
            }
        }
    }
    REP(i, 1, cnt) ++ ans[Map[p[i]]];
    LL sum = 0; REP(i, 1, m) sum += ans[i];
    printf("%lld\n", n - sum);
    REP(i, 1, m) printf("%lld\n", ans[i]);
    return 0;
}
