/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月29日 星期日 10时05分37秒
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
    freopen("distant.in", "w", stdout);
    int n = 100, m = 10000, q = 100000;
    printf("%d %d %d\n", n, m, q);
    srand(time(0));
    REP(i, 1, m) printf("%d %d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 100000000, rand() % 2 + 1);
    REP(i, 1, q) printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    return 0;
}
