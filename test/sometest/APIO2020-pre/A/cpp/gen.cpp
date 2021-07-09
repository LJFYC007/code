/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年08月09日 星期日 20时42分46秒
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
    freopen("input.txt", "w", stdout);
    srand(time(0));
    int n = 10; printf("%d\n", n);
    REP(i, 1, 5)
    {
        int x = rand();
        printf("0 %d\n", x);
        printf("1 %d %d\n", rand() % i, i - 1);
    }
    return 0;
}
