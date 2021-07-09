/***************************************************************
	File name: walking.cpp
	Author: ljfcnyali
	Create time: 2020年11月26日 星期四 10时16分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n;
bool f[110][maxn];
char t[110], s[maxn];

int main()
{
    freopen("walking.in", "r", stdin);
    freopen("walking.out", "w", stdout);
    scanf("%s", t + 1); int m1 = str(t + 1);
    scanf("%d", &n);
    REP(o, 1, n) 
    {
        scanf("%s", s + 1); int m2 = str(s + 1);
        REP(i, 0, m1) REP(j, 0, m2) f[i][j] = false; f[0][0] = true;
        REP(i, 0, m1 - 1) 
        {
            if ( t[i + 1] == '*' ) 
            {
                REP(j, 0, m2 - 1) if ( f[i][j] )
                {
                    REP(k, j, m2) f[i + 1][k] = true;
                    break ; 
                }
                continue ;
            }
            REP(j, 0, m2 - 1) if ( f[i][j] )
            {
                if ( t[i + 1] == '?' ) { f[i + 1][j + 1] = true; continue ; }
                if ( t[i + 1] == '[' )
                {
                    bool flag = true; int k = i + 2, sum = 1;
                    while ( sum >= 1 ) 
                    {
                        if ( t[k] == '[' ) ++ sum;
                        if ( t[k] == ']' ) -- sum;
                        ++ k;
                    }
                    f[k - 1][j] = f[i + 1][j] = true; 
                    continue ;
                }
                if ( t[i + 1] == ']' ) { f[i + 1][j] = true; continue ; }
                if ( t[i + 1] == s[j + 1] ) f[i + 1][j + 1] = true;
            }
        }
        REP(i, 1, m2) printf("%d", f[m1][i]); puts("");
    }
    return 0;
}
