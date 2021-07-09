/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年08月04日 星期日 19时56分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
    int a, b, c; scanf("%d%d%d", &a, &b, &c); printf("%d\n", max(0, b + c - a));
    return 0;
}
