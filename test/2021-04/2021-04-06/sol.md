### s

可以发现，最优方案下，一定是给每个点分配一个权值$c_i$，对于一条边，有$w_i=\dfrac{c_{s_i}-c_{t_i}}{v_i}$。
加入边时，需要检查是否有关于$c$的等式冲突，且$c_1>c_i>c_n,i\in(1,n)$，特别的，需要不存在$c_1-c_n\le c_u-c_v,u,v\in(1,n)$的情况。
用并查集简单维护即可。
PS: 可以发现，$c,v,w,vw^2$分别和电压，电阻，电流，功率等效。

### l
令$g=\gcd((n+a)^3+b,n^3+b)$，则：
$$
\begin{align}
g=&\gcd(3n^2a+3na^2+a^3,n^3+b)\\
\le&\gcd(3n^2a+3na^2+a^3,3n^3a+3ab)\\
=&a\gcd(3n^2+3na+a^2,-3n^2a-na^2+3b)\\
=&a\gcd(3n^2+3na+a^2,2na^2+a^3+3b)\\
\le&a\gcd(6n^2a^2+6na^3+a^4,2na^2+a^3+3b)\\
=&a\gcd(3n(a^3-3b)+a^4,2na^2+a^3+3b)\\
\le&a\gcd(6n(a^3-3b)a^2+2a^6,2na^2+a^3+3b)\\
=&a\gcd(2a^6-3(a^3-3b)(a^3+3b),2na^2+a^3+3b)\le|a(2a^6-3(a^3-3b)(a^3+3b))|=|-a^7-27ab^2|\\
\end{align}
$$

其中每个$\le$都包含前者是后者的因子的意思。~~相信大家知道数据范围为什么这么奇怪了~~<img src="01.png" style="zoom: 40%"></img>

枚举它的因子即可，然后是检验：
$$
\cases{n^3+b\bmod g=0\\(n+a)^3+b\bmod g=0}
$$
可得$3an^2+3a^2n+a^3\bmod g=0$，令$p=\dfrac{g}{\gcd(g,a)}$，则$3n^2+3an+a^2\bmod p=0$，令$t=3^{-1}a^2\bmod p$，则$n^2+an+t\bmod p=0$，$n^2+an+(t+kp)\bmod g=0,k<\gcd(g,a)\le a$，令$t_0=t+kp$。

则：
$$
\begin{align}
0=&n^3+b-n(n^2+an+t_0)\bmod g\\
=&-an^2-t_0n+b\bmod g\\
=&-an^2-t_0n+b+a(n^2+an+t_0)\bmod g\\
=&(a^2-t_0)n+(at_0+b)\bmod g
\end{align}
$$
枚举$k$，然后求逆，可得：
$$
n=n_0+qn_1,n_1=\dfrac{g}{\gcd(a^2-t_0,g)}
$$
在此基础上，需要满足$n^2+an+t_0=0$，因为$q$的取值范围是两个几乎没有关系的数（甚至可以认为$a^2-t_0\bmod g$是$[0,g)$内的随机数）的$\gcd$，可以认为它很小，事实上，可以在0.05s内（std处理用时最大的询问用了25ms）跑出对于任意$a\le 18,b\le 2000$的询问的答案。

### p
当$m=1$时，每一次一定是向施肥次数最少的树施肥，$m\not=1$时，可以当成$m$次$m=1$的情况操作。
求期望可以转化为对概率的求和，现在只要求下式即可（最后除以$n$即可，$a/b$表示$\lfloor\frac ab\rfloor$）：
$$
\sum_{p=1}^n\sum_{i\ge 0}0.5^{mi/n+[mi\bmod n\ge p]}
$$
其中$mi/n+[mi\bmod n\ge p]=(mi+n-p)/n$，交换求和项，得：
$$
\sum_{i\ge 0}\sum_{p=1}^n0.5^{(mi+n-p)/n}=\sum_{i\ge 0}\sum_{j=0}^{n-1}0.5^{(mi+j)/n}=\sum_{i\ge 0}0.5^{mi/n}(n+(mi\bmod n)(0.5-1))
$$
现在变成了两个问题：
$$
\sum_{i\ge 0}0.5^{mi/n};\sum_{i\ge 0}0.5^{mi/n}(mi\bmod n)
$$
后式可以变为$\sum_{i\ge 0}0.5^{mi/n}(mi-n(mi/n))$，也就是相当于求：
$$
\sum_{i\ge 0}0.5^{mi/n};\sum_{i\ge 0}0.5^{mi/n}i;\sum_{i\ge 0}0.5^{mi/n}(mi/n)
$$
用类欧几里得算法可以\sout{简单}解决，下面简述一下类欧几里得算法：

考虑一个$m\times n$的网格，从$(0,0)$向$(m,n)$的射线，连线下方的点可以视为$mi/n$。

考虑在这条线下方尽可能向上走（能上就上，不行就右），可以得到一个UR序列，如$n=3,m=2$就是RURUU的循环。

可以发现，若$(n,m)\rightarrow (m,n)$，就是序列逆序后$(R,U)\rightarrow(U,R)$（容易发现，去掉开头结尾的RU，这是一个回文串（不妨考虑从$n-1,m$走到$0,0$的路径，或者归纳证明一下），所以除开头结尾交换RU即可），若$(n,m)\rightarrow(n+km,m)$，就是$(R,U)\rightarrow(RU^k,U)$。

类似DP去求解即可。

