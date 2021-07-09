/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月12日 星期六 10时59分49秒
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
    freopen("backronym.in", "w", stdout);
    REP(i, 1, 20000) printf("%c", rand() % 2 == 0 ? 'a' : 'b'); puts("");
    printf("50\n");
    REP(i, 1 ,50)
    {
        REP(h, 1, 200) printf("%c", rand() % 2 == 0 ? 'a' : 'b'); printf(" %d\n", rand() % 200 - 100);
    }
    return 0;
}
