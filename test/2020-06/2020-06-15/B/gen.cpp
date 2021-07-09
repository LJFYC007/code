/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年06月15日 星期一 09时35分11秒
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
    freopen("B.in", "w", stdout);
    srand(time(0));
    int n = 1, m = 200; 
    // int n = 3, m = 5; 
    printf("%d %d\n", n, m);
    REP(i, 1, n)
    {
        int len = rand() % 3 + 1;
        REP(j, 1, len) printf("%c", rand() % 4 + 'a'); puts("");
    }
    REP(i, 1, m) printf("%c", rand() % 4 + 'a'); puts("");
    REP(i, 1, m)
    {
        int op = rand() % 2 + 1, l = rand() % m + 1, r = rand() % m + 1;
        if ( l > r ) swap(l, r);
        if ( op == 2 ) printf("%d %d %d\n", op, l, r);
        else 
        {
            printf("%d %d %d ", op, l, r);
            int len = rand() % 3 + 1;
            REP(j, 1, len) printf("%c", rand() % 4 + 'a'); puts("");
        }
    }
    return 0;
}
