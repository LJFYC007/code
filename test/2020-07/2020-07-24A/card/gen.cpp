/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月24日 星期五 16时21分16秒
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
    freopen("card.in", "w", stdout);
    int n = rand() % 500 + 1, m = rand() % 500 + 1, k = rand() % (2 * m) + 2;
    printf("%lld %lld %lld\n", m, n, k);
    return 0;
}
