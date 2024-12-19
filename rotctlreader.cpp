#include "rotctlreader.h"

namespace rotoctlTools {

RotatorCommandTypes determineMessageType(const std::string& command)
{
    if (command.empty()) {
        return RotatorCommandTypes::Invalid;
    }

    // Determine detection method
    bool longDetection = (command.at(0) == '\\');

    if (!longDetection)
    {
        char command_prefix = command.at(0);
        // Function to safely convert a char to RotatorCommandType
        switch (command_prefix) {
        case 'P': return RotatorCommandTypes::SetPosition;
        case 'p': return RotatorCommandTypes::GetPosition;
        case 'M': return RotatorCommandTypes::MovePosition;
        case 'S': return RotatorCommandTypes::Stop;
        case 'K': return RotatorCommandTypes::Park;
        case 'C': return RotatorCommandTypes::SetConfig;
        case 'R': return RotatorCommandTypes::Reset;
        case '_': return RotatorCommandTypes::GetInfo;
        default: return RotatorCommandTypes::Invalid;
        }
    }

    // Implement long detection logic here if needed
    return RotatorCommandTypes::Invalid;
}

} // namespace rotoctlTools
