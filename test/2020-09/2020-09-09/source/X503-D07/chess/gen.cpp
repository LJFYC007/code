/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年09月09日 星期三 19时27分40秒
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
    freopen("chess.in", "w", stdout);
    int T = 10; printf("%d\n", T);
    srand(time(0));
    while ( T -- ) 
    {
        int n, q; n = rand() % 1000 + 1; q = rand() % 1000 + 1; printf("%d %d\n", n, q);
        REP(i, 1, n) printf("%d %d\n", rand(), rand());
        REP(i, 1, q) printf("%d %d\n", rand(), rand());
    }
    return 0;
}
