#define BUTTON_PIN 4                                                      //Define work the button

#include <Arduino.h>                                                      //Libery incude
#include <WiFi.h>                                                         //Connect lib. working for the wifi

const int conf_par_size = 25;
char conf_wifi_ssid [conf_par_size] = "***";
char conf_wifi_password [conf_par_size] = "***";
int check = 0;
int max_connect_attempts = 10;
bool s_button = false;

bool connect_to_wife();                                                   //Connect to network
void disconnect_wifi();                                                   //Disconnect to network
void start_sys();                                                         //Funktions start work
void IRAM_ATTR isr();                                                     //Funktion interrupt button

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(BUTTON_PIN, isr, FALLING);
  delay(200);
  if(String(conf_wifi_ssid) == "" || String(conf_wifi_password) == ""){         //If we don't have creatials to wifi...
    //
  } else {
    //
  }
  start_sys();
}

void loop() {
  if(s_button){
    connect_to_wife();
  } else {
    //
    disconnect_wifi();
  }
}

bool connect_to_wife(){                                                    //Connect to network
  bool w_status = false;

  WiFi.mode(WIFI_STA);
  WiFi.begin(conf_wifi_ssid, conf_wifi_password);
  while (WiFi.status() != WL_CONNECTED && check < max_connect_attempts && !s_button){
    delay(1000);
    Serial.println("-");
    check++;
  }
  if(WiFi.status() != WL_CONNECTED){
    esp_sleep_enable_timer_wakeup(1 * 10L * 1000000L);
    esp_deep_sleep_start();
    w_status = false;
  } else {
    w_status = true;
  }
  return w_status;
}

void start_sys(){
  if(!connect_to_wife()){
    Serial.println("Failed connect to wifi!");
  } else {
    Serial.println("Succesfully connect to wifi!");
    delay(2000);
    disconnect_wifi();
  }
}

void disconnect_wifi(){
  Serial.println("Disconnect Wifi");
  WiFi.disconnect();
  WiFi.softAPdisconnect();
  WiFi.mode(WIFI_OFF);
}

void IRAM_ATTR isr(){
  s_button = !s_button;
}