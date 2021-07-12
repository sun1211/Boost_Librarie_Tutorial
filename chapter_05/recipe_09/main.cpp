#include <iostream>
#include <vector>
// we are designing a safety-critical class 
//that is used from multiple threads,
//receives answers from a server,
//postprocesses them, and outputs the response

//Executes for a long time.
std::vector<std::string> read_defaults();

struct postprocessor {
    typedef std::vector<std::string> answer_t;

    // Concurrent calls on the same variable are safe.
    answer_t act(const std::string& in) const {
        if (in.empty()) {
            // Extremely rare condition.
            //when server does not respond because of networking issues or some other problems.
            // In those cases, we attempt to read defaults from file
            return read_defaults();
        }

        // ...
    }
};

//we hit the problem: the server may be unreachable for some noticeable time,
// and for all that time we'll be re-reading the file on each act call.
// This significantly affects performance.

//That's also not a perfect solution:
// we do not know how many instances of postprocessor class are constructed by the user
//and we are wasting memory on defaults that may not be required during the run.
struct postprocessor_v1 {
    typedef std::vector<std::string> answer_t;

private:
    answer_t default_;

public:
    postprocessor_v1(): default_(read_defaults())
    {}

    // Concurrent calls on the same variable are safe.
    answer_t act(const std::string& in) const {
        if (in.empty()) {
            // Extremely rare condition.
            return default_;
        }

        // ...
    }
};

//We have to add variables for storing information that defaults were initialized and a variable for storing the defaults
#include <boost/thread/once.hpp>
struct postprocessor_v2 {
    typedef std::vector<std::string> answer_t;

private:
    mutable boost::once_flag default_flag_;
    mutable answer_t default_;

public:
    postprocessor_v2(): default_flag_(BOOST_ONCE_INIT), default_()
    {}

    // Concurrent calls on the same variable are safe.
    answer_t act(const std::string& in) const {
        answer_t ret;
        if (in.empty()) {
            // Extremely rare condition.
            boost::call_once(default_flag_, [this]() {
                this->default_ = read_defaults();
            });
            return default_;
        }

        // ...
        return ret;
    }
};

//The boost::call_once may pass parameters to the function to call
void once_printer(int i) {
    static boost::once_flag flag = BOOST_ONCE_INIT;
    boost::call_once(
        flag,
        [](int v) { std::cout << "Print once " << v << '\n'; },
        i // <=== Passed to lambda from above.
    );

    // ...
};

int main(){
    for (unsigned i = 0; i < 10000000; ++i) {
        once_printer(i);
    }

    return 0;
}

