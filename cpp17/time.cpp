#include <chrono>
#include <iostream>
#include <thread>
#include <iomanip>

namespace {
    using clock = std::chrono::system_clock;
    using time_point = std::chrono::time_point<clock>;
    using timestamp = int64_t;
    using seconds = std::chrono::duration<double>;
    using milliseconds = std::chrono::duration<double, 
          std::ratio_multiply<seconds::period, std::milli>>;
    using microseconds = std::chrono::duration<double, 
          std::ratio_multiply<seconds::period, std::micro>>;

    /// Converts time_point to unix timestamp
    timestamp unix_timestamp(time_point tp) 
    {
        auto sec = std::chrono::time_point_cast<std::chrono::seconds>(tp);
        auto epoch = sec.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::seconds>(epoch);
        return value.count();
    }

    /// Returns current unix timestamp
    timestamp unix_timestamp() 
    {
        return unix_timestamp(clock::now());
    }

    /// Cast to time_point
    time_point cast_time_point(timestamp t) 
    {
        std::chrono::duration<timestamp> dur(t);
        return time_point(dur);
    }

    /// Duration in seconds for time_point arguments
    double duration(time_point a, time_point b) 
    {
        return (a - b).count();
    }

    /// Duration in milliseconds for time_point arguments
    double duration_milli(time_point a, time_point b) 
    {
        return milliseconds(a - b).count();
    }

    /// Duration in microseconds for time_point arguments
    double duration_micro(time_point a, time_point b) 
    {
        return microseconds(a - b).count();
    }

    /// Duration in seconds for unix timestamp arguments
    double duration(timestamp a , timestamp b) 
    {
        return (a - b);
    }

    /// Duration in milliseconds for unix timestamp arguments
    double duration_milli(timestamp a , timestamp b) 
    {
        return duration_milli(cast_time_point(a), cast_time_point(b));
    }
    
    /// Duration in microseconds for unix timestamp arguments
    double duration_micro(timestamp a , timestamp b) 
    {
        return duration_micro(cast_time_point(a), cast_time_point(b));
    }

    /// Elapsed time in seconds since 'a'
    double elapsed(time_point a) 
    {
        return duration(clock::now(), a);
    }

    /// Elapsed time in milliseconds since 'a'
    double elapsed_milli(time_point a) 
    {
        return duration_milli(clock::now(), a);
    }

    /// Elapsed time in microseconds since 'a'
    double elapsed_micro(time_point a) 
    {
        return duration_micro(clock::now(), a);
    }

    /// Elapsed time in seconds since 'a'
    double elapsed(timestamp a) 
    {
        return elapsed(cast_time_point(a));
    }

    /// Elapsed time in milliseconds since 'a'
    double elapsed_milli(timestamp a) 
    {
        return elapsed_milli(cast_time_point(a));
    }

    /// Elapsed time in microseconds since 'a'
    double elapsed_micro(timestamp a) 
    {
        return elapsed_micro(cast_time_point(a));
    }
}

int main()
{
    auto tp = clock::now();
    timestamp ts = unix_timestamp();
    std::this_thread::sleep_for(seconds(4));
    std::cout << elapsed(ts) << std::endl;
    std::cout << elapsed_milli(ts) << std::endl;
    std::cout << elapsed_micro(ts) << std::endl;
    std::cout << "time point" << std::endl;
    std::cout << elapsed(tp) << std::endl;
    std::cout << elapsed_milli(tp) << std::endl;
    std::cout << elapsed_micro(tp) << std::endl;

    /*
    timestamp ts = unix_timestamp();
    time_point a = clock::now();
    std::this_thread::sleep_for(seconds(4));
    time_point b = clock::now();
    std::cout << duration(b, a) << std::endl;
    std::cout << duration_milli(b, a) << std::endl;
    std::cout << duration_micro(b, a) << std::endl;
    auto tp = cast_time_point(ts);
    auto ts1 = unix_timestamp(tp);
    std::cout << ts1 << " " << ts << std::endl;

    std::cout << duration_milli(unix_timestamp(), ts) << std::endl;
    std::cout << "elapsed : " << elapsed(a) << std::endl;
    std::cout << "elapsed : " << elapsed_milli(a) << std::endl;
    std::cout << "elapsed : " << elapsed_micro(a) << std::endl;
    std::cout << "elapsed1 : " << elapsed(ts) << std::endl;
    std::cout << "elapsed2 : " << elapsed_milli(ts) << std::endl;
    std::cout << "elapsed3 : " << elapsed_micro(ts) << std::endl;
    */
}
