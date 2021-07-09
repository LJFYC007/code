/***************************************************************
	File name: butterfly.cpp
	Author: ljfcnyali
	Create time: 2019年10月09日 星期三 19时03分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int n, m, ans, N, a[10], b[10], t[10];
bool p[1000];

inline bool calc(int x)
{
    int num = 0;
    REP(i, 1, m)
    {
        if ( x % 2 == 0 ) ++ num;
        else -- num;
        if ( num < 0 ) return false;
        x /= 2;
    }
    if ( num > 0 ) return false;
    return true;
}

inline int Check()
{
    int sum = 0;
    REP(i, 1, n) b[i] = a[i];
    for ( int j = m; j >= 1; -- j )
    {
        int num = 0; bool flag = false;
        for ( int i = n; i >= 1; -- i ) 
        {
            if ( b[i] % 2 == 0 ) ++ num;
            else -- num;
            if ( num < 0 ) flag = true;
            b[i] /= 2;
        }
        if ( !flag && num == 0 ) ++ sum;
    }
    return sum;
}

inline void DFS(int x, int num)
{
    if ( num + (n - x + 1) + m <= ans ) return ;
    if ( x == n + 1 ) 
    {
        num += Check(); 
        if ( num > ans ) 
        {
            ans = num;
            REP(i, 1, n) t[i] = a[i];
        }
        return ; 
    }
    REP(i, 0, N - 1)
    {
        a[x] = i; DFS(x + 1, num + p[i]);
    }
}

int main()
{
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
    scanf("%d%d", &n, &m); N = 1 << m;
    REP(i, 0, N - 1) p[i] = calc(i);
    DFS(1, 0);
    printf("%d %d %d\n", n, m, ans);
    REP(i, 1, n)
    {
        REP(j, 1, m) { b[j] = t[i] % 2; t[i] /= 2; }
        for ( int j = m; j >= 1; -- j ) printf("%c", b[j] ? '(' : ')');
        puts("");
    }
    return 0;
}
