# Pokojový teplo/vlhkoměr s Ř-duino-LED
Ahoj, v dnešním projektu si vytvoříme přístroj, který nám bude měřit teplotu a vlhkost místnosti a poté co tyto údaje změří je zobrazí na námi připojeném OLED displeji.

# Součástky
- Ř-duino-LED
- OLED 128x64 0.96 I2C
- AHT 10
- vodiče
- nepájivé pole

# AHT 10
<img alt="AHT 10" src="https://github.com/prokyber/r-duino-led-AHT10/blob/main/img/460_aht10-full.webp" style="Height: 30vh;">

AHT10 představuje novou generaci snímače teploty a vlhkosti. Je zabudován do pouzdra 4×5 mm a výškou 1,6mm. Čidlo vysílá kalibrovaný digitální signál ve standardním formátu I2C. AHT10 je vybaven nověnavrženým čipem specifickým pro ASIC, vylepšeným MEMS polovodičovým kapacitním snímačem vlhkosti a standardním snímačem teploty na čipu. Jeho výkon byl výrazně vylepšen nad úroveň spolehlivosti senzorů předchozí generace.

# OLED 128x64 0.96 I2C
<img alt="OLED displej" src="https://github.com/prokyber/r-duino-led-AHT10/blob/main/img/468_ezgif-1-d094aebd32.png" style="Height: 30vh;">

OLED displej s modrými znaky má v porovnání s alfanumerickými LCD displeji mnoho výhod. Patří mezi například vyšší rozlišení (v tomto případě 128x64 bodů) či nižší spotřeba. Právě nižší spotřeby je dosaženo tím, že u OLED displeje svítí pouze ty body, které jsou aktivovány. Pro článek vybraný OLED displej obsahuje řídící obvod SSD1306, který obstarává komunikaci s Ř-DUINEM po rozhraní I2C či SPI, v tomto případě je použita sběrnice I2C. Co se týká velikosti, tak tento displej má úhlopříčku 0,96 palce a celková velikost modulu je 2,7 x 2,7 cm.

# I2C
<img alt="" src="https://github.com/prokyber/r-duino-led-temperature-sensor/blob/main/img/900px-I2C_data_transfer.png" style="Height: 30vh;">

I2C graf Inter-Integrated Circuit je sériový komunikační protokol používaný pro komunikaci mezi mikrocontroly nebo jinými elektronickými součástkami v elektronických systémech. I2C je určen pro komunikaci mezi dvěma nebo více zařízeními, která jsou propojena pomocí dvou vedení: Master-out/Slave-out (SCL) a Serial Data Line (SDA).

Přenos dat se zahajuje START bitem (S), když je SDA nízká, zatímco SCL zůstává vysoká. Pak, SDA nastaví přenášený bit zatímco SCL je nízká (modrá) a jsou odebrány vzorky dat (přijaté) při SCL stoupá (zelená). Když je přenos dokončen, je poslaný STOP bit (P) pro uvolnění datové linky, změnou SDA na vysokou, zatímco SCL je trvale vysoký. Aby se zabránilo falešně detekci, je úroveň na SDA změněn na negativní hraně a je zachycen na kladné hrany SCL.

# Zapojení
<img alt="zapojení" src="https://github.com/prokyber/r-duino-led-AHT10/blob/main/img/zapojeni.png" style="Height: 70vh;">

Při zpojení chceme v tomto projektu vždy u všech tří součástek propojit
5V -> VCC/VIN
GND -> GND
SDA -> SDA
SCL -> SCL/SCK

# Knihovny
Před tím než začeme psát kód tak si pro účely tohoto projektu budeme muset stáhnou pár externích knihoven díky kterým si usnadníme komunikaci s displejem a senzorem. Klikněte na Nástorje -> Spravovat knihovny. Na levé straně by se vám měla otevřít lišta s možností vyhledávání. Zde vyhledejte "Adafruit AHT10" na příslušné kartě pak vyberte verzi 0.1.0 a klikněte na instalovat.

Tím jsme získali knihovnu pro komunikaci s AHT 10 teď ještě druhou pro OLED displej. Tentokrát vyhledáme "U8glib" vybereme verzi 1.19.1 a dáme instalovat.

# Kód
(Soubor ke stažení výše)

``` cpp
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
```
