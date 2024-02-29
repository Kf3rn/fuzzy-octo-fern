

### Mga Kagamitan:
1. Arduino Board
2. DC Motor (12V, 250RPM)
3. L298N Motor Driver Module
4. LM35 Temperature Sensor
5. Power Source (12V Battery)
6. Jumper Wires

### Mga Koneksyon:
1. **Ikonekta ang DC Motor sa L298N:**
   - Ikonekta ang mga terminal ng DC motor sa OUT1 at OUT2 sa L298N.
   - Ikonekta ang GND ng L298N sa GND ng Arduino.

2. **Ikonekta ang L298N sa Arduino:**
   - Ikonekta ang IN1 at IN2 ng L298N sa digital pins sa Arduino (halimbawa, 2 at 3).
   - Ikonekta ang ENA ng L298N sa isang PWM-enabled na digital pin sa Arduino (halimbawa, 9).

3. **Ikonekta ang LM35 Temperature Sensor sa Arduino:**
   - Ikonekta ang VCC ng LM35 sa 5V sa Arduino.
   - Ikonekta ang GND ng LM35 sa GND sa Arduino.
   - Ikonekta ang output pin ng LM35 sa isang analog pin sa Arduino (halimbawa, A0).

4. **Power Connections:**
   - Ikonekta ang VCC ng L298N sa 12V na power source.
   - Ikonekta ang GND ng L298N sa GND ng 12V na power source.
   - Ikonekta ang VCC ng LM35 sa 5V na power source.

5. **Ikonekta ang Battery:**
   - Ikonekta ang positibong terminal ng 12V battery sa VCC ng L298N.
   - Ikonekta ang negatibong terminal ng battery sa GND ng L298N at Arduino.

### Arduino Code:
Gumamit ng code ng Arduino na ibinigay ko sa aming usapan kanina. I-adjust ang mga numero ng pin at iba pang mga parameter kung kinakailangan.

### Pagsusuri:
1. I-upload ang code sa iyong Arduino.
2. I-power up ang 12V battery.
3. Obserbahan ang pag-uugali base sa pagbabago ng temperatura.

Tandaan na suriin ng mabuti ang iyong mga koneksyon, at siguruhing ang iyong power supply at mga specification ng motor ay tugma sa iyong setup. Kung may mga isyu o karagdagang tanong, huwag mag-atubiling itanong!