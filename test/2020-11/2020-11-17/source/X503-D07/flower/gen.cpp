/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月17日 星期二 09时33分05秒
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
    freopen("flower.in", "w", stdout);
    int n = 5000, m = n; printf("%d %d\n", n, m);
    srand(time(0));
    REP(i, 1, n) printf("%d ", rand() % 300 + 1); puts("");
    REP(i, 1, m)
    {
        int l = rand() % n + 1, r = rand() % n + 1, k = rand() % 300 + 1;
        if ( l > r ) swap(l, r);
        printf("%d %d %d\n", l, r, k);
    }
    return 0;
}
