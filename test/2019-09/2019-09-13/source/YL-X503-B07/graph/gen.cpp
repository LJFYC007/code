/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年09月13日 星期五 08时54分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef unsigned long long LL;

const LL Mod = 1ll << 63;

int main()
{
    freopen("graph.in", "w", stdout);
    srand(time(0));
    int n = 100000, m = 500000;
    printf("%d %d\n", n, m);
    REP(i, 1, m)
    {
        LL u = rand() % n + 1, v = rand() % n + 1;
        LL w = rand() * rand(); w = (rand() % Mod + Mod) % Mod;
        w = ((w * w) % Mod + Mod) % Mod;
        printf("%llu %llu %llu\n", u, v, w);
    }
    return 0;
}
