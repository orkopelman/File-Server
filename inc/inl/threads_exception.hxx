#ifndef THREADS_EXCEPTION_HXX
#define THREADS_EXCEPTION_HXX

#include <exception>
#include <string>
#include <iostream>

#include "threads_exception.hpp"

namespace threads {

inline ThreadException::ThreadException(const char* a_func, const char* a_what, int a_errno)
: m_func(a_func)
, m_what(a_what)
, m_errno(a_errno)
{}

inline const char* ThreadException::what() const noexcept
{
    return m_what.c_str();
}

inline int ThreadException::getErrno() const noexcept
{
    return m_errno;
}

}//threads

#endif /* THREADS_EXCEPTION_HXX */