# Problem description

Brief overview of the problem, context and engineering approach to tackle the problem:

## Problem in Context: Rural Lighting in Ethiopia

- 43.6% of rural Ethiopia has no access to electricity so rely on kerosene lamps for lighting which cause indoor pollution and health risks <sup>1</sup>
    - Inhaling the fumes from kerosene lamps is equivalent to smoking several packs of cigarettes a day <sup>2</sup>
    - Respiratory diseases caused by kerosene lamps decrease life expectancy <sup>3</sup>
    - Kerosene lamps emit 'black carbon' which contributes to global warming <sup>3</sup>
 
<img src="assets/Gaslight.jpg" alt="Alt Text" width="200" height="300"> 
  
- **Electrification** and the access to lighting have a **positive** impact on the **Human Development Index** <sup>4</sup>
  - Electrification improves life expectancy and QoL within a country <sup>4</sup>

https://www.modernghana.com/news/1381887/why-solar-lanterns-and-shs-failed-in-ethiopia.html

There have been previous attempts to electrify rural villages, however, when something breaks there is most likely no-one there to fix it. 

## Engineering Solution

We are building an **affordable** and **scalable** solar charged battery powered light source for domestic use to replace Kerosene lamps.

A prototype board has already been designed and built by our supervisor, Noam. The aim of our project is to further develop and improve the product.

- Current Issues:
    - Exposed electronics
      - Current exposed electronics are more susceptible to dust and damage, decreasing expected lifespan of the product
    - Inefficient and costly LEDs
      - Currently 3 Red, Orange, Green LEDs to display battery level. Would be cheaper to have just a single RGB LED.
    - Harsh, undiffused light
      - Very bright to look at, risk of damaging the eyes   
    - Needs a discrete boost to replace IC
      - ICs can be expensive

# Presentation of the proposal

Technical aspects:  
There are three components to the project: mechanical, electrical and programming. 

## Mechanical:  
### Case Design:  
Possible but not necessary implementations:
**design constraints in bold**
- **Loop for hanging**
- (clips for clipping)
- Diffusing transparent plastic cover
- **Slots for the USBs**
- Kick stand to angle the panel perpendicular to sun rays
- Dust resistant
- (dust covers for the ports)
- **Cheap**
- **3D printable**
- Acrylic/ PMMA is the likely material to be used

## Electrical/ Programming:  
There are 2 main electrical improvements to be made:

### Implement RGB LED
  - Individual red, orange and green LEDs waste power and money
  - There is already a WS2812 LED on the PCB, but it currently has no code
  
### Replace Integrated Circuit with Boost Converter
 - Both are present on the test boards
 - Current driver is UCC2751x, which is a high performance, expensive chip from Texas Instruments
 - Aim to replace with discrete boost system using RY3730 chip, designed for low performance, budget applications
 - Code needs to be written to incorporate the boost converter into the circuit so that the IC can be removed to reduce cost
   
### Cost Reduction Challenges
- The CH32V003F4P6 is cheaper than Arduino, but less popular so fewer libraries: must write code from scratch
- The WS2812 LED requires code specific to the chip which will require research into its libraries/ documentation in order to program it correctly
- Cheaper components require more programming skill to successfully integrate, the cheaper chip only has basic features and lacks the protection systems of the more expensive one. 

Reducing the cost doesn't decrease the quality of components, it increases the difficulty of the programming for us!


# Assessment of the quality of the proposal

Evaluate its value in the context of the project. 
What will it solve, is it safe, etc. Check Lara’s slides for what to cover.
-
- Responsible
    - Printed Circuit Boards are manufactured with different material compositions and are intrinsically complex generating multiple challenges at the end of 
      life<sup>5</sup>
    - Recycling of the lithium ion batteris brings challenges as the contents are difficult to separate, unlike lead acid batteries 
    - Single purchase/ donation, therefore, no payment plan option is possible for the lighting solution
- Genuine need
    - Light in the home enables more flexible working hours, allowing for breaks during the hottest parts of the day <sup>3</sup>
    - facilitates productive work in the evening, freeing up daytime hours for other income streams<sup>3</sup>
- Adds significant value
    - existing products are more expensive or inaccessible
    - solar infrastructure and hubs are the desired end goal, however, the time frame for implementation is longer
- Accessible
    - Self sufficient product, can be rapidly implemented without new infrastructure requirements
    - Noam is planning to donate the boards to local sellers, a 15% import tax might be applied and need to be considered <sup>6</sup>
    - Parts produced in China and assembled in Ethiopia (mostly soldering)
- Context appropriate
    - Ethiopia has a high solar potential of 5.2KWh/m<sup>2</sup>/day<sup>7</sup>
    - Rechargeable battery: does not require grid connection so it is suitable for rural settings
    - Requirement of 4 hours 40 minutes battery life to meet local requirements. Daylight hours are fairly constant through the year so there will be little variation in requirements annualy 
    - Potentially better to make a higher quality but more expensive product. A more robust/ repairable product would likely be more expensive (tradeoff)
    - Repairability concerns: soldering is better for assembly but bolts would allow for disassembly and potential repair in homes



# References
 1. World Bank Open Data. (n.d.). World Bank Open Data. https://data.worldbank.org/indicator/EG.ELC.ACCS.RU.ZS?end=2023&locations=ET&start=2008
 2. Clair, B. (2022, February 1). Impact of kerosene — PowerWells. PowerWells. https://www.powerwells.org/blog/blog-post-title-three-babra#:~:text=The%20use%20of%20these%20fuels,smoking%2040%20cigarettes%20per%20day.
 3. 2023 Unfccc.int. Available at: https://unfccc.int/climate-action/momentum-for-change/activity-database/momentum-for-change-solar-lighting-in-rural-ethiopia (Accessed: 21 May 2025).
 4. Da Silveira Bezerra, P. B., Callegari, C. L., Ribas, A., Lucena, A. F. P., Portugal-Pereira, J., Koberle, A., Szklo, A., & Schaeffer, R. (2017). The power of light: socio-economic and environmental implications of a rural electrification program in Brazil. Environmental Research Letters, 12(9), 095004. https://doi.org/10.1088/1748-9326/aa7bdd
 5. Patil, T., Rebaioli, L. and Fassi, I. (2022) ‘Cyber-physical systems for end-of-life management of printed circuit boards and Mechatronics Products in home automation: A Review’, Sustainable Materials and Technologies, 32. doi:10.1016/j.susmat.2022.e00422.
 6. Ethiopia - import tariffs. (2024, January 18). International Trade Administration | Trade.gov. https://www.trade.gov/country-commercial-guides/ethiopia-import-tariffs
 7. Bekele Mulatu, A., Ayall Negash, W. and Teshome, M. (2023) ‘The status of solar energy utilization and development in Ethiopia’, American Journal of Applied Scientific Research [Preprint]. doi:10.11648/j.ajasr.20230903.13. 

