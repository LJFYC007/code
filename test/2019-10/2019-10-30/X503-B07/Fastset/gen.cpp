/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月30日 星期三 08时45分57秒
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
    freopen("Fastset.in", "w", stdout);
    srand(time(0));
    int n = 300000;
    printf("%d\n", n);
    REP(i, 2, n) printf("%d %d\n", i, i - 1);
    REP(i, 1, n)
    {
        int l = rand() % (n / 2) + 1;
        int r = rand() % (n / 2) + l;
        int p = rand() % n + 1;
        printf("%d %d %d\n", l, r, p);
    }
    return 0;
}
