# pool-of-threads
一个简单实现的线程池

cthread_task:定义了一个任务接口，所有的任务都需要继承这个接口

csafe_vector:定义了一个push/pop安全的vector，便于存储任务

cthreads:定义了线程池的创建和管理的方法，基于上面定义的两个类

main:定义了主函数和任务类的实现
