#ifndef THREADS_POOL_HXX
#define THREADS_POOL_HXX

#include "threads_pool.hpp"

namespace threads {

class PoisonAppleException : public std::runtime_error {
public:
    PoisonAppleException() : std::runtime_error("end thread") {};
};

class TerminatorTask : public AbstractAct {
    void Act() override { throw PoisonAppleException{}; }
};

inline void ThreadPool::threadAct()
{
    while (true) {
        std::shared_ptr <AbstractAct> ptrAct;        
        m_queue.Dequeue(ptrAct);

        try {
            ptrAct->Act();
            
        } catch(PoisonAppleException const& e){
            
            break; 
        }catch(...){
            
            std::cerr << "excedption was thrown" << std::endl;
            continue;
        }
    }
} 

inline ThreadPool::ThreadPool(size_t a_numOfThreads)
: m_queue()
, m_threads()
, m_terminate(false)
{
    if(a_numOfThreads == 0) {
        throw std::invalid_argument("Number of threads cannot be 0");
    }

    for(size_t i = 0; i < a_numOfThreads; ++i) {
        m_threads.push_back(std::thread{&ThreadPool::threadAct, this});
    }
}

inline ThreadPool::~ThreadPool()
{
    for(auto &e: m_threads) {
        e.join();
    }
}


template <typename FunctionObject>
void ThreadPool::AddTask(FunctionObject a_act)
{
    AddTask(std::unique_ptr<AbstractAct> {new threads::FunctionObjectAct(a_act)});   
}


////////////////////////

inline void ThreadPool::internalAddTask(std::unique_ptr<AbstractAct> a_act) 
{
     m_queue.Enqueue(std::move(a_act)); 
} 

inline void ThreadPool::internalAddTask(std::shared_ptr<AbstractAct> a_act)
{ 
    m_queue.Enqueue(a_act); 
} 


inline void ThreadPool::AddTask(std::unique_ptr<AbstractAct> a_act) 
{ 
    if(!m_terminate){ 
        internalAddTask(std::move(a_act)); 
    } else { 
            std::cout << "cannot insert task" <<std::endl; 
    } 
} 


inline void ThreadPool::AddTask(std::shared_ptr<AbstractAct> a_act) 
{ 
    if(!m_terminate){ 
            internalAddTask(a_act); 
    } else { 
        std::cout << "cannot insert task" <<std::endl; 
    } 
} 

inline void ThreadPool::ShutDown() 
{ 
    m_terminate = true; 
    size_t numOfThreads = m_threads.size(); 
    for (size_t i = 0; i < numOfThreads; ++i) { 
            internalAddTask(std::unique_ptr<AbstractAct>{new TerminatorTask{}});
        } 
} 


} //threads


#endif /* THREADS_POOL_HXX */