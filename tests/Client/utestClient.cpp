#include "mu_test.h"
#include "client.hpp"
#include "memory"
#include "protocol.hpp"
#include <string.h> //strlen()
#include <thread>



BEGIN_TEST(OpenNewFile)
    std::unique_ptr<nfs> client = std::make_unique<mynfs>();
    int resp = client->open("filename.txt", protocol::flags::WRITE);
    
    ASSERT_EQUAL(resp,protocol::SUCCESS);
END_TEST

BEGIN_TEST(OpenCloseFile)
    std::unique_ptr<nfs> client = std::make_unique<mynfs>();
    client->open("filename2.txt", protocol::flags::WRITE);
    int resp = client->close();
    
    ASSERT_EQUAL(resp,protocol::SUCCESS);
END_TEST

BEGIN_TEST(WriteToEmptyFile)
    const char* buf = "this is the text to write into the file";
    std::unique_ptr<nfs> client = std::make_unique<mynfs>();
    client->open("filename.txt", protocol::flags::WRITE);
    int resp = client->write(buf,strlen(buf));
    client->close();
    
    
    ASSERT_EQUAL(resp,protocol::SUCCESS);
END_TEST

BEGIN_TEST(AppendToFile)
    const char* buf = "this is the text to be added to the file";
    std::unique_ptr<nfs> client = std::make_unique<mynfs>();
    client->open("filename.txt", protocol::flags::APPEND);
    int resp = client->write(buf,strlen(buf));
    client->close();
    
    ASSERT_EQUAL(resp,protocol::SUCCESS);
END_TEST


BEGIN_TEST(ReadFromFile)
    const char* buf = "this is the text to write into the file";
    char bufToRead[4];
    
    std::unique_ptr<nfs> client = std::make_unique<mynfs>();
    client->open("filename.txt", protocol::flags::WRITE);
    client->write(buf,strlen(buf));
    client->close();

    client->open("filename.txt", protocol::flags::READ);
    int resp = client->read(bufToRead, 4);
    client->close();

    const char* compare = "this";

    ASSERT_EQUAL(resp,4);
    ASSERT_EQUAL(strcmp(bufToRead,compare), 0);
END_TEST




BEGIN_TEST(SeveralClients)

    const char* msg= "hi i am writing to mfuck you\n";

    std::unique_ptr<nfs> client1 = std::make_unique<mynfs>();
    std::unique_ptr<nfs> client3 = std::make_unique<mynfs>();
    std::unique_ptr<nfs> client4 = std::make_unique<mynfs>();

    int resp1 = client1->open("filenameClient1.txt", protocol::flags::WRITE);
    std::unique_ptr<nfs> client2 = std::make_unique<mynfs>();
    int resp2 = client2->open("filenameClient2.txt", protocol::flags::WRITE);
    int resp3 = client3->open("filenameClient3.txt", protocol::flags::WRITE);
    int resp4 = client4->open("filenameClient4.txt", protocol::flags::WRITE);
    
    resp1 = client1->write(msg,strlen(msg));
    resp2 = client2->write(msg,strlen(msg));

    client1->close();
    client2->close();
    client3->close();
    client4->close();

    ASSERT_EQUAL(resp1,protocol::SUCCESS);
    ASSERT_EQUAL(resp2,protocol::SUCCESS);
    ASSERT_EQUAL(resp3,protocol::SUCCESS);
    ASSERT_EQUAL(resp4,protocol::SUCCESS);
END_TEST

BEGIN_TEST(TwoClientsWriteToSameFile)
    const char* buf = "this is the text to write into the file";
    char bufToRead1[4];
    char bufToRead2[4];
    std::unique_ptr<nfs> client1 = std::make_unique<mynfs>();
    std::unique_ptr<nfs> client2 = std::make_unique<mynfs>();
    client1->open("filename.txt", protocol::flags::WRITE);
    client1->write(buf,strlen(buf));
    client1->close();
    client1->open("filename.txt", protocol::flags::READ);
    client2->open("filename.txt", protocol::flags::READ);
    int resp1 =  client1->read(bufToRead1, 4);
    int resp2 =  client2->read(bufToRead2, 4);
    client1->close();
    client2->close();
    char compare[5] = "this";

    std::cout << bufToRead1 <<"\n";
    std::cout << bufToRead2 <<"\n";
    ASSERT_EQUAL(resp1,4);
    ASSERT_THAT(strcmp(bufToRead1,compare));
    ASSERT_EQUAL(resp2,4);
    ASSERT_THAT(strcmp(bufToRead2,compare));
END_TEST




BEGIN_SUITE(Its what you learn after you know it all that counts)
	//TEST(OpenNewFile)
    //TEST(OpenCloseFile) 
    //TEST(WriteToEmptyFile) 
    //TEST(AppendToFile) 
    TEST(ReadFromFile)
    //TEST(TwoClientsWriteToSameFile)
    //TEST(SeveralClients)

END_SUITE

