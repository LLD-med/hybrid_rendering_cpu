#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>
#include <exception>

class BaseException : public std::exception
{
public:
    explicit BaseException(std::string &msg) : _msg(msg) { }

    const char *what() const noexcept override { return "Something went wrong!"; }
    const std::string &getInfo() const noexcept { return _msg; }

protected:
    std::string _msg;
};


class CameraException : public BaseException
{
public:
    explicit CameraException(std::string &msg) : BaseException(msg) { }

    const char *what() const noexcept override { return "Camera isn't added"; }
};

class LightException : public BaseException
{
public:
    explicit LightException(std::string &msg) : BaseException(msg) { }

    const char *what() const noexcept override { return "Light isn't added"; }
};

class SourceException : public BaseException
{
public:
    explicit SourceException(std::string &msg) : BaseException(msg) { }

    const char *what() const noexcept override { return "Load error"; }
};


class ModelException : public BaseException
{
public:
    explicit ModelException(std::string &msg) : BaseException(msg) { }

    const char *what() const noexcept override { return "Can't build model"; }
};

#endif //EXCEPTIONS_HPP
