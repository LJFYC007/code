/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2019年11月12日 星期二 18时52分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int main()
{
    freopen("catch.in", "r", stdin);
    freopen("catch.out", "w", stdout);
    int x, y, m, n, L; 
    scanf("%d%d%d%d%d", &x, &y, &m, &n, &L);
    REP(i, 0, 1000)
    {
        if ( x == y ) { printf("%d\n", i); return 0; }
        x = (x + m) % L;
        y = (y + n) % L;
    }
    puts("Impossible");
    return 0;
}
