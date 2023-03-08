#ifndef PROTCOL_HPP
#define PROTCOL_HPP
#include <fstream>  

namespace protocol {

namespace flags {
enum FILE_OPEN_FLAGS {
    READ,
    WRITE,
    APPEND,
    BINARY
};
} // flags


// a message is limited to 256 bytes
constexpr int MTU = 256;
constexpr int bufSize = 1500;


enum TAG {
    // Requests
    OPEN = 0,   // flags (uint8_t),  name file to open.    ///(OPEN, APPEND, "filename.txt")
    CLOSE,      //                                         ///(CLOSE)
    READ,       // size bytes to read (uint8_t)            ///(READ, 152)
    WRITE,      // buffer to write                         ///(WRITE, asdasdasdasdasdasdasd)

    // Responses
    FAILED,   //none                                       // (FAILED)
    SUCCESS,  //none                                       // (SUCCESS)
    DATA     //buffer                                      // (DATA, dasdasdasdasdasdasdasd)
};

} //protocol

#endif //PROTCOL_HPP