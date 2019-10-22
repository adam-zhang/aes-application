cmake_minimum_required(VERSION 2.8)
project(aes_test)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
set(sources 
	main.cpp
	AESWrapper.cpp
	base64.cpp
	)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})
