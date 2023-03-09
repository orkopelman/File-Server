#ifndef THREAD_POOLACTIONS_HPP
#define THREAD_POOLACTIONS_HPP

#include "threads_pool_act.hpp"
#include "thread_pool_actions.hpp"

namespace threads {

bool IsPrime(unsigned int a_num);
bool isSumDigits0(unsigned int a_num);
bool isPolyndrum(unsigned int a_num);
void IsPrimeActFunc(unsigned int a_num);
void IsSumOfDigits0ActFunc(unsigned int a_num);
void IsPolyndrumActFunc(unsigned int a_num);


struct IsPrimeAct : public threads::AbstractAct {
	IsPrimeAct(unsigned int a_num) : m_num(a_num) {}
	virtual void Act() override {IsPrimeActFunc(m_num);}

 	unsigned int m_num;
};

struct IsSumDigits0Act : public threads::AbstractAct {
	IsSumDigits0Act(unsigned int a_num) : m_num(a_num) {}
	virtual void Act() override {IsSumOfDigits0ActFunc(m_num);}

 	unsigned int m_num;
};

struct IsPolyndrumAct : public threads::AbstractAct {
	IsPolyndrumAct(unsigned int a_num) : m_num(a_num) {}
	virtual void Act() override {IsPolyndrumActFunc(m_num);}

 	unsigned int m_num;
};


struct IsPrimeFuncObject {
	void operator()(){
		threads::IsPrimeActFunc(m_num);
	}
	unsigned int m_num;
};


} //threads

#include "inl/thread_pool_actions.hxx"

#endif //THREAD_POOLACTIONS_HPP