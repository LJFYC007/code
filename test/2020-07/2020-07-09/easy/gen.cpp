/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月09日 星期四 11时39分40秒
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
    freopen("easy.in", "w", stdout);
    srand(time(0));
    int n = 200000, Q = 200000;
    printf("%d %d\n", n, Q);
    REP(i, 1, n) printf("%d ", rand() % 998244353); puts("");
    REP(i, 1, Q) 
    {
        int l = rand() % n + 1, r = rand() % n + 1;
        if ( l > r ) swap(l, r);
        printf("%d %d\n", l, r);
    }
    return 0;
}
