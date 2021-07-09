$$
\begin{align}
f(d)=&\sum_{i=1}^m|i-d|\times w_i-S\times d\\
=&\sum_{i=1}^d(d-i)\times w_i+\sum_{i=d+1}^m(i-d)\times w_i-S\times d\\
=&d\times (\sum_{i=1}^dw_i-\sum_{i=d+1}^mw_i)-S\times d+\sum_{i=d+1}^mi\times w_i-\sum_{i=1}^d i\times w_i
\end{align}
$$

设 $g_i=\sum_{j=1}^i j\times w_j,t_i=\sum_{j=1}^iw_j$ 那么有
$$
f(d)=d\times (2\times t_{\lfloor d\rfloor}-S)-S\times d+g_m-2\times g_{\lfloor d\rfloor}=0\\
d\times (2\times t_{\lfloor d\rfloor}-2\times S)=2\times g_{\lfloor d\rfloor}-g_m\\
d=\dfrac{2\times g_{\lfloor d\rfloor}-g_m}{2\times(t_{\lfloor d\rfloor}-S)}
$$
所以首先二分 $\lfloor d\rfloor$ ，每次 $Check$ 在原式中的是否小于0

找到最后的 $\lfloor d\rfloor$ 后通过结尾的式子计算 $d$ 即可

