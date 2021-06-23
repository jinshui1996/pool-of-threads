#pragma once
#include <iostream>
#include <queue>
#include <mutex>
using namespace std;
//用来重新定义vector，使其可以并发；
template<typename type>//模板的定义
class csafe_vector
{
public:
	using creferenced = type&;
	//这里是写函数的模板类，里面可以加参数
	template<typename... Args>
	void push(Args &&... args) {
		lock_guard<mutex> lock(_mutex);
		_safe_vector.push_back(args...);
	}
	//
	bool pop(creferenced value) {
		lock_guard<mutex> lock(_mutex);
		if (_safe_vector.empty())return false;
		value = _safe_vector.back();
		_safe_vector.pop_back();
		return true;
	}

private:
	vector<type> _safe_vector;
	mutex _mutex;//用来实现vector的互斥访问
};

