#include "LineNotify.h"
#include <Arduino.h>
#include <WiFiClientSecure.h>

LINENOTIFY::LINENOTIFY()
{
	
}
String LINENOTIFY::sendMessage(String token,String message)
{
	String bodyTxt = body("message",message)+String("--")+ LINE_BOUNDARY+String("--\r\n");
	String data =  header(token,bodyTxt.length())+bodyTxt;
	Debug(data);	
	return(sendData(data));
}
String LINENOTIFY::sendSticker(String token,String message,unsigned int stickerPackage,unsigned int stickerID)
{
	String bodyTxt  = body("message",message);
	       bodyTxt += body("stickerPackageId",String(stickerPackage));
		   bodyTxt += body("stickerId",String(stickerID));
		   bodyTxt += String("--")+LINE_BOUNDARY+String("--\r\n");
	String data =  header(token,bodyTxt.length())+bodyTxt;
	Debug(data);	
	return(sendData(data));
}
String LINENOTIFY::sendImage(String token,String message, uint8_t *data_pic,size_t size_pic)
{
	String bodyTxt =  body("message",message);
	String bodyPic =  body("imageFile",message);
	String bodyEnd =  String("--")+LINE_BOUNDARY+String("--\r\n");
	size_t allLen = bodyTxt.length()+bodyPic.length()+size_pic+bodyEnd.length();
	String headerTxt =  header(token,allLen);
	WiFiClientSecure client;
	 if (!client.connect(LINE_SERVER,LINE_PORT)) 
	 {
		Debugln("connection failed");
		return("connection failed");   
	 }
	 
	 client.print(headerTxt+bodyTxt+bodyPic);
	 client.write(data_pic,size_pic);
	 client.print("\r\n"+bodyEnd);
	 
	 delay(20);
	 long tOut = millis() + LINE_TIMEOUT;
	 while(client.connected() && tOut > millis()) 
	 {
		if (client.available()) 
		{
			String serverRes = client.readStringUntil('\r');
			Debug(serverRes);
			 if(serverRes.indexOf("\"status\"")!=-1)
			{
				Debugln("Send Success");
				return(serverRes);
			}
		}
	 }
	 Debugln("TimeOut No Response From Server");
	 return("TimeOut");
}
String LINENOTIFY::header(String token,size_t length)
{
	String  data;
			data =  F("POST /api/notify HTTP/1.1\r\n");
			data += F("cache-control: no-cache\r\n");
			data += F("Postman-Token: 62d00e94-8de0-45c6-9353-b96c3d228f4d\r\n");
			data += F("Authorization: Bearer ");
			data += token;
			data += F("\r\n");
			data += F("Content-Type: multipart/form-data; boundary=");
			data += LINE_BOUNDARY;
			data += "\r\n";
			data += F("User-Agent: PostmanRuntime/6.4.1\r\n");
			data += F("Accept: */*\r\n");
			data += F("Host: ");
			data += LINE_SERVER;
			data += F("\r\n");
			data += F("accept-encoding: gzip, deflate\r\n");
			data += F("Connection: keep-alive\r\n");
			data += F("content-length: ");
			data += String(length);
			data += "\r\n";
			data += "\r\n";
    return(data);
}
String LINENOTIFY::body(String content , String message)
{
	String data;
	data = "--";
	data += LINE_BOUNDARY;
	data += F("\r\n");
	if(content=="imageFile")
	{
		data += F("Content-Disposition: form-data; name=\"imageFile\"; filename=\"picture.jpg\"\r\n");
		data += F("Content-Type: image/jpeg\r\n");
		data += F("\r\n");
	}
	else
	{
		data += "Content-Disposition: form-data; name=\"" + content +"\"\r\n";
		data += "\r\n";
		data += message;
		data += "\r\n";
	}
	 return(data);
}
String LINENOTIFY::sendData(String data)
{
	 WiFiClientSecure client;
	 if (!client.connect(LINE_SERVER,LINE_PORT)) 
	 {
		Debugln("connection failed");
		return("connection failed");  
	 }
	 client.print(data);
	 delay(20);
	 long tOut = millis() + LINE_TIMEOUT;
	 while(client.connected() && tOut > millis()) 
	 {
		if (client.available()) 
		{
			String serverRes = client.readStringUntil('\r');
			Debug(serverRes);
			 if(serverRes.indexOf("\"status\"")!=-1)
			{
				Debugln("Send Success");
				return(serverRes);
			}
		}
	 }
	 Debugln("TimeOut No Response From Server");
	 return("TimeOut");
	 
}
void LINENOTIFY::Debugln(String str)
{
	Debug(str+"\r\n");
}
void LINENOTIFY::Debug(String str)
{
	if(!SerialDebug)
		return;
	Serial.print(str);
}