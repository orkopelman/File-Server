#include <cassert> //assert()
#include <cerrno> //errno

#include "semaphore.hpp" // TODO remove

static const char* Ooops = "Ooopss - invalid semaphore, see ctor";

namespace threads {

inline Semaphore::Semaphore(unsigned a_value)
{ 
    if (::sem_init(&m_sem, 0, a_value) == -1) {
        switch(errno) {
            case EINVAL:
                throw SemaphoreException("Semaphore Ctor", "semaphore excced max value", errno);
            case ENOSYS:
                assert(false);        
        }
    }
}

inline Semaphore::~Semaphore() 
{ 
    if (sem_destroy(&m_sem) == -1) {
        switch (errno) {
            case EINVAL:
                assert(!Ooops);
        }
    } 
}


inline void Semaphore::Post()
{
    if(::sem_post(&m_sem) == -1) {
        switch (errno) {
            case EINVAL:
                assert(!Ooops);
            case EOVERFLOW:
                throw SemaphoreException("semaphore post", "The maximum allowable value for a semaphore would be exceeded", errno);
        }
    }
}

inline void Semaphore::Wait() noexcept
{
    if(::sem_wait(&m_sem) == -1) {
        switch (errno) {
            case EINVAL :
                assert(!Ooops);
            case EINTR:
                try {
                    ::sem_wait(&m_sem);
                } 
                catch (...){
                    break;
                }
                
        }
    }
}

} //threads



