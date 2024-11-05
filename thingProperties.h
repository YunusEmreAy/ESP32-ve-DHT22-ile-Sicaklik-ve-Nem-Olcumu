#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "635d3a94-166b-4c23-8dd0-211a47f69789";

const char SSID[]               = "Wokwi-GUEST";    // Network SSID (name)
const char PASS[]               = "";    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = "f8cXrBgtS9IbJKwuLfw7dccUF";    // Secret device password

void onMesajChange();
void onLedChange();

String mesaj;
CloudTemperatureSensor sicaklik;
CloudRelativeHumidity nem;
bool led;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(mesaj, READWRITE, ON_CHANGE, onMesajChange);
  ArduinoCloud.addProperty(sicaklik, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(nem, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(led, READWRITE, ON_CHANGE, onLedChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
