#include <cstring>
#include <cstdint>
#include <sys/time.h>
#include <utility>
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
#if 0
struct PairHash
{
    const size_t operator()(const std::pair<int32_t, int32_t>& x)const
    {
#if 0
        return x.second;
        uint64_t v = (uint64_t)x.second;
        uint32_t hash = 0xabcdef;
        hash = hash ^ v;
        return (size_t)(hash % 10240);
#endif
        return x.first ^ x.second;
    }
};
struct PairComparer
{
    bool operator()(const std::pair<int32_t, int32_t> &x1, const std::pair<int32_t, int32_t> &x2) const
    {
        return x1.first == x2.first && x1.second == x2.second;
    }
};

#endif
