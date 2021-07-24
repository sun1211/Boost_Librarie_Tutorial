#include <iostream>
//header for interprocess communications
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/atomic.hpp>

//a check will help us make sure that atomics are usable for this example
typedef boost::atomic<int> atomic_t;
#if (BOOST_ATOMIC_INT_LOCK_FREE != 2)
#error "This code requires lock-free boost::atomic<int>"
#endif

//#include <atomic>
//typedef std::atomic<int> atomic_t;

int main() {
    //Create, or get, a shared segment of memory
    boost::interprocess::managed_shared_memory 
        segment(boost::interprocess::open_or_create, "shm1-cache", 1024);

    //Get, or construct, an atomic variable
    atomic_t& atomic 
        = *segment.find_or_construct<atomic_t> //1
            ("shm-counter") // 2
            (0)             // 3
    ;

    //Work with the atomic variable in a usual way
    std::cout << "I have index " << ++ atomic 
        << "\nPress any key...";
    std::cin.get();

    //Destroy the atomic variablE
    int snapshot = -- atomic;
    if (!snapshot) {
        segment.destroy<atomic_t>("shm1-counter");
        boost::interprocess::shared_memory_object
                ::remove("shm-cache");
    }
} /*main*/
