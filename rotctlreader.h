#ifndef ROTCTLREADER_H
#define ROTCTLREADER_H

#include <string>
#include <stdexcept>

namespace rotoctlTools {

enum class RotatorCommandTypes : char{
    SetPosition = 'P',
    GetPosition = 'p',
    MovePosition = 'M',
    Stop = 'S',
    Park = 'K',
    SetConfig = 'C',
    Reset = 'R',
    GetInfo = '_',
    Invalid = '\0'
};

RotatorCommandTypes determineMessageType(const std::string& command);



}



#endif // ROTCTLREADER_H
