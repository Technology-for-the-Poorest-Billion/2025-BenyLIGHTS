Focus on our unique strengths as a team: 
- Noam has the expertise to develop the electronics
- Mechanical engineering of the case is a unique solution that we can contribute, especially diffusion of light
- We bring value in the difficulty of engineers building/fixing the board
- Challenges we face whilst understanding the project are the same as the challenges that will be faced by the engineers in Ethiopia
- Focus on documenting the solutions to challenges that we face, to make the process easier for the engineers in Ethiopia

Look at competitors: D-light
BenyLIGHTs has the advantage of being assembled in Ethiopia, which competitors cannot bring
Cheaper because avoids import tax etc

Things to clarify with Noam:
- Where is the manufacturing happening, is it in China or Ethiopia?
- Ask what is unique compared to D-lights, how this product is different
- Feedback was to focus more on the documentation than the coding
- What to do if we can't get the LED to light up?
- Propose ideas on case and diffuser

Takeaways from meeting with Noam:
Electrical:
- LED and dicrete boost are not the priority: these are added extras
- Priority is getting circuit functional
- Big board doesn't light up because it needs the battery connection: possibly need to enable 5V 5VEN pin to get it working
- Start by getting BAt to USB boost converter to work, then apply similar code to the Bat to LED section
- Boost converter diagrams from Noam are on ipad
- Smaller board requires higher Vout because boosting up from 5V
- Bigger board requires output of 5V, boosted up from the battery which is between 3-4.2V
- Goal is to get the basic operation working before trying to reduce cost

Manufacturing/setup:
- Raw materials are taxed less than complete product
- Raw materials are shipped into Ethiopia and final product is assembled in Ethiopia, to minimise taxes
- Around 5 workers in Ethiopia, with 2 trained to solder
- Most likely ways of failing
  - 95% of failures come from battery: make battery easy to replace using ziptie
  - 4% of failures come from push button getting stuck: replaceable by removing case?
  - Remaining failures with electrical components etc are very unlikely
 
Case:
- Frosted material should be used, not transparent
- Setup should ideally be slanted
- Explore options of screws and soldering to attach case
- Red orange green LEDs may need to be moved so they can be displayed, not covered by casing

