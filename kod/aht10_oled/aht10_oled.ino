// OLED displej přes I2C
// řadič SSD1306
#include <Adafruit_AHT10.h>

Adafruit_AHT10 aht;

// připojení knihovny U8glib
#include "U8glib.h"

// inicializace OLED displeje z knihovny U8glib
U8GLIB_SSD1306_128X64 mujOled(U8G_I2C_OPT_NONE);

// proměnná pro uchování času poslední obnovy displeje
long int prepis = 0;

void setup(void) {
  // pro otočení displeje o 180 stupňů
  // stačí odkomentovat řádek níže
  // mujOled.setRot180();
   Serial.begin(9600);
  Serial.println("Adafruit AHT10 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT10? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 found");
}


void loop(void) {
   
  // porovnání uloženého a aktuálního času
  // při rozdílu větším než 100 ms se provede
  // obnovení displeje, čas můžeme nastavit dle potřeby
  if (millis()-prepis > 1) {
    // následující skupina příkazů
    // obnoví obsah OLED displeje
    mujOled.firstPage();
    do {
      // funkce vykresli vykreslí žádaný obsah
      vykresli();
    } while( mujOled.nextPage() );
    // uložení posledního času obnovení
    prepis = millis();
  }
  
  // zde je místo pro další příkazy pro Arduino
  
  // volitelná pauza 10 ms pro demonstraci
  // vykonání dalších příkazů
  delay(1);
}
// funkce vykresli pro nastavení výpisu informací na OLED
void vykresli(void) {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  // nastavení písma, toto písmo umožní vypsat
  // přibližně 15x4 znaků
  mujOled.setFont(u8g_font_unifont);
  // nastavení pozice výpisu v pixelech
  // souřadnice jsou ve tvaru x, y
  // souřadnice 0, 0 je v levém horní rohu
  // OLED displeje, maximum je 128, 64
  mujOled.setPrintPos(0, 10);
  // výpis textu na zadanou souřadnici
  mujOled.print("prokyber navody");
  mujOled.setPrintPos(0, 25);
  mujOled.print("aht 10");
  mujOled.setPrintPos(0, 40);
  mujOled.print("teplota ");
    mujOled.print(temp.temperature);
      mujOled.print("C");
  mujOled.setPrintPos(0, 55);
    mujOled.print("vlhkost ");
  mujOled.print(humidity.relative_humidity);
  mujOled.print("%");
}
