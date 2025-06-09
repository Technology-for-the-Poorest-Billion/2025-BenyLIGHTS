---
title: BenyLIGHTS
---

## The Problem: Rural Lighting in Ethiopia

- 43.6% of rural Ethiopia has no access to electricity so rely on kerosene lamps for lighting which cause indoor pollution and health risks <sup>1</sup>
    - Inhaling the fumes from kerosene lamps is equivalent to smoking several packs of cigarettes a day <sup>2</sup>
    - Respiratory diseases caused by kerosene lamps decrease life expectancy <sup>3</sup>
    - Kerosene lamps emit 'black carbon' which contributes to global warming <sup>3</sup>
 
<img src="assets/Gaslight.jpg" alt="Alt Text" width="200" height="300"> 
  
- **Electrification** and the access to lighting have a **positive** impact on the **Human Development Index** <sup>4</sup>
  - Electrification improves life expectancy and quality of life within a country <sup>4</sup>

There have been previous attempts to electrify rural villages, however, when something breaks there is most likely no-one there to fix it. 

## The Solution: Beny LIGHTs

### Starting Point

At the start of this project, we had a PCB with no case and which only had basic functionality. The LEDs were too bright to look at with the naked eye and the coloured LEDs simply counted up in binary, providing no meaningful implementation. Over the four weeks of this project, we have designed and prototyped a case to protect the electronics and diffuse light effectively. We have programmed the user interface of the board, so that the battery charge level can be displayed by the coloured LEDs. We also investigated some energy saving measures like introducing sleep mode and sun detection to minimise unnecessary power usage.

The light has the following features, and each feature has a link to it's technical implementation. 

#### Button Functionality
- Button press [increases LED brightness](Lucy.md) in steps
  - Reduced from 100 to 60 to stop browning out (Lucy)
- Button press also shows battery voltage on red, orange, green LEDs
  - Multichannel ADC (Lucy)
  - Calibration (Jim)
  - batcount (Jim)
  - averaging (Jim)

#### Power Conservation
- Sleep mode when battery voltage drops below 3.2V (Lucy)
  - averaging: issues when battery drops to 0V if bad connection: sleep when it's not supposed to
  - Button interrupt and __WFI()
  - Need extra button for actual useful product (unrealistic to remake PCB in 4 weeks but will feedback to Noam)
  - Currently uses periodic wakeup and standby mode as proof of concept
- Sleep mode after 2 minutes of LED on 0
- Sun detected the LED mode sets back to zero to save energy




### To configure your website:

- The required files to run a basic website are included in the repository. We use here Jekyll to turn markdown files into html that will be automatically updated on the website. The component responsible for this is a GitHub action, which is specified in the folder .github/workflows. There is no need to change this file. However:

- In the settings of your repository, go the section "Pages", and select GitHub Actions in the drop down menu to indicate that this is the way you'd like the webpage to be generated.

- Each time you update the markdown files in the www folder of the repository, it will regenerate the web content. The address of the website will be:

```
https://technology-for-the-poorest-billion.github.io/[your repo name here]
```

- index.md is the root of your website. To link another page from here, located within the www folder, use the following syntax:

```
This is a [link](linkedpage.md) to interesting content.
```

Which results in:

This is a [link](linkedpage.md) to interesting content.

- Pay attention to the header of the markdown files in this section. It contains a title section that you will need to reproduce for each page to render them properly.


