cmake_minimum_required(VERSION 3.21)

project("crispy-dtls")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CXX_STANDARD_REQUIRED ON)

if(WIN32)
    link_libraries("ws2_32")
endif()


set(CERTS "${PROJECT_SOURCE_DIR}/certs")
set(SERVER_CERT "${CERTS}/public/server-cert.pem")
set(SERVER_KEY "${CERTS}/private/server-key.pem")
set(CA_CERT "${CERTS}/public/ca-cert.pem")

if(WIN32)
	if(NOT EXISTS ${OPENSSL_CRYPTO})
		message(FATAL_ERROR "Variable OPENSSL_CRYPTO is not set. Set it in CMakeUserPresets.json")
	endif()
endif()

#find_package(OpenSSL REQUIRED)

add_library("OpenSSL_Crypto" SHARED IMPORTED)


if(WIN32)
	set_target_properties("OpenSSL_Crypto" PROPERTIES IMPORTED_IMPLIB ${OPENSSL_CRYPTO_LIB})
	set_target_properties("OpenSSL_Crypto" PROPERTIES IMPORTED_LOCATION ${OPENSSL_CRYPTO})
else()
	set_target_properties("OpenSSL_Crypto" PROPERTIES IMPORTED_LOCATION ${OPENSSL_CRYPTO_LIB})
endif()


set_target_properties("OpenSSL_Crypto" PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${OPENSSL_INCLUDE_DIR})

add_compile_definitions(CA_CERT="${CA_CERT}" SERVER_CERT="${SERVER_CERT}" SERVER_KEY="${SERVER_KEY}")


add_subdirectory("dtls")
add_subdirectory("server")

target_link_libraries("dtls" PRIVATE "OpenSSL_Crypto")
target_link_libraries("server" PRIVATE "dtls")