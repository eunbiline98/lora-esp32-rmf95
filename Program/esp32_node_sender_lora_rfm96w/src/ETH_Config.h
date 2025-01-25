/**
 * MQTT & ETH CONFIG
 * --------------------------------------
 */
#include "EthernetSPI2.h"
#define led_indi 23

const char *MQTT_SERVER = "192.168.8.2";
const char *MQTT_STATUS = "paditech/pow/3phase";

const char *MQTT_POW_STATE = "paditech/pow/3phase/runn";
const char *WILL_MESSAGE = "Offline";

const char *MQTT_CLIENT_ID = "POW_3-phase-@#!!@$";
const char *MQTT_USERNAME = "busol";
const char *MQTT_PASSWORD = "p4d1n3t";

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0x02, 0xAB, 0xCD, 0xEF, 0x00, 0x01};
IPAddress ip(192, 168, 8, 161);
IPAddress dns(202,6,232,66);
IPAddress gateway(192, 168, 8, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetClient espClient;

void ConnectionSetup()
{
      Ethernet.init(15);
      Ethernet.begin(mac, ip, dns, gateway, subnet);
      // Ethernet.begin(mac);

      // Check for Ethernet hardware present
      if (Ethernet.hardwareStatus() == EthernetNoHardware)
      {
            Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
            while (true)
            {
                  Serial.print(".");
                  digitalWrite(led_indi, HIGH);
                  delay(100);
                  digitalWrite(led_indi, LOW);
                  delay(100);
            }
      }
      while (Ethernet.linkStatus() == LinkOFF)
      {
            Serial.println("Ethernet cable is NOT connected.");
            digitalWrite(led_indi, HIGH);
            delay(250);
            digitalWrite(led_indi, LOW);
            delay(250);
      }

      Serial.println("Ethernet cable is now connected.");

      delay(500);
      // print ip address
      Serial.print("Local IP : ");
      Serial.println(Ethernet.localIP());
      Serial.print("Subnet Mask : ");
      Serial.println(Ethernet.subnetMask());
      Serial.print("Gateway IP : ");
      Serial.println(Ethernet.gatewayIP());
      Serial.print("DNS Server : ");
      Serial.println(Ethernet.dnsServerIP());
}