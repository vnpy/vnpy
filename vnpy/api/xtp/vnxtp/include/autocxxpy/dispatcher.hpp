#pragma once

#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <assert.h>

namespace autocxxpy
{
    class dispatcher
    {
    public:
        using task_type = std::function<void()>;
        using task_list_type = std::vector<task_type>;
    public:
        inline void add(const task_type &f)
        {
            {
                std::lock_guard<std::mutex> l(_m);
                _ts.push_back(f);
            }
            this->_notify_one();
        }
        void start()
        {
            _run = true;
            _thread = std::thread(&dispatcher::_loop, this);
        }
        void stop()
        {
            _run = false;
        }
        void join()
        {
            assert(!this->_run);
            this->_notify_one();
            _thread.join();
        }
    public:
        inline static dispatcher &instance()
        {
            static dispatcher *_instance = nullptr;
            if (_instance != nullptr)
                return *_instance;

            static std::mutex m;
            std::lock_guard<std::mutex> l(m);
            if (_instance == nullptr)
                _instance = new dispatcher;
            return *_instance;
        }
    protected:
        void _loop()
        {
            while (_run)
            {
                task_list_type ts;
                {
                    auto l = _wait_and_lock();
                    ts = this->_ts;
                    _ts.clear();
                    l.unlock();
                }
                _process_all(ts);
            }
        }

        inline void _process_all(const task_list_type &ts)
        {
            for (const auto &task : ts)
            {
                task();
            }
        }

        inline void _notify_one()
        {
            return _cv.notify_one();
        }

        inline std::unique_lock<std::mutex> _wait_and_lock()
        {
            std::unique_lock<std::mutex> l(_m);
            _cv.wait(l, [this]()
            {
                return !_run || _ts.size();
            });
            return std::move(l);
        }

    protected:
        volatile bool _run = false;
        std::thread _thread;
        std::mutex _m;
        std::condition_variable _cv;
        task_list_type _ts;
    };
}

