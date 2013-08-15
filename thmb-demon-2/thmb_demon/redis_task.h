#pragma once

#include <string>
#include <memory>
#include <boost/optional.hpp>

using namespace std;
using namespace boost;

class TTaskException: public exception {
public:
    TTaskException(const string& message);
    virtual ~TTaskException() throw();
    const char* what() const throw();
private:
    string Message;
};

struct TConnectionError: public TTaskException {
    TConnectionError() : TTaskException("Connection error") {}
};

struct TSelectDbError: public TTaskException {
    TSelectDbError() : TTaskException("Database select error") {}
};

struct TUnexpectedResponseError: public TTaskException {
    TUnexpectedResponseError() : TTaskException("Unexpected response error") {}
};

struct TTask {
    enum EType {
        Image,
        Text
    };
    string FilePath;
    EType Type;
};

class TRedisTaskManagerImpl;

class TRedisTaskManager {
public:
    TRedisTaskManager(const string& host, uint16_t port, size_t dbNum);
    ~TRedisTaskManager();
    optional<TTask> GetTask();
private:
    unique_ptr<TRedisTaskManagerImpl> Impl;
};
