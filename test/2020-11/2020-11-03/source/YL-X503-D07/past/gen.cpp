/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月03日 星期二 10时41分56秒
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
    freopen("past.in", "w", stdout);
    srand(time(0));
    int n = 500; printf("%d\n", n);
    REP(i, 2, n) printf("%d %d\n", rand() % (i - 1) + 1, i);
    REP(i, 2, n) printf("%d %d\n", rand() % (i - 1) + 1, i);
    return 0;
}
