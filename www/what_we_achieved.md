---
title: What We Achieved
---
This section outlines what we have achieved in the 4 weeks we have been working on this project. 

### Programming
#### Button Functionality
- Button press increases LED brightness in steps
  - Reduced maximum brightness from 100 to 60 to stop browning out
- Button press also shows battery voltage on red, orange and green LEDs

 ![image](https://github.com/user-attachments/assets/ca544c57-47a2-442d-8706-7d09a57061c9)


#### Power Conservation
This work was more exploratory: code has been written but will ideally be implemented if a second interrupt button is added to the board. 
- Sleep mode under the following conditions. Either:
  - White LEDs on zero brightness for over 2 minutes
  - Battery voltage falls below 3.2 V

How to wake the MCU up from sleep? This is an issue that we investigated carefully. There are several options available which are demonstrated in this table 

![image](https://github.com/user-attachments/assets/9dbf2862-3740-445f-881d-b93bf5a0ae10)

We think the best long term solution is adding an extra button, so the user can always wake the battery manually. 

 
#### Cost Reduction

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




