#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

class base
{
public:

   virtual ~base()
   {
   }
};

class derived: public base
{
};

template <class BasePtr>
void check_if_it_is_derived(const BasePtr &ptr)
{
   assert(boost::dynamic_pointer_cast<derived>(ptr) != 0);
}

int main()
{
   // Create a raw and a shared_ptr

   base *ptr = new derived;
   boost::shared_ptr<base> sptr(new derived);
   
   // Check that base pointer points actually to derived class
   check_if_it_is_derived(ptr);
   check_if_it_is_derived(sptr);
   
   // Ok!
   delete ptr;
   return 0;
}