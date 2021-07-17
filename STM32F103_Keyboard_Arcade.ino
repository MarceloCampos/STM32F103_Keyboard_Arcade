/*  
 *                                STM32F103_Keyboard_Arcade.ino
 *  Hardware: Blue Pill
 *  Versão  : 0.1 - 17/07/2021
 *  
 *  Definições dos pinos do STM:
 *    C:\Users\marcelo\AppData\Local\Arduino15\packages\STM32\hardware\stm32\1.9.0\variants\PILL_F103XX
 * 
 *  by 
 *    Marcelo Campos - www.marcelocampos.cc - https://github.com/marcelocampos
 *    
*/

#include "Keyboard.h"

#define qtdTeclas 10
#define primeiroIo 18   // 18 = PC14 no variant.h do bluepill
#define LED PC13

unsigned char teclaUltEstado[qtdTeclas + primeiroIo];

void setup() 
{
  int pinInicial = primeiroIo;

  Serial.begin(57600);    // A9:TX  A10:RX
  while(!Serial);

  Serial.print("# Init");
  
  pinMode(LED, OUTPUT);
  
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
      
  pinMode(pinInicial, INPUT_PULLUP);    // F1
  pinMode(++pinInicial, INPUT_PULLUP);  // espaço
  pinMode(++pinInicial, INPUT_PULLUP);  // Esc
  pinMode(++pinInicial, INPUT_PULLUP);  // Enter
  pinMode(++pinInicial, INPUT_PULLUP);  // 
  pinMode(++pinInicial, INPUT_PULLUP);   //
  pinMode(++pinInicial, INPUT_PULLUP);   // Cima
  pinMode(++pinInicial, INPUT_PULLUP);   // Baixo  
  pinMode(++pinInicial, INPUT_PULLUP);  // Esquerda
  pinMode(++pinInicial, INPUT_PULLUP);  // Direita

  for(int i = primeiroIo; i < qtdTeclas + primeiroIo; i++)
    teclaUltEstado[i] = 0;

  Serial.print(".");
  
  Keyboard.begin();

  Serial.print(".. OK");
}

void loop() 
{
  for(int j = primeiroIo; j < qtdTeclas + primeiroIo; j++)
  {
    monitoraTecla(j);
  }
   
}

void monitoraTecla(int tecla)
{
  if(digitalRead(tecla) == 0 && teclaUltEstado[tecla] == 0)
  {
    teclaUltEstado[tecla] = 1;
    Keyboard.press( KeyboardMap(tecla) );   
    digitalWrite(LED, LOW );
    Serial.print(tecla); Serial.println(" :ON");
  }
  else if(digitalRead(tecla) == 1 && teclaUltEstado[tecla] == 1)
  {
    teclaUltEstado[tecla] = 0;
    Keyboard.release( KeyboardMap(tecla) );  
    digitalWrite(LED, HIGH);
    Serial.print(tecla); Serial.println(" :OFF");
  }
}

byte KeyboardMap(int key)
{
  byte k = -1;

  if(key > ( primeiroIo + qtdTeclas -1) )
    return k;
    
  switch(key)
  {
    case primeiroIo:
      k = KEY_F1;
      break;    
    case primeiroIo + 1:
      k = 0x20;   // espaço ?
      break;
    case primeiroIo + 2:
      k = KEY_ESC;
      break;
    case primeiroIo + 3:                  
      k = KEY_RETURN;
      break;
    case primeiroIo + 4:
      k = 0;    // definir
      break; 
    case primeiroIo + 5:
      k = 0;    // definir
      break;
    case primeiroIo + 6:
      k = KEY_UP_ARROW;
      break;
    case primeiroIo + 7:
      k = KEY_DOWN_ARROW;
      break;
    case primeiroIo + 8:
      k = KEY_LEFT_ARROW;
      break; 
    case primeiroIo + 9:
      k = KEY_RIGHT_ARROW;
      break;                          
  }
  return k;
}


/*
como está como keyboard.h:

#define KEY_LEFT_CTRL   0x80
#define KEY_LEFT_SHIFT    0x81
#define KEY_LEFT_ALT    0x82
#define KEY_LEFT_GUI    0x83
#define KEY_RIGHT_CTRL    0x84
#define KEY_RIGHT_SHIFT   0x85
#define KEY_RIGHT_ALT   0x86
#define KEY_RIGHT_GUI   0x87

#define KEY_UP_ARROW    0xDA
#define KEY_DOWN_ARROW    0xD9
#define KEY_LEFT_ARROW    0xD8
#define KEY_RIGHT_ARROW   0xD7
#define KEY_BACKSPACE   0xB2
#define KEY_TAB       0xB3
#define KEY_RETURN      0xB0
#define KEY_ESC       0xB1
#define KEY_INSERT      0xD1
#define KEY_DELETE      0xD4
#define KEY_PAGE_UP     0xD3
#define KEY_PAGE_DOWN   0xD6
#define KEY_HOME      0xD2
#define KEY_END       0xD5
#define KEY_CAPS_LOCK   0xC1
#define KEY_F1        0xC2
#define KEY_F2        0xC3
#define KEY_F3        0xC4
#define KEY_F4        0xC5
#define KEY_F5        0xC6
#define KEY_F6        0xC7
#define KEY_F7        0xC8
#define KEY_F8        0xC9
#define KEY_F9        0xCA
#define KEY_F10       0xCB
#define KEY_F11       0xCC
#define KEY_F12       0xCD
#define KEY_F13       0xF0
#define KEY_F14       0xF1
#define KEY_F15       0xF2
#define KEY_F16       0xF3
#define KEY_F17       0xF4
#define KEY_F18       0xF5
#define KEY_F19       0xF6
#define KEY_F20       0xF7
#define KEY_F21       0xF8
#define KEY_F22       0xF9
#define KEY_F23       0xFA
#define KEY_F24       0xFB


*/
