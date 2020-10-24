#pragma once
#include <memory>
#include <atomic>
#include <thread>
#include "csafe_vector.h"
#include "cthread_task.h"

class cthreads //:public cthread_task
{
public:
	void push_task(cthread_task *task);
	void add_thread();
	void del_thread();
	size_t count() const;

private:
	void run_thread(std::atomic_bool* thread_flag);

private:
	csafe_vector<std::shared_ptr<cthread_task>> _tasks;//存放任务
	vector<std::atomic_bool*> _threads;//记录并且管理线程
};

