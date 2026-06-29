#include <LPC21xx.h>
void KeyPad_Init(void);
char KeyPad_GetKey(void);
void LCDInit(void);
void LCDString(char*);
void LCDCommand(unsigned char);
void LCDChar(char);
char key;

int main()
{
    LCDInit();
    KeyPad_Init();

    LCDString("Press Key");

    while(1)
    {
        key = KeyPad_GetKey();

        LCDCommand(0xC0);
        LCDChar(key);
    }
}
