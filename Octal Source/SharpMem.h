#include "mbed.h" 
#include "Adafruit_GFX.h"

#define WIDTH_LCD 400
#define HEIGHT_LCD 240
#define ARRAYSIZE 12000

typedef volatile uint32_t RwReg;


class SharpMem : public Adafruit_GFX {
 public:
  SharpMem(uint16_t width, uint16_t height);
  boolean begin();
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  uint8_t getPixel(uint16_t x, uint16_t y);
  void clearDisplay();
  void testRun();
  void refresh(void);
  void dump();
  void setPC(Serial *pc);
  void blackArray();
  void whiteArray();

 private:
  Serial *pc;
  uint32_t _sharpmem_vcom;
  void sendbyte(uint8_t data);
  void sendbyteLSB(uint8_t data);
};
