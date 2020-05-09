
  // Connecter la diode sur P1
  // Connecter l'interrupteur reed sur P0
  // Les Lignes en High (1) les colonnes en low(0)
  // Les lignes sont paires colonnes impaires



// ------ Libraries and Definitions ------
#include "simpletools.h"
// ---- define some constants ------
#define LCD_X0Y0 128
#define LCD_X0Y1 148
#define BKSPACE 8
#define CLR 12

// ---- constant serial for terminal ---------
#define TERM_X0 10
#define TERM_Y0 2

#define ON 22
#define LCD_RXPIN 24
#define LCD_TXPIN 24
#define LCD_BAUD  19200

// --- define some value for reed grid ----
#define reed_start_Pin 8
#define reed_end_Pin   23
// colonnes en Pins pairs (start=8) et lignes sur Pins impairs
#define Columns           0x5555 //0b0101010101010101
#define Rows              0xAAAA //0b1010101010101010
#define Dir_RowOut_ColIn  0xAAAA // Output = 1 input = 0
#define RowsHigh          0xAAAA 

#define RowsLow           0



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


// --- Pin Row Col ----
#define COL_A  reed_start_Pin
#define ROW_1  (reed_start_Pin+1)

//
// ------ Global Variables and Objects ------

// ------ inverse un octet  ------
// 0b010011 ===> 0b110010 
// est utilisé pour afficher une ligne
unsigned char reversebit(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

// ------ recup les colonnes  ------
// récupere un bit sur 2 en partant de la droite et du 2eme 
// ex  si v = 0b11110010
// retour = 0b1101
int getcolpinval(unsigned int v)
{
    unsigned int d,i;
    // efface le dernier bit a droite
    //v>>=1;
    // on passe de 2 en 2 vers la gauche (on shift v vers la droite)
    for (d = 0; v; v >>= 2, i++) {
      // on accumule le résultat dans d
        d = d | (v&1) << i ;
    }
    return d;
}

// ------ Affiche une ligne ------
// 
// S'il y a une piece affiche X
// Si la case est vide =====> O
void displayrow(int n)
{
    char row[16]="........\0";
       
     for (int i=0;n; i++) {
        if (n & 1)  row[i]='.';
        else        row[i]='X';
        n >>= 1;
    }
//    printf("\t%s\n",row);
    printf("%s",row);
}



// ------ Main Program ------
int main()
{
  // Mettre les lignes en direction output et les colonnes en input
  set_directions(reed_end_Pin,reed_start_Pin,Dir_RowOut_ColIn);
  pause(500);

  // mettre les lignes en High
  set_outputs(reed_end_Pin,reed_start_Pin,RowsHigh);
  pause(500);
    
  unsigned int pinvalues = 0;  // recupere les valeurs des pins
  int rowpin    = 0;  // pins des lignes
  int d = 0;
  char test[255];
  for(;;){
    //pause(5000);
    term_cmd(CRSRXY, TERM_X0, TERM_Y0);

    for (int r = 4; r>=1; r--){
   
       // Mettre la ligne a 0 
        rowpin=ROW_1+(r-1)*2;
        set_output(rowpin,0);
        pause(500);

       // récupère les valeurs des colonnes
       pinvalues = get_states(reed_end_Pin,reed_start_Pin);
       //pause(1000);
      // afficher
//       printf ("row=%d\tpin=%d\tpinval=%u",r,rowpin,pinvalues);
       printf ("Row_%d: ",r);
       d = getcolpinval(pinvalues);
       //printf("\td=%d\n",d); 
       displayrow(d);   
       printf("\n");
       term_cmd(CRSRXY,TERM_X0,TERM_Y0 + 4-r+1);
       // reinitialiser la ligne a High
       set_output(rowpin,1);
      // pause(500);

    } // for row     
  } // for(;;)
}
