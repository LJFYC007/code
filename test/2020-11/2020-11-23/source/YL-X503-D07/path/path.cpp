/***************************************************************
	File name: path.cpp
	Author: ljfcnyali
	Create time: 2020年11月23日 星期一 08时46分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n;
struct node { vector<int> a; } a[maxn][maxn];

inline node operator +(node x, node y)
{
    vector<int> a = x.a, b = y.a;
    int len = max(a.size(), b.size()); a.resize(len); b.resize(len);
    REP(i, 0, len - 1) a[i] += b[i]; 
    for ( int i = 0; i < a.size(); ++ i )
    {
        if ( a[i] < 10 ) continue ;
        if ( i + 1 == a.size() ) a.push_back(0);
        a[i + 1] += a[i] / 10; a[i] %= 10;
    }
    while ( a.size() > 1 && a.back() == 0 ) a.pop_back();
    node z; z.a = a; return z;
}

inline node operator -(node x, node y)
{
    vector<int> a = x.a, b = y.a;
    int len = max(a.size(), b.size()); a.resize(len); b.resize(len);
    REP(i, 0, len - 1) a[i] -= b[i];
    for ( int i = 0; i < a.size(); ++ i ) 
    {
        if ( a[i] >= 0 ) continue ;
        a[i] += 10; -- a[i + 1];
    }
    while ( a.size() > 1 && a.back() == 0 ) a.pop_back();
    node z; z.a = a; return z;
}

inline void output(node x)
{
    if ( !x.a.size() ) { printf("0"); return ; }
    while ( x.a.size() ) { printf("%d", x.a.back()); x.a.pop_back(); }
}

int main()
{
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    scanf("%d", &n);
    for ( int i = n - 1; i >= 1; -- i ) REP(j, 2, n)
    {
        node val; val.a.clear(); val.a.push_back(1);
        REP(k, j - 1, n) val = val + a[i + 1][k];
        REP(k, i + 2, n) val = val + a[k][n];
        REP(k, i + 1, n) val = val - a[k][j];
        REP(k, j + 1, n) val = val - a[n][k];

        a[i][j] = val;
    }

    REP(i, 1, n) 
    { 
        REP(j, 1, n) { output(a[i][j]); printf(" "); }
        puts(""); 
    }
    return 0;
}
