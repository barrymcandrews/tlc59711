# C++ library for controlling LED Driver TLC59711 from a Raspberry Pi
 **(with python bindings!)**
 ---

The TLC59711 is a 12-channel 16-bit PWM LED driver controlled via SPI. This project adapts [Adafruit's TLC59711 Library for Arduino](https://github.com/adafruit/Adafruit_TLC59711) into a C++ library for Raspberry Pi. It uses the [BCM2835 C library](https://www.airspayce.com/mikem/bcm2835/) to send SPI messages to the driver.



## Getting Started
### Prerequsites
If you don't already have the [BCM2835 C Library](https://www.airspayce.com/mikem/bcm2835/) installed download and install it from source:

```bash
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz
tar xvfz bcm2835-1.60.tar.gz
cd bcm2835-1.60
./configure
make
sudo make install
```
You will also need the pybind11:

```
pip install pybind11
```
### Installation
You can install either the C++ library, python bindings, or both depending on how you plan to use the project.
#### C++ Library
```
mkdir build
cd build
cmake ..
make
sudo make install
```
#### Python Bindings
```
./setup.py install
```

## Examples 
The project uses the same API as [Adafruit's Arduino Library](https://github.com/adafruit/Adafruit_TLC59711).

### C++
```C++
#include <tlc59711.h>

uint8_t n = 1;  # Number of chained TLC59711 chips
TLC59711 tlc = TLC59711(n);
tlc.begin();

uint8_t led_num = 1;
tlc.setLED(led_num, 65535, 65535, 65535);  # Set led 1 to white
tlc.write();
```

### Python
```python
from tlc59711 import TLC59711

n = 1  # Number of chained TLC59711 chips
tlc = TLC59711(n)
tlc.begin()

led_num = 1
tlc.setLED(led_num, 65535, 65535, 65535)  # Set led 1 to white
tlc.write()

```