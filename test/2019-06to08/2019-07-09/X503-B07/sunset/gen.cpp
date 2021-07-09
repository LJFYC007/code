/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年07月09日 星期二 10时33分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int main()
{
    freopen("sunset.in", "w", stdout);
    int n = 500, m = 500, q = 500;
    printf("%d %d\n", n, m);
    srand(time(0));
    REP(i, 1, m)
    {
        int u = rand() % n + 1, v = rand() % n + 1;
        printf("%d %d\n", u, v);
    }
    printf("%d\n", q);
    REP(i, 1, q)
    {
        int u = rand() % n + 1, v = rand() % n + 1;
        printf("%d %d\n", u, v);
    }
    return 0;
}
