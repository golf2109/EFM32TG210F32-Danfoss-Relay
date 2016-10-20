#include "em_system.h"   
#include "em_leuart.h"

extern	uint8_t  receive[8];
extern	void Delay (uint32_t dlyTicks);

void  start_danfoss(void);
void  stop_danfoss(void);
void  set_frq_danfoss(uint8_t frq_danfoss_h, uint8_t frq_danfoss_l);
void  test_danfoss(void);
uint16_t crc16(uint8_t *adr_buffer, uint32_t byte_cnt);

