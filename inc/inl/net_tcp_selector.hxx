#ifndef NET_TCP_SELECTOR_HXX
#define NET_TCP_SELECTOR_HXX

#include <sys/select.h>   /* select */
#include <stdlib.h> //NULL

namespace net {

namespace tcp {

inline Selector::Selector()
: m_master()
, m_proxy()
{
    FD_ZERO(&m_master);
    FD_ZERO(&m_proxy);
}

inline int Selector::Select() noexcept
{
    m_proxy = m_master;
    return select(FD_SETSIZE, &m_proxy, NULL, NULL, NULL);
}

inline void Selector::Track(int a_descriptor)
{
    FD_SET(a_descriptor, &m_master);
}

inline void Selector::Untrack(int a_descriptor)
{
    FD_CLR(a_descriptor, &m_master);
}

inline bool Selector::IsSet(int a_descriptor)
{
    return FD_ISSET(a_descriptor, &m_proxy);
}

} // tcp

} // net

#endif /* NET_TCP_SELECTOR_HXX */