/***************************************************************
	File name: UVA10572.cpp
	Author: ljfcnyali
	Create time: 2019年09月22日 星期日 18时44分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int n, m, a[10][10], T, Con[10], Col[10], ans[10][10];
bool vis[10], flag;
map<LL, int> f;

inline char read()
{
    char c = getchar();
    while ( c != '#' && c != '.' && c != 'o' ) c = getchar();
    return c;
}

inline void Solve(int C, int S)
{
    REP(i, 1, m) { Con[i] = S % 8; S /= 8; }
    REP(i, 1, m + 1) { Col[i] = C % 2; C /= 2; }
}

inline int DFS(int x, int y, int C, int S, int Color)
{
    if ( flag ) ans[x][y] = Color;
    LL t = C * 100000000000ll + S * 1000 + ((x - 1) * m + y) * 10 + Color, ans = 0;
    if ( a[x][y] != -1 && a[x][y] != Color ) return f[t] = ans;
    if ( f.count(t) ) return t;
    Solve(C, S);
    printf("%d %d %d\n", x, y, Color);
    printf("Con: "); REP(i, 1, m) printf("%d ", Con[i]); puts("");
    printf("Col: "); REP(i, 1, m + 1) printf("%d ", Col[i]); puts("");
    // cerr << x << " " << y << " " << Color << endl;
    // cerr << "Con: "; REP(i, 1, m) cerr << Con[i] << " "; cerr << endl;
    // cerr << "Col: "; REP(i, 1, m + 1) cerr << Col[i] << " "; cerr << endl; 
    if ( Col[y - 1] == Col[y] && Col[y] == Col[y + 1] && Col[y] == Color ) return f[t] = ans;
    if ( x == n && y == m )
    {
        if ( !(Col[y] == Color && Col[y - 1] == Col[y]) ) 
        { 
            int Last = 0;
            REP(i, 1, m - 1) if ( Col[i] ) { Last = Con[i]; break ; }
            if ( Col[m + 1] ) Last = Con[m];
            REP(i, 1, m - 1) if ( Col[i] && Con[i] != Last ) goto Next;
            Last = 0;
            REP(i, 1, m - 1) if ( !Col[i] ) { Last = Con[i]; break ; }
            if ( !Col[m + 1] ) Last = Con[m];
            REP(i, 1, m - 1) if ( !Col[i] && Con[i] != Last ) goto Next;
            ans = 1; flag = false; 
        }
Next: ;
        return f[t] = ans;
    }
    if ( Col[y + 1] != Color && x > 1 ) 
    {
        int sum1 = 0, sum2 = 0;
        REP(i, 1, m + 1) if ( Col[i] != Color ) ++ sum1;
        REP(i, 1, m) if ( Con[i] == Con[y] ) ++ sum2;
        if ( sum1 > 1 && sum2 == 1 ) return f[t] = ans; 
        if ( sum2 == 1 && (x < n - 1 || y < m - 1) ) return f[t] = ans;
    }
    if ( Col[y - 1] == Color && Col[y + 1] != Color ) Con[y] = Con[y - 1];
    if ( Col[y - 1] != Color && Col[y + 1] != Color ) 
    {
        REP(i, 1, m) vis[i] = false;
        REP(i, 1, m) vis[Con[i]] = true;
        REP(i, 1, m) if ( !vis[i] ) { Con[y] = i; break ; }
    }
    if ( Col[y - 1] == Color && Col[y + 1] == Color ) 
    {
        int tmp = Con[y + 1];
        REP(i, 1, m) if ( Con[i] == tmp ) Con[i] = Con[y - 1];
    }
    C = S = 0;
    for ( int i = m; i >= 1; -- i ) S = S * 8 + Con[i];
    Col[y] = Color;
    if ( y != m ) for ( int i = m + 1; i >= 1; -- i ) C = C * 2 + Col[i];
    else for ( int i = m; i >= 0; -- i ) C = C * 2 + Col[i];
    if ( y != m ) ans += DFS(x, y + 1, C, S, 0) + DFS(x, y + 1, C, S, 1);
    else ans += DFS(x + 1, 1, C, S, 0) + DFS(x + 1, 1, C, S, 1);
    return f[t] = ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        f.clear(); flag = true;
        scanf("%d%d", &n, &m);
        REP(i, 1, n) REP(j, 1, m)
        {
            char c = read();
            if ( c == '#' ) a[i][j] = 0;
            else if ( c == 'o' ) a[i][j] = 1;
            else a[i][j] = -1;
        }
        int sum = DFS(1, 1, 0, 0, 0) + DFS(1, 1, 0, 0, 1);
        printf("%d\n", sum);
        if ( sum ) REP(i, 1, n) { REP(j, 1, m) printf("%c", ans[i][j] == 0 ? '#' : 'o'); puts(""); }
    }
    return 0;
}
