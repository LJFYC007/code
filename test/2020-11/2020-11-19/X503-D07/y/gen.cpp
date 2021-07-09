/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 11时20分12秒
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
    freopen("y.in", "w", stdout);
    int n = 40, m =rand() % (n * (n - 1)) + 1, d = 11;
    printf("%d %d %d\n", n, m, d);
    srand(time(0));
    REP(i, 1, m)
    {
        int x = rand() % n + 1, y = rand() % n + 1;
        printf("%d %d %d\n", x, y, rand() % 2);
    }
    return 0;
}
