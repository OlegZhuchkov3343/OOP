#include <exceptions.h>


InvalidShipPlacementException::InvalidShipPlacementException(const std::string &message): message(message) {};

const char* InvalidShipPlacementException::what() const noexcept{
    return message.c_str();
}

NoAbilitiesException::NoAbilitiesException(const std::string &message): message(message) {};

const char* NoAbilitiesException::what() const noexcept{
    return message.c_str();
}

OutOfBoundsException::OutOfBoundsException(const std::string &message): message(message) {};

const char* OutOfBoundsException::what() const noexcept{
    return message.c_str();
}