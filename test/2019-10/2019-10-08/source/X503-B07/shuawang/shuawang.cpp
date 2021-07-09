/***************************************************************
	File name: shuawang.cpp
	Author: ljfcnyali
	Create time: 2019年10月08日 星期二 20时20分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 10;

int T, n, m, a, q, tot, ans[10000000], len;
char s[maxn], b[maxn];

inline void calc()
{
    len = 1; a = 0; int n = str(b + 1);
    REP(i, 1, n)
    {
        a = a * 10 + b[i] - '0';
        len *= 10;
    }
}

inline bool Check(int x)
{
    REP(i, 1, n) 
    {
        if ( x < a || x < len / 10 ) break ; 
        if ( (x - a) % len == 0 ) return true;
        x /= 10;
    }
    return false;
}

inline void DFS(int x, int num)
{
    if ( x == n + 1 ) 
    {
        if ( Check(num) ) ans[++ tot] = num; 
        return ;
    }
    if ( s[x] != '?' ) { DFS(x + 1, num * 10 + s[x] - '0'); return ; }
    REP(i, 0, 9)
    {
        if ( x == 1 && i == 0 ) continue ;
        DFS(x + 1, num * 10 + i);
    }
}

int main()
{
    freopen("shuawang.in", "r", stdin);
    freopen("shuawang.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &q);
        scanf("%s", b + 1); calc();
        scanf("%s", s + 1);  
        tot = 0; DFS(1, 0);
        sort(ans + 1, ans + tot + 1);
        REP(i, 1, q) { int x; scanf("%d", &x); printf("%d\n", x <= tot ? ans[x] : -1); }
    }
    return 0;
}
