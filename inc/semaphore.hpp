#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <semaphore.h>
#include "threads_exception.hpp"

namespace threads{

class SemaphoreException : public ThreadException {
public:
    using ThreadException::ThreadException;
    ~SemaphoreException() = default;
};


class Semaphore  {
public:
    Semaphore(unsigned int a_value);
    Semaphore(const Semaphore& a_other) = delete;
    Semaphore &operator=(const Semaphore& a_other) = delete;
    ~Semaphore();

    void Post(); //inc (unlock) 
    void Wait() noexcept; //dec (lock) 

private:
    sem_t m_sem;
};

} // threads

#include "semaphore.hxx"

#endif //SEMAPHORE_HPP