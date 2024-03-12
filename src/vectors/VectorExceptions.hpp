#ifndef VECTOREXCEPTIONS_H
#define VECTOREXCEPTIONS_H

#include <exception>
#include <string>

class VectorException: public std::exception
{
public:
    VectorException(std::string filename,
              std::string classname,
              int line,
              const char *time,
              std::string info = "Exception!")
    {
        error_info = "\nFile name: " + filename +
                     "\nClass: " + classname +
                     "\nLine: " + std::to_string(line) +
                     "\nTime: " + time +
                     "Info: " + info;
    }

    virtual const char* what() const noexcept override
    {
        return error_info.c_str();
    }

    virtual ~VectorException() {};

protected:
    std::string error_info;
};

class MemoryException: public VectorException
{
public:
    MemoryException(std::string filename,
                std::string classname,
                int line,
                const char *time,
                std::string info = "Memory allocation error!\n"):
        VectorException(filename, classname, line, time, info) {};
};

class DeletedObject: public VectorException
{
public:
    DeletedObject(std::string filename,
                std::string classname,
                int line,
                const char *time,
                std::string info = "Attempt to work with a remote object!\n"):
        VectorException(filename, classname, line, time, info) {};
};

class InvalidIterator : public VectorException
{
public:
    InvalidIterator(
        std::string filename,
        std::string classname,
        int line,
        const char *time,
        std::string info = "Attempt to use an invalid iterator!\n") :
    VectorException(filename, classname, line, time, info) {};
};

class EmptyVectorException : public VectorException
{
public:
    EmptyVectorException(std::string filename,
                     std::string classname,
                     int line, const char *time,
                     std::string info = "The size of the vector must be greater than 0!\n") :
    VectorException(filename, classname, line, time, info) {};
};

class IndexVectorException : public VectorException
{
public:
    IndexVectorException(std::string filename,
               std::string classname,
               int line, const char *time,
               std::string info = "Going beyond the vector limit!\n") :
    VectorException(filename, classname, line, time, info) {};
    virtual const char* what() const noexcept
    {
        return error_info.c_str();
    }
};

class ZeroDivException : public VectorException
{
public:
    ZeroDivException(std::string filename,
                 std::string classname,
                 int line,
                 const char *time,
                 std::string info = "Division by zero is not allowed!\n") :
    VectorException(filename, classname, line, time, info) {};
};

class InvalidCopyArrayPointer : public VectorException
{
public:
    InvalidCopyArrayPointer(std::string filename,
                 std::string classname,
                 int line,
                 const char *time,
                 std::string info = "The original array does not exist!\n") :
    VectorException(filename, classname, line, time, info) {};
};

class DifferentSizeVectors: public VectorException
{
public:
    DifferentSizeVectors(std::string filename,
                 std::string classname,
                 int line,
                 const char *time,
                 std::string info = "The Vectors are different size!\n") :
    VectorException(filename, classname, line, time, info) {};
};

#endif // VECTOREXCEPTIONS_H
