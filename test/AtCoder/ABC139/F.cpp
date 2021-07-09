#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200010;
int n;
ll ans;
struct node
{
    int x,y;
    double a;
}p[maxn<<1];
ll sx[maxn<<1],sy[maxn<<1];
bool cmp(const node &a,const node &b)
{
    return a.a<b.a;
}
inline void check(int l,int r)
{
    if(l<=r) ans=max(ans,(sx[r]-sx[l-1])*(sx[r]-sx[l-1])+(sy[r]-sy[l-1])*(sy[r]-sy[l-1]));
}
int main()
{
    scanf("%d", &n);
    int i,j;
    for(i=1;i<=n;i++)    scanf("%d%d", &p[i].x, &p[i].y), p[i].a=atan2(p[i].x,p[i].y),p[i+n]=p[i],p[i+n].a+=2*pi;
    sort(p+1,p+2*n+1,cmp);
    for(i=1;i<=2*n;i++)  sx[i]=sx[i-1]+p[i].x,sy[i]=sy[i-1]+p[i].y;
    for(i=j=1;i<=2*n;i++)
    {
        for(;j<i&&p[j].a<=p[i].a-pi;j++,check(j,i-1));
        check(j,i);
    }
    for(;j<=2*n;check(j,2*n),j++);
    printf("%.11lf\n",sqrt((double)ans));
    return 0;
}
