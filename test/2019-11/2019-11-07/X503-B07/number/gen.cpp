/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年11月07日 星期四 09时38分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int main()
{
    srand(time(0));
    freopen("number.in", "w", stdout);
    int n = 1000000, m = 1000000;
    printf("%d %d\n", n, m);
    REP(i, 1, m) printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand());
    return 0;
}
