#include "SharpMem.h"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif
#ifndef _swap_uint16_t
#define _swap_uint16_t(a, b) { uint16_t t = a; a = b; b = t; }
#endif

/**************************************************************************
    Sharp Memory Display Connector
    -----------------------------------------------------------------------
    Pin   Function        Notes
    ===   ==============  ===============================
      1   VIN             3.3-5.0V (into LDO supply)
      2   3V3             3.3V out
      3   GND
      4   SCLK            Serial Clock
      5   MOSI            Serial Data Input
      6   CS              Serial Chip Select
      9   EXTMODE         COM Inversion Select (Low = SW clock/serial)
      7   EXTCOMIN        External COM Inversion Signal
      8   DISP            Display On(High)/Off(Low)

 **************************************************************************/

#define SHARPMEM_BIT_WRITECMD   (0x80)
#define SHARPMEM_BIT_VCOM       (0x40)
#define SHARPMEM_BIT_CLEAR      (0x20)
#define TOGGLE_VCOM             do { _sharpmem_vcom = _sharpmem_vcom ? 0x00 : SHARPMEM_BIT_VCOM; } while(0);


uint8_t *sharpmem_buffer;

DigitalOut _ss(PC_11);
//DigitalOut _clk(PE_13);
//DigitalOut _mosi(PE_15);
//DigitalOut _sharpmem_vcom(PA_2);
DigitalOut _disp(NC);
DigitalOut _extm(NC);
SPI spi(PE_15, PE_14, PE_13);

/* ************* */
/* CONSTRUCTORS  */
/* ************* */
SharpMem::SharpMem(uint16_t width, uint16_t height) : Adafruit_GFX(width, height) {
  /*_clk  = clk;
  _mosi = mosi;
  _ss   = ss;*/
  _width = WIDTH_LCD;
  _height = HEIGHT_LCD;
  
  spi.frequency(1000000);
}

boolean SharpMem::begin(void) {
  // Set pin state before direction to make sure they start this way (no glitching)
  _ss = 1; 
  //_clk = 0;
  //_mosi = 1;
  _extm = 1;
  _disp = 1;


  // Set the vcom bit to a defined state
  _sharpmem_vcom = SHARPMEM_BIT_VCOM;

  sharpmem_buffer = (uint8_t *)malloc((WIDTH * HEIGHT) / 8);

  if (!sharpmem_buffer) return false;

  setRotation(90);
  wait_us(50);
  return true;

}

/* *************** */
/* PRIVATE METHODS */
/* *************** */

 
/**************************************************************************/
/*!
    @brief  Sends a single byte in pseudo-SPI.
*/
/**************************************************************************/
void SharpMem::sendbyte(uint8_t data)
{
  spi.write(data);
}

void SharpMem::testRun() {
  uint16_t i, totalbytes, currentline, oldline;  
  totalbytes = ARRAYSIZE;

  // Send the write command
  _ss = 1;
  wait_us(3);
  sendbyte(SHARPMEM_BIT_WRITECMD | _sharpmem_vcom);
  TOGGLE_VCOM;

  // Send the address for line 1
  currentline = 1;
  sendbyteLSB(currentline);

  // Send image buffer
  int line_track = 0;
  for (i = 0; i < ARRAYSIZE; i++)
  {
    sendbyteLSB(0);
    line_track++;
    
    if (line_track == 50 && currentline < HEIGHT)
    {
      // Send end of line and address bytes
      sendbyteLSB(0x00);
      
      // Send next line
      currentline++;
      if (currentline <= HEIGHT)
      {
        sendbyteLSB(currentline);
      }
      
      // Reset line tracking
      line_track = 0;
    }
    
  }

  // Send another trailing 16 bits for the last line
  sendbyteLSB(0x00);
  sendbyteLSB(0x00);
  
  
  _ss = 0;
  wait_us(3);
  
}

#define REVERSE_BITS(byte) (((reverse_lookup[(byte & 0x0F)]) << 4) + reverse_lookup[((byte & 0xF0) >> 4)])
static const uint8_t reverse_lookup[] = { 0, 8,  4, 12, 2, 10, 6, 14,1, 9, 5, 13,3, 11, 7, 15 };
void SharpMem::sendbyteLSB(uint8_t data)
{
  spi.write(REVERSE_BITS(data));
}

/* ************** */
/* PUBLIC METHODS */
/* ************** */

// 1<<n is a costly operation on AVR -- table usu. smaller & faster
static const uint8_t set[] = {  1,  2,  4,  8,  16,  32,  64,  128 };
static const uint8_t clr[] = { (uint8_t)~1 , (uint8_t)~2 , (uint8_t)~4 , (uint8_t)~8,
            (uint8_t)~16, (uint8_t)~32, (uint8_t)~64, (uint8_t)~128 };

