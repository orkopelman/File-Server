#ifndef THREADS_POOL_HPP
#define THREADS_POOL_HPP

#include <thread>
#include <vector>
#include <memory>
#include <atomic>

#include "threads_pool_act.hpp"
#include "blocking_queue.hpp"

namespace threads {

class ThreadPool {
public:
    //using Task = std::function<void()>;
    ThreadPool(size_t a_numOfThreads);
    ThreadPool(ThreadPool const& a_other) = delete;
	ThreadPool& operator=(ThreadPool const&)  = delete;
    ~ThreadPool();

    template <typename FunctionObject>
    void AddTask(FunctionObject a_act);

    void AddTask(std::unique_ptr<AbstractAct> a_act);
    void AddTask(std::shared_ptr<AbstractAct> a_act);
    
    void internalAddTask(std::unique_ptr<AbstractAct> a_act); 
    void internalAddTask(std::shared_ptr<AbstractAct> a_act);

    void ShutDown();

private:
    void threadAct();
    BlockingQueue<std::shared_ptr<AbstractAct>> m_queue;
    std::vector<std::thread> m_threads;
    std::atomic<bool> m_terminate;
};

} //threads

#include "threads_pool.hxx"

#endif /* THREADS_POOL_HPP */