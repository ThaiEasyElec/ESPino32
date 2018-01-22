#include <WiFi.h>
#include "Camera_Exp.h"
CAMERA cam;
const char *ssid = "ESPINOCam";
const char *password = "12345678";
WiFiServer server(80);
void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  cam.setFrameSize(CAMERA_FS_QVGA);   //320x240
  cam.setMirror(false);
  cam.setVflip(false);
  cam.setWhiteBalance(false);
  
  esp_err_t err = cam.init();
  if(err != ESP_OK)
  {
    Serial.println("Camera init failed with error ="+String( err));
    return;
  }
  server.begin();
}

void loop() 
{
  
     WiFiClient client = server.available(); 
      if (client) 
      {
        Serial.println("New Client.");
        String currentLine = "";
        while (client.connected()) 
        {
           if (client.available()) 
           {
               String str = client.readStringUntil('\n');
               if(str.indexOf("GET")!= -1)
               {
                    esp_err_t err = cam.capture();
                    if (err != ESP_OK) 
                    {
                        Serial.println("Camera capture failed with error ="+String(err));
                    } 
                    else
                    {
                      Serial.println("Capture OK");
                      client.write(cam.getfb(),cam.getSize());
                      client.println("End");
                    }
               } 
           }
        }
      }
}


