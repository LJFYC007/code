/***************************************************************
	File name: line.cpp
	Author: ljfcnyali
	Create time: 2019年11月12日 星期二 08时45分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;

int n, a[maxn];

int main()
{
    freopen("line.in", "r", stdin);
    freopen("line.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int x; scanf("%d", &x);
        REP(j, 1, n)
            if ( !a[j] ) 
            {
                -- x;
                if ( x == -1 ) { a[j] = i; break ; }
            }
    }
    REP(i, 1, n) printf("%d ", a[i]); puts("");
    return 0;
}
