#include "main.h"

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {

  if ((msTicks++ % 1000) == 0) {                /* Set Clock1s to 1 every sec */
    clock_1s = 1;
  }
}

/*----------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *----------------------------------------------------------------------------*/
void Delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) { __NOP(); }
}

void  send_char(uint8_t data)
{
USART1->CMD |= USART_CMD_RXDIS;		
USART_IntDisable(USART1, USART_IF_RXDATAV);			
GPIO_PinOutSet(RE_TR_PORT, RE_TR_PIN);		
USART_Tx(USART1, data);	
}

void  send_danfoss(uint8_t data)
{
LEUART0->CMD |= LEUART_CMD_RXDIS;		
LEUART_IntDisable(LEUART0, LEUART_IF_RXDATAV);			
GPIO_PinOutSet(RE_DANFOSS_PORT, RE_DANFOSS_PIN);		
LEUART_Tx(LEUART0, data);	
}

int	main(void)
{
CHIP_Init();
	
//      /* Enable HFRCO, will set as HFCLK in interrupt handler for HFRCORDY */
//      CMU_OscillatorEnable(cmuOsc_HFRCO, true, false);
//      /* Set HFRCO band back to 14 Mhz*/
//
CMU_HFRCOBandSet(cmuHFRCOBand_14MHz);
	
enter_DefaultMode_from_RESET();
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1) __NOP();                          /* Capture error              */
	}
	

GPIO_PinOutClear(RE_TR_PORT, RE_TR_PIN);	
GPIO_PinOutClear(RE_DANFOSS_PORT, RE_DANFOSS_PIN);		
//GPIO_PinOutSet(RE_TR_PORT, RE_TR_PIN);
USART_IntClear(USART1, _USART_IF_MASK);
USART_IntEnable(USART1, USART_IF_RXDATAV);
USART_IntEnable(USART1, USART_IF_TXC);	
NVIC_ClearPendingIRQ(USART1_RX_IRQn);
NVIC_ClearPendingIRQ(USART1_TX_IRQn);
NVIC_EnableIRQ(USART1_RX_IRQn);	
NVIC_EnableIRQ(USART1_TX_IRQn);			
//		USART_Enable(USART, enable);
  /* Initialize USART and map LF to CRLF */
	
LEUART_IntClear(LEUART0, _LEUART_IF_MASK);
LEUART_IntEnable(LEUART0, LEUART_IF_RXDATAV);
LEUART_IntEnable(LEUART0, LEUART_IF_TXC);	
NVIC_ClearPendingIRQ(LEUART0_IRQn);
NVIC_EnableIRQ(LEUART0_IRQn);	
	
//  RETARGET_SerialInit();
//  RETARGET_SerialCrLf(1);
//  printf("Hello World\n");
crcsum = crc16(data, len);
while(1)
{
//	while(1)
//	{
//				send_danfoss(0x35);	
//		Delay(100);
//						send_danfoss(0x20);	
//		Delay(100);
//	}
	switch(cmd_receive)
	{
		case 0:
			break;
		case 1:
			cmd_receive = 0;				
//			USART_Tx(USART1, 0xE5);		
			send_char(0xE5);		
			break;
		case 2:
			cmd_receive = 0;				
//			USART_Tx(USART1, 0xE5);			
			send_char(0xE5);		
			break;
		case 3:
			cmd_receive = 0;				
//			USART_Tx(USART1, 0xE5);			
			send_char(0xE5);		
			break;		
		case 0x20:
			cmd_receive = 0;
		  start_danfoss();
//			USART_Tx(USART1, 0xE5);		
			send_char(0xE5);		
		  break;
		case 0x21:
			cmd_receive = 0;			
		  stop_danfoss();
//			USART_Tx(USART1, 0xE5);		
			send_char(0xE5);		
		  break;		
    case 0x22:			
			cmd_receive = 0;			
			set_frq_danfoss(data_receive[0], data_receive[1]);
//			USART_Tx(USART1, 0xE5);		
			send_char(0xE5);		
			break;		
    case 0x23:			
			cmd_receive = 0;			
			test_danfoss();
//			USART_Tx(USART1, 0xE5);		
			send_char(0xE5);		
			break;			
		
		default:
			break;	
	}

//in_byte = USART_Rx(USART1);	
//USART_Tx(USART1, in_byte);	
//LEUART_Tx(LEUART0, 0x55);	
//Delay(100);
//	
//LEUART_Tx(LEUART0, 0xAA);	

/*	
if (USART_Rx(USART1) ==0x01)
{
in_rel[2]=	USART_Rx(USART1);
in_rel[1]=	USART_Rx(USART1);
in_rel[0]=	USART_Rx(USART1);	
in_byte = 100*(0xF & in_rel[2]) + 10*(0xF & in_rel[1])+ (0xF &in_rel[0]);
	
if ((in_byte & 0x1)== 1){
	GPIO_PinOutSet(COM1_PORT, COM1_PIN);}
else{
	GPIO_PinOutClear(COM1_PORT, COM1_PIN);}
if ((in_byte & 0x2)== 2){
	GPIO_PinOutSet(COM2_PORT, COM2_PIN);}
else{
	GPIO_PinOutClear(COM2_PORT, COM2_PIN);}
if ((in_byte & 0x4)== 4){
	GPIO_PinOutSet(COM3_PORT, COM3_PIN);}
else{
	GPIO_PinOutClear(COM3_PORT, COM3_PIN);}
if ((in_byte & 0x8)== 8){
	GPIO_PinOutSet(COM4_PORT, COM4_PIN);}
else{
	GPIO_PinOutClear(COM4_PORT, COM4_PIN);}
if ((in_byte & 0x10)== 0x10){
	GPIO_PinOutSet(COM5_PORT, COM5_PIN);}
else{
	GPIO_PinOutClear(COM5_PORT, COM5_PIN);}
if ((in_byte & 0x20)== 0x20){
	GPIO_PinOutSet(COM6_PORT, COM6_PIN);}
else{
	GPIO_PinOutClear(COM6_PORT, COM6_PIN);}
if ((in_byte & 0x40)== 0x40){
	GPIO_PinOutSet(COM7_PORT, COM7_PIN);}
else{
	GPIO_PinOutClear(COM7_PORT, COM7_PIN);}
}

USART1->TXDATA = 0x55;
if (USART_Rx(USART1) ==0x02)
{
in_fr[3] = USART_Rx(USART1);
in_fr[2] = USART_Rx(USART1);
in_fr[1] = USART_Rx(USART1);
in_fr[0] = USART_Rx(USART1);	
freq = 1000*(0xF & in_fr[3]) + 100* (0xF & in_fr[2]) + 10*(0xF & in_fr[1]) + (0xF & in_fr[0]);
		if(freq != 0)
	{
	// Enable clock for TIMER0 //
	CMU_ClockEnable(cmuClock_TIMER0, true);	
TIMER_TopSet(TIMER0,54264/freq); 
	}
	else
	{
	// Enable clock for TIMER0 //
	CMU_ClockEnable(cmuClock_TIMER0, false);	
	}
}	

*/
			
//USART1->TXDATA = 0xAA;	
}	
			
}

