/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2020年01月11日 星期六 09时47分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int sum[maxn], p[maxn], f[maxn][maxn];
string c[maxn];
map<string, int> Map[3][maxn];

inline string Solve(int n)
{
    string s = "", S;
    printf("? 1 %d\n", n); fflush(stdout);
    REP(i, 1, n * (n + 1) / 2) { cin >> S; sort(S.begin(), S.end()); ++ Map[1][S.length()][S]; }
    if ( n == 1 ) return S;
    printf("? 1 %d\n", n - 1); fflush(stdout);
    REP(i, 1, n * (n - 1) / 2) { cin >> S; sort(S.begin(), S.end()); ++ Map[2][S.length()][S]; }
    REP(i, 1, n)
    {
        for ( auto j : Map[1][i] )
            if ( Map[2][i][j.first] < j.second ) { S = j.first; break ; }
        // cout << S << endl;
        REP(j, 0, 25) p[j] = 0;
        for ( auto j : S ) ++ p[j - 'a'];
        REP(j, 0, 25) if ( p[j] > sum[j] ) { ++ sum[j]; s = c[j] + s; }
    }
    return s;
}

inline string Query(string s, int n)
{
    string S;
    printf("? 1 %d\n", n);
    REP(i, 1, n * (n + 1) / 2)
    {
        cin >> S;
        for ( auto j : S ) ++ f[S.length()][j - 'a'];
    }
    REP(i, 0, 25) sum[i] = 0;
    if ( n & 1 ) REP(j, 0, 25) if ( f[n / 2 + 1][j] - f[n / 2][j] > 0 ) { ++ sum[j]; s = s + c[j]; }
    for ( int i = n / 2 - 1; i >= 0; -- i )
    {
        ++ sum[s[i] - 'a'];
        REP(j, 0, 25) if ( f[i + 1][j] - f[i][j] > sum[j] ) { ++ sum[j]; s = s + c[j]; }
    }
    return s;
}

int main()
{
    int n; scanf("%d", &n);
    REP(i, 0, 25) c[i] = i + 'a';
    if ( n <= 1 ) 
    {
        string s = Solve(n);
        printf("! ");
        cout << s << endl;
        return 0; 
    }
    string s = Solve(n / 2);
    s = Query(s, n);
    printf("! ");
    cout << s << endl;
    return 0;
}
