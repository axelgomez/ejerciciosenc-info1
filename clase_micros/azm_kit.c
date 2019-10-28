/*
 * azm_kit.c
 *
 */

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "azm_kit.h"

//---------------------------------------------------------------------
// variables globales
//---------------------------------------------------------------------
unsigned char TRIM_32KHz @0xFFAF;							// 32 kHz ICGTRM value
							  // 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   .
unsigned char tabla_7seg[12]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x10,0x7F};
unsigned int mseg=0, adc_ch8, adc_ch9, adc_ch5;
//---------------------------------------------------------------------
// funciones
//---------------------------------------------------------------------
//*********************************************************************
//---------------------------------------------------------------------
// unsigned int Led_On(unsigned char lo)
// Parametro -> lo = Color de LED (VERDE, ROJO, AMARILLO, BLANCO)
// Devuelve  -> SUCCESS ó 0, ERROR ó 255
//---------------------------------------------------------------------
unsigned int Led_On(unsigned char lo){
	if(lo == VERDE){
		LED_VERDE = LED_ON;
		return SUCCESS;
	}
	if(lo == ROJO){
		LED_ROJO = LED_ON;
		return SUCCESS;
	}
	if(lo == AMARILLO){
		LED_AMARILLO = LED_ON;
		return SUCCESS;
	}
	if(lo == BLANCO){
		Bright_Power_Led(100);
		return SUCCESS;
	}
	return ERROR;
}
//*********************************************************************
//---------------------------------------------------------------------
// unsigned int Led_Off(unsigned char lo)
// Parametro -> lo = Color de LED (VERDE, ROJO, AMARILLO, BLANCO)
// Devuelve  -> SUCCESS ó 0, ERROR ó 255
//---------------------------------------------------------------------
unsigned int Led_Off(unsigned char lo){
	if(lo ==  VERDE){
		LED_VERDE = LED_OFF;
		return SUCCESS;
	}
	if(lo ==  ROJO){
		LED_ROJO = LED_OFF;
		return SUCCESS;
	}
	if(lo ==  AMARILLO){
		LED_AMARILLO = LED_OFF;
		return SUCCESS;
	}
	if(lo ==  BLANCO){
		Bright_Power_Led(0);
		return SUCCESS;
	}
	return ERROR;
}
//*********************************************************************
//---------------------------------------------------------------------
// unsigned char Read_Switch(unsigned char lo)
// Parametro -> lo = S2 (switch S2) ó S3 (switch S3)
// Devuelve  -> Estado logico del switch 0, 1 ó ERROR si es distinto a S2 o S3
//---------------------------------------------------------------------
unsigned int Read_Switch(unsigned char lo){
	if(lo ==  S2) return SW_S2;
	if(lo ==  S3) return SW_S3;
	return ERROR;
}		 	
//*********************************************************************
//---------------------------------------------------------------------
// unsigned char Lcd_7Segment(unsigned char lo)
// Parametro -> lo = de 0 a 9 
// Devuelve  -> SUCCESS ó 0, ERROR ó 255 si esta fuera de rango
//---------------------------------------------------------------------
unsigned int Lcd_7Segment(unsigned char lo){
	if(lo < 10){
		DATOS_7SEG = tabla_7seg[lo];
		return SUCCESS;
	}
	return ERROR;
}
//*********************************************************************
//---------------------------------------------------------------------
// void Beep(unsigned int b)
// Parametro -> b = tiempo que activa el buzzer en milisegundos (Maximo 65535)
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void Beep(unsigned int b){
	BUZZER = BUZZER_ON;
	Delay_mseg(b);
	BUZZER = BUZZER_OFF;
}
//*********************************************************************
//---------------------------------------------------------------------
// void Delay_mseg(unsigned int ms)
// Parametro -> mseg = tiempo de demora en milisegundos (Maximo 65535)
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void Delay_mseg(unsigned int ms){
	mseg = ms;
	while(mseg!=0);										
}
//*********************************************************************
//---------------------------------------------------------------------
// void Init_S08JM(void) -- configura perifericos segun AZM_KIT
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void Init_S08JM(void){
	inicio_cop_lvi_irq();
	inicio_osc();
	inicio_puertos();
	inicio_rtc();
	inicio_adc();
	lcd_char_init4();
	DATOS_7SEG = 0xFF;
	EnableInterrupts;
}
//*********************************************************************
//---------------------------------------------------------------------
// void inicio_puertos(void) -- configura puertos segun AZM_KIT
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void inicio_puertos(void){
	PTAD = 0;										// salidas=0
	PTADD = 0xFF;									// configuro salidas
	PTAPE = 0xFF;									// habilito pullup
	PTASE = 0xFF;

	PTBD = 0;										// salidas=0
	PTBDD = 0xFF;									// configuro salidas
	PTBPE = 0xFF;									// habilito pullup
	PTBSE = 0xFF;

	PTCD = 0x14;									// salidas=0
	PTCDD = 0xFF;									// configuro salidas
	PTCPE = 0xFF;									// habilito pullup
	PTCSE = 0xFF;

	PTDD = 0;										// salidas=0
	PTDDD = 0xFF;									// configuro salidas
	PTDPE = 0xFF;									// habilito pullup
	PTDSE = 0xFF;

	PTED = 0xFF;										// salidas=0
	PTEDD = 0xFF;									// configuro salidas
	PTEPE = 0xFF;									// habilito pullup
	PTESE = 0xFF;

	PTFD = 1;										// salidas=0
	PTFDD = 0xFF;									// configuro salidas
	PTFPE = 0xFF;									// habilito pullup
	PTFSE = 0xFF;

	PTGD = 0;										// salidas=0
	PTGDD = 0xFC;									// configuro salidas, PTG0/1 entrada
	PTGPE = 0xFF;									// habilito pullup
	PTGSE = 0xFF;
}
//*********************************************************************
//---------------------------------------------------------------------
// void inicio_cop_lvi_irq(void) -- configura LVI,COP, IRQ pin segun AZM_KIT
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void inicio_cop_lvi_irq(void){
    IRQSC = 0;                                      // IRQ disable
    SOPT1 = 0;                                      // cop disable
    SOPT2 = 0;                      
    SPMSC1 = 0;                                     // LVD disable
    SPMSC2 = 0;
}
//*********************************************************************
//---------------------------------------------------------------------
// void inicio_osc(void) -- Osc fecuencia de bus en 8MHz
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void inicio_osc(void){								
	MCGTRM = TRIM_32KHz;
	MCGC2 = 0x40;									// Fref = 31.25KHz; BDIV=1; VDIV=4; R=1;
	MCGC1 = 0x04;									// M = VDIV * 256 ;
	MCGC3 = 0x01;									// FLL = M * fref / R ; Fbus = (FLL/BDIV) / 2
	while(MCGSC_LOCK == 0) ; 						// espera enganche FLL
}
//*********************************************************************
//---------------------------------------------------------------------
// void inicio_rtc(void) -- rtc en 1mseg
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void inicio_rtc(void){
	RTCMOD = 0;
	RTCSC = 0x18;									// RTCLKS=00->1Khz,RTIE=1,RTCPS=0x8->1mseg
}
//*********************************************************************
//---------------------------------------------------------------------
// void inicio_kbi(void) -- habilita kbi S2 y S3
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void inicio_kbi(void){
	KBISC = 0x04;									// KBACK=1
	KBIPE = 0x03;									// KBP0=1,KBP1=1
	KBIES = 0x00;									// KBP0 Y KBP1  Falling edge/low level
	KBISC = 0x07;									// KBACK=1,KBIE=1,KMOD=1
}
//*********************************************************************
//---------------------------------------------------------------------
// void inicio_sci2(void) -- Habilita SCI2
// Parametro -> br -> selecciona baud rate
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void inicio_sci2(unsigned int br){
	unsigned char a;
	SCI2S1 = SCI2S1;
	a = SCI2D;
	SCI2BD = (int)(500000/br); 	// Baud Rate = BUSCLK / ([SBR12:SBR0] x 16)=(8M/16)/br
	SCI2C1 = 0x00; 			// Loop mode disabled, disable SCI, Tx output not inverted,
	SCI2C2 = 0x2C; 			// Enable SCI receive interrupts, Enable transmitter and
	SCI2C3 = 0x00; 			// Disable all error interrupts 
}
//*********************************************************************
//---------------------------------------------------------------------
// void sci2_byte(void) -- envia un byte por sci2
// Parametro -> sci_tx = byte a enviar
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void sci2_byte(unsigned char sci_tx){
  SCI2D = sci_tx;             						// cargo el buffer del transmisor
  while(SCI2S1_TC==0);        						// espero completar la transmision   
}
//*********************************************************************
//---------------------------------------------------------------------
// void sci2_string(void) -- envia una cadena de caracteres por sci2
// Parametro -> *dato = cadena a enviar
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void sci2_string(unsigned char *dato){
  while(*dato != '\0') sci2_byte(*(dato++)); 		// envia datos por SCI
}
//*********************************************************************
//---------------------------------------------------------------------
// void inicio_adc(void) -- habilita ADC
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void inicio_adc(void){
	APCTL1 = 0x20;
	APCTL2 = 0x03;									
	ADCCFG = 0x69;								// 10bit,clock/4,bus_clock/2,high speed
	ADCSC2 = 0;										// trigger soft, 
	ADCSC1 = 0x48;								// habilito Int, conversion simple
}
//*********************************************************************
//---------------------------------------------------------------------
// unsigned int Read_preset(unsigned char pr) -- lectura del ADC
// Parametro -> PRESET_R17,PRESET_R18 y SENSOR
// Devuelve  -> valor de 0 a 1024 o ERROR
//---------------------------------------------------------------------
unsigned int Read_Preset(unsigned char pr){
	unsigned char ax,ch; 
	unsigned int valor=0;
	if(pr==PRESET_R17) return adc_ch8;
	if(pr==PRESET_R18) return adc_ch9;
	return ERROR;
}
//*********************************************************************
//---------------------------------------------------------------------
// unsigned int Read_sensor(void) -- lectura de sensor de temp
// Parametro -> No aplica
// Devuelve  -> valor de 0C a 150C
//---------------------------------------------------------------------
unsigned int Read_Sensor(void){
	unsigned int temp;
	return adc_ch5/2;
}
//*********************************************************************
//---------------------------------------------------------------------
//----------- Declaracion de interrupciones 
interrupt 29 void RTC_ISR(void){
	RTCSC_RTIF = 1;									// limpio la bandera
	if(mseg != 0) mseg--;							// decrementa segundos
}
interrupt 26 void ADC_ISR(void){
	if(ADCSC1 == (ADC_CANAL8 | 0x80)){
		adc_ch8 = ADCR;
		ADCSC1 = ADC_CANAL9;
	}
	if(ADCSC1 == (ADC_CANAL9 | 0x80)){
		adc_ch9 = ADCR;
		ADCSC1 = ADC_LM35;
	}
	if(ADCSC1 == (ADC_LM35 | 0x80)){
		adc_ch5 = ADCR;
		ADCSC1 = ADC_CANAL8;
	}
}
//*********************************************************************
//---------------------------------------------------------------------



