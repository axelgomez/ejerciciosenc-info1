/*
 * azm_kit.h
 *
 */
#include "derivative.h"


#ifndef AZM_KIT_H_
#define AZM_KIT_H_

//---------------------------------------------------------------------
// defines
//---------------------------------------------------------------------

#define LED_VERDE		PTCD_PTCD2
#define LED_ROJO		PTCD_PTCD4
#define LED_AMARILLO	PTFD_PTFD0
#define LED_BLANCO		PTFD_PTFD5
#define SW_S2			PTGD_PTGD0
#define SW_S3			PTGD_PTGD1
#define BUZZER			PTFD_PTFD4
#define DATOS_7SEG      PTED

#define ERROR			65535
#define SUCCESS			0

#define BUZZER_ON		1
#define BUZZER_OFF		0
#define LED_ON			0
#define LED_OFF			1
#define VERDE			1
#define ROJO			2
#define AMARILLO		3
#define BLANCO			4
#define S2				5
#define S3				6
#define PRESET_R17		10
#define PRESET_R18		20
#define SENSOR			30
#define PRESET_R17_AD	8
#define PRESET_R18_AD	9
#define SENSOR_AD		5

// lcd inteligente
#define delay_short		250
#define delay_long		5000
#define BUSY			1
#define NBUSY			0

#define RS 				PTED_PTED0	            		// Register select 
#define RW				PTED_PTED1						// read/write lcd char
#define E1	 			PTED_PTED2         				// Enable chip1
#define DB4 			PTED_PTED4						// mode 4 bit 
#define DB5				PTED_PTED5
#define DB6	 			PTED_PTED6
#define DB7	 			PTED_PTED7 

#define BACKLIGHT	PTGD_PTGD3 

#define ADC_CANAL8      0x48
#define ADC_CANAL9      0x49
#define ADC_LM35        0x45

//---------------------------------------------------------------------
// Prototipos
//---------------------------------------------------------------------
unsigned int Led_On(unsigned char lo);
unsigned int Led_Off(unsigned char lo);
unsigned int Read_Switch(unsigned char lo);
unsigned int Lcd_7Segment(unsigned char lo);
unsigned int Read_Preset(unsigned char pr);
unsigned int Read_Sensor(void);
unsigned int Bright_Power_Led(unsigned char b);

void Beep(unsigned int b);
void Delay_mseg(unsigned int mseg);

void inicio_puertos(void);
void inicio_cop_lvi_irq(void);
void inicio_osc(void);
void inicio_rtc(void);
void inicio_kbi(void);
void inicio_sci2(unsigned int br);
void sci2_byte(unsigned char sci_tx);
void sci2_string(unsigned char *dato);
void inicio_adc(void);
void Init_MCU(void);

//---------------------------------------------------------------------
// Prototipos lcd inteligente
//---------------------------------------------------------------------
void nibble_lcd4(unsigned char nb);
unsigned char check_busy4(void);
void mode4bit(void);		// mode 4bit
void write_com_lcd4(unsigned char w4b);
void ClearDisplay4(void);
void ReturnHome4(void);
void EntryModeSet4(unsigned char ems);
void DisplayOnOff4(unsigned char dof);
void CurDisShift4(unsigned char cdf);
void FuntionSet4(unsigned char fs);
void SetCGRAMAddress4(unsigned char sca);
void SetDDRAMAddress4(unsigned char sda);
void write_data_lcd4(unsigned char wd);
unsigned char read_data_lcd4(void);
void lcd_char_init4(void);
void lcd_init4(void);
unsigned int Line_Lcd4(unsigned char *p,unsigned char r);



#endif /* AZM_KIT_H_ */
