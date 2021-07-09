#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
 
const int maxn = 3e4 + 10;
const int Mod = 998244353;
 
int n, k, f[maxn][3][2], ans;
char s[maxn], t[maxn];
 
namespace Subtask1
{
    int ans, f[10][10];
 
    inline void Check()
    {
    /*
        REP(i, 1, n) REP(j, 1, n)   
        {
            f[i][j] = 0;        
            if ( i && j && s[i] == t[j] ) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
            if ( i ) f[i][j] = max(f[i][j], f[i - 1][j]);
            if ( j ) f[i][j] = max(f[i][j], f[i][j - 1]);
        }
        */
        if ( f[n][n] >= n - k ) ++ ans;
    }
 
    inline void DFS(int x)
    {
        if ( x == n + 1) { Check(); return ; } 
        REP(i, 0, 25) 
        { 
            t[x] = i + 'A'; 
            REP(y, 1, n) 
            {
                f[y][x] = 0;
                if ( t[x] == s[y] ) f[y][x] = max(f[y][x], f[y - 1][x - 1] + 1);
                f[y][x] = max(f[y][x], f[y - 1][x]);
                f[y][x] = max(f[y][x], f[y][x - 1]);
            }
            DFS(x + 1); 
        } 
    }
 
    int main()
    {
        DFS(1); cout << ans << endl;
        return 0;
    }
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1); scanf("%lld", &k);
    if ( k == 0 ) puts("1");
    else return Subtask1 :: main();
    f[0][0][0] = 1;
    REP(i, 1, n)
    {
        REP(o, 0, 1) f[i][0][o] = (f[i - 1][0][o] + f[i - 1][1][o] * (i == n ? 26 : 25)) % Mod;
        f[i][0][1] = (f[i][0][1] + f[i - 1][2][0] * (s[i] == s[i - 1] ? 0 : 1)) % Mod;
 
        REP(o, 0, 1) f[i][1][o] = f[i - 1][1][o];
        f[i][1][1] = (f[i][1][1] + f[i - 1][0][0] * (s[i] == s[i + 1] ? 0 : 1)) % Mod;
 
        REP(o, 0, 1) f[i][2][o] = (f[i - 1][2][o]); // + f[i - 1][0][o] * (s[i] == s[i + 1] ? 25 : 24)) % Mod;
 
        if ( i >= 2 ) f[i][2][0] = (f[i][2][0] + f[i - 2][0][0] * (s[i] == s[i - 1] ? 25 : 24)) % Mod;
        if ( i >= 2 ) f[i][0][1] = (f[i][0][1] + f[i - 2][0][0] * (s[i] == s[i - 1] ? 0 : 24)) % Mod;
    }
    ans = (f[n][0][1] + f[n - 1][0][0] * 26 + f[n][2][0]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