/**************************************************************************/
/*! 
    @brief Draws a single pixel in image buffer

    @param[in]  x
                The x position (0 based)
    @param[in]  y
                The y position (0 based)
*/
/**************************************************************************/
void SharpMem::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) {
      return;
  }

  switch(rotation) {
   case 1:
    _swap_int16_t(x, y);
    x = WIDTH  - 1 - x;
    break;
   case 2:
    x = WIDTH  - 1 - x;
    y = HEIGHT - 1 - y;
    break;
   case 3:
    _swap_int16_t(x, y);
    y = HEIGHT - 1 - y;
    break;
  }

  if(color) {
    sharpmem_buffer[(y * WIDTH + x) / 8] |= set[x & 7];
  } else {
    sharpmem_buffer[(y * WIDTH + x) / 8] &= clr[x & 7];
  }
}

/**************************************************************************/
/*! 
    @brief Gets the value (1 or 0) of the specified pixel from the buffer

    @param[in]  x
                The x position (0 based)
    @param[in]  y
                The y position (0 based)

    @return     1 if the pixel is enabled, 0 if disabled
*/
/**************************************************************************/
uint8_t SharpMem::getPixel(uint16_t x, uint16_t y)
{
  if((x >= _width) || (y >= _height)) return 0; // <0 test not needed, unsigned

  switch(rotation) {
   case 1:
    _swap_uint16_t(x, y);
    x = WIDTH  - 1 - x;
    break;
   case 2:
    x = WIDTH  - 1 - x;
    y = HEIGHT - 1 - y;
    break;
   case 3:
    _swap_uint16_t(x, y);
    y = HEIGHT - 1 - y;
    break;
  }

  return sharpmem_buffer[(y * WIDTH + x) / 8] & set[x & 7] ? 1 : 0;
}

/**************************************************************************/
/*! 
    @brief Clears the screen
*/
/**************************************************************************/
void SharpMem::clearDisplay()
{
  /*for(int x = 0; x < ARRAYSIZE; x++) {
    sharpmem_buffer[x] = 255;
  }

  // Send the clear screen command rather than doing a HW refresh (quicker)
  _ss = 1;
  sendbyte(_sharpmem_vcom | SHARPMEM_BIT_CLEAR);
  sendbyteLSB(0x00);
  TOGGLE_VCOM;
  _ss = 0;*/
  
  memset(sharpmem_buffer, 0xff, (WIDTH * HEIGHT) / 8);
  // Send the clear screen command rather than doing a HW refresh (quicker)
  _ss = 1;
  wait_us(3);
  sendbyte(_sharpmem_vcom | SHARPMEM_BIT_CLEAR);
  sendbyteLSB(0x00);
  TOGGLE_VCOM;
  _ss = 0;
  wait_us(3);
}

/**************************************************************************/
/*! 
    @brief Renders the contents of the pixel buffer on the LCD
*/
/**************************************************************************/
void SharpMem::refresh(void)
{
  uint16_t i, totalbytes, currentline, oldline;  
  totalbytes = ARRAYSIZE;

  // Send the write command
  _ss = 1;
  wait_us(1);
  sendbyte(SHARPMEM_BIT_WRITECMD | _sharpmem_vcom);
  TOGGLE_VCOM;

  // Send the address for line 1
  currentline = 1;
  sendbyteLSB(currentline);

  // Send image buffer
  int line_track = 0;
  for (i = 0; i < ARRAYSIZE; i++)
  {
    sendbyteLSB(sharpmem_buffer[i]);
    line_track++;
    
    if (line_track == 50 && currentline < HEIGHT)
    {
      // Send end of line and address bytes
      sendbyteLSB(0x00);
      
      // Send next line
      currentline++;
      if (currentline <= HEIGHT)
      {
        sendbyteLSB(currentline);
      }
      
      // Reset line tracking
      line_track = 0;
    }
    
  }

  // Send another trailing 16 bits for the last line
  sendbyteLSB(0x00);
  sendbyteLSB(0x00);
  
  _ss = 0;
  wait_us(1);
}

void SharpMem::dump(void) {
    pc->printf("\n");
    int counter = 0; 
    for (int i = 0; i < (HEIGHT * WIDTH) / 8; i++) {
        pc->printf("%0.2X ", sharpmem_buffer[i]);
        counter++;
        if (counter == 50) {
            pc->printf("\n");
            counter = 0;
        }
    }
    pc->printf("\n\n");
}

void SharpMem::setPC(Serial *pc) {
    this->pc = pc;
    
    pc->printf("WIDTH = %i\n", WIDTH);
    pc->printf("HEIGHT = %i\n", HEIGHT);
    pc->printf("_width = %i\n", _width);
    pc->printf("_height = %i\n", _height);
    pc->printf("WIDTH_LCD = %i\n", WIDTH_LCD);
    pc->printf("HEIGHT_LCD = %i\n", HEIGHT_LCD);
    
}


void SharpMem::blackArray() {
    memset(sharpmem_buffer, 0x00, (WIDTH * HEIGHT) / 8);
}

void SharpMem::whiteArray() {
    memset(sharpmem_buffer, 0xFF, (WIDTH * HEIGHT) / 8);
}
