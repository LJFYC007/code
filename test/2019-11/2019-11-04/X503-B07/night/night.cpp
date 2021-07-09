/***************************************************************
    File name: night.cpp
    Author: ljfcnyali
    Create time: 2019年11月04日 星期一 08时28分16秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 1050010;
 
int T, n, m, q, c, a[maxn], b, ans[maxn], Max;
 
inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}
 
namespace Subtask1
{
    inline void FWT(int *a, int n, int opt)
    {
        REP(i, 0, n - 1)
            for ( int j = 0; j < (1 << n); j += (1 << (i + 1)) )
                REP(k, 0, (1 << i) - 1)
                    a[j + k] = a[j + k] + opt * a[j + k + (1 << i)];
    }
     
    int f[maxn], g[maxn], ans[maxn], b[maxn];
 
    inline void main()
    {
        mem(f); 
        REP(i, 1, n) ++ f[a[i]];
        read(q);
        FWT(f, m, 1); 
        REP(i, 1, q) { int x; scanf("%d", &x); printf("%d\n", f[x]); }
    }
}
 
namespace Subtask2
{
    inline void DFS(bitset<20> ret, int x, const int val)
    {
        if ( x == 20 || Max >= m - x ) { ans[ret.to_ulong()] += val; return ; }
        DFS(ret, ret._Find_next(x), val);
        if ( ret[x] )
        {
            bitset<20> s = (b << (x + 1)) | (1 << x);
            if ( (s & ret) == s )
            {
                ret = ret & s.flip();
                DFS(ret, ret._Find_next(x), val);
            }
        }
    }
 
    inline void main()
    {
        sort(a + 1, a + n + 1);
        bitset<20> ret;
        for ( int i = 1, j; i <= n; i = j + 1 )
        {
            j = i;
            while ( a[i] == a[j] && j <= n ) ++ j;
            -- j;
            ret = a[i]; DFS(ret, ret._Find_first(), j - i + 1);
        }
        read(q);
        REP(i, 1, q)
        {
            int x; read(x);
            printf("%d\n", ans[x]);
        }
    }
}
 
int main()
{
    freopen("night.in", "r", stdin);
    freopen("night.out", "w", stdout);
    read(T);
    while ( T -- )
    {
        Max = b = 0; mem(ans);
        read(n); read(m);
        REP(i, 1, n) read(a[i]);
        read(c);
        REP(i, 1, c) { int x; read(x); b |= (1 << x - 1); Max = max(Max, x); }
        if ( c == 0 ) Subtask1 :: main();
        else Subtask2 :: main();
    }
    return 0;
}
