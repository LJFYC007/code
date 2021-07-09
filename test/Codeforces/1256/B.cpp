/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 21时03分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int T, a[maxn], n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n);
        REP(i, 1, n) scanf("%d", &a[i]);
        int now = 1;
        while ( now < n ) 
        {
            int Min = n + 1, pos;
            REP(i, now, n) if ( a[i] < Min ) { Min = a[i]; pos = i; }
            if ( pos == now ) { ++ now; continue ; }
            for ( int j = pos; j > now; -- j ) swap(a[j], a[j - 1]);
            now = pos;
        }
        REP(i, 1, n) printf("%d ", a[i]); puts("");
    }
    return 0;
}
