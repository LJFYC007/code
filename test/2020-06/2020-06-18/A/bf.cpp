/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月18日 星期四 10时20分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 51;

int n, m, op;
struct Matrix { int a[maxn][maxn]; } f[20010], g;
Matrix operator + (Matrix a, Matrix b)
{
    Matrix c;
    REP(i, 1, n) REP(j, 1, n) c.a[i][j] = a.a[i][j] | b.a[i][j];
    return c;
}
Matrix operator * (Matrix a, Matrix b)
{
    Matrix c;
    REP(i, 1, n) REP(j, 1, n) 
    {
        c.a[i][j] = 0;
        REP(k, 1, n) c.a[i][j] |= a.a[i][k] & b.a[k][j];
    }
    return c;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &op);
    REP(i, 1, m) { int x, y; scanf("%d%d", &x, &y); f[1].a[x][y] = 1; }
    int now = 1;
    while ( 1 ) 
    {
        ++ now;
        f[now] = f[now - 1] * f[1];
        REP(i, 1, n) { REP(j, 1, n) printf("%d ", f[now].a[i][j]); puts(""); }
        puts("");
        REP(j, 1, now - 1)
        {
            REP(x, 1, n) REP(y, 1, n) if ( f[now].a[x][y] != f[j].a[x][y] ) goto Next ;
            printf("%d %d\n", j, now - j);
            return 0;
Next : ; 
        }
    }
    return 0;
}
