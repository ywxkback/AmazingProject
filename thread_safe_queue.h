#ifndef _THREAD_SAFE_QUEUE_
#define _THREAD_SAFE_QUEUE_

#include <mutex>
#include <queue>

template <typename T>
class thread_safe_queue {
 public:
  thread_safe_queue();

  void push(const T& value);

  void push(T&& value);

  void pop();

  T& front();

  size_t size();

  bool empty();

 private:
  std::queue<T> _self;
  std::mutex _m;
};

template <typename T>
thread_safe_queue<T>::thread_safe_queue() {}

template <typename T>
void thread_safe_queue<T>::push(const T& value) {
  std::lock_guard<std::mutex> lck(_m);
  _self.push(value);
}

template <typename T>
void thread_safe_queue<T>::push(T&& value) {
  std::lock_guard<std::mutex> lck(_m);
  _self.push(value);
}

template <typename T>
void thread_safe_queue<T>::pop() {
  std::lock_guard<std::mutex> lck(_m);
  _self.pop();
}

template <typename T>
T& thread_safe_queue<T>::front() {
  std::lock_guard<std::mutex> lck(_m);
  return _self.front();
}

template <typename T>
size_t thread_safe_queue<T>::size() {
  std::lock_guard<std::mutex> lck(_m);
  return _self.size();
}

template <typename T>
bool thread_safe_queue<T>::empty() {
  std::lock_guard<std::mutex> lck(_m);
  return _self.empty();
}

#endif