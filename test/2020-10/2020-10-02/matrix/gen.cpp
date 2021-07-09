/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 10时12分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
    freopen("matrix.in", "w", stdout);
    srand(time(0));
    int n = 1000, m = 3000; 
    // n = 2; m = 6;
    printf("%d %d\n", n, m);
    REP(i, 1, n)
    {
        int l = rand() % m + 1, r = rand() % m + 1;
        if ( l == r ) { if ( l == 1 ) ++ r; else -- l; }
        if ( l > r ) swap(l, r);
        printf("%d %d\n", l, r);
    }
    return 0;
}
