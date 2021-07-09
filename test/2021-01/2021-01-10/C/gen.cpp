/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 16时53分07秒
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
    freopen("input.txt", "w", stdout);
    int n = 20, m = 21, q = 1000; printf("%d %d %d\n", n, m, q);
    srand(time(0));
    REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    REP(i, n, m) 
    {
        int x = rand() % n + 1, y = rand() % n + 1;
        while ( x == y ) x = rand() % n + 1;
        printf("%d %d\n", x, y);
    }
    REP(i, 1, q)
    {
        int k = rand() % n + 1; printf("%d ", k);
        REP(j, 1, k) printf("%d " ,rand() % n + 1); puts("");
    }
    return 0;
}
