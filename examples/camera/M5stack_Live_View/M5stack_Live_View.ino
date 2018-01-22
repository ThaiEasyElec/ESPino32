#include <M5Stack.h>
#include <WiFi.h>

const char* ssid     = "ESPINOCam";
const char* password = "12345678";
const char* host = "192.168.4.1";

#define BUFSIZE 30000
uint8_t buf[BUFSIZE];
unsigned int cnt=0;
bool flag_stream = false;

void setup()
{
  M5.begin();
  Serial.begin(115200);
  M5.Lcd.setBrightness(200);
  M5.lcd.drawBitmap(0, 0, 320, 240, (uint16_t *)gImage_logoM5);
  delay(2000);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    m5.Lcd.printf(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  m5.Lcd.printf("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{

  if (M5.BtnA.wasPressed())
  {
    getpic();
  }
  if (M5.BtnB.wasPressed())
  {
    flag_stream = true;
  }
  if(flag_stream)
  {
    getpic();
  }
  exit_stream();
  M5.update();
}
void exit_stream()
{
  if (M5.BtnC.wasPressed())
  {
    flag_stream = false;
    M5.Lcd.fillScreen(BLACK);
  }
}

void getpic()
{
  Serial.print("connecting to ");
    Serial.println(host);
    WiFiClient client;
    const int Port = 80;
    if (!client.connect(host, Port))
    {
      Serial.println("connection failed");
      return;
    }
    client.println("GET");
    unsigned long timeout = millis();
   cnt=0;
   bool flag =true;
   while(flag)
   {
    exit_stream();
    if(client.available())
    {
      buf[cnt] = client.read();
      if(cnt>3)
      {
        if((buf[cnt]=='d')&&(buf[cnt-1]=='n')&&(buf[cnt-2]=='E'))
        {
          Serial.println("End...");
          //client.stop();
          M5.Lcd.drawJpg(buf,cnt-5);
           flag =false;
        }
      }
       M5.update();
      cnt++;
    }
   }
   client.stop();
}

