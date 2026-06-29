#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define BAUDRATE 9600
#define DIVISOR (PCLK / (16 * BAUDRATE))  // Result is 97
#define TxD0_PIN 0
#define RxD0_PIN 1

//defines for UxLCR
#define _8BIT 3
#define WORD_LEN_SEL_BIT _8BIT 
#define DLAB_BIT 7

// defines for UxLSR
#define DR_BIT 0
#define TEMT_BIT 6

