add_executable(server main.cpp InternetSocketAddress.hpp InternetSocketAddressHasher.hpp)
set_property(TARGET server PROPERTY CXX_STANDARD 23)