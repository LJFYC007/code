$f_i$表示钦定$y$之后$x=i$的答案

$x$表示钦定阈值后距离$y$大于阈值的点的个数

$sum1$表示小于阈值的点的距离和，$sum2$表示距离$y$大于阈值的点的答案(都是一样的)

因为距离$y$小于阈值的点的$f_i$都表示$dis_i$，所以我们就不用考虑这些点了

可以假设后面出现的$f_i$都满足$dis>$阈值(意思就是小于等于阈值的$i$我们不考虑)

$Mid$是我们分数规划出来的答案

我们设 $val$ 是我们枚举的阈值，最后发现 $Mid=val$
$$
sum=\frac{1}{n}\sum_{i=1}^nf_i=\frac{1}{n}\times(sum_1+x\times sum_2)\\
f_i=1+\frac{x}{n}f_i+\frac{sum_1}{n}\\
\frac{n-x}{n}f_i=1+\frac{sum_1}{n}\\
f_i=\frac{n+sum_1}{n-x}<Mid\\
n+sum_1<n\times Mid -x\times Mid\\
x\times Mid+sum_1-n\times(Mid-1)<0\\
min(\sum_{dis_i\geq val}1\times Mid+\sum_{dis_i<val}dis_i)
$$

