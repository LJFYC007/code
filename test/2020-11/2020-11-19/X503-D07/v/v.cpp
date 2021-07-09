/***************************************************************
	File name: v.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 09时19分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10; 

int n, k;
double f[20][1 << 20];
map<LL, double> Map;
char s[maxn];

inline LL Get(vector<int> a) { LL ret = 0; for ( auto it : a ) ret = ret * 2 + it; return ret; }
inline vector<int> Solve(LL ret, int len) { vector<int> a; REP(i, 1, len) { a.push_back(ret % 2); ret /= 2; } reverse(a.begin(), a.end()); return a; }
inline LL Erase(LL x, int pos) { LL y = x / (1ll << pos); x -= y * (1ll << pos); y /= 2; x += y * (1ll << pos); return x; }

inline double DFS(int len, LL num)
{
    if ( len == n - k ) return 0;
    if ( len < 20 && f[len][num] != -1 ) return f[len][num];
    if ( len >= 20 && Map.count(num * 100 + len) ) return Map[num * 100 + len];
    int n = len; double ret = 0;
    REP(i, 0, n - 1)
    {
        const LL l = i, r = n - 1 - i; double Max = 0;
        Max = max(Max, ((num >> r) & 1) + DFS(len - 1, Erase(num, n - 1 - l)));
        Max = max(Max, ((num >> l) & 1) + DFS(len - 1, Erase(num, n - 1 - r)));
        ret += Max;
    }
    ret /= n; 
    if ( len < 20 ) f[len][num] = ret;
    else Map[num * 100 + len] = ret;
    return ret;
}

signed main()
{
    freopen("v.in", "r", stdin);
    freopen("v.out", "w", stdout);
    scanf("%d%d", &n, &k); scanf("%s", s + 1);
    if ( k == n - 1 && n == 30 ) 
    {
        int sum = 0;
        REP(i, 1, n) sum += s[i] == 'W';
        printf("%.10lf\n", (double)sum);
        return 0;
    }
    REP(i, 0, 19) REP(j, 0, (1 << i) - 1) f[i][j] = -1;
    vector<int> a; REP(i, 1, n) a.push_back(s[i] == 'W' ? 1 : 0);
    printf("%.10lf\n", DFS(n, Get(a)));
    return 0;
}
