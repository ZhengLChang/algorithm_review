#include <cstring>
#include <cstdint>
#include <sys/time.h>
#include <string>

uint64_t GetNowUsecs()
{
    timeval time_now;
    uint64_t t_now = 0;
    gettimeofday(&time_now, NULL);
    t_now = time_now.tv_sec * 1000000 + time_now.tv_usec;
    return t_now;
}

struct StringHash
{
    const size_t operator()(const std::string& x)const
    {
        size_t r = 0;
        for(int i = 0; i < x.size(); ++i)
        {
            r += (size_t)(x.at(i) - 'a');
        }
        return r;
    }
};
struct StringComparer
{
    bool operator()(const std::string &x1, const std::string &x2) const
    {
        return x1 == x2;
        return false;
    }
};

