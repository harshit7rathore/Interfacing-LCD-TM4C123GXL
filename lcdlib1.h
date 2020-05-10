//#define DATA 0x0F
//#define EN BIT4
//#define RS BIT5

void lcdInit();
void lcdWriteData(unsigned char data);
void lcdWriteCmd(unsigned char cmd);
void lcdTriggerEn();
void lcdWriteString(unsigned char str[] );
void lcdWriteInt(unsigned int number);
