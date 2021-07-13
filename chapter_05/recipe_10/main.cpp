#include <boost/thread/lock_factories.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>

#include <vector>

typedef std::string item_t;

class user {
    boost::mutex        loot_mutex_;
    std::vector<item_t> loot_;
public:
    // ...

    void exchange_loot(user& u);
    void exchange_loot_1(user& u);
    void exchange_loot_2(user& u);
};

void user::exchange_loot(user& u) {
    typedef boost::unique_lock<boost::mutex> lock_t;

    std::tuple<lock_t, lock_t> l = boost::make_unique_locks(
        loot_mutex_, u.loot_mutex_
    );

    loot_.swap(u.loot_);
}

void user::exchange_loot_1(user& u) {
    auto l = boost::make_unique_locks(
        loot_mutex_, u.loot_mutex_
    );

    loot_.swap(u.loot_);
}


void user::exchange_loot_2(user& u) {
    typedef boost::unique_lock<boost::mutex> lock_t;

    lock_t l0(loot_mutex_, boost::defer_lock);
    lock_t l1(u.loot_mutex_, boost::defer_lock);
    boost::lock(l0, l1);
 
    loot_.swap(u.loot_);
}

int main(){

    return 0;
}