/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 08时52分46秒
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
    freopen("lipschitz.in", "w", stdout);
    srand(time(0));
    int n = 1000, m = 1000; 
    printf("%d\n", n);
    REP(i, 1, n) printf("%d ", rand() % 1000); puts("");
    printf("%d\n", m);
    REP(i, 1, m) 
    {
        int opt = rand() % 2;
        printf("%d " ,opt);
        if ( !opt ) printf("%d %d\n", rand() % n + 1,  rand() % 1000);
        else 
        {
            int l = rand() % n + 1, r = rand() % n + 1;
            if ( l > r ) swap(l, r);
            printf("%d %d\n", l, r);
        }
    }
    return 0;
}