void USART1_RX_IRQHandler(void)
{
//	unsigned leuartif = USART_IntGet(USART1);	
//  /* Store and reset pending interupts */
//  leuartif = USART_IntGet(USART1);
////  USART_IntClear(USART1, leuartif);
    USART_IntClear(USART1, USART_IF_RXDATAV);
////USART_IntClear(USART1, _USART_IF_MASK);	
//USART_IntClear(USART1, leuartif);
	test_irq_uart_rx = 1;
  /* Signal frame found. */
//  if (leuartif & LEUART_IF_SIGF)
//  {
//    /* Zero-terminate rx buffer */
//    len            = BUF_MAX - 1 - ((dmaControlBlock->CTRL >> 4) & 0x3FF);
//    rxbuf[len - 1] = 0;
//rx_char = USART1->RXDATAXP;
rx_char = (uint8_t)USART_Rx(USART1);
uart1_RX[len_packet]=rx_char;
if(uart1_RX[0] == 0x68  && uart1_RX[1] == 1)
{

	if(len_packet == 4)
		{
	  len_l_receive = uart1_RX[3];
		len_h_receive = uart1_RX[4];				
		data_len = 256*len_h_receive + len_l_receive;
		}
	if(data_len  > 0)
		{
		data_receive[len_packet-5] = uart1_RX[len_packet];
		data_len--;
		crc_data = crc_data + uart1_RX[len_packet];
		}
	else
		{
		data_receive[len_packet-5] = uart1_RX[len_packet];			
		crc_receive = uart1_RX[len_packet];
		stop_receive = uart1_RX[len_packet];
		crc_calc = uart1_RX[0]+ uart1_RX[1] + uart1_RX[2] + crc_data;
		}
}
len_packet++;
if(stop_receive == 0x17)
{
	len_packet=0;
	stop_receive=0;
	cmd_receive = uart1_RX[2];
}

  /* Check for RX data valid interrupt */
//  if (USART1->STATUS & USART_STATUS_RXDATAV)
//  {
//    /* Copy data into RX Buffer */
//    uint8_t rxData = USART_Rx(uart1);
//    rxBuf.data[rxBuf.wrI] = rxData;
//    rxBuf.wrI             = (rxBuf.wrI + 1) % BUFFERSIZE;
//    rxBuf.pendingBytes++;



    /* Clear RXDATAV interrupt */
//    USART_IntClear(USART1, USART_IF_RXDATAV);
//  }
}

void USART1_TX_IRQHandler(void)
{
	test_irq_uart_tx = 2;
    USART_IntClear(USART1, USART_IF_TXC);	
GPIO_PinOutClear(RE_TR_PORT, RE_TR_PIN);	
	    USART_IntClear(USART1, USART_IF_RXDATAV);
USART_IntEnable(USART1, USART_IF_RXDATAV);		
USART1->CMD |= USART_CMD_RXEN;	
}

void LEUART0_IRQHandler(void)
{
	test_irq_LEUART ++;
	
  if (LEUART0->STATUS & LEUART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    receive[counter_from_danfoss] = LEUART_Rx(LEUART0);	
		counter_from_danfoss++;
	}
	
  if (LEUART0->STATUS & LEUART_STATUS_TXC)
  {
    LEUART_IntClear(LEUART0, LEUART_IF_TXC);			
GPIO_PinOutClear(RE_DANFOSS_PORT, RE_DANFOSS_PIN);	
	    LEUART_IntClear(LEUART0, LEUART_IF_RXDATAV);
LEUART_IntEnable(LEUART0, LEUART_IF_RXDATAV);		
LEUART0->CMD |= LEUART_CMD_RXEN;	
	}	
	
    LEUART_IntClear(LEUART0, LEUART_IF_TXC);	
    LEUART_IntClear(LEUART0, LEUART_IF_TXBL);		
    LEUART_IntClear(LEUART0, LEUART_IF_RXDATAV);	
    LEUART_IntClear(LEUART0, LEUART_IF_RXOF);		
}

