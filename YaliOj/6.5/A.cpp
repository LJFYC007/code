/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年06月08日 星期六 08时17分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int n, m, p, a[110][110], b[110][110];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, m) scanf("%d", &a[i][j]);
    scanf("%d", &p);
    REP(i, 1, m) REP(j, 1, p) scanf("%d", &b[i][j]);
    REP(i, 1, n) 
    {
        REP(j, 1, p)
        {
           int x = 0;
           REP(k, 1, m) x += a[i][k] * b[k][j];
           printf("%d ", x);
        } 
        puts("");
    }
    return 0;
}
