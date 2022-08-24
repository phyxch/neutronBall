Radon Emanation & Soil Model Simulation
=======================================

commands:

/vis/viewer/set/style surface OR wireframe
/vis/viewer/addCutAwayPlane 0 1 0 

<br/>

<hr/>

## Instructions to run simulation

* build the code in directory build_nb : using cmake ../neutronBall
* cd build_nb
* ./neutronBall
* under session textbox type: /control/execute fullChain.mac

## Note:

Initially beamOn was set on 100,000 particles but it takes more than 15 mins to run the simulation. Hence beamOn is set to 1000 particles only.

## Tasks:

- [ ] understand varible naming conventions and different data members 
