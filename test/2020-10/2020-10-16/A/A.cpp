/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年10月16日 星期五 18时38分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int T, n, d, a[maxn];
bool vis[maxn];

int main()
{
    while ( ~scanf("%d%d", &n, &d) )
    {
        int now = n; mem(vis);
        REP(i, 1, n)
        {
            now += d + 1; 
            if ( now > n ) 
            {
                now = d + 1; 
                while ( vis[now] ) -- now;
            }
            a[i] = now; vis[now] = true;
        }
        REP(i, 1, n - 1) if ( abs(a[i] - a[i + 1]) <= d ) { puts("-1"); goto Next ; }
        REP(i, 1, n) printf("%d ", a[i]); puts("");
Next : ;
    }
    return 0;
}
