#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include <assert.h>
#include "blocking_queue.hpp"

namespace threads{

inline static unsigned int checkNoZeroSize(unsigned int a_size)
{
    if (a_size == 0) {
        throw BlockingQueueException("Blocking Queue Ctor","size zero error", 0);
    }
    return a_size;
}

template<typename T>
inline BlockingQueue<T>::BlockingQueue(unsigned int a_size)
: m_size(checkNoZeroSize(a_size))
, m_queue()
, m_emptySlots(a_size)
, m_fullSlots(0)
{}


template<typename T>
void BlockingQueue<T>::Enqueue(const T& a_item)  //producer
{   
    m_emptySlots.Wait();
    try {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(a_item);
    } catch (...) {
        m_emptySlots.Post();
    }

    m_fullSlots.Post();
   
}

template<typename T>
void BlockingQueue<T>::Enqueue(T&& a_item)  //producer
{   
    m_emptySlots.Wait();
    try {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(std::move(a_item));
    } catch (...) {
        m_emptySlots.Post();
    }

    try {
        m_fullSlots.Post();
    } catch (...) {
        assert("!what should be here?");
    }
}

template<typename T> 
void BlockingQueue<T>::Dequeue(T& a_item)  //consumer
{  
    m_fullSlots.Wait();
    try {
        std::lock_guard<std::mutex> lock(m_mutex);
        a_item = m_queue.front();
        m_queue.pop();
        m_emptySlots.Post();
    }
    catch (...) {
        m_fullSlots.Post();
        throw BlockingQueueException("blocking queue dequeue", "pop failed", 0);
    }
}

template<typename T> 
void BlockingQueue<T>::Dequeue(T&& a_item)  //consumer
{  
    m_fullSlots.Wait();
    try {
        std::lock_guard<std::mutex> lock(m_mutex);
        a_item = std::move(m_queue.front());
        m_queue.pop();
        m_emptySlots.Post();
    }
    catch (...) {
        m_fullSlots.Post();
        throw BlockingQueueException("blocking queue dequeue", "pop failed", 0);
    }
}

template <typename T>
unsigned int BlockingQueue<T>::Size() const
{
	std::lock_guard<std::mutex> guard(m_mutex);
	return m_queue.size();
}


template<typename T>
bool BlockingQueue<T>::IsEmpty() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
}


template<typename T>
void BlockingQueue<T>::Print() const {
    std::queue<T>q2(m_queue);
    while (!q2.empty()) {
        std::cout << ' ' << q2.front() << ' ';
        q2.pop();
    }
    std::cout << std::endl;
}


} // threads


#endif // BLOCKING_QUEUE_HXX






