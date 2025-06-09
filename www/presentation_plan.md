# Index

- Outline key problem
- Introduce solution BenyLIGHTs
- Outline features with links to technical reports

## Features
### Programming
- Button press increases LED brightness in steps
  - Reduced from 100 to 60 to stop browning out (Lucy)
- Button press also shows LED brightness
  - Multichannel ADC (Lucy)
  - Calibration (Jim)
  - batcount (Jim)
  - averaging (Jim)
- Sun detected the LED mode sets back to zero to save energy
  - averaging (Jim)
- Sleep mode when battery voltage drops below 3.2V (Lucy)
  - averaging: issues when battery drops to 0V if bad connection: sleep when it's not supposed to
  - Button interrupt and __WFI()
  - Need extra button for actual useful product (unrealistic to remake PCB in 4 weeks but will feedback to Noam)
  - Currently uses periodic wakeup and standby mode as proof of concept
- Sleep mode after 2 minutes of LED on 0
  - dsxjsjsgaud

 ### Mechanical
-

Reflective discussion about the work’s alignment with the Sustainable Development
Goals and where applicable with the UNICEF principles for Digital Development. ~500
words, attached to the web page.
