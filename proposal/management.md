# Project management plan


## The people

The project was initially proposed as an electrical project, but the team includes 3 mechanical engineers and 1 electrical engineer.
Electrical expertise required to bridge the gap between software and hardware, but after this has been achieved, all team members can contribute to the programming. We also chose to extend the project to further develop the mechanical side of the product, by designing and building a case with a light diffuser. 

### Lucy  
- Experience in coding from degree projects
- B modules provide electrical knowledge on boost converters
- Training required in programming CH32V003F4P6 using MounRiver Studio, provided by YouTube videos

### Samuel 
- Gained Solidworks expertise in first year internship
- Resident SCAD expert, self taught 

### Jim  
- Jim of all trades: knowledge in all engineering areas
- Information gatherer

### Leo
- 15 years of manufacturing experience
- Case fanatic
- Cyborg brain

## The resources needed

### Mechanical Resources
- Laser cutter
- 3D printing
- PCBs/soldering

### Electrical Resources
- Circuit boards to practice on
- Driver Cable
- Batteries

## The timeline

### Week 1
- Identify key challenges
- Matching team members with task that align with their strengths
- Propose feasible solutions
- Familiarisation with new software
  - SCAD
  - MounRiver Studio

### Week 2
#### Mechanical
- Produce CAD files
- Have first prototype of the case produced
- Begin testing diffuser materials/design
- Solder battery connections to breadboards

#### Electrical
- Complete training videos on programming the CH32V003F4P6
- Communicate with RGB LED
- Begin to test code for discrete boost

### Week 3
*Dependent on progress made in week 2*

#### Mechanical
- Further testing on case and diffuser designs
- Finalise manufacturing choices (soldering vs bolts)

#### Electrical
- Complete code for RGB LED
- Fully change from IC to discrete boost


#### Week 4
*Final changes before project output submission*

#### Mechanical
- Produce and assemble final product

#### Electrical
- Explore further improvements on code above and beyond the brief
- Test the discrete boost on the PCB by measuring output voltage using oscilloscope
- Test combined system of WS8212 driven by discrete boost power system



## The assessment of the risks and safety
| Category         | Risk Description                                                                 | Mitigation Strategy                                                                 |
|------------------|----------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| **Electrical**   | Overcharging the battery (Li-ion or LiFePO₄)                                     | Use a charge controller                                                            |
|                  | High voltage from solar panels                                                   | Design for low-voltage systems                                                     |
| **Thermal**      | Overheating due to LED heat generated                                            | Use heat-tolerant materials, ventilation, and heat sinks where needed              |
| **Mechanical**   | Panel or enclosure damage from impact or rough handling                          | Use strong materials to withstand damage                                           |
|                  | Battery puncture or crush leading to fire or failure                             | Handle the boards with care and store in plastic container                         |
| **User-related** | Eye damage from bright LEDs                                                      | Use lowest brightness possible for testing, build cover asap                       |
| **Battery**      | Improper disposal or exposure to open flames                                     | Include safety labels and user education on battery handling and disposal          |



## Contingency plans
- Device already works, so can fall back on this if coding doesn't work
- Can shift the focus to the case
- Electrical mistakes can blow the boards, we have a limited supply
  - Take care when connecting board and make sure there is a control system in place to prevent the boards from blowing
  - Run simulations before connecting the board to identify any possible mistakes

