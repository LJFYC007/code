/***************************************************************
	File name: HaHa
	Author: ljfcnyali
	Create time: 2019年11月06日 19时40分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int m, n, p[60];

int main()
{
    scanf("%d%d", &m, &n);    
    REP(i, 1, n)
    {
        printf("1\n"); 
        fflush(stdout);
        scanf("%d", &p[i]);
        if ( p[i] == 0 ) exit(0);
        if ( p[i] == 1 ) p[i] = 1; else p[i] = 0;
    }
    int L = 1, R = m;
    REP(i, n + 1, 60)
    {
        int Mid = L + R >> 1;
        printf("%d\n", Mid);
        fflush(stdout);
        int x; scanf("%d", &x);
        if ( p[(i - 1) % n + 1] == 0 ) x = -x;
        if ( x == 0 ) exit(0);
        if ( x == 1 ) L = Mid + 1;
        else R = Mid - 1;
    }
    return 0;
}
