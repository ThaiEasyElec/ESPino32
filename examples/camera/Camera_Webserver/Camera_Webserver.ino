#include "Camera_Exp.h"
#include <WiFi.h>

CAMERA cam;
char ssid[] = "yourNetwork";      //  your network SSID (name)
char pass[] = "secretPassword";   // your network password
WiFiServer server(80);

String http_header = "HTTP/1.1 200 OK\r\n";
String http_stream = "Content-type: multipart/x-mixed-replace; boundary=123456789000000000000987654321\r\n\r\n";
String http_jpg = "Content-type: image/jpg\r\n\r\n";
String http_boundary = "--123456789000000000000987654321\r\n";
WiFiClient client;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  cam.setFrameSize(CAMERA_FS_VGA);
  esp_err_t err = cam.init();
  if (err != ESP_OK)
  {
    Serial.println("Camera init failed with error =" + String( err));
    return;
  }

Serial.println("Open Web Browser");
Serial.print("Get for single frame --> http://");//http://192.168.0.102/capture
Serial.print(WiFi.localIP());
Serial.println("/capture");

Serial.print("Stream  --> http://");//http://192.168.0.102/capture
Serial.print(WiFi.localIP());
Serial.println("/stream");


}

void loop()
{
  String httpreq;
  client = server.available();
  if (client)
  {
    Serial.println("New Client.");
    String httpreq = "";
    while (client.connected())
    {
      if (client.available())
      {
        String httpreq_line = client.readStringUntil('\n');
        httpreq += httpreq_line;
        if (httpreq_line == "\r")
        {
          if (httpreq.indexOf("GET /stream") != -1)
          {
                Serial.println("Stream");
                stream();
          }
          if (httpreq.indexOf("GET /capture") != -1)
          {
                Serial.println("Capture");
                capture();
          }
          
          httpreq = "";
          client.stop();
        }

      }
    }

  }
}

void stream()
{
  client.print(http_header);
  client.print(http_stream);  
  while (client.connected())
  {
    esp_err_t err;
    err = cam.capture();
    if (err != ESP_OK)
    {
      Serial.println("Camera capture failed with error =" + String(err));
      return;
    }
    client.print(http_jpg);
    client.write(cam.getfb(),cam.getSize());
    client.print(http_boundary);
  }
}
void capture()
{
   esp_err_t err;
    err = cam.capture();
    if (err != ESP_OK)
    {
      Serial.println("Camera capture failed with error =" + String(err));
      return;
    }
   client.print(http_header);
   client.print(http_jpg);
   client.write(cam.getfb(),cam.getSize());
   
}
