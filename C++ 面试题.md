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


## new operator、operator new 和 placement new

**区别：**

**(1) operator new**

* operator new 是一个函数

* 只分配空间，不调用构造函数

* 当无法满足所分配的空间时：

    * 如果有 `new_handler` 则调用 `new_handler`；
    * 否则如果能抛出异常，则抛出 `bad_alloc`；
    * 否则返回 `NULL`

* 可以重载，重载格式如下：

    * 返回类型是 `void*`
    * 第一个形参为表达要求分配空间的大小
    * 其他形参自定义

    > 通过重载，就可以利用自己写的内存管理库

* 在头文件 `<new>` 中定义了一个全局 operator new，用来分配空间，通过

    ```c++
    ::operator new
    ```

    方式调用

**(2) placement new**

* placement new 是一个函数

* 本质是 operator new 的重载

    ```c++
    void * operator new(size_t, void* __p) { return __p }
    ```

* 作用是在已分配的空间上构造对象

* 优点：允许在缓冲区上创建对象，不必动态分配内存空间

**(3) new operator**

* new operator 是一个关键字，操作符
* 分配空间，调用构造函数。

**使用 new 关键字创建一个对象会发生什么？**

1. 调用全局 operator new 分配空间（也可以使用自定义的 operator new）
2. 在该空间上调用构造函数构造一个对象
