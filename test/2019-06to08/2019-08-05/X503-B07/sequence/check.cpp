/***************************************************************
	File name: check.cpp
	Author: ljfcnyali
	Create time: 2019年08月05日 星期一 09时38分01秒
***************************************************************/
#include<bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 10000;

int n, a[maxn], b[maxn];

int main()
{
    freopen("sequence1.in", "r", stdin);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &a[i], &b[i]);
    freopen("sequence.out", "r", stdin);
    int sum1 = 0, sum2 = 0;
    REP(i, 1, n / 2) { int x; scanf("%d", &x); sum1 += a[x]; }  
    REP(i, 1, n / 2) { int x; scanf("%d", &x); sum2 += b[x]; }  
    if ( sum1 == sum2 ) cerr << "AC~~~" << endl;
    else { cerr << "WA!!!" << endl; sleep(1000); }
    return 0;
}
