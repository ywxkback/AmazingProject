/**
 *  Compile: g++ spsc_queue_test.cc -o test.exe -g -Wall -lpthread
 **/
#include "spsc_queue.h"

#include <iostream>
#include <thread>

using namespace ywxk;
using namespace std;
SPSCQueue<int> q(1000);

void prod() {
  for (int i = 0; i < 1000000; i++) {
    if (!q.Full()) {
      q.Enqueue(i);
      cout << "Productor product " << i << "\n";
    }
  }
}

void cons() {
  for (int i = 0; i < 1000000; i++) {
    if (!q.Empty()) {
      int front = q.Dequeue();
      cout << "Consumer use " << front << "\n";
    }
  }
}

int main() {
  thread th1(prod);
  thread th2(cons);
  // thread th3(cons);
  th1.join();
  th2.join();
  // th3.join();
  cout << "Current Size: " << q.Size() << "\n";
  return 0;
}