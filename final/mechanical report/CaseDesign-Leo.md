## Beny LIGHTS: Protective and Diffusive Case Design  
**Author:** Leo Mills  

### Overview

This document describes the design and testing of the enclosure for the Beny LIGHTS system — a solar-powered light and charger unit developed for low-cost, non-profit use in rural Ethiopia. The enclosure was created to house a battery, PCB, USB connectors, and button actuator, while also diffusing light and protecting the components during handling and transport.

The design was driven by the need for a solution that is simple to assemble, cheap to produce, easy to print on potentially low tolerance 3D printers, and safe for use in close-contact environments, including households with children.

### File Overview  

- Final case design: [CASEv5.SLDPRT](../../CAD/CASEv5.SLDPRT)  
- Pushrod actuator: [rod.SLDPRT](../../CAD/rod.SLDPRT)  
- PCB model: [PCBv2.SLDPRT](../../CAD/PCBv2.SLDPRT)  
- Full assembly: [ASSEMBLYv3curved.SLDASM](../../CAD/ASSEMBLYv3curved.SLDASM)  
- Visual reference: [rendered_light.jpg](../../CAD/rendered_light.jpg)  


### Design Details

The case is fully parametric, with dimension-driven sketches to allow for easy modification. The final version (`CASEv5`) was selected for its balance between strength, printability, and simplicity.

- **Wall thickness**: 1.5 mm (external), 1.0 mm (internal and dome)
- **Material**: Printed in frosted PMMA; compatible with PLA and other basic filaments
- **Shape**: Hemispherical light dome integrated with a rectangular base
- **Ports**: Snap-fit USB-C cutout; slotted opening for USB-A
- **Battery retention**: A zip tie secures the battery and helps hold the case together
- **Orientation**: Designed to rest upside down and at an angle for solar panel charging

The part was designed to print with minimal support structures, reducing print time and material use and, therefore, cost. Multifilament printing could be used to save cost by applying more expensive transparent material only to the dome area and using opaque material elsewhere. The **top surface was kept flat and uniform in height** to avoid overhangs, which minimizes slicer complexity and the need for support material — especially important when printing on basic printers.

### Pushrod Actuator

To activate the internal button, a custom 3D-printed pushrod (`rod.SLDPRT`) was created. It features:

- A flared internal head that prevents the rod from falling out
- A flat, external surface for pressing
- Zero reliance on bolts, nuts, soldering, or adhesives

This design replaced an earlier metal bolt-based mechanism so all components can be 3D printed. It operates with ~1–2 mm of travel and minimal force. However, it is slightly uncomfortable owing to the small surface area on the exposed end required for it to pass through the tube.

### Assembly Process

1. Insert the pushrod into the case's guide tube
2. Snap the case onto the USB-C connector  
3. Insert the battery  
4. Secure the battery with a zip tie — this also locks the case shut  
5. Use the external end of the pushrod to activate the button

No tools are needed aside from scissors to trim the zip tie.

### Testing Summary

- Tested with full internal component setup (PCB, battery, USB ports)
- Case withstood repeated a 1-meter drop onto a stone surface without structural damage
- USB-C cutout was adjusted after early versions cracked at tight corners
- A slicer bug caused one print to seal the battery slot; model geometry was adjusted to prevent this
- Dome performed well in diffusing light using frosted 3D printing filament

### Evaluation

| Strengths                                      | Limitations                                           |
|------------------------------------------------|-------------------------------------------------------|
| Passed repeated drop tests                     | Not weatherproof — no sealing against dust/moisture   |
| Pushrod is printable, low-cost, and reliable   | Zip tie is not reusable — must be cut for access      |
| Fully parametric CAD — easy to modify          | Internal access depends on external port fit          |
| Low part count — minimal fasteners and tools   | Some slicers may mishandle thin dome geometry         |
| Comfortable and safe for handling              | No latch or hinge for reassembly                      |

### Alternate Design: CASEv6

An alternative design (`CASEv6.SLDPRT`) explored a cylindrical extension instead of the original lofted dome for the light diffusion section. This would have produced a more uniform shape but introduced several drawbacks:

- **More external corners**, increasing the risk of injury, especially around children
- **Greater print complexity**, requiring more support material and post-processing  

These trade-offs were not aligned with the project's cost and safety priorities, so `CASEv6` was documented but not implemented. The `CASEv5` design remained preferred due to its simplicity, safety, and printability.

### Deployment Context

This enclosure was developed specifically for **non-profit use in rural Ethiopia**, where access to grid power and commercial lighting is limited. It supports a low-cost solar-powered light/charger system that must be safe, repairable, and manufacturable using local or readily accessible resources to replace the toxic and dangerous gas lights currently used inside homes at night.

Key characteristics include:

- Printable on common, affordable 3D printers
- Assembled with minimal tools
- No screws or proprietary hardware required
- Safe to handle, even in households with children

All mechanical and electrical components are open, modular, and easy to replace. The design is documented for replication, improvement, or adaptation to related off-grid applications.
