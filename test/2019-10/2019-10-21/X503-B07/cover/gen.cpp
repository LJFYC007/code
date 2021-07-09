/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月21日 星期一 10时39分18秒
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
    freopen("cover.in", "w", stdout);
    srand(time(0));
    int n = 1000, m = 1000;
    printf("%d %d\n", n, m);
    REP(i, 1, m)
    {
        int l = rand() % n + 1, r = rand() % n + 1;
        if ( l > r ) swap(l, r);
        printf("%d %d %d\n", l, r, rand() % 10);
    }
    return 0;
}
