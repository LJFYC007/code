#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
    T x=0,f=0;char c=getchar();
    while(!isdigit(c)) f=c=='-',c=getchar();
    while(isdigit(c)) x=x*10+c-48,c=getchar();
    return f?-x:x;
}
namespace run{
    const int N=20009;
    const int inf=1e9;
    int n,w,k,a[N],b[N],f[5005],g[N][5005];
    int ans=inf,L[N],R[N],topL,topR;
    int main(){
        n=read<int>(),w=read<int>(),k=read<int>();
        for(int i=1;i<=n;i++)
            a[i]=read<int>(),b[i]=read<int>();
        for(int i=1;i<=w;i++)
            f[i]=g[0][i]=inf;
        f[0]=g[0][0]=0;

        for(int i=1;i<=n;i++){
            R[++topR]=i;
            for(int j=w;j>=a[i];j--)
                f[j]=min(f[j],f[j-a[i]]+b[i]);

            while(1){
                bool peg=0;
                for(int j=0;j<=w;j++)
                    if(f[j]+g[topL][w-j]<=k){
                        peg=1;break;
                    }

                if(peg==1){
                    ans=min(ans,static_cast<int>(topL+topR));
                    if(!topL){
                        for(int q=1,tmp=topR,pos;q<tmp;++q){
                            pos=R[tmp-q+1],topR--,L[++topL]=pos;
                            for(int j=w;j>=a[pos];j--)
                                g[q][j]=min(g[q-1][j-a[pos]]+b[pos],g[q-1][j]);
                            for(int j=a[pos]-1;j>=0;j--) g[q][j]=g[q-1][j];
                        }
                        topR--;
                        for(int j=1;j<=w;j++) f[j]=inf;
                        f[0]=0;
                    }else topL--;
                }else break;
            }
        }
        printf("%d\n",ans==inf?-1:ans);
        return 0;
    }
}
int main(){
    freopen("cactus.in","r",stdin);
    freopen("cactus.out","w",stdout);
    return run::main();
}