//*********************************************************************
//---------------------------------------------------------------------
// Funciones display inteligente
//*********************************************************************
//---------------------------------------------------------------------
//void delay(unsigned int dl) -- demora por software
// Parametro -> valor desde 0 a 65355
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void delay(unsigned int dl){
	unsigned int d;
	for(d=0;d<dl;d++);
}
//*********************************************************************
//---------------------------------------------------------------------
// nibble_lcd4(unsigned char nb) -- Envia nibble bajo 
// Parametro -> byte
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void nibble_lcd4(unsigned char nb){
	nb &= 0x0F;
	DB7 = (nb>>3 & 1);
	DB6 = (nb>>2 & 1);
	DB5 = (nb>>1 & 1);
	DB4 = (nb & 1);
}
//*********************************************************************
//---------------------------------------------------------------------
// void write_com_lcd4(unsigned char wb) -- Comando para LCD
// Parametro -> byte a transmitir
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void write_com_lcd4(unsigned char wb){
	RS = 0;
	RW = 0;
	nibble_lcd4(wb >> 4);		//data h
	E1 = 1;
	delay(delay_short);
	E1 = 0;
	nibble_lcd4(wb);			//data l
	E1 = 1;
	delay(delay_short);
	E1 = 0;
	delay(delay_short);
}
//*********************************************************************
//---------------------------------------------------------------------
// void write_dar_lcd4(unsigned char wb) -- Comando para LCD
// Parametro -> byte a transmitir
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void write_data_lcd4(unsigned char wd){
	RS = 1;
	RW = 0;
	nibble_lcd4(wd >> 4);		// data h
	E1 = 1;
	delay(delay_short);
	E1 = 0;
	nibble_lcd4(wd);			// data l
	E1 = 1;
	delay(delay_short);
	E1 = 0;
	delay(delay_short);
}
//*********************************************************************
//---------------------------------------------------------------------
// void mode4bit(void) -- Coloca el LCD en modo 4bits
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void mode4bit(void){
	delay(delay_long);			
	delay(delay_long);			
	nibble_lcd4(3);
	RS = 0;
	E1 = 1;
	delay(delay_short);
	E1 = 0;
	delay(delay_short);
	nibble_lcd4(3);
	RS = 0;
	E1 = 1;
	delay(delay_short);
	E1 = 0;
	delay(delay_short);
	nibble_lcd4(2);
	RS = 0;
	E1 = 1;
	delay(delay_short);
	E1 = 0;
	delay(delay_short);				
}
//*********************************************************************
//---------------------------------------------------------------------
// void ClearDisplay4(void) -- Comando LCD
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void ClearDisplay4(void){
	write_com_lcd4(0x01);		// Display clear
	delay(delay_long);			// delay 1.53mseg
}
//*********************************************************************
//---------------------------------------------------------------------
// void ReturnHome4(void) -- Comando LCD
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void ReturnHome4(void){
	write_com_lcd4(0x02);		// Display clear
	delay(delay_long);			// delay 1.53mseg
}
//*********************************************************************
//---------------------------------------------------------------------
// void EntryModeSet4(void) -- Comando LCD
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void EntryModeSet4(unsigned char ems){
	ems &= 0x03; ems |= 0x04;
	write_com_lcd4(ems);		// Entry mode set: I/D=1-increment mode,SH=0-shift off
	delay(delay_short);			// delay 39useg
}
//*********************************************************************
//---------------------------------------------------------------------
// void DisplayOnOff4(void) -- Comando LCD
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void DisplayOnOff4(unsigned char dof){
	dof &= 0x07; dof |= 0x08;
	write_com_lcd4(dof);		// Display ON/OFF:D=1 display on,C=0 cursor off,B=0,blink off
	delay(delay_short);			// delay 39useg
}
//*********************************************************************
//---------------------------------------------------------------------
// void CurDisShift4(void) -- Comando LCD
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void CurDisShift4(unsigned char cdf){
	cdf &= 0x0C; cdf |= 0x10;
	write_com_lcd4(cdf);		// cursor display shift
	delay(delay_short);			// delay 39useg
}
//*********************************************************************
//---------------------------------------------------------------------
// void FuntionSet4(unsigned char fs) -- Comando LCD
// Parametro -> byte
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void FuntionSet4(unsigned char fs){
	fs &= 0x1C; fs |= 0x20;
	write_com_lcd4(fs);		// Funtion set: 8bit bus,N=1-1line,F=0-5x8dots
	delay(delay_short);			// delay 39useg
}
//*********************************************************************
//---------------------------------------------------------------------
// void SetCGRAMAddress4(unsigned char sca) -- Comando LCD
// Parametro -> byte
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void SetCGRAMAddress4(unsigned char sca){
	sca &= 0x3F; sca |= 0x40;
	write_com_lcd4(sca);		// Funtion set: 8bit bus,N=1-1line,F=0-5x8dots
	delay(delay_short);			// delay 39useg
}
//*********************************************************************
//---------------------------------------------------------------------
// void SetDDRAMAddress4(unsigned char sda) -- Comando LCD
// Parametro -> byte
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void SetDDRAMAddress4(unsigned char sda){
	sda &= 0x7F; sda |= 0x80;
	write_com_lcd4(sda);		// Funtion set: 8bit bus,N=1-1line,F=0-5x8dots
	delay(delay_short);			// delay 39useg
}
//*********************************************************************
//---------------------------------------------------------------------
// void lcd_char_init4(void) -- Comando LCD
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
void lcd_char_init4(void){
	RS=0;E1=0;
	BACKLIGHT=0;
	mode4bit();
	FuntionSet4(0x28);			
	DisplayOnOff4(0x0C);
	EntryModeSet4(0x06);
	ClearDisplay4();
	ReturnHome4();
	BACKLIGHT=1;
}
//*********************************************************************
//---------------------------------------------------------------------
// unsigned int line_lcd4(unsigned char *p,unsigned char r) -- Comando LCD escritura de linea
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
unsigned int Line_Lcd4(unsigned char *p,unsigned char r){
	if(r>4 || r == 0) return ERROR;
	if(r==1) r = 0;
	if(r==2) r = 0x40;
	if(r==3) r = 0x14;
	if(r==4) r = 0x54;

	SetDDRAMAddress4(r);
	r = 0;
	while(r<20){
		write_data_lcd4(*p);
		p++;
		r++;
		if(*p == 0) r = 20;
	}
	return SUCCESS;
}
//*********************************************************************
//---------------------------------------------------------------------
// void ClearDisplay4(void) -- Comando LCD
// Parametro -> No aplica
// Devuelve  -> No aplica
//---------------------------------------------------------------------
unsigned char char_read_lcd4(void){
	unsigned char l;
	l = read_data_lcd4();
	return l;
}
//*********************************************************************
//---------------------------------------------------------------------
// unsigned int Bright_Power_Led(unsigned char b) – Brillo led Blanco
// Parametro -> Porcentaje de brillo
// Devuelve  -> SUCCESS ó 0, ERROR ó 65535
//---------------------------------------------------------------------
unsigned int Bright_Power_Led(unsigned char b){
	if(b > 100) return ERROR;
	TPM2SC = 0x0B;									// bus clock=8MHZ , prescaler=8
	TPM2C1SC = 0x28;								// PWM mode, set output on channel value match
	TPM2MOD = 50000;								// 
	TPM2C1V = 500 * b;				 				//
}
//*********************************************************************
//---------------------------------------------------------------------
// 
// Parametro -> 
// Devuelve  -> 
//---------------------------------------------------------------------
