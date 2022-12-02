#include <gtest.h>
#include<iostream>

int main(int argc, char **argv) {
    char tmp;
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    std::cin >> tmp;
    return 1;
    
}
