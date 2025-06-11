---
title: What We Achieved
---
This section outlines what we have achieved in the 4 weeks we have been working on this project. 

# Programming
## Button Functionality
- Button press increases LED brightness in steps
  - Reduced maximum brightness from 100 to 60 to stop browning out
- Button press also shows battery voltage on red, orange and green LEDs

 ![image](https://github.com/user-attachments/assets/ca544c57-47a2-442d-8706-7d09a57061c9)


## Power Conservation
This work was more exploratory: code has been written but will ideally be implemented if a second interrupt button is added to the board. 
- Sleep mode under the following conditions. Either:
  - White LEDs on zero brightness for over 2 minutes
  - Battery voltage falls below 3.2 V

How to wake the MCU up from sleep? This is an issue that we investigated carefully. There are several options available which are demonstrated in this table 

![image](https://github.com/user-attachments/assets/cd6c6156-ef3a-4c04-b65a-84cbea7356bc)

We think the best long term solution is adding an extra button, so the user can always wake the battery manually. This was unachievable in the short time scale of the project but the periodic sleep mode worked as a proof of concept, so it should be easy to impliment an extra button as an interrupt in the future.

## Cost Reduction
### Replacing coloured LEDs

Replacing the 3 battery status LEDs with one single LED would reduce the cost
We configured the pins so the RGB LED lit up, which is a useful step in the right direction. 

![image](https://github.com/user-attachments/assets/962bd02d-dfdb-4951-8aaa-53aef2dadd6a)

![image](https://github.com/user-attachments/assets/3e46c980-7e0a-47e4-ad51-366d803d6a43)


 ### Mechanical
- Produceable Case
  - Produced design that can easily be 3D printed
  - Produced files accesible to open source software with clear guidelines for modification [openscad_case](../../CAD/openscad_case)
- Protective Case
  - Case modified to protect some sensitive components
  - Case shown to be robust
  - Case protects input pins from damage
- Diffusing Case
  - Case shown to reduce intensity of direct light
  - Case shown to improve diffusion of light around a room
  - Case does not significantly undermine effectiveness of battery indicator LEDs
 
*Programming written by Lucy Munson
Mechanical written by Leo Mills*




