#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

//  ssid , password
const char ssid[] = "RV";
const char password[] = "air42659";

//  RGb led pins
byte r_pin = 25;
byte g_pin = 26;
byte b_pin = 27;

//  defining channels
#define r_channel 0
#define g_channel 1
#define b_channel 2

//  defining frequency and reolution
#define frequency 5000
#define resolution 8
String html = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>ESP32 RGB CONTROLLER</title></head><body><div style=\"padding-left: 50%; padding-top: 10%;\"><h1>COLOR GENERATOR</h1></div><div style=\"padding-left: 40%;\"><a href=\"/red\"><button>Red</button></a><a href=\"/green\"><button>Green</button></a><a href=\"/blue\"><button>Blue</button></a><a href=\"/yellow\"><button>Yellow</button></a><a href=\"/cyan\"><button>Cyan</button></a><a href=\"/magenta\"><button>Magenta</button></a><a href=\"/orange\"><button>Orange</button></a><a href=\"/off\"><button>OFF</button></a></div></body></html>";
//  starting a server at port 80
WebServer server(80);
void handleRoot(){
// (192.168.1.1/){
  server.send(200, "text/html", html); //here 200 is Success code 
}

void handleNotFound() {
  
  String message = "File Not Found  ";
  message += "URI: "; // (192.168.1.1/page1/on)
  message += server.uri();
  message += " Method: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += " Arguments: ";
  message += server.args();
  message += " ";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + " ";
  }
  server.send(404, "text/plain", message);
 
}

void setup(void){

  //  setting frequency and resolution at channels
  ledcSetup(r_channel , frequency , resolution);
  ledcSetup(g_channel , frequency , resolution);
  ledcSetup(b_channel , frequency , resolution);

  //  attaching GPIOs
  ledcAttachPin(r_pin , r_channel);
  ledcAttachPin(g_pin , g_channel);
  ledcAttachPin(b_pin , b_channel);

  //   starting serial communication
  Serial.begin(115200);

  //  connecting with the WiFi and printing IP Address
  Serial.print("Connecting with : ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid , password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with the Network !");
  Serial.print("IP address assgined by the access point : ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) { //esp32.local/
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  
  server.on("/red", []() {
    server.send(200, "text/html",html);
    color_generator(255,0,0);
  });

  server.on("/green", []() {
    server.send(200, "text/html",html);
    color_generator(0,255,0);
  });
  server.on("/blue", []() {
    server.send(200, "text/html",html);
    color_generator(0,0,255);
  });
  server.on("/yellow", []() {
    server.send(200, "text/html",html);
    color_generator(255,255,0);
  });
  server.on("/cyan", []() {
    server.send(200, "text/html",html);
    color_generator(0,255,255);
  });
  server.on("/magenta", []() {
    server.send(200, "text/html",html);
    color_generator(255,0,255);
  });
  server.on("/orange", []() {
    server.send(200, "text/html",html);
    color_generator(255,69,0);
  });
  server.on("/off", []() {
    server.send(200, "text/html",html);
    color_generator(0,0,0);
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  server.handleClient();
}

void color_generator(byte r , byte g , byte b){
  ledcWrite(r_channel , r);
  ledcWrite(g_channel , g);
  ledcWrite(b_channel , b);
}


//  generating HTML Page
String generate_html(void){
  
  String html = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>ESP32 RGB CONTROLLER</title></head><body><div style=\"padding-left: 50%; padding-top: 10%;\"><h1>COLOR GENERATOR</h1></div><div style=\"padding-left: 40%;\"><a href=\"/red\"><button>Red</button></a><a href=\"/green\"><button>Green</button></a><a href=\"/blue\"><button>Blue</button></a><a href=\"/yellow\"><button>Yellow</button></a><a href=\"/cyan\"><button>Cyan</button></a><a href=\"/magenta\"><button>Magenta</button></a><a href=\"/orange\"><button>Orange</button></a></div></body></html>";
}