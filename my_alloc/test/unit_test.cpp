#include <iostream>
#include <gtest/gtest.h>



TEST(testName, subTestName1) {
    ASSERT_FALSE(32 == 93 );
}


TEST(testName, subTestName2) {
    ASSERT_FALSE(32 == 93 );
}
int main(int argc,char ** argv){
    testing::InitGoogleTest(&argc,argv);
    
    return RUN_ALL_TESTS();
}