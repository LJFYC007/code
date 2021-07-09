#include <bits/stdc++.h>
#define F(i, l, r) for(int i = (l), _end_ = (int)(r); i <= _end_; ++i)
#define f(i, r, l) for(int i = (r), _end_ = (int)(l); i >= _end_; --i)
#define Set(a, v) memset(a, v, sizeof(a))
using namespace std;

bool chkmin(int &a, int b) {return b < a ? a = b, 1 : 0;}
bool chkmax(int &a, int b) {return b > a ? a = b, 1 : 0;}

inline int read() {
 int x = 0, fh = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar() ) if (ch == '-') fh = -1;
    for (; isdigit(ch); ch = getchar() ) x = (x<<1) + (x<<3) + (ch ^ '0');
    return x * fh;
}
inline int ran()
{
    return (rand())^rand();
}
int main () {
     freopen("winner5.in","w",stdout);
	 srand(19260817);
	 int n=1000,m=1000;
	 cout<<n<<" "<<m<<endl;
	 F(i,1,n)printf("%d ",ran());
	 cout<<endl;
	 F(i,1,m){
	   printf("%d %d\n",ran(),ran());
	 }
	 return 0;
}
