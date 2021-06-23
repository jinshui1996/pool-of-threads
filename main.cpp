#include <iostream>
#include <queue>
#include <mutex>
#include "cthreads.h"
//using namespace std;
class ctask :public cthread_task {//任务的实例化一
	void tasks() override {
		cout << "hello ctask" << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
};

class ctask_t :public cthread_task {//任务的实例化二，里面加了参数
public:
	void tasks() override {
		cout << "hello tasks" << k << endl;
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