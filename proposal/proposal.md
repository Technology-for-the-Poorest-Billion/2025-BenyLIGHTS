# Problem description

Brief overview of the problem, context and engineering approach to tackle the problem.

## Problem in Context

- 43.6% of rural Ethiopia has no access to electricity, so rely on kerosene lamps for lighting, which cause indoor pollution and health risks.
    - Inhaling the fumes from kerosene lamps is equivalent to smoking several packets of cigarettes daily
    - Respiratory diseases caused by kerosene lamps decrease life expectancy
    - Kerosene lamps emit 'black carbon', which contributes to global warming. 
  
- **Electrification** and the access to light which it brings has a **positive** impact on the **Human Development Index**.
  - Electrification improves life expectancy and education within a country.

https://www.modernghana.com/news/1381887/why-solar-lanterns-and-shs-failed-in-ethiopia.html

There have been previous attempts to electrify rural villages but one of the main issues is that when something breaks, there is nobody to fix it. 


![image](assets/Gaslight.jpg)

## Engineering Solution

We are building an **affordable** and **scalable** solar powered light source for domestic use, to replace Kerosene lamps.

A prototype board has already been designed and built by our supervisor, Noam, and the aim of our project is to further develop the product.

- Current Issues:
    - Exposed electronics
      - Current exposed electronics are more susceptible to dust and damage, decreasing expected lifespan of the product
    - Inefficient LEDs
      - Currently 3 Red, Orange, Green LEDs to display battery level
    - Harsh, undiffused light
      - Very bright to look at, risk of damaging the eyes   
    - Needs a discrete boost to replace IC
      - ICs can be expensive

# Presentation of the proposal

Technical aspects may be described here.
There are two main components to the project, the mechanical and electrical sides. 

## Mechanical:  
### Case Design:  
(): Possible but not necessary implementations  
**design constraints in bold**
- **Loop for hanging** (clips for clipping)
- Diffusing transparent plastic cover
- **Slots for the USBs**
- Kick stand to angle the panel perpendicular to sun rays
- Dust resistant (dust covers for the ports)
- **Cheap**
- **3D printable**
- Acyrlic/ PMMA likely material to be used

## Electronics:  
There are 2 main electrical improvements to be made:

### Implement RGB LED
  - Individual red, orange and green LEDs waste power
  - There is already a WS2812 LED on the PCB, but it is currently not programmed
  
### Replace Integrated Circuit with Boost Converter
    - Current driver is UCC2751x, which is a high performance, expensive chip from Texas Instruments
    - Aim to replace with discrete boost system using RY3730 chip, designed for low performance, budget applications
   
### Cost Reduction Challenges
- The CH32V003F4P6 is cheaper than Arduino, but less popular so less libraries: code from scratch
- The WS2812 LED is usually programmed as a strip, so programming one individual component is less well documented
- Cheaper components require more programming skill to successfully integrate, the cheaper chip only has basic features and lacks the protection systems of the more expensive one. 

Reducing the cost doesn't decrease the quality of components, it increases the difficulty of the programming for us!


# Assessment of the quality of the proposal

Evaluate its value in the context of the project. 
What will it solve, is it safe, etc. Check Lara’s slides for what to cover.

- Self sufficient product, can be rapidly implemented without new infrastructure requirements.
- Rechargeable battery: does not require grid connection so suitable for rural Ethiopia
- Requirement of 4 hours 40 minutes battery life, to meet local requirements with annually invariant daylight.
- Better to make higher quality, but more robust/repairable could increase cost (tradeoffs)
- Manufacturing and Distribution
  - Noam is planning to donate the boards to local sellers, may have to consider import tax
  - Parts produced in China, assembled in Ethiopia
  - Repairability concerns: soldering is easier for in factory but bolts would be easier to repair in home. 


