#ifndef THREADS_POOL_ACT_HPP
#define THREADS_POOL_ACT_HPP

#include <functional> 

namespace threads{

class AbstractAct {
public:
    virtual ~AbstractAct() = default;

    virtual void Act() = 0;
    
protected:
    AbstractAct() = default;
    AbstractAct(AbstractAct const& a_other) =  default;
    AbstractAct& operator=(AbstractAct const& a_other) =  default;

};

template <typename F>
class FunctionObjectAct : public AbstractAct {
public:
    FunctionObjectAct(F a_func);
    FunctionObjectAct(FunctionObjectAct const& a_other) = default;
    FunctionObjectAct& operator=(FunctionObjectAct const& a_other) = default;

    virtual void Act() override;

private:
    F m_func;
};

class FunctionAct : public AbstractAct {
public:
    FunctionAct(std::function<void()> a_func);
    FunctionAct(FunctionAct const& a_other) = default;
	FunctionAct& operator=(FunctionAct const&) = default;
    ~FunctionAct() = default;

    virtual void Act() override;

private:
    std::function<void()> m_func;
};


} //threads

#include "threads_pool_act.hxx"

#endif //THREADS_POOL_ACT_HPP