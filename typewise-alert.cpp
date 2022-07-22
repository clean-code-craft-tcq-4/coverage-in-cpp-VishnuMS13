#include "typewise-alert.hpp"

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  BreachType returnValue = NORMAL;
  if(value < lowerLimit) {
    returnValue = TOO_LOW;
  } 
  if(value > upperLimit) {
    returnValue = TOO_HIGH;
  }
  return returnValue;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  switch(coolingType) {
    case PASSIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 35;
      break;
    case HI_ACTIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 45;
      break;
    case MED_ACTIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 40;
      break;
    default:
      break;
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  cout << header << ":" << breachType << endl;
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "ms.vishnu@gmail.com";
  switch(breachType) {
    case TOO_LOW:
      cout << "To: " << recepient << endl;
      cout << "Hi, the temperature is too low" << endl;
      break;
    case TOO_HIGH:
      cout << "To: " << recepient << endl;
      cout << "Hi, the temperature is too High" << endl;
      break;
    case NORMAL:
      break;
  }
}
