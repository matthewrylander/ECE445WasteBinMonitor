1/30/2024 - Group met up and did initial discussion on how to build the overall circuit, tried to use ultrasonic sensor board with the ESP and tested range. I worked on looking at the specs of various components and summing up power requirements.

2/4/2024 - Project proposal work as a group, completed team contract. Created visual aid and requirements list, with specific power requirements of all components.

2/13/2024 - Unable to attend TA meeting, talked with group later on about the things that needed to be changed for the project proposal

2/14/2024 - Group met up to talk about changes needed for the project proposal, changed visual aid and talked about new requirements for simplifying high level requirements and R/V tables.


2/16/2024 - Made initial version of schematic for the tag. Took portions of ESP32 example circuit needed from website (programming circuit) and added connectors for the sensors on the trash tag.
![image](https://github.com/matthewrylander/ECE445WasteBinMonitor/assets/22122062/0bf9d769-cccb-4bf1-ab21-02c8764a10e8)


2/18/2024 - Completed the modified visual aid, added R/V tables with concrete numbers to project proposal
![image](https://github.com/matthewrylander/ECE445WasteBinMonitor/assets/22122062/4ef5606d-85eb-4073-9aa0-2b2af9b847fc)

2/20/2024 - Met with TA to discuss the corrected Project Proposal, made suggested changes (adding numbers to requirements side of R/V tables) and submitted new Project Proposal. Made mockup 3d models.
![image](https://github.com/matthewrylander/ECE445WasteBinMonitor/assets/22122062/3a42c7f1-aaee-4cec-ad21-26760dfd77d9)
![image](https://github.com/matthewrylander/ECE445WasteBinMonitor/assets/22122062/c6235dc3-b4c5-4625-82f2-63877547e434)


2/21/2024 - Added custom footprints, footprint assignemnts to schematic. Corrected schematic symbols with N.C. connections. Created V1 of the Sensor Tag layout

2/24/2024 - Created V2 of the sensor tag layout, passed pcbway trial. Discussed with group the parts available for powering the board (micro usb from lab). Identified issues such as missing ground planes.
![image](https://github.com/matthewrylander/ECE445WasteBinMonitor/assets/22122062/11d0162b-a267-4b12-babe-2509f69b5fc1)

2/25/2024 - Created V1 of the Hub board layout
![image](https://github.com/matthewrylander/ECE445WasteBinMonitor/assets/22122062/27baf644-486e-4084-a685-228c6527ef88)


2/26/2024 - Met to prepare design review for the 27th. Discussed remaining part acquisition with group.

2/29/2024 - Prepped for PCB design review. Determined that we needed to change everything to 0805 (was usuing 0604), and change footprint to the correct footprint for regulator (I was confused by the many different variations with different pinouts on the datasheet)

3/1/2024 - PCB Design review. Determined that the main changes on the layout should be to remove ground planes and signals beneath the ESP-32. 

3/5/2024 - TA meeting: Talked about changing high level requirements format, talked about how the focus would be explaining the choice of battery power over a usb cable and how the ZMOD sensor categorizes air quality.

On leave for the week of the 7th due to club sport/tournament. Communicated remotely and was updated to the status of the soldering.

4/11/2024
Communicated with remotely after Matt and Allen soldered sensor board. Talked about what I would work on after I got back to campus and worked out the modifications I would have to make in order to fit the cases and 3d print them successfully. Ordered m3 screws online for case assembly.

4/13/2024
Arrived back on campus and started working on bringing my 3d printer online after a year of disuse and 3d modelling the cases. Measured the locations of the openings for the sensors and figured out how to stack the screen on top of the hub board to integrate them in one case.

4/14/2024 
Started printing hub case, ran into several issues related to printer underextrusion and adhesion. Multiple failed prints and printer tuning.

4/15/2024 
Talked with group about progress on the prints. Continued to run into various printer issues and fixing them one by one. (cleaned bed, cold pull on printer nozzle, replaced the extruder springs, oiled the z axis screw, generally just a massive pain). Around ~10-15 failed prints at this point, about half of which failed halfway thru due to extruder clogs or z axis skipping. See image: underextrusion that later led to a nozzle clog. and failed the print 70% thru.
![IMG_3890](https://github.com/matthewrylander/ECE445WasteBinMonitor/assets/22122062/371ca050-84e7-4acc-b67a-73c2123208e3)


4/16/24
Met with the group. Hub board didn't work due to me sitting on the hub board while modelling it. We desoldered various components until we figured out that the issue was the microusb plug, which we promptly replaced via a microusb from an old experimental board with the heat gun. Got it to work again and mount inside the hub case. We decided to order some project boxes in case the case for the sensor boards also ran into printing issues. The hub case lid was yet to be printed.
![IMG_3891](https://github.com/matthewrylander/ECE445WasteBinMonitor/assets/22122062/27d997fa-91c3-4433-8d3c-114559739b82)


4/17/24
Got the first sensor case printed with no issues. Printed the cover of the hub case lid which fit after a bit of filing/sanding. One of the sensors was slightly misaligned so the case cover didn't fit, but it otherwise worked. Modelled V2 of the case with a few QOL improvements (chamfered edges for the lid to slide into place, adjusted sensor hole positioning, adjusted support settings for printing)

4/18/24 
Got the working final version of the sensor case printed out successfully. Updated the team remotely about the success and dropped off the parts for calibration in the locker.

4/20/24
Communicated with team remotely about my responsibilities regarding prepping for the demo. Highlighted the sections I would be working on in the final report.

4/22/24
30 min before the demo, made some minor changes to the case regarding final assembly and adding inset nuts. Assembled all the cases together for the demo.
![IMG_3892](https://github.com/matthewrylander/ECE445WasteBinMonitor/assets/22122062/02451e4c-60c6-4b92-9845-a520458637ab)


4/25/24
Finished up slides for presentation.
