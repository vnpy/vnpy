#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <iostream>
#include <codecvt>
#include <condition_variable>
#include <locale>

#include "pybind11/pybind11.h"


using namespace std;
using namespace pybind11;


struct Task
{
    int task_name;
    void* task_data;
    void* task_error;
    int task_id;
    bool task_last;
};

class TerminatedError : std::exception
{};

class TaskQueue
{
private:
    queue<Task> queue_;
    mutex mutex_;
    condition_variable cond_;

    bool _terminate = false;

public:


    void push(const Task& task)
    {
        unique_lock<mutex > mlock(mutex_);
        queue_.push(task);
        mlock.unlock();
        cond_.notify_one();
    }


    Task pop()
    {
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return !queue_.empty() || _terminate;
            });
        if (_terminate)
            throw TerminatedError();
        Task task = queue_.front();
        queue_.pop();
        return task;
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all();	
    }
};


void getInt(const dict& d, const char* key, int* value)
{
    if (d.contains(key))
    {
        object o = d[key];
        *value = o.cast<int>();
    }
};


void getDouble(const dict& d, const char* key, double* value)
{
    if (d.contains(key))
    {
        object o = d[key];
        *value = o.cast<double>();
    }
};



void getChar(const dict& d, const char* key, char* value)
{
    if (d.contains(key))
    {
        object o = d[key];
        *value = o.cast<char>();
    }
};


template <size_t size>
using string_literal = char[size];


template <size_t size>
void getString(const pybind11::dict& d, const char* key, string_literal<size>& value)
{
    if (d.contains(key))
    {
        object o = d[key];
        string s = o.cast<string>();
        const char* buf = s.c_str();
        strcpy_s(value, buf);
    }
};


inline string toUtf(const string& gb2312)
{
#ifdef _MSC_VER
    const static locale loc("zh-CN");
#else
    const static locale loc("zh_CN.GB18030");
#endif

    vector<wchar_t> wstr(gb2312.size());
    wchar_t* wstrEnd = nullptr;
    const char* gbEnd = nullptr;
    mbstate_t state = {};
    int res = use_facet<codecvt<wchar_t, char, mbstate_t> >
        (loc).in(state,
            gb2312.data(), gb2312.data() + gb2312.size(), gbEnd,
            wstr.data(), wstr.data() + wstr.size(), wstrEnd);

    if (codecvt_base::ok == res)
    {
        wstring_convert<codecvt_utf8<wchar_t>> cutf8;
        return cutf8.to_bytes(wstring(wstr.data(), wstrEnd));
    }

    return string();
}