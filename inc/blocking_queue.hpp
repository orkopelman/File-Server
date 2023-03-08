#ifndef BLOCKINGQUEUE_HPP
#define BLOCKINGQUEUE_HPP

#include <limits.h> //max unsinged int
#include <queue>
#include <mutex>

#include "semaphore.hpp"

namespace threads{

class BlockingQueueException : public ThreadException {
public:
	using ThreadException::ThreadException;
	~BlockingQueueException() = default;
};

template<typename T>
class BlockingQueue {
public:
	BlockingQueue(unsigned int a_size = INT_MAX);	
	BlockingQueue(const BlockingQueue& a_other) = delete;
	BlockingQueue& operator = (const BlockingQueue& a_other) = delete;
	~BlockingQueue() = default;

	void Enqueue(const T& a_item);
	void Enqueue(T&& a_item);
	void Dequeue(T& a_item);
	void Dequeue(T&& a_item);

    bool IsEmpty() const;
	unsigned int Size() const;
    void Print() const;
   
private:
	unsigned int m_size;
    std::queue<T> m_queue;
    Semaphore m_emptySlots;
    Semaphore m_fullSlots;
    mutable std::mutex m_mutex;
};

} //threads


#include "blocking_queue.hxx"

#endif //BLOCKINGQUEUE_HPP