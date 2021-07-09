/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年12月31日 星期四 14时51分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int m;
pii a[maxn];

inline void print(int len, int op)
{
    int A = rand() % 1000000000;
    REP(i, 1, len)
        if ( op == 0 ) a[++ m] = pii(A, rand() % 1000000000);
        else a[++ m] = pii(A, rand() % 1000);
}

signed main(int argc, char* argv[])
{
    REP(i, 1, 1000000000) ;
    srand(time(0));
    int N = atoi(argv[1]), n = rand() % N + 1; printf("%d\n", n);
    int t = atoi(argv[2]);
    if ( t != 1 ) 
    {
        int lst = 1, x = rand() % min(10000, n - lst + 1) + 1;
        print(x, t); lst += x;
        while ( lst <= n ) 
        {
            x = rand() % min(100, n - lst + 1) + 1;
            print(x, t); lst += x;
        }
    }
    else print(n, 0);
    random_shuffle(a + 1, a + n + 1); 
    REP(i, 1, n) printf("%d %d\n", a[i].first, a[i].second);
    return 0;
}
