/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 08时43分06秒
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
    freopen("u.in", "w", stdout);
    int n = 1000, q = 1000; printf("%d %d\n", n, q);
    srand(time(0));
    REP(i, 1, q)
    {
        int r = rand() % n + 1;
        int c = rand() % n + 1;
        int l = rand() % n + 1;
        int s = rand() % 1000000 - 500000;
        printf("%d %d %d %d\n", r, c, l, s);
    }
    return 0;
}
