#include <iostream>
#include <queue>
#include <mutex>
#include "cthreads.h"
//using namespace std;
class ctask :public cthread_task {
	void tasks() override {
		cout << "hello world" << k << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
private:
	int k = 1;
};

class ctask_t :public cthread_task {
public:
	void tasks() override {
		cout << "hello task" << k << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
public:
	ctask_t(int K){
		k = K;
	}
private:
	int k = 1;
};


int main() {
	cthreads thread;
	for (int i = 0; i < 50; i++) {
		if (i % 2) {
			thread.push_task(new ctask());
		}
		else {
			thread.push_task(new ctask_t(2));
		}
	}
	thread.add_thread();
	thread.add_thread();
	thread.add_thread();
	getchar();
	thread.del_thread();
	getchar();
	thread.del_thread();
	getchar();
	return 0;
}