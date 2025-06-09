---
title: What We Achieved
---

#### Button Functionality
- Button press [increases LED brightness](Lucy.md) in steps
  - Reduced maximum brightness from 100 to 60 to stop browning out
- Button press also shows battery voltage on red, orange, green LEDs
  - Multichannel ADC (Lucy) <- maybe move this to Jim's section bc it fits better here
  - Calibration (Jim)
  - batcount (Jim)
  - averaging (Jim)

#### Mechanical Case Design
Basic mechanical case design to be outlined here and links to individual webpages

#### Power Conservation
This work was more exploratory: code has been written but will ideally be implemented if a second interrupt button is added to the board. 
- Sleep mode when battery voltage drops below 3.2V (Lucy)
- Sleep mode after 2 minutes of LEDs on zero brightness
- Sun detected the LED mode sets back to zero to save energy
  - averaging: issues when battery drops to 0V if bad connection: sleep when it's not supposed to
  - Button interrupt and __WFI()
  - Need extra button for actual useful product (unrealistic to remake PCB in 4 weeks but will feedback to Noam)
  - Currently uses periodic wakeup and standby mode as proof of concept



