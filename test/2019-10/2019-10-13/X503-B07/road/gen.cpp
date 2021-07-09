/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月13日 星期日 09时38分52秒
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
    freopen("road.in", "w", stdout);
    int n = 50000, m = 100000, k = 10;
    int s = rand() % n + 1, t = rand() % n + 1;
    srand(time(0));
    printf("%d %d %d %d %d\n", n, m, k, s, t);
    REP(i, 1, m)
    {
        int u = rand() % n + 1, v = rand() % n + 1, w = rand() % 1000000000;
        printf("%d %d %d\n", u, v, w);
    }
    return 0;
}
