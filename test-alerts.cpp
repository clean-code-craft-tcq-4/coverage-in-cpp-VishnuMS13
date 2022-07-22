#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.hpp"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("Test for classify Temperature breach") {
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, MID_VALUE) == NORMAL);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, LOW_VALUE) == TOO_LOW);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, HIGH_VALUE) == TOO_HIGH);

	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, MID_VALUE) == NORMAL);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, LOW_VALUE) == TOO_LOW);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, HIGH_VALUE) == TOO_HIGH);

	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, MID_VALUE) == NORMAL);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, LOW_VALUE) == TOO_LOW);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, HIGH_VALUE) == TOO_HIGH);

}

TEST_CASE("Test for Conroller") {
	BatteryCharacter batteryChar {PASSIVE_COOLING,"AMARON"};
	checkAndAlert(TO_CONTROLLER, batteryChar, LOW_VALUE);
	checkAndAlert(TO_CONTROLLER, batteryChar, MID_VALUE);
	checkAndAlert(TO_CONTROLLER, batteryChar, HIGH_VALUE);
}

TEST_CASE("Test for Email(checkAlert)"){
	BatteryCharacter batteryCheckForEmail = {.coolingType = PASSIVE_COOLING};
	
	ostringstream sendEmail;
	streambuf* streamBuffer = cout.rdbuf();
	cout.rdbuf(sendEmail.rdbuf());
	
	checkAndAlert(TO_EMAIL, batteryCheckForEmail, LOW_VALUE);
	
	cout.rdbuf(streamBuffer);
	REQUIRE(sendEmail.str() == "To: ms.vishnu@gmail.com\nHi, the temperature is too low\n");	
}