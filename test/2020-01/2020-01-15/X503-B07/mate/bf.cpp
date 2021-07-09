/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年01月15日 星期三 08时22分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 22;

int n, m1, m2, ans, a[maxn], p1[maxn], p2[maxn], b[maxn];

int main()
{
    freopen("mate.in", "r", stdin);
    freopen("mate.out", "w", stdout);
    scanf("%d%d%d", &n, &m1, &m2);
    REP(i, 1, m1) { int u, v; scanf("%d%d", &u, &v); p1[u] = v; p1[v] = u; }
    REP(i, 1, m2) { int u, v; scanf("%d%d", &u, &v); p2[u] = v; p2[v] = u; }
    REP(i, 1, n) a[i] = i;
    do
    {
        REP(i, 1, n) b[a[i]] = i;
        REP(i, 1, n) 
        {
            if ( !p1[b[i]] ) continue ;
            if ( p1[b[i]] == b[p1[i]] ) ;
            else goto finish ;
        }
        REP(i, 1, n) 
        {
            if ( !p2[i] ) continue ;
            if ( p2[b[i]] == b[p2[i]] ) ;
            else goto finish ;
        }
        REP(i, 1, n) printf("%d ", b[i]); puts("");
        ++ ans;
finish : ;
    } while ( next_permutation(a + 1, a + n + 1) ) ;
    printf("%d\n", ans);
    return 0;
}
