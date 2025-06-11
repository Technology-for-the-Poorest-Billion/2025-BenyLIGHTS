## Beny LIGHTS: Protective and Diffusive Case Design  
**Author:** Samuel Hinks 

### Overview

This document focuses on the production, testing and finalising of a 3D-printable case for the BenyLIGHTS PCB mounted light. The intention throughout this process was to create a design that, while fulfilling its design function, was simple to 3D print, replicable, and modifiable by future users. This was with the vision of creating a case that would be printable with limited equipment, and open to modification by someone not fully trained in CAD software, should the design of the PCB change.

### File Links 
#### The primary output:
- Final OpenSCAD model of the case [openscad_case](/CAD/openscad_case) - ready to be exported as an STL
- STL of final case model [final_case](/CAD/final_case.stl) - ready to be exported to printing compiler
#### Other useful links
- OpenSCAD PCB model [PCB_model_SCAD](/CAD/PCB_model_SCAD) - potentially useful for checking case fit
- Full assembly [OpenSCAD_Assembly](/CAD/OpenSCAD_Assembly) - approximate model of the compelte assembly
- Battery Jig used for testing [Battery_Jig](/CAD/Battery_Jig) - works in supporting battery in lieu of a zip-tie

### Challenges of compiling the 3D Print
One of the first challenges to be overcome in 3D printing this case was ensuring that it compiled well, even on the lower quality software used by the cheapest of the department's printers. A layering error in Solidworks has meant an overlap between lines in the STL file, and the compiler that readied the 3D prints was misinterpreting this and inverting the lower section of the print, printing where there should have been void, and leaving voids where supports were required. The GCode outputted by the compiler is shown below, followed by the desired GCode - the void that should be present to allow space for the battery is clearly seen to be filled in in the first image.


![image](https://github.com/user-attachments/assets/db4a00d0-7441-41b2-8314-ad59514a5eec)
#### Flawed GCode


![image](https://github.com/user-attachments/assets/cb0085da-0996-4d35-aba9-4954e32c9847) 
#### Desired GCode

As can doubtless be deduced from the presence of correctly compiled GCode, we resolved this issue. This was done by changing the Solidworks sketch from which the STL file was derived and by changing the design of the case to lessen the impact of any other compilation error. Happily, when the OpenSCAD case model was ready, no such issue was observed with the production of the STL file.

### 3D printing limitations
In creating this case, we used the lower standard range of 3D printers available in the department. This was partly a cost associated decision where we wished to replicate budget production conditions, but also aprtly because they were supplied with a roll of transparent PLA. We, correctly, surmised that when printed over the curved surface of our case this "transparent" filament would become translucent. This was a positive result for us, since it is the translucency that helps the case to diffuse the light well. Therefore, this apparent limitation of the 3D printing is really an advantage. We envisage that were these cases to be produced en masse, it would be best to do it with a low cost home-run 3D printer, to keep costs low and generate this same effect. Alternatively, if high cost low quality printing is available, it may be possible to request a rough finish to refract light.

### Testing of the 3D prints
Once we were able to print prototypes, a few minor dimensional modifications were required, espeically woith the tolerances around the USB port and push rod holes. These components were a tight fit, and some corners of the case cracked when the prototypes clipped into place. The hole for the push rod was espeically problematic, as with the low resolution of the printers available it had a tendency to fill up with filament. A fairly wide diameter of 4mm prevented this, leaving space for the push rod to move freely.

Having created a well fitted and robust case design, we began testing of the case in two forms: diffusion testing and protection testing.
#### Light Diffusion
To test the diffusive effectiveness of the case, we activated the lights in a dark room, and measured light levels using a light detector built into a phone. We measured light levels between 0 and 3 meters, directly and indirectly. The tables and graphs below show the resutls of this testing. Overall, it showed a reduction in the intensity of light directly in front of the LEDs, as desired, with an increase in the intensity of light levels perpendicular to the case, as intended. This increase in light levels was roughly of an order of 2.
Direct Viewing:
| Distance  (Metres)             | Intensity without case (Lux)         | Intensity with case (Lux) |
|--------------------|-----------------------------|----------------------------
| 0                                 | 170   | 80|
| 1   | 30     | 22|
| 2         | 9         | 7 |
| 3   | 5         | 3|

Indirect Viewing:
| Distance  (Metres)             | Intensity without case (Lux)         | Intensity with case (Lux) |
|--------------------|-----------------------------|----------------------------
| 0                                 | 10   | 23|
| 1   | 3   | 5|
| 2         | 0         | 1 |
| 3   | 0         | 0|


<img width="450" alt="image" src="https://github.com/user-attachments/assets/8fdca3a4-1ae5-410e-9b68-2ecf31b5ef29" />

#### Strength 
In order to test the strength of the case and its protective capacity, we conducted several drop tests outside. These were conducted on two different surfaces - a flat, but hard concrete, and an uneven surface of large rocks. We observed several things through these tests. Noticeably, the case survived the test, but in some cases did not prevent the board from suffering damage. For instance, the soldered connection to one of the battery supports was broken in one test, although fixing this would be simple for a technician. More critically, a second test damaged the USB-A port, as the board landed directly on it. This dented the port and separated its solder connections, wich was a more critical fault. Correspondingly, the case was modified to protrude over the USB-A port, as seen in this image.

<img width="547" alt="image" src="https://github.com/user-attachments/assets/dba25db9-4cf5-4c8b-84d6-e13adb4906aa" />


### Modelling in OpenSCAD
In achieving the desired aim of creating a case model that was able to be shared easily online, it was important to ensure that the final assembly (`openscad_case`) was a fairly simple construction. However, design at this point was ongoing with the main 3D printed assembly using Solidworks, which creates more complex curves. It was necessary to simplify the design somewhat using basic hemispheres,cuboids and hull shapes. However, the result was a close approximation of the initial designs which performed well in tests. Having created this model in OpenSCAD, it was then parameterised carefully, with all salient dimensions and some notes for potential future editors placed at the top of the file. With everything labelled, the hope is that even without much knowledge of OpenSCAD specifically, someone at least familiar with basic programming should be able to make minor modifications to the design.

### Taking this forward

The case was designed to be cheap and simple to print on a budget, and not overly complex. With the exception of the push rod, the whole case can be made with a single print, and then all that is required is the removal of whatever external supports the printer applies. Some external supports are advisable, but no internal supports are needed, reducing print effort. Additionally, were other engineers to approach this problem, they should be able to simply and rapidly modify the files for the case design if they chose to, streamlining the process if a 3rd version of the BenyLIGHTS PCB was created and required a new case.
