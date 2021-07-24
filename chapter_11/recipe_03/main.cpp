//users may start writing plugins/shared library in the following way
#include <string>
#include <boost/config.hpp>

#define API extern "C" BOOST_SYMBOL_EXPORT

API std::string greeter(const std::string& name) {
    return "Good to meet you, " + name + ".";
}

//Your program code for loading a shared library must include the header from Boost.DLL
#include <boost/dll/shared_library.hpp>

//The code for loading a library must be the following
int main() {
    boost::filesystem::path plugin_path = /* path-to-pligin */;

    boost::dll::shared_library plugin(
        plugin_path,
        boost::dll::load_mode::append_decorations
    );

    //Getting the user's function must look like this
    auto greeter = plugin.get<std::string(const std::string&)>("greeter");
    std::cout << greeter("Sally Sparrow");
}