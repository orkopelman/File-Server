#include "mu_test.h"
#include "server.hpp"
#include "file_actions.hpp"

#include "memory"



BEGIN_TEST(RunServer)
    std::unique_ptr<InterfaceServer> myServer = std::make_unique<Server>("127.0.0.1");
    myServer->Run();
    //myServer->Kill();
    ASSERT_PASS();
END_TEST


BEGIN_SUITE(Its what you learn after you know it all that counts)
    TEST(RunServer)
END_SUITE
