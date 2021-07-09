#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
inline int rd(){
    char c=getchar();int x=0,flag=1;
    for(;c<'0'||c>'9';c=getchar())if(c=='-')flag=-1;
    for(;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
    return x*flag;
}
struct trie{
    int fail,fa,ch[26];ll val;
}t[2000010]={0};
int n,m,cnt=0;char s[2000010];queue<int>q;
ll f[2000010]={0},g[2000010]={0},h[2000010]={0};
inline void insert(int val){
    int len=strlen(s+1),now=0;
    for(int i=1;i<=len;i++){
        int c=s[i]-'a';
        if(!t[now].ch[c])
            t[t[now].ch[c]=++cnt].fa=now;
        now=t[now].ch[c];
    }
    t[now].val+=val;
    return;
}
inline void build(){
    for(int i=0;i<26;i++)
        if(t[0].ch[i]) q.push(t[0].ch[i]);
    for(;!q.empty();q.pop()){
        int u=q.front();
        t[u].val+=t[t[u].fail].val;
        g[u]=g[t[u].fa]+t[u].val;
        if(!t[u].fail) h[u]=h[t[u].fa];
        else{
            h[u]=-1e18;
            for(int i=t[u].fa;i^t[t[u].fail].fa;i=t[i].fail)
                h[u]=max(h[u],h[i]+t[t[u].fail].val);
        }
        g[u]=max(g[u],h[u]);
        f[u]=max(f[t[u].fail],g[u]);
        for(int i=0;i<26;i++){
            if(!t[u].ch[i]){
                t[u].ch[i]=t[t[u].fail].ch[i];
                continue;
            }
            t[t[u].ch[i]].fail=t[t[u].fail].ch[i];
            q.push(t[u].ch[i]);
        }
    }
    return;
}
inline ll solve(){
    ll res=0;int now=0;
    for(int i=1;i<=m;i++){
        int c=s[i]-'a';
        now=t[now].ch[c];
        res=max(res,f[now]);
    }
    return res;
}
int main(){
 freopen("C.in","r",stdin);
    freopen("C1.out", "w", stdout);
    for(;!q.empty();q.pop());
    n=rd();m=rd();
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        insert(rd());
    }
    scanf("%s",s+1);insert(0);build();
    printf("%lld\n",solve());
    return 0;
}
