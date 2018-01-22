
#include "Display.h"
ILI9341 Lcd;
#include "Camera_Exp.h"
CAMERA cam;
uint8_t *data;
void setup() 
{
  Serial.begin(115200);
  Lcd.begin();
  Lcd.fillScreen(BLACK);
  Lcd.printf("hello world");
  delay(500);
  cam.setFrameSize(CAMERA_FS_QVGA);   //320x240
  esp_err_t err = cam.init();
  if(err != ESP_OK)
  {
    Serial.println("Camera init failed with error ="+String( err));
    return;
  }
}
void loop() 
{
  esp_err_t err;
  err = cam.capture();
  if (err != ESP_OK) 
  Serial.println("Camera capture failed with error ="+String(err));
  Lcd.drawJpg(cam.getfb(),cam.getSize());
}
