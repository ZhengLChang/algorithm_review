#include <iostream>
#include <memory>
#include <mutex>

using namespace std;
class Singleton{
private:
    static Singleton *m_instance_ptr;
    static mutex m_mutex;
private:
    Singleton(){};
public:
    ~Singleton(){
        if(m_instance_ptr != nullptr)
        {
            delete m_instance_ptr;
            m_instance_ptr = nullptr;
        }
    }
    Singleton(Singleton&) =delete;
    Singleton& operator=(const Singleton&)=delete;
    static Singleton* get_instance(){
        if(m_instance_ptr == nullptr)
        {
            lock_guard<mutex> lk(m_mutex);
            if(m_instance_ptr == nullptr)
            {
                m_instance_ptr = new Singleton;
            }
        }
        return m_instance_ptr;
    }
};

Singleton* Singleton::m_instance_ptr = nullptr;
mutex Singleton::m_mutex;

int main()
{
    Singleton *instance = Singleton::get_instance();
    Singleton *instance2 = Singleton::get_instance();
    if(instance == instance2)
    {
        cout << "same" << endl;
    }
    return 0;
}
