/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 12时27分07秒
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
    freopen("light.in", "w", stdout);
    int T = 5;
    printf("%d\n", T);
    srand(time(0));
    while ( T -- ) 
    {
        int n = 100; printf("%d 10\n", n);
        REP(i, 1, n) printf("%c", rand() % 2 ? '1' : '0'); puts("");
    }
    return 0;
}
