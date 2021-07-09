/***************************************************************
        File name: F.cpp
        Author: ljfcnyali
        Create time: 2019年05月12日 星期日 09时53分13秒
***************************************************************/
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i <= _end_; ++i)
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)

const int maxn = 1000010;

char s1[maxn], s2[maxn];
int Next[maxn], a[maxn], last[maxn], n, m, fail[maxn];

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s1);
    scanf("%s", s2);
    n = str(s1);
    m = str(s2);
    int j = 0;
    REP(i, 1, m - 1) {
        while (j && s2[i] != s2[j]) j = Next[j];
        Next[i + 1] = s2[i] == s2[j] ? ++j : 0;
    }
    REP(i, 0, n - 1) a[i] = i + 1;
    REP(i, 1, n) last[i] = i - 1;
    j = 0;
    for (int i = 0; i <= n - 1; i = a[i]) {
        while (j && s1[i] != s2[j]) j = Next[j];
        if (s1[i] == s2[j])
            ++j;
        fail[i] = j;
        //		printf("%d %d\n", i, j);
        if (j == m) {
            int now = i;
            while (j) {
                i = last[i];
                --j;
            }
            a[i] = now + 1;
            last[now] = i - 1;
            j = fail[i];
        }
    }
    //	REP(i, 0, n) printf("%d ", a[i]); puts("");
    //	REP(i, 0, n) printf("%d ", last[i]); puts("");
    for (int i = 0; i <= n - 1; i = a[i]) printf("%c", s1[i]);
    puts("");
    return 0;
}
