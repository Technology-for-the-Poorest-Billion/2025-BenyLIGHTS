## Beny LIGHTS: Protective and Diffusive Case Design  
**Author:** Leo Mills  

### Overview

This section covers the iterative design and testing of the protective case for the Beny LIGHTS system. The enclosure was developed in SolidWorks and is designed to protect internal electronics (PCB, battery, connectors) while also diffusing light during operation. The case is drop-resistant, compact, and designed for semi-permanent assembly using only printable and low-cost mechanical components.

The final model (`CASEv5.SLDPRT`) meets core functional goals:
- Survives repeated 1-meter drops onto uneven stone surfaces
- Provides effective light diffusion using a shaped translucent dome
- Houses USB-C and USB-A connectors, PCB, battery, and a push-button actuator
- Requires no adhesives or complex fasteners for assembly

### Files and Structure

- Final case design: `CASEv5.SLDPRT`
- Working pushrod: `rod.SLDPRT`
- PCB model: `PCBv2.SLDPRT`
- Full assembly: `ASSEMBLYv3curved.SLDASM`
- Located in: `/CAD/` directory  
- Rendered view with the lights: `rendered_light.jpg`

### Design Summary

- The model is fully parametric, with clean feature history and editable dimensions
- Wall thickness:
  - External walls: **1.5 mm** for durability
  - Internal walls and dome: **1.0 mm** for lightweight design and optical diffusion
- The dome is as close to a hemisphere as geometry and base-plane constraints allow
- Snap-fit feature around USB-C port; USB-A cutout included
- Case is mechanically secured by inserting the battery and applying a **zip tie**
- Designed to rest on a plane with the solar panel exposed during charging

### Button Actuator: Final Solution

A 3D-printable pushrod (`rod.SLDPRT`) was designed to actuate a button inside the case:

- The rod has a **flat shaft with a wider cylindrical end** that stays inside the enclosure
- The **wider internal head prevents the rod from falling out**
- The external end is **flat and comfortable to press**, removing the need for external nuts or bolts
- This replaces earlier bolt-and-nut prototypes, offering a cleaner and more integrated solution
- No soldering, gluing, or tools are required for installation

This design is more ergonomic and reliable while remaining compatible with low-resolution FDM 3D printers.

### Assembly Process

1. **Snap-fit** the case onto the USB-C connector
2. Insert PCB, battery, and pushrod
3. Secure the battery using a **zip tie**, which also locks the case together
4. The pushrod is retained by its internal head and can be pressed from outside

### Testing Observations

- Case was tested with live hardware: PCB, battery, connectors, and pushrod in place
- Earlier iterations showed fractures near the USB-C cutout due to tight corners; clearances were increased
- A slicer bug caused a layer to cover the battery opening — fixed by adjusting wall thickness and model export
- Drop tests showed no structural failures once USB port reinforcements were applied
- A short circuit occurred in one test, but was unrelated to case design
- Pushrod requires **1–2 mm vertical travel** with **minimal force** to actuate the button reliably

### Evaluation

| Strengths                             | Limitations / Areas to Improve                |
|--------------------------------------|-----------------------------------------------|
| Strong physical durability            | Not sealed against moisture or dust           |
| Clean and fully parametric model      | No hinge/latch for reusable assembly          |
| Pushrod solution is ergonomic & printable | Print errors may occur if wall settings vary |
| Compact and functional layout         | Snap-fits rely on precise port positioning     |

### Recommendations for Future Work

- Add **gasket or lip** features for weather sealing
- Design a **tool-free locking or hinge mechanism** for maintainability
- Replace the zip tie with a **reusable mechanical clip**
- Use a **diffuse textured pattern** on the dome interior to improve light scattering
- Recheck slicer compatibility and document ideal print settings
- Ensure **PCB layout** accommodates mechanical features like the button pushrod

