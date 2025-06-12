# Final contributions report   

Across the duration of the project, i worked on a range of the deliverables. Initially this meant research around the ecosystem which the product will be implemented into, focussing on evaluating the constraints Noam had established and aiming to quantify how responsible the innovation is in the context of the problem. Further development and clarification on this came both after the proposal presentation and the second meeting with Noam. As well as this, hardware work was required on the PCBs. These contributions occured as we were establishing the electrical and mechanical sub-teams. From then on, the main focus was programming with Lucy. In the last week of the project i conducted some proof of concept case work with the dyson centre vacuum former. There was a delay in getting the vacuum former working and testing was dependant on the technician availability meaning i ran out of time. This kept this somwhat standalone and hasnt been incorporated into the presentations due to the incompleteness of this exploration. 

## Technical aspects covered in this document
- Hardware improvements
- Multichannel ADC initialisation
- Battery feedback calibration
- LED battery status method
- Averaging for sleep mode
- Sun detection
- Vacuum forming exploration

## Hardware work
I soldered the battery tabs on to make all the provided PCBs compatible with batteries and soldered a solar panel enabling recharging tests. As well as this, the link used to upload the code to the microprocessor was tempremental so needed improving, this involved sourcing a stackable header to replace the crimp connectors and solder with heat shrink to form a more robust and reliable connector to the board.

<img src="https://github.com/user-attachments/assets/10359e71-8a03-48a1-8b19-658339ee1749" alt="Alt Text" width = "200" height = "auto" > 
<img src="https://github.com/user-attachments/assets/40b017b3-633a-459c-94f5-c3fb7f206591" alt="Alt Text" width = "200" height = "auto" > 
<img src="https://github.com/user-attachments/assets/f2514679-2f2c-4216-b054-9af071d4101a" alt="Alt Text" width = "200" height = "auto" > 

## Programming contributions 
Me and Lucy worked together on lots of the programming, further detail can be found both on [Lucy](Lucy_Report)'s page and for fully commented code all iterations are available on the [code](code) page.
### Battery status 
Noam specified that upon pressing the button the charge status of the battery would be displayed for 10 seconds using the coloured LEDs. The charge status can be inferred from the voltage across the battery which needs to be recieved through the boards feedback infrastructure.
#### Multi-channel ADC
Upon the user pressing the button on the board, as well as increasing the brightness of the white LEDs, the coloured LEDs are required to display the battery voltage. In order to implement this, we obtain the battery voltage using the **getFB_BAT()** function, which pulls values from a buffer used to store values that are read using the multichannel ADC. 

The code we received from Noam initialised a single channel ADC, which obtained the USB voltage used for regulating the PWM_USB so we had to implement a 4 channel ADC to gather new FB values. 

There are 4 sampling channels available from the circuit diagram which we can access with the microcontroller by initialising a multichannel ADC. 
  - **FB_USB** (PC4/A2) Channel 1
  - **FB_SOLAR** (PA2/A0) Channel 2
  - **FB_BAT** (PD4/A7) Channel 3
  - **FB_ILED** (PD3/A4) Channel 4
    
#### Calibration
Now able to recieve a 10 bit value from these feedback channels the battery value needs to be calibrated to account for the relative resistors in the potential divider and return an accurate voltage reading. This was done by sequentially draining the battery and using voltmeter as well as the serial moniter to plot ADC values and voltage measurements. From this a linear relationship was observed and enabled a simple coeficient to convert the ADC value to the battery voltage.

<img src="https://github.com/user-attachments/assets/f49cfa9e-fc85-4d3a-a35d-d5480c50ba74" alt="Alt Text" width = "500" height = "auto" > 

#### Using the LEDs 
Armed with the calibrated battery voltage we could write the code for the LEDs to display the battery status for 10 seconds upon button press. There was many ways to implement this however we decided to choose a counter than incremented each time through the main **while** loop. Upon a button press this counter was reset to zero and outside of the button press code an **if** statement incorporated the LED status by turning them on if the **batcount** was less than a specified value **statusledtime**. This meant that after a button was pressed the code looped through this if statement so long as the **batcount** remained less than **statusledtime**. Inside the **if** statement, comparitors were used to selectively light up the different LEDs depending on voltage thresholds specified in the code. The designated low middle and fully charges thresholds, as well as **statusledtime** will need adjusting to produce the desired duration and appropriate colour associated with charge level of the battery.

### Averaging to incorporate sleepmode 
In order to prevent the battery charge dropping to damaging levels, a low power sleep mode was to be incorporated that engaged when the calibrated battery voltage dropped below 3.2V. This was implemented using interupts and is discussed further on [Lucy](Lucy_Report)'s page. One of the issues we faced in implementing this was that the comparison with a value that wasnt averaged was prone to sleep mode based on quick dips in battery voltage. This occured when the white LEDs were on the brighter settings with the voltage dip potentially amplified in the ADC measurements. And also occured with physical movement of the battery and potentially requires a more rigid support structure to mitigate this discrepency in voltage reading.

In order to combat this a simple iterative averaging function was implemented and the code used this value to dictate wether to sleep. This however gave rise to another issue in that if sleep mode was entered, when woken up the code loops back one time until the **if** statement is hit with the average only having one more datapoint and thus waking up can become a very long process if an effective average with many datapoints was to be used. The remedy for this was to incorporate the averaging of the battery voltage value in a self contained **for** loop such that an average is made each iteration of the main while loop.

There is however issues with this fix, a longer average is more robust to sudden dips that shouldn't constitute triggering sleep mode. But averaging over longer occupies the code making it neglect user imputs such as button presses whilst it is occupied with looping to average each time. A compromise was made for **samples** to be around 100 such that individual spikes are smoothed yet the code is still responsive to button presses. This does seem to uncover some deaper issues with the architecture of our code, with potential future changes to use running averages and button interupts rather than using the main while loop for LED changes. 

### Sun detection
From the multichannel ADC data it was required as an energy saving measure to turn the white LEDs off if solar supply is detected. There was insufficeint time for full calibration of the solar pannel to produce an accurate voltage reading within the code from the ADC signal. Despite this, we wrote code that took an uncalibrated value and compared to a threshold value currently set to be 0.27, and appears below the button press code such that with solar voltage detected the white LEDs PMW are set to zero, overiding the button press. Although the button press is overiden in terms of controlling the white LEDs, the batcount is still returned to zero and as such the status LEDs still show battery status for 10 seconds during charging which is important to preserve. 

## Case manufacture exploration 
The convex thin shape of the case could potentially lend itself to be vacuum formed out of plastic sheet. This has the potential to be much more affordable at scale compared to 3D printing. In order to explore this avenue i used one of the damaged PCBs and an early iteration of 3D printed case design to create a proof of concept mould for vaccuum forming. Holes were drilled across the combined part in order to ensure vacuum force could be applied uniformly. This was tested on the Dyson centre vacuum forming to give an idea of how feasible this manufacturing route could be and wether the results could match the performance of the 3D printed cases. 

Due to the time constraints only one iteration of the vacuum formed case could be performed. The 3D printed form used to vacuum around held up well across the thicker portions however the high temperature caused the thin diffuser element on the early PLA prototype to flatten. This is a problem, however it is easily fixed by either printing a thicker reinforced dome, or better, 3D routing a wooden block in the required shape. These would both ensure repeatability and accuracy of the produced part.

The mechanical properties of this case were not rigourously tested however there is definately potential with comparable qualitative strength and rigidity to the 3D print. Some benefits could be that the case provides a fully enclosed battery compartment which may aid in dust protection.

Further work is required to evaluate the diffusive capabilities with PLA colour options and potentially other plastics/thickness sheets needing to be tested. Also refine the process with better moulding that produces repeatable outputs. Care will be needed to integrate the button access as well as ensuring the status LEDs are visible through the case. The strategy to secure the battery may also need work as forming around the tabs creates a cavity that could lead to inconsistent connections. And finally, developing an effective mounting strategy wether that be with glue, mechanical fasteners or friction press fit that ensures a reliable connection to the PCB will be important. 

<img src="https://github.com/user-attachments/assets/6edc0e43-20a9-4def-be17-9e4c2de4bff5" width="500"/>
<img src="https://github.com/user-attachments/assets/7586e114-db21-4b71-9598-86453e2277ac" width="500"/>

## Conclusions 
Throughout the project, I contributed to research around the responsibility and context of the solution as well as the hardware and software progression. Collaborating closely with Lucy, I helped develop key features including multichannel ADC battery voltage measurement, calibrated battery status LED display, sleep mode with voltage averaging to prevent false triggers, and solar detection to conserve power. In the final stage, I explored vacuum forming as a scalable manufacturing method for the case, producing a proof-of-concept mold and part, though time constraints limited further testing and integration. During the 4 weeks, lots was learnt both regarding the specifics of this issue in Ethiopia as well as generic skills such as programming in C and familiarity with PCBs and there accompanying circuit diagrams. Working in a team as well as communicating and leazing with an external supervisor/entity being Noam and Beny LIGHTS developed lots of interpersonal skills. The clear documentation and distinct code version uploads available in this repository and on the website should provide strong foundations for further development. I hope the contributions we have made bring us closer to kerosene lamps being replaced by Beny LIGHTS in rural Ethiopian homes.  


*Written by Jim*


