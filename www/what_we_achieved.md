---
title: What We Achieved
---
This section outlines what we have achieved in the 4 weeks we have been working on this project. There were two key subteams working on the project, the programming team and the mechanical team, and the final outcomes from each team are explained on this page. All code was documented in our [GitHub](/code) so that it can be used in future iterations of the project and CAD models can be found in the [CAD folder](/CAD).

# What can the device do?

## When you press the button...
- Button press increases LED brightness in steps
- 4 different brightness levels available, useful for a range of external light levels
- Button press also shows battery voltage on red, orange and green LEDs

 ![image](https://github.com/user-attachments/assets/ca544c57-47a2-442d-8706-7d09a57061c9)


## Power Conservation Features

### Sleep Mode

![image](https://github.com/user-attachments/assets/1b8bc5e7-ce51-484f-8685-86cc52cb3a5d)

The board enters sleep mode under the following conditions. 

Either:
  - White LEDs on zero brightness for over 2 minutes
  - Battery voltage falls below 3.2 V

Sleep mode reduces power consumption, which extends battery life and reduces likelihood of discharging the battery below the safe limit. 

How to wake the MCU up from sleep? This is an issue that we investigated carefully. There are several options available which are demonstrated in this table 

![image](https://github.com/user-attachments/assets/cd6c6156-ef3a-4c04-b65a-84cbea7356bc)

We think the best long term solution is adding an extra button, so the user can always wake the battery manually. This was unachievable in the short time scale of the project but the periodic sleep mode worked as a proof of concept, so it should be easy to impliment an extra button as an interrupt in the future.

### Solar Detection

- The microcontroller automatically switches the white LEDs to zero when sunlight is detected.

- This minimises wasted power: it is unlikely the light will be needed when the sun is shining. 

- User can override this function by pressing the button, so they can force the lights to be on if required

## Cost Reduction 
### Replacing coloured LEDs

- Replacing the 3 battery status LEDs with one single LED would reduce the cost
- We configured the pins so the RGB LED lit up, which is a useful step in the right direction.

<img src="https://github.com/user-attachments/assets/962bd02d-dfdb-4951-8aaa-53aef2dadd6a" width="300"/>
<img src="https://github.com/user-attachments/assets/3e46c980-7e0a-47e4-ad51-366d803d6a43" width="300"/>



# Mechanical
- Produceable Case
  - Produced design that can easily be 3D printed
  - Produced files accesible to open source software with clear guidelines for modification [openscad_case](/CAD/openscad_case)
- Protective Case
  - Case modified to protect some sensitive components
  - Case shown to be robust
  - Case protects input pins from damage
- Diffusing Case
  - Case shown to reduce intensity of direct light
  - Case shown to improve diffusion of light around a room
  - Case does not significantly undermine effectiveness of battery indicator LEDs
 
 # Technical Details
 If you would like more information on how these features were implemented or how the case was designed, please read our individual technical reports. These are split into the programming and mechanical subteams and are located in the [final](/final) folder of our Github repository.
 
*Programming written by Lucy Munson and Mechanical written by Leo Mills*




