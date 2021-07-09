/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月23日 星期五 19时50分46秒
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
    freopen("c.in", "w", stdout);
    srand(time(0));
    int n = 10, m = 5; printf("%d %d\n", n, m);
    REP(i, 2, n) printf("%d %d\n", i - 1, i);
    REP(i, 1, m) 
    {
        int u = rand() % n + 1, v = rand() % n + 1;
        while ( u == v ) v = rand() % n + 1;
        printf("%d %d %d %d\n", rand() % 5 + 1, rand() % 3 + 1, u, v);
    }
    return 0;
}
