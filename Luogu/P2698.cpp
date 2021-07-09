/***************************************************************
	File name: P2698.cpp
	Author: ljfcnyali
	Create time: 2019年07月30日 星期二 20时48分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

struct node1
{
    int x, y;
    bool operator < (const node1 &a) const { return x < a.x; }
} a[maxn];

struct node2
{
    int pos, val;
} p1, p2;

int n, m, ans;

inline bool check(int Mid)
{
    deque<node2> Q1, Q2;
    REP(i, 1, n)
    {
        while ( !Q1.empty() && Q1.front().pos < a[i].x - Mid ) Q1.pop_front();
        while ( !Q2.empty() && Q2.front().pos < a[i].x - Mid ) Q2.pop_front();
        while ( !Q1.empty() && Q1.back().val <= a[i].y ) Q1.pop_back();
        while ( !Q2.empty() && Q2.back().val >= a[i].y ) Q2.pop_back(); 
        p1.pos = a[i].x; p1.val = a[i].y;
        Q1.push_back(p1); Q2.push_back(p1);
        // if ( Mid == 2 ) cerr << Q1.front().val << " " << Q2.front().val << endl;
        if ( Q1.front().val - Q2.front().val >= m ) return true;
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); REP(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1);
    int L = 0, R = 1000000;
    ans = -1;
    while ( L <= R ) 
    {
        int Mid = (L + R) >> 1;
        if ( check(Mid) ) { ans = Mid; R = Mid - 1; }
        else L = Mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
