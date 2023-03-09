#ifndef THREADS_POOL_ACT_HXX
#define THREADS_POOL_ACT_HXX

#include "threads_pool_act.hpp"
#include <iostream>

namespace threads {


template <typename F>
FunctionObjectAct<F>::FunctionObjectAct(F a_func)
: m_func(std::move(a_func)) 
{
}

template <typename F>
void FunctionObjectAct<F>::Act()
{
    m_func();
}

inline FunctionAct::FunctionAct(std::function<void()> a_func)
: m_func(a_func)
{
}

inline void FunctionAct::Act()
{
    m_func();
}

}//threads


#endif /* THREADS_POOL_ACT_HXX */