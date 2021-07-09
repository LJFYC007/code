/***************************************************************
	File name: loop.cpp
	Author: ljfcnyali
	Create time: 2020年01月18日 星期六 09时10分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int INF = 0x3f3f3f3f;

char s[maxn];
int n, las[maxn], f[maxn];
bool vis[maxn];

int main()
{
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
    while ( ~scanf("%s", s) )
    {
        n = str(s); mem(vis); mem(las); memset(f, 0x3f, sizeof(f));
        REP(i, 0, n - 1) if ( s[i] == s[(i + 1) % n] ) vis[i] = true;
        REP(i, 0, n - 1) if ( vis[i] ) 
        {
            int x = i, pos = i;
            REP(j, 1, n)
            {
                x = (x - 1 + n) % n; 
                if ( vis[x] ) { pos = (i + 1) % n; las[pos] = j; break ; }
            }
            x = n - las[pos]; 
            if ( x == 0 ) { f[pos] = 1; ++ x; pos = (pos - 1 + n) % n; }
            // printf("%d %d\n", x, pos);
            REP(j, 0, n - 1)
            {
                f[pos] = min(f[pos], x);
                ++ x; pos = (pos - 1 + n) % n;
            }
        }
        // REP(i, 0, n - 1) printf("%d ", f[i]); puts("");
        REP(i, 0, n - 1) if ( f[i] == INF ) f[i] = 0;
        REP(i, 0, n - 1)
        {
            bool flag = false;
            REP(j, 0, n - 1)
                if ( f[j] <= i && s[(j + i) % n] != s[(j - 1 + n) % n] ) 
                {
                    flag = true; break ;
                }
            printf("%d", flag);
        }
        puts("");
    }
    return 0;
}
