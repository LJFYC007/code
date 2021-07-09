/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年01月14日 星期二 11时16分04秒
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
    freopen("reverse.in", "w", stdout);
    srand(time(0));
    int T = 100; printf("%d\n", T);
    while ( T -- ) 
    {
        int n = 20; printf("%d 0\n", n);
        REP(i, 1, n) printf("%d ", rand() % 100 + 1); puts("");

    }
    return 0;
}
