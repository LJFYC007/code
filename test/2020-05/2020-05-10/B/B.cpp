/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年05月10日 星期日 10时00分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int __int128
typedef long long LL;

const int maxn = 1e2 + 10;
const long double eps = 1e-10;

int ans;
LL n;
struct Vector 
{ 
    int x, y; 
    Vector(int a = 0, int b = 0) { x = a; y = b; }
} ;
Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Vector a, Vector b) { return Vector(a.x - b.x, a.y - b.y); }
struct node { int vx, vy; Vector x; } a[maxn], b[maxn];

inline int f(int x) { return x * x; }

inline void read(int &ret) {
    ret=0; int f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f;ch=getchar();}
    while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    ret = ret * f;
}

void wrtn(int x){
    if(x<0) {putchar('-');x=-x;}
    int y=10,len=1;
    while(y<=x) {y*=10;len++;}
    while(len--){y/=10;putchar(x/y+48);x%=y;}
}

inline int Solve(int lst, int j, int o, int t)
{
    if ( t <= 0 ) return 0;
    int ret = 1; bool flag = false;
    long double k = 0;
    if ( b[j].x.x + b[j].vx * t != 0 ) 
    {
        k = (b[j].x.y + b[j].vy * t) * 1.0 / (b[j].x.x + b[j].vx * t);
        flag = true;
    }
    if ( b[o].x.x + b[o].vx * t != 0 ) 
    {
        k = (b[o].x.y + b[o].vy * t) * 1.0 / (b[o].x.x + b[o].vx * t);
        flag = true;
    }
    REP(i, lst + 1, n)
    {
        long double X = (b[i].x.x + b[i].vx * t) * k;
        long double Y = (b[i].x.y + b[i].vy * t);
        // printf("%.12Lf %.12Lf\n", X, Y);
        // printf("%.12Lf %.12Lf\n", X, Y - eps);
        // printf("%.12Lf %.12Lf\n", X, Y + eps);
        // if ( X >= Y - eps ) cerr << "True1" << endl;
        // if ( X <= Y + eps ) cerr << "True2" << endl;
        if ( flag == true && X >= Y - eps && X <= Y + eps ) ++ ret;  
        else if ( flag == false && b[i].x.x + b[i].vx * t == 0 ) ++ ret;
    }
    return ret;
}

signed main()
{
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    while ( scanf("%lld", &n) != EOF )
    {
        if ( n == 0 ) return 0;
        REP(i, 1, n) read(a[i].x.x), read(a[i].x.y), read(a[i].vx), read(a[i].vy);
        /*
        REP(t, 1, 100)
        {
            printf("%lld %lld\n", (a[10].x.x + a[10].vx * t - a[1].x.x - a[1].vx * t), (a[10].x.y + a[10].vy * t - a[1].x.y - a[1].vy * t));
        }
        */
        ans = 2;
        if ( n == 1 ) ans = 1;
        REP(i, 1, n)
        {
            REP(j, i + 1, n) 
            {
                b[j].x = a[j].x - a[i].x;
                b[j].vx = a[j].vx - a[i].vx;
                b[j].vy = a[j].vy - a[i].vy;
            }
            REP(j, i + 1, n) REP(k, j + 1, n)
            {
                int t, x1 = b[j].x.x, x2 = b[k].x.x, y1 = b[j].x.y, y2 = b[k].x.y;
                int vx1 = b[j].vx, vx2 = b[k].vx, vy1 = b[j].vy, vy2 = b[k].vy;
                int A = 2 * (-vx2 * vy1 + vx1 * vy2);
                int B = -vy2 * x1 + vy1 * x2 + vx2 * y1 - vx1 * y2;
                int Delta = f(vy2 * x1 - vy1 * x2 - vx2 * y1 + vx1 * y2) - 4 * (-vx2 * vy1 + vx1 * vy2) * (-x2 * y1 + x1 * y2);
                if ( A == 0 && B == 0 && Delta == 0 ) ans = max(ans, Solve(i, j, k, 1));
                if ( Delta < 0 ) continue ;
                int x = sqrt(Delta);
                if ( x * x != Delta ) continue ;
                Delta = x;
                if ( A == 0 ) { ans = max(ans, Solve(i, j, k, B + Delta)); continue ; }
                t = (B + Delta) / A;
                if ( A * t == (B + Delta) && t > 0 ) ans = max(ans, Solve(i, j, k, t));
                t = (B - Delta) / A;
                if ( A * t == (B - Delta) && t > 0 ) ans = max(ans, Solve(i, j, k, t));
            }
        }
        wrtn(ans);
        puts("");
    }
    return 0;
}
