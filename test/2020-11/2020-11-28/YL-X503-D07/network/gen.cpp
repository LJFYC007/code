/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月28日 星期六 11时24分46秒
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
    freopen("network.in", "w", stdout);
    int n = 4, m = 10; printf("%d %d\n", n, m);
    srand(time(0));
    REP(i, 1, m)
    {
        int x = rand() % n + 1, y = rand() % n + 1;
        while ( x == y ) x = rand() % n + 1;
        printf("%d %d\n", x, y);
    }
    return 0;
}
