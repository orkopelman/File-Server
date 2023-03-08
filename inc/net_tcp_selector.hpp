#ifndef NET_TCP_SELECTOR_HPP
#define NET_TCP_SELECTOR_HPP

#include <sys/select.h>   /* select */

namespace net {

namespace tcp {

class Selector {
public:
    Selector();
    Selector(const Selector& a_other) = delete;
    Selector& operator=(const Selector& a_other) = delete;
    ~Selector() = default;

    // return number of activities in tracked file descriptors
    int Select() noexcept;

    void Track(int a_descriptor);
    void Untrack(int a_descriptor);

    bool IsSet(int a_descriptor);

private:
    fd_set m_master;
    fd_set m_proxy;
};

} // tcp

} // net

#include "inl/net_tcp_selector.hxx"

#endif /* NET_TCP_SELECTOR_HPP */