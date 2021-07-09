/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月25日 星期五 11时25分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

signed main(int argc, char* argv[])
{
    REP(i, 1, 1000000000) ;
    srand(time(0));
    int n = atoi(argv[1]), op = atoi(argv[2]);
    printf("%d\n", n);
    REP(i, 1, n) printf("%d ", rand() % 1000000); puts("");
    if ( op == 0 ) 
    {
        REP(i, 2, n) printf("%d %d %d\n", rand() % (i - 1) + 1, i, rand() % 1000000);
    }
    if ( op == 1 ) 
    {
        REP(i, 2, n) printf("%d %d %d\n", i, i - 1, rand() % 1000000);
    }
    if ( op == 2 ) 
    {
        REP(i, 2, n) printf("%d %d %d\n", 1, i, rand() % 1000000);
    }
    if ( op == 3 ) 
    {
        int m = n / 2;
        REP(i, 2, m) printf("%d %d %d\n", i / 2, i, rand() % 1000000);
        REP(i, m + 1, n) printf("%d %d %d\n", m / 2, i, rand() % 1000000);
    }
    return 0;
}

