# Pokojový teplo/vlhkoměr s Ř-duino-LED
Ahoj, v dnešním projektu si vytvoříme přístroj, který nám bude měřit teplotu a vlhkost místnosti a poté co tyto údaje změří je zobrazí na námi připojeném OLED displeji.

# Součástky
- Ř-duino-LED
- OLED 128x64 0.96 I2C
- AHT 10
- vodiče
- nepájivé pole

# AHT 10
AHT10 představuje novou generaci snímače teploty a vlhkosti. Je zabudován do pouzdra 4×5 mm a výškou 1,6mm. Čidlo vysílá kalibrovaný digitální signál ve standardním formátu I2C. AHT10 je vybaven nověnavrženým čipem specifickým pro ASIC, vylepšeným MEMS polovodičovým kapacitním snímačem vlhkosti a standardním snímačem teploty na čipu. Jeho výkon byl výrazně vylepšen nad úroveň spolehlivosti senzorů předchozí generace.

# OLED 128x64 0.96 I2C
OLED displej s modrými znaky má v porovnání s alfanumerickými LCD displeji mnoho výhod. Patří mezi například vyšší rozlišení (v tomto případě 128x64 bodů) či nižší spotřeba. Právě nižší spotřeby je dosaženo tím, že u OLED displeje svítí pouze ty body, které jsou aktivovány. Pro článek vybraný OLED displej obsahuje řídící obvod SSD1306, který obstarává komunikaci s Ř-DUINEM po rozhraní I2C či SPI, v tomto případě je použita sběrnice I2C. Co se týká velikosti, tak tento displej má úhlopříčku 0,96 palce a celková velikost modulu je 2,7 x 2,7 cm.

# I2C
I2C graf Inter-Integrated Circuit je sériový komunikační protokol používaný pro komunikaci mezi mikrocontroly nebo jinými elektronickými součástkami v elektronických systémech. I2C je určen pro komunikaci mezi dvěma nebo více zařízeními, která jsou propojena pomocí dvou vedení: Master-out/Slave-out (SCL) a Serial Data Line (SDA).

Přenos dat se zahajuje START bitem (S), když je SDA nízká, zatímco SCL zůstává vysoká. Pak, SDA nastaví přenášený bit zatímco SCL je nízká (modrá) a jsou odebrány vzorky dat (přijaté) při SCL stoupá (zelená). Když je přenos dokončen, je poslaný STOP bit (P) pro uvolnění datové linky, změnou SDA na vysokou, zatímco SCL je trvale vysoký. Aby se zabránilo falešně detekci, je úroveň na SDA změněn na negativní hraně a je zachycen na kladné hrany SCL.
