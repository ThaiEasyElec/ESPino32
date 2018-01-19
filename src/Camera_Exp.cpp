#include "Camera_Exp.h"
#include "camera.h"


void CAMERA :: setFrameSize(unsigned char fs_siz)
{
	framsize = fs_siz;
}
esp_err_t CAMERA :: init()
{
	camera_config_t config; 
	 config.ledc_channel = LEDC_CHANNEL_0;
        config.ledc_timer = LEDC_TIMER_0;
        config.pin_d0 = CONFIG_D0;
        config.pin_d1 = CONFIG_D1;
        config.pin_d2 = CONFIG_D2;
        config.pin_d3 = CONFIG_D3;
        config.pin_d4 = CONFIG_D4;
        config.pin_d5 = CONFIG_D5;
        config.pin_d6 = CONFIG_D6;
        config.pin_d7 = CONFIG_D7;
        config.pin_xclk = CONFIG_XCLK;
        config.pin_pclk = CONFIG_PCLK;
        config.pin_vsync = CONFIG_VSYNC;
        config.pin_href = CONFIG_HREF;
        config.pin_sscb_sda = CONFIG_SDA;
        config.pin_sscb_scl = CONFIG_SCL;
        config.pin_reset = CONFIG_RESET;
        config.xclk_freq_hz = CONFIG_XCLK_FREQ;
        config.pixel_format = CAMERA_PF_JPEG;
        config.frame_size =  (camera_framesize_t)framsize;          //CAMERA_FS_VGA;//CAMERA_FS_SVGA;//CAMERA_FS_VGA,
        config.jpeg_quality = 15;
        config.mirror = set_mirror;
	    config.vflip = set_vflip;
		
		config.whitebal = set_whitebal;
		esp_err_t err = camera_init(&config);
		
		return(err);
}

esp_err_t CAMERA ::capture() 
{
	return(camera_run());
}

size_t CAMERA :: getSize()
{
	return(camera_get_data_size()-1);
}
uint8_t* CAMERA :: getfb()
{
	return(camera_get_fb());
}
void CAMERA :: setMirror(unsigned char enable)
{
	set_mirror = enable;
}
void CAMERA :: setVflip(unsigned char enable)
{
	set_vflip = enable;
}
void CAMERA :: setWhiteBalance(unsigned char enable)
{
	set_whitebal = enable;
}