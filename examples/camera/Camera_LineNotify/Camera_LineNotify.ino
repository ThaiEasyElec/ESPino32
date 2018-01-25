#include "LineNotify.h"
#include "Camera_Exp.h"
CAMERA cam;
const char* ssid = "your network SSID";    //  your network SSID (name)
const char* pass = "your network password";   // your network password
#define LINE_TOKEN "yout Token"

#define BUTTON_MASSAGE 26
#define BUTTON_PICTURE 19
#define BUTTON_STICKER 23


LINENOTIFY line;
void setup() 
{
  pinMode(BUTTON_MASSAGE,INPUT);
  pinMode(BUTTON_PICTURE,INPUT);
  pinMode(BUTTON_STICKER,INPUT);
  Serial.begin(115200);
  Serial.println("\r\nHello Line Notify");
  cam.setFrameSize(CAMERA_FS_QVGA);
  cam.setMirror(false);
  cam.setVflip(false);
  cam.setWhiteBalance(true);
  esp_err_t err = cam.init();
  if (err != ESP_OK)
  {
    Serial.println("Camera init failed with error =" + String( err));
    return;
  }
  WiFi.begin(ssid, pass);
  unsigned char led_cnt=0;
  while (WiFi.status() != WL_CONNECTED) 
  {
     Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  String res;
  if(!digitalRead(BUTTON_MASSAGE))
   {
      Serial.println("Send Messgae");
      res = line.sendMessage(LINE_TOKEN,"สวัสดีครับ Hello");
      Serial.println(res);
   }
   if(!digitalRead(BUTTON_PICTURE))
   {
      Serial.println("Send Picture");
      esp_err_t err;
      err = cam.capture();
      if (err == ESP_OK)
      {
        res = line.sendImage(LINE_TOKEN,"Take Picture",cam.getfb(),cam.getSize());
        Serial.println(res);
      }
      else
        Serial.println("Camera Error");
   }
    if(!digitalRead(BUTTON_STICKER))
   {
       Serial.println("Send Sticker");
      res = line.sendSticker(LINE_TOKEN,"ส่งสติ๊กเกอร์",2,509);
      Serial.println(res);
   }

}
