#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 20;
const int maxh = 110;

int N, HM, HR, HC, HX, HY, M; // Like face

bool ICE_BLOCK[maxn][maxn][maxh]; // ICE_BLOCK
int ICE_CUBE[maxn][maxn]; // -1 : x 
int ICE_BLOCK_SUM;
int dt[8][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
int dr[6][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {-1, 0, 0}, {0, -1, 0}, {0, 0, -1}};
int Flag, MAX_HIGH;
bool Fuck1 = true, Fuck2 = true, Fuck3 = true;

char s[maxh];

inline void SOLVE_BY_1()
{
    int R, C, D, S;
    scanf("%d%d%d%d", &R, &C, &D, &S);
    int sum = 0;
    while ( R >= 0 && C >= 0 && R < N && C < N && S >= 0 )
    {
        -- S;
        if ( ICE_CUBE[R][C] >= 4 ) goto OK1 ;
        if ( ICE_BLOCK[R][C][0] == true ) goto OK2 ;
        ++ sum; ++ ICE_CUBE[R][C];
OK1 :;
        R += dt[D][0]; C += dt[D][1];
    }
OK2 :;
    printf("CIRNO FREEZED %d BLOCK(S)\n", sum);
}

inline void SOLVE_BY_2()
{
    int NEW_MADE = 0;
    REP(i, 0, N - 1)
        REP(j, 0, N - 1)
        {
            if ( ICE_CUBE[i][j] == 4 || ICE_CUBE[i][j] == 9 ) 
            {
                ICE_CUBE[i][j] -= 4; ++ NEW_MADE;
            }
        }
    ICE_BLOCK_SUM += NEW_MADE;
    printf("CIRNO MADE %d ICE BLOCK(S),NOW SHE HAS %d ICE BLOCK(S)\n", NEW_MADE, ICE_BLOCK_SUM);
}

inline void SOLVE_BY_3()
{
    int R, C, H;
    scanf("%d%d%d", &R, &C, &H);
    if ( ICE_BLOCK_SUM == 0 )
    {
        printf("CIRNO HAS NO ICE_BLOCK\n");
        return ;
    }
    if ( ICE_BLOCK[R][C][H] == true )
    {
        printf("BAKA CIRNO,CAN'T PUT HERE\n");
        return ;
    }
    bool flag = false;
    REP(i, 0, 5)
    {
        int r = R + dr[i][0], c = C + dr[i][1], h = H + dr[i][2];
        if ( r < 0 || c < 0 || h < 0 || r >= N || c >= N ) continue ;
        if ( ICE_BLOCK[r][c][h] == true ) { flag = true; goto yes ; }
    } 
yes: ;
    if ( flag == false && H > 0 ) 
    {
        printf("BAKA CIRNO,CAN'T PUT HERE\n");
        return ;
    }
    ICE_BLOCK[R][C][H] = true; -- ICE_BLOCK_SUM;
    if ( R < HR || R > HR + HX - 1 || C < HC || C > HC + HY - 1 ) 
    {
        printf("CIRNO MISSED THE PLACE\n");
        return ;
    }
    if ( HR + 1 <= R && R <= HR + HX - 2 && HC + 1 <= C && C <= HC + HY - 2 )
    {
        printf("CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE\n");
        return ;
    }
    printf("CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS %d ICE_BLOCK(S)\n", ICE_BLOCK_SUM);
}

inline bool PD_ICE(int R, int C, int H)
{
    if ( H == 0 ) return true;
    REP(i, 0, 5)
    {
        int r = R + dr[i][0], c = C + dr[i][1], h = H + dr[i][2];
        if ( r < 0 || c < 0 || h < 0 || r >= N || c >= N ) continue ;
        if ( ICE_BLOCK[r][c][h] == true ) return true;
    } 
    return false;
}

inline void DFS(int R, int C, int H)
{
    REP(i, 0, 5)
    {
        int r = R + dr[i][0], c = C + dr[i][1], h = H + dr[i][2];
        if ( r < 0 || c < 0 || h < 0 || r >= N || c >= N ) continue ;
        if ( ICE_BLOCK[r][c][h] == false ) continue ;
        if ( PD_ICE(r, c, h) == false ) 
        {
            ++ Flag;
            ICE_BLOCK[r][c][h] = false;
            DFS(r, c, h);
        }
    }
}

inline void SOLVE_BY_4()
{
    int R, C, H; scanf("%d%d%d", &R, &C, &H);
    if ( ICE_BLOCK[R][C][H] == false ) 
    {
        printf("BAKA CIRNO,THERE IS NO ICE_BLOCK\n");
        return ;
    }
    ++ ICE_BLOCK_SUM;
    ICE_BLOCK[R][C][H] = false;
    Flag = 0;
    DFS(R, C, H);
    if ( Flag )
    {
        printf("CIRNO REMOVED AN ICE_BLOCK,AND %d BLOCK(S) ARE BROKEN\n", Flag);
        return ;
    }
    printf("CIRNO REMOVED AN ICE_BLOCK\n");
}

inline void DELETE_ICE_BLOCK()
{
    int sum_k1 = 0, sum_k2 = 0;
    REP(i, HR + 1, HR + HX - 2)
    {
        REP(j, HC + 1, HC + HY - 2)
        {
            REP(k, 0, MAX_HIGH - 1)
            {
                if ( ICE_BLOCK[i][j][k] == true ) 
                {
                    ICE_BLOCK[i][j][k] = false;
                    ++ ICE_BLOCK_SUM;
                    ++ sum_k1;
                }
            }
        }
    }
    REP(i, 0, N - 1)
        REP(j, 0, N - 1)
            REP(k, 0, HM)
            {
                if ( ICE_BLOCK[i][j][k] == false ) continue ;
                if ( i < HR || i > HR + HX - 1 || j < HC || j > HC + HY - 1 || k > MAX_HIGH )
                {
                    ICE_BLOCK[i][j][k] = false;
                    ++ sum_k2;
                    ++ ICE_BLOCK_SUM;
                }
            }
    printf("%d ICE_BLOCK(S) INSIDE THE HOSUE NEED TO BE REMOVED\n", sum_k1);
    printf("%d ICE_BLOCK(S) OUTSIDE THE HOSUE NEED TO BE REMOVED\n", sum_k2);
    Flag = 0;
    REP(i, 0, N - 1)
    {
        REP(j, 0, N - 1)
        {
            REP(k, 0, HM)
            {
                if ( ICE_BLOCK[i][j][k] == false ) continue ;
                if ( PD_ICE(i, j, k) == true ) continue ;
                ICE_BLOCK[i][j][k] = false; ++ Flag;
                DFS(i, j, k);
            }
        }
    }
    bool flag = false;
    REP(i, HR, HR + HX - 1)
        REP(j, HC, HC + HY - 1)
            if ( PD_ICE(i, j, MAX_HIGH) == true ) { flag = true; goto over; }
    printf("SORRY CIRNO,HOUSE IS BROKEN WHEN REMOVING BLOCKS\n");
    exit(0);
    return ;
over: ;
    ICE_BLOCK_SUM += Flag;
}

inline void FIX_ICE_BLOCK()
{

}

inline void SOLVE_BY_5()
{
    MAX_HIGH = 0;
    REP(i, 0, N - 1)
        REP(j, 0, N - 1)
            REP(k, 0, HM - 1)
            {
                if ( ICE_BLOCK[i][j][k] == false ) continue ;
                if ( i == HR && HC <= j && j <= HC + HY - 1 ) 
                    MAX_HIGH = max(MAX_HIGH, k);
                if ( j == HC && HR <= i && i <= HR + HX - 1 )
                    MAX_HIGH = max(MAX_HIGH, k);
                if ( i == HR + HX - 1 && HC <= j && j <= HC + HY - 1)
                    MAX_HIGH = max(MAX_HIGH, k);
                if ( j == HC + HY - 1 && HR <= i && i <= HR + HX - 1)
                    MAX_HIGH = max(MAX_HIGH, k);
                // printf("%d %d %d\n", i, j, k);
            } 
    ++ MAX_HIGH;
    int sum = 0;
    REP(i, HR, HR + HX - 1)
        REP(j, HC, HC + HY - 1)
            if ( ICE_BLOCK[i][j][MAX_HIGH] == false )
            {
                ICE_BLOCK[i][j][MAX_HIGH] = true;
                ++ sum;
            }
    if ( sum > ICE_BLOCK_SUM ) { printf("SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO MAKE ROOF\n"); return ; }
    ICE_BLOCK_SUM -= sum;
    int Acreage = (HX - 2) * (HY - 2) * (MAX_HIGH - 1);
    if ( Acreage < 2 || MAX_HIGH < 2 ) 
    {
        printf("SORRY CIRNO,HOUSE IS TOO SMALL\n");
        return ;
    } 
    DELETE_ICE_BLOCK();
    FIX_ICE_BLOCK();
    printf("GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE\n");
    if ( Fuck1 == true ) printf("DOOR IS OK\n");
    else printf("HOUSE HAS NO DOOR\n");
    if ( Fuck2 == true ) printf("WALL IS OK\n");
    else printf("WALL NEED TO BE FIXED\n");
    if ( Fuck3 == true ) printf("CORNER IS OK\n");
    else printf("CORNER NEED TO BE FIXED\n");
    printf("CIRNO FINALLY HAS %d ICE_BLOCK(S)\n", ICE_BLOCK_SUM);
    printf("CIRNO IS PERFECT\n");
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &N, &HM);
    scanf("%d%d%d%d", &HR, &HC, &HX, &HY);
    scanf("%d", &M);
    while ( M -- ) 
    {
        scanf("%s", s);
        if ( s[0] == 'I' ) SOLVE_BY_1();
        else if ( s[0] == 'M' && s[5] == 'I' ) SOLVE_BY_2();
        else if ( s[0] == 'P' ) SOLVE_BY_3();
        else if ( s[0] == 'R' ) SOLVE_BY_4();
        else SOLVE_BY_5();
    }
    return 0;
}
