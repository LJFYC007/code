/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年01月11日 星期一 08时45分33秒
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
    freopen("amino.in", "w", stdout);
    int n = 18, q = 500000; printf("%d %d\n", n, q);
    srand(time(0));
    REP(i, 1, q) if ( rand() % 2 ) 
    {
        printf("I "); REP(j, 1, n) printf("%c" ,rand() % 2 + '0'); printf(" %d\n", rand()); 
    }
    else 
    {
        printf("Q ");
        REP(j, 1, n) 
            printf("*");
        /*
            if ( rand() % 2 )
        {
            printf("%c" ,rand() % 2 + '0'); 
        }
        else printf("*");
        */
        puts("");
    }
    return 0;
}
