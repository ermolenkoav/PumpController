#include "../businessLogic/model.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(PumpControllerModel, setSupplyTime) {
    PumpControllerModel model;;
    EXPECT_TRUE(model.setSupplyTime(1));
    EXPECT_TRUE(model.setSupplyTime(5));
    EXPECT_TRUE(model.setSupplyTime(9));
    EXPECT_FALSE(model.setSupplyTime(-1));
    EXPECT_FALSE(model.setSupplyTime(10));
    EXPECT_FALSE(model.setSupplyTime(30000));
}
TEST(PumpControllerModel, setDelayTime) {
    PumpControllerModel model;
    EXPECT_TRUE(model.setDelayTime(1));
    EXPECT_TRUE(model.setDelayTime(30));
    EXPECT_TRUE(model.setDelayTime(100));
    EXPECT_FALSE(model.setDelayTime(-1));
    EXPECT_FALSE(model.setDelayTime(101));
    EXPECT_FALSE(model.setDelayTime(30000));
}
