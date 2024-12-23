#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>

class InvalidShipPlacementException : public std::exception{
private:
    const std::string message;
public:
    explicit InvalidShipPlacementException(const std::string& message);
    const char* what() const noexcept override;
};

class NoAbilitiesException : public std::exception{
private:
    const std::string message;
public:
    explicit NoAbilitiesException(const std::string& message);
    const char* what() const noexcept override;
};

class OutOfBoundsException : public std::exception{
private:
    const std::string message;
public:
    explicit OutOfBoundsException(const std::string& message);
    const char* what() const noexcept override;
};

#endif