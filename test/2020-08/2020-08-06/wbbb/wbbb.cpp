/***************************************************************
	File name: wbbb.cpp
	Author: ljfcnyali
	Create time: 2020年08月06日 星期四 09时16分44秒
***************************************************************/
#include<bits/stdc++.h>
#include "wbbb.h"

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int a[1000];

void init() 
{ 
    int n = 0;
    REP(i, 0, (1 << 12) - 1)
    {
        int num = 0; REP(j, 1, 12) if ( (i >> j - 1) & 1 ) ++ num;
        if ( num == 6 ) a[++ n] = i;
    }
}   

int helpAlice(int x, int y)
{
    x = a[x]; y = a[y];
    REP(i, 1, 12) if ( !((x >> i - 1) & 1) && ((y >> i - 1) & 1) ) return i;
}

int helpBob(int x, int k)
{
    x = a[x];
    if ( (x >> k - 1) & 1 ) return 0;
    return 1;
}
