/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年11月03日 星期日 09时42分26秒
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
    freopen("c.in", "w", stdout);
    int n = 200000;
    printf("%d\n", n);
    REP(i, 1, n) printf("%d %d\n", rand(), rand());
    return 0;
}
