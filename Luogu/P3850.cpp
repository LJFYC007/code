/***************************************************************
	File name: P3850.cpp
	Author: ljfcnyali
	Create time: 2019年06月23日 星期日 15时36分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100210;

vector<int> a;
char s[maxn][20];
int cnt, n, m, q;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%s", s[++ cnt]); a.push_back(cnt); }
    scanf("%d", &m);
    REP(i, 1, m) { int x; scanf("%s %d", s[++ cnt], &x); a.insert(a.begin() + x, cnt); }
    scanf("%d", &q);
    REP(i, 1, q)
    {
        int x; scanf("%d", &x);
        printf("%s\n", s[a[x]]);
    }
    return 0;
}
