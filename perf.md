### [CPU Flame Graphs](https://www.brendangregg.com/FlameGraphs/cpuflamegraphs.html#C++)

---

```
# git clone https://github.com/brendangregg/FlameGraph  # or download it from github
# cd FlameGraph
# perf record -F 99 -a -g -- sleep 60
# perf script | ./stackcollapse-perf.pl > out.perf-folded
# ./flamegraph.pl out.perf-folded > perf.svg
# firefox perf.svg  # or chrome, etc.
```





### [reference](https://www.ruanyifeng.com/blog/2017/09/flame-graph.html)

---

```
$ sudo perf record -F 99 -p 13204 -g -- sleep 30
```

* **y 轴表示调用栈**，每一层都是一个函数。调用栈越深，火焰就越高，**顶部就是正在执行的函数**，下方都是它的父函数。

* **x 轴表示抽样数**，**如果一个函数在 x 轴占据的宽度越宽，就表示它被抽到的次数多，即执行的时间长**。注意，x 轴不代表时间，而是所有的调用栈合并后，按字母顺序排列的。





### [深入理解perf报告中的swapper进程](https://www.jianshu.com/p/c41cac2826ea)

---

* 当CPU上没有其他任务运行时，就会执行swapper。换句话说swapper意味着CPU啥事也没干，跑去休息去了





### 其他

---

top 和 htop 可以查看进程的CPU利用率

[官方](https://www.brendangregg.com/flamegraphs.html)

[用CPI火焰图分析Linux性能问题](https://cloud.tencent.com/developer/article/1517979)

