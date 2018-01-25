#ifndef _TEECAM_H_
#define _TEECAM_H_


#include "camera.h"


#define   CONFIG_D0     33
#define   CONFIG_D1     39
#define   CONFIG_D2     36
#define   CONFIG_D3     32
#define   CONFIG_D4     34
#define   CONFIG_D5     35
#define   CONFIG_D6     04
#define   CONFIG_D7     15
#define   CONFIG_XCLK   13
#define   CONFIG_PCLK   12
#define   CONFIG_VSYNC  14
#define   CONFIG_HREF   27
#define   CONFIG_SDA    21
#define   CONFIG_SCL    22
#define   CONFIG_RESET  25


/*
#define   CONFIG_D0      13
#define   CONFIG_D1      15
#define   CONFIG_D2      2
#define   CONFIG_D3      4
#define   CONFIG_D4      35
#define   CONFIG_D5      34
#define   CONFIG_D6      33
#define   CONFIG_D7      32
#define   CONFIG_XCLK    18
#define   CONFIG_PCLK    17
#define   CONFIG_VSYNC   36
#define   CONFIG_HREF    39
#define   CONFIG_SDA     21
#define   CONFIG_SCL     22
#define   CONFIG_RESET   27
*/

#define   CONFIG_XCLK_FREQ  10000000

class CAMERA
{
public:
  CAMERA()
  {
		framsize = CAMERA_FS_VGA ;
		set_mirror=0;
		set_vflip=0;
		set_whitebal=0;
  };
  esp_err_t init();
  void setFrameSize(unsigned char fs_siz);
  size_t getSize();
  esp_err_t capture(); 
  uint8_t* getfb();
  void setMirror(unsigned char enable);
  void setVflip(unsigned char enable);
  void setWhiteBalance(unsigned char enable);

private:
	unsigned char framsize;
	unsigned char set_mirror;
	unsigned char set_vflip;
	unsigned char set_whitebal;
};

























#endif