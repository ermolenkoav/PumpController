#include <gtest/gtest.h>
#include "controller.h"

TEST(ControllerTest, setStartValueTest) {
	Controller controller = new Controller();
	controller->setStartValue(-1,1);
}