#include <iostream>
#include <thread>
#include "thread_safe_queue.h"

const int number_of_operation = 100000;

template<typename queue_type, typename T>
void get(queue_type &q) {
  for (int i = 0; i < number_of_operation; i++) {
    if (!q.empty()) {
      q.pop();
    }
  }
}

template<typename queue_type, typename T>
void release(queue_type &q) {
  for (int i = 0; i < number_of_operation; i++) {
    q.push(T());
  }
}

// 线程不安全，会报错
void unsafe_queue_unit_test() {
  std::cout << "[INFO] Start unsafe queue unit test" << std::endl;
  std::queue<int> unsafe_queue;
  std::thread t1(get<std::queue<int>, int>, std::ref(unsafe_queue));
  std::thread t2(release<std::queue<int>, int>, std::ref(unsafe_queue));
  t1.join();
  t2.join();
  std::cout << "[INFO] Final queue size = " << unsafe_queue.size() << std::endl;
  std::cout << "[INFO] End unsafe queue unit test" << std::endl;
}

// 注意到，虽然队列的大小并非零，但是他是线程安全的。
// 因为我们在get函数中，还需要检查队列是否为空，
// 所以它不一定能够pop，因此最终也不一定是空队列。
void safe_queue_unit_test() {
  std::cout << "[INFO] Start unsafe queue unit test" << std::endl;
  thread_safe_queue<int> safe_queue;
  std::thread t2(release<thread_safe_queue<int>, int>, std::ref(safe_queue));
  std::thread t1(get<thread_safe_queue<int>, int>, std::ref(safe_queue));
  t1.join();
  t2.join();
  std::cout << "[INFO] Final queue size = " << safe_queue.size() << std::endl;
  std::cout << "[INFO] End unsafe queue unit test" << std::endl;
}

int main() {
  safe_queue_unit_test();
  unsafe_queue_unit_test();
  return 0;
}