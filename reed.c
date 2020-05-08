// ------ Libraries and Definitions ------
#include "simpletools.h"
// ---- define some constants ------
#define LCD_X0Y0 128
#define LCD_X0Y1 148
#define BKSPACE 8
#define CLR 12

#define ON 22
#define LCD_RXPIN 24
#define LCD_TXPIN 24
#define LCD_BAUD  19200

// --- define some value for reed grid ----
#define reed_start_Pin 8
#define reed_end_Pin   23

// --- define Pins ----
#define Pin0  0
#define Pin1  1
#define Pin2  2
#define Pin3  3
#define Pin4  4
#define Pin5  5
#define Pin6  6
#define Pin7  7
#define Pin8  8
#define Pin9  9
#define Pin10 10
#define Pin11 11
#define Pin12 12
#define Pin13 13
#define Pin14 14
#define Pin15 15


//
// ------ Global Variables and Objects ------
serial *serial_lcd;

/* 

Group I/O
unsigned int 	get_states (int endPin, int startPin)
 	Get states of a contiguous group of I/O pins.
unsigned int 	get_directions (int endPin, int startPin)
 	Get directions for a contiguous group of I/O pins.
unsigned int 	get_outputs (int endPin, int startPin)
 	Get output settings for a contiguous group of I/O pins.
void 	set_directions (int endPin, int startPin, unsigned int pattern)
 	Set directions for a contiguous group of I/O pins.
void 	set_outputs (int endPin, int startPin, unsigned int pattern)
 	Set output states for a contiguous group of I/O pins. 



*/


// ------ Main Program ------
int main()
{
  serial_lcd = serial_open(LCD_RXPIN, LCD_TXPIN, 0, LCD_BAUD);
//  serial_lcd  = serial_open(12, 12, 0, 19200);
  // Connecter la diode sur P1
  // Connecter l'interrupteur reed sur P0
  // Les Lignes en High (1) les colonnes en low(0)
  // Les lignes sont paires colonnes impaires
  set_outputs(reed_end_Pin,reed_start_Pin,0b0101010101010101)
  // Connecter le LCD sur P12 et le rouge sur P40, le noir sur P39
  writeChar(serial_lcd, ON);
  writeChar(serial_lcd, CLR);
  pause(5);
  dprint(serial_lcd, "Bonjour Quentin");
  writeChar(serial_lcd, 215);
  writeChar(serial_lcd, 214);
  writeChar(serial_lcd, 223);
  pause(2000);
  writeChar(serial_lcd, CLR);
  pause(5);
  dprint(serial_lcd, "Test connexion");
  pause(2000);
  // Effacer l'ecran
  writeChar(serial_lcd, CLR);
  pause(5);
  while(1) {
    // Tester P1 si le courant passe
    if (input(1) == 1) {
      // Afficher a la position 0,0 du LCD
      //writeChar(serial_lcd, (128 + (constrainInt(0, 0, 3) * 20) + constrainInt(0, 0, 19)));
      writeChar(serial_lcd, LCD_X0Y0);
      dprint(serial_lcd, "Pion A1");
      // Remettre P1 a 0
      low(1);
    }
    else {
      // Effacer l'ecran sinon
      writeChar(serial_lcd, CLR);
      pause(5);
    }

  }

}
