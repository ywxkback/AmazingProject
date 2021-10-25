# C++ 面试题

收录 C++ 面试题。

PS：不保证回答正确。

## 一个程序在内存中的布局是怎样的？

1. 文本段（Text Segment）

    也被称为代码段（Code segment），包含了可执行指令。

2. 数据段（Data Segment）

    数据段分为两部分：

    **已初始化的数据段（Initialized Data Segment）**

    包含了已经初始化的全局和静态变量

    **未初始化的数据段（Uninitialized Data Segment）**

    这个通常也叫做 BSS 段（BSS Segment）。

    程序执行之前，在这个段的数据通常被内核初始化为 0。

    BSS 段 一般在已初始化的数据段之后

3. 栈（Stack）

    临时变量存储在这个区域。

4. 堆（Heap）

    动态内存分配

最后附上图片

![img](./img/memoryLayoutC.jpg)
