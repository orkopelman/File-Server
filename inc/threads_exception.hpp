#ifndef THREADS_EXCEPTION_HPP
#define THREADS_EXCEPTION_HPP

#include <exception>
#include <string>

namespace threads {

class ThreadException : public std::exception {
public:
    ThreadException(const char* a_func, const char* a_what, int a_errno);
    ~ThreadException() = default; 
    virtual const char* what() const noexcept;
    virtual int getErrno() const noexcept;

private:
    std::string m_func;
    std::string m_what;
    int m_errno;
};

}//threads

#include "threads_exception.hxx"

#endif /* THREADS_EXCEPTION_HPP */
