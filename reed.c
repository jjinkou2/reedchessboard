
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


// ------ recup les colonnes  ------
// récupere un bit sur 2 en partant de la droite 
// ex  si v = 0b11110010
// retour = 0b1100
unsigned int getcolpinval(unsigned int v)
{
    unsigned int d,i;
    // on passe de 2 en 2 vers la gauche (on shift v vers la droite)
    for (d = 0,i=0; v; v >>= 2, i++) {
      // on accumule le résultat dans d
        d = d | (v&1) << i ;
    }
    return d;
}

// ------ Remplie une ligne ------
// 
// S'il y a une piece affiche X
// Si la case est vide =====> .
// retourne row[8]
void fill_rowStr(int n, char *row )
{
   for (int i=0;i<8; i++,n>>=1) {
       row[i] = (n&1) ? '.' : 'X' ;
   }
   row[8]='\0';
}

void printBoard(char* chessStr)
{
  term_cmd(CRSRXY, TERM_X0, TERM_Y0);

  for (int i=0;i<64;i++){
    if (i%8==0) term_cmd(CRSRXY,TERM_X0,TERM_Y0 + i/8);
    printf("%c",chessStr[i]);
  }  
}

// ------ Main Program ------
int main()
{
  // Variables internes  
  unsigned int pinvalues = 0;  // recupere les valeurs des pins
  int rowpin    = 0;  // pins des lignes
  unsigned int colpin_value = 0; //  Pins colonnes
  char rowStr[9]; // une ligne vide
  char chessboard[100];

  // Mettre les lignes en direction output et les colonnes en input
  set_directions(reed_end_Pin,reed_start_Pin,Dir_RowOut_ColIn);
  pause(50);

  // mettre les lignes en High
  set_outputs(reed_end_Pin,reed_start_Pin,RowsHigh);
  pause(50);
   
  for(;;){
    *chessboard='\0';
    for (int row = 4; row>=1; row--){

       // Mettre la ligne a 0 
        rowpin=ROW_1+(row-1)*2;
        set_output(rowpin,0);

       // récupère les valeurs des colonnes
       pinvalues = get_states(reed_end_Pin,reed_start_Pin);
       colpin_value = getcolpinval(pinvalues);

        // mettre Row a X...XX
       fill_rowStr(colpin_value, rowStr);   
       
       // remplir l'echiquier
       strcat(chessboard,rowStr);       
       strcat(chessboard,"\n");       
    
       // reinitialiser la ligne a High
       set_output(rowpin,1);
       pause(50);

    } 

    // afficher l'échiquier
  //  printBoard(chessboard);
    term_cmd(CRSRXY,0,TERM_Y0);
    printf("%s",chessboard);
  } // for(;;)
}
