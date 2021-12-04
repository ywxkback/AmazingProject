#ifndef _SPSC_QUEUE_H_
#define _SPSC_QUEUE_H_

#include <atomic>
#include <cassert>
#include <cstdlib>
#include <iostream>

namespace ywxk {

/**
 * @brief 单生产者单消费无锁队列（Single producer single consumer）
 *        通过内存屏障的技术在并发环境下实现无锁
 **/
template <typename T>
class SPSCQueue {
 public:
  /**
   * @brief 创建一个SPSC，最多可以放 size 个元素
   *        实现中，为了区分“队列满”和“队列空”两种状态，
   *        我们需要申请 size + 1 大小的数组
   * @param size 循环队列的大小
   **/
  SPSCQueue(unsigned int size);

  /**
   * @brief 析构函数，释放申请的资源并重置指针指向和数组大小。
   **/
  ~SPSCQueue();

  /**
   * @brief 禁止复制
   * @param rhs 被复制的对象
   **/
  SPSCQueue(const SPSCQueue& rhs) = delete;

  /**
   * @brief 禁止赋值运算符
   * @param rhs 被复制的对象
   **/
  SPSCQueue operator=(const SPSCQueue& rhs) = delete;

  /**
   * @brief 入队函数，将 value 入队
   *        根据内存屏障技术，先入队，再修改指针 in_。
   * @param value 入队的元素
   * @return 如果返回 true 则入队成功；反之入队失败。
   **/
  bool Enqueue(const T& value);

  /**
   * @brief 出对函数，弹出一个元素
   *        如果队列为空，程序直接终止
   * @return 返回队首元素
   **/
  T Dequeue();

  /**
   * @brief 判断队列是否为空
   * @return 如果队列为空，返回 true；反之返回 false
   **/
  bool Empty();

  /**
   * @brief 判断队列是否满
   * @return 如果队列已满，返回 true；反之返回 false\
   **/
  bool Full();

  /**
   * @brief 返回队列中元素的个数
   * @return 队列大小
   **/
  unsigned int Size();

 private:
  /// 数组大小
  unsigned int size_;

  /// 数组
  T* arr_;

  /// 入队指针，指向可插入位置的下标
  std::atomic<unsigned int> in_;

  /// 出队指针，指向队列首元素（如果队列不是空）
  std::atomic<unsigned int> out_;
};

template <typename T>
SPSCQueue<T>::SPSCQueue(unsigned int size) : size_(size + 1), in_(0), out_(0) {
  arr_ = new T[size_];
  if (arr_ == nullptr) {
    std::cerr << "[SPSCQueue::SPSCQueue] No enough memory to use, BUY RAM!\n";
    std::abort();
  }
}

template <typename T>
SPSCQueue<T>::~SPSCQueue() {
  delete arr_;
  size_ = in_ = out_ = 0;
  arr_ = nullptr;
}

template <typename T>
bool SPSCQueue<T>::Enqueue(const T& value) {
  if (Full()) {
    std::cerr << "[SPSCQueue::Enqueue] SPSCQueue is full when you enqueue an "
                 "element.\n";
    return false;
  }
  unsigned int in = in_.load(std::memory_order_relaxed);
  assert(in < size_);
  arr_[in_] = value;
  in_.store((in + 1) % size_, std::memory_order_release);
  return true;
}

template <typename T>
T SPSCQueue<T>::Dequeue() {
  if (Empty()) {
    std::cerr << "[SPSCQueue::Dequeue] SPSCQueue is Empty when you dequeue "
                 "from it.\n";
    std::abort();
  }
  unsigned int out = out_.load(std::memory_order_relaxed);
  assert(out < size_);
  T ret = arr_[out];
  out_.store((out + 1) % size_, std::memory_order_release);
  return ret;
}

template <typename T>
bool SPSCQueue<T>::Empty() {
  return in_.load(std::memory_order_relaxed) ==
         out_.load(std::memory_order_relaxed);
}

template <typename T>
bool SPSCQueue<T>::Full() {
  unsigned int in = in_.load(std::memory_order_relaxed);
  unsigned int out = out_.load(std::memory_order_relaxed);
  return (in + 1) % size_ == out;
}

template <typename T>
unsigned int SPSCQueue<T>::Size() {
  unsigned int in = in_.load(std::memory_order_relaxed);
  unsigned int out = out_.load(std::memory_order_relaxed);
  return (in + size_ - out) % size_;
}

}  // namespace ywxk
#endif
