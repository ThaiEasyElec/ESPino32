#ifndef _LINENOTIFY_H_
#define _LINENOTIFY_H_

#include <WiFiClientSecure.h>

#define SerialDebug			0
#define LINE_SERVER 		"notify-api.line.me"
#define LINE_PORT			443
#define LINE_BOUNDARY 		"--------------------------133747188241686651551404" 	
#define LINE_TIMEOUT    	10000

class LINENOTIFY
{
public:
	LINENOTIFY();
	String sendMessage(String token,String message);
	String sendSticker(String token,String message,unsigned int stickerPackage,unsigned int stickerID);
	String sendImage(String token,String message, uint8_t *data_pic,size_t size_pic);
private:
	String header(String token,size_t length);
	String body(String content,String message);
	String sendData(String data);
	void Debugln(String str);
	void Debug(String str);
};












































#endif