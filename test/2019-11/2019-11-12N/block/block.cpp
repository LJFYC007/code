/***************************************************************
	File name: block.cpp
	Author: ljfcnyali
	Create time: 2019年11月12日 星期二 19时20分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 11;

int T, Time, n, m, k, t, p[maxn], Map[maxn][maxn][4], ans; // 0 -> up, 1 -> right, 2 -> down, 3 -> left
int a[maxn][maxn], b[maxn][maxn], val;
bool flag;

inline void Move(int k, int &ret)
{
    if ( k == 0 || k == 3 )
    {
        REP(i, 1, n) REP(j, 1, n)
        {
            if ( !a[i][j] ) continue ;
            int x = i, y = j, w = a[i][j]; a[i][j] = 0;
            while ( !Map[x][y][k] )
            {
                if ( k == 0 ) -- x; else -- y;
                if ( a[x][y] ) { if ( k == 0 ) ++ x; else ++ y; break ; }
                if ( b[x][y] && b[x][y] != w ) { flag = false; return ; }                
                if ( b[x][y] == w ) { ret += b[x][y]; b[x][y] = 0; flag = true; goto finish1 ; }
            }
            if ( x != i || y != j ) flag = true;
            a[x][y] = w;
finish1 : ;
        }
    }
    else
    {
        for ( int i = n; i >= 1; -- i ) for ( int j = n; j >= 1; -- j )
        {
            if ( !a[i][j] ) continue ;
            int x = i, y = j, w = a[i][j]; a[i][j] = 0;
            while ( !Map[x][y][k] )
            {
                if ( k == 2 ) ++ x; else ++ y; 
                if ( a[x][y] ) { if ( k == 2 ) -- x; else -- y; break ; }
                if ( b[x][y] && b[x][y] != w ) { flag = false; return ; }                
                if ( b[x][y] == w ) { ret += b[x][y]; b[x][y] = 0; flag = true; goto finish ; }
            }
            if ( x != i || y != j ) flag = true;
            a[x][y] = w;
finish : ;
        }
    }
}

inline void DFS(int x, int ret)
{
    if ( x > Time ) return ;
    // cerr << ret + (Time - x) * val << endl;
    if ( x > 15 && ret + (Time - x) * val < ans ) return ;
    if ( ret > ans ) ans = ret;
    int A[maxn][maxn], B[maxn][maxn];
    REP(k, 0, 3)
    {
        REP(i, 1, n) REP(j, 1, n) { A[i][j] = a[i][j]; B[i][j] = b[i][j]; }
        int sum = ret; flag = false; Move(k, ret);
        if ( flag ) DFS(x + 1, ret); ret = sum;
        REP(i, 1, n) REP(j, 1, n) { a[i][j] = A[i][j]; b[i][j] = B[i][j]; }
    }
}

int main()
{
    freopen("block.in", "r", stdin);
    freopen("block.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d%d%d", &n, &m, &k, &t);
        mem(Map); mem(a); mem(b); 
        int sum = 0;
        REP(i, 1, n) Map[1][i][0] = Map[n][i][2] = Map[i][1][3] = Map[i][n][1] = 1;
        REP(i, 1, m) { int x, y; scanf("%d%d%d", &x, &y, &p[i]); ++ x; ++ y; a[x][y] = p[i]; sum += p[i]; }
        REP(i, 1, m) { int x, y; scanf("%d%d", &x, &y); ++ x; ++ y; b[x][y] = p[i]; }
        REP(i, 1, k) 
        {
            int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
            ++ a; ++ b; ++ c; ++ d;
            if ( a > c ) { swap(a, c); swap(b, d); }
            if ( a + 1 == c ) Map[a][b][2] = Map[c][d][0] = 1;
            if ( b > d ) { swap(a, c); swap(b, d); }
            if ( b + 1 == d ) Map[a][b][1] = Map[c][d][3] = 1;
        }
        ans = 0;
        REP(i, 0, t) 
        { 
            Time = i; val = ans / (i + 1);
            if ( i > 15 ) val -= 10 * (i - 15);
            if ( i > 20 ) break ; 
            DFS(0, 0); 
            if ( ans == sum ) { printf("1 %d\n", i); goto Next; }
        }
        printf("0 %d\n", ans);
Next : ;
    }
    return 0;
}

