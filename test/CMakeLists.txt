set(target polinoms_test)

#file(GLOB hdrs "*.h*" "../include/*.h" "../gtest/*.h")
file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../src/*.cpp")

add_executable(${target} ${srcs} ${hdrs} "test_avl.cpp" "test_hash.cpp" "test_sm.cpp" "test_nsm.cpp")
target_link_libraries(${target} gtest)