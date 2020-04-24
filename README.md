# Watermark irrometer-555withMux
This repository contains the PCB design files to interface the popular Irrometer 200SS soil moisture sensor and read the equivalent soil tension in Frequency.

The RT9193-33GB IC is an LDO used to convert 5V to 3.3V for LMC555 and 74HC4052D ICs. Using the ENABLE pin of the LDO, we can control the poweron-off of the circuit. It is a LDO with drop voltage of around 0.3V. SO your board supply VCC can go as low as 3.6V and the circuit will still function.

The Frequency to KPa (CB) conversion is as below: <br>
```
kPa = 0                             for Hz > 6430
kPa = 9 - (Hz - 4600) * 0.004286    for 4330 <= Hz <= 6430
kPa = 15 - (Hz - 2820) * 0.003974   for 2820 <= Hz <= 4330
kPa = 35 - (Hz - 1110) * 0.01170    for 1110 <= Hz <= 2820
kPa = 55 - (Hz - 770) * 0.05884     for 770 <= Hz <= 1110
kPa = 75 - (Hz - 600) * 0.1176      for 600 <= Hz <= 770
kPa = 100 - (Hz - 485) * 0.2174     for 485 <= Hz <= 600
kPa = 200 - (Hz - 293) * 0.5208     for 293 <= Hz <= 485
kPa = 200                           for Hz < 293
```

You can achieve this in the microcontroller program using "If" conditions. The conversion reference is from the datasheet of SMX circuit (https://www.emesystems.com/smx/documents/SMX_2018.pdf)

The attached Arduino code is tested successfully with ATmega328p and STM32F103 microcontrollers. Same can be adapted to PIC controllers and others as well.

Read more here - https://medium.com/fasal-engineering/a-low-cost-circuit-to-read-from-multiple-watermark-irrometer-200ss-sensors-a4c838da233a

# Liscense
MIT 

# Warranty
THE SOFTWARE AND HARDWARE FILES ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE AND OR HARDWARE.
