#include "cthreads.h"
//增加任务
void cthreads::push_task(cthread_task* task) {
	shared_ptr< cthread_task> T(task);
	_tasks.push(T);
}
//增加线程数：其实就是创建一个线程然后让其在后台执行run
void cthreads::add_thread() {
	atomic_bool* flag = new atomic_bool;
	_threads.push_back(flag);
	flag->store(true);
	std::thread(&cthreads::run_thread, this, flag).detach();//detch()表示将线程丢到后台去运行
}
//删除线程
void cthreads::del_thread() {
	atomic_bool* flag = _threads.back();
	flag->store(false);//将flag定义为false，在run中就会停止运行了
	_threads.pop_back();
}
//计算线程池的大小
size_t cthreads::count() const {
	return _threads.size();
}
//运行线程的函数（这个函数最重要）
void cthreads::run_thread(std::atomic_bool* thread_flag) {
	while (*thread_flag) {
		shared_ptr<cthread_task> task;
		bool ispop = _tasks.pop(task);
		if (ispop) {
			task->tasks();
		}
		else {
			this_thread::yield();//释放资源
		}
	}
	delete thread_flag;
}