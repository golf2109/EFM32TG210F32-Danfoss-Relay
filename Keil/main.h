#include "em_device.h"
#include "em_chip.h"
#include "em_system.h"   
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_leuart.h"
#include "em_timer.h"
#include "InitDevice.h"
//#include "retargetserial.h"
#include "danfoss.h"
#include <stdio.h>

uint8_t	in_byte;
uint8_t  in_rel[3];
uint8_t  in_fr[4];
uint8_t	temp0,temp1,temp2,temp3,test_irq=0,test_irq_uart_rx, test_irq_uart_tx, test_irq_LEUART;
uint8_t  receive[8]={0};
uint8_t  data[6] = {0x01, 0x06, 0x3E, 0xB1, 0x05, 0x00};
uint16_t  len=6;
uint8_t	uart1_TX[16]={0};
uint8_t	uart1_RX[16]={0};
uint8_t uart_test_RX[16]={0};
uint16_t crcsum;
const char test_string[] = "\n\rHello World!\n\r";
char rx_char;
uint16_t freq;

volatile uint32_t msTicks;                      /* counts 1ms timeTicks       */
uint8_t  clock_1s;                              /* Flag activated each second */

uint8_t  cmd_receive, crc_calc, crc_data, len_l_receive, len_h_receive, crc_receive, stop_receive;  				

uint8_t  data_receive[20];
uint16_t  data_len;
uint16_t  len_packet;

uint8_t  test_crc[6];
uint16_t  calc_test_crc;

uint8_t  counter_from_danfoss;
