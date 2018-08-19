# Skywriter gesture control
## A gesture control project using a skywriter and Arduino Leonardo

A Leonardo/pro micro/ATmega32u4-based-board is required for this project, as it needs to be able to masquerade as a keyboard.
All gestures are translated to keyboard commands or sequences and sent to the host that way.

Due to the fact that a lot of the keyboard shortcuts used are ones I have defined myself, some tweaking will be needed for other systems. 

Linux redshift users may find the *redshift_increment.sh* script useful, so I have included it. 
To use it, setup a decrease keyboard shortcut for the following:
```bash
bash /home/$USER/redshift_increment.sh -
```
and an increase shortcut for this:
```bash
bash /home/$USER/redshift_increment.sh +
```

You will also need a copy of the [pimoroni skywriter library](https://github.com/pimoroni/skywriter-hat).

## Connections

Skywriter  | Arduino
-----------|--------------
VCC        | 5V
GND        | GND
TRFR       | GPIO 12
RESET      | GPIO 13
SCL        | SCL
SDA        | SDA
