# POB_SLAM
**P**rototype **O**ptimization-**B**ased SLAM. A pet-project.  

Note: everything is computed in double terms but when it calls for visualize

### Design and pseudocode
Initialize.
Draw the 2 plot graph: true and estimated trajectory.
In the loop:
    Get command: get direction with helper, get length of movement.
        Forward command to robot.
    Implicitly call Localizer to localize.
        Localizer calls sensor to get a measurement. Total of four (one for each landmark).
            Sensor has a robust sense of the angle between orientation and vector from robot to landmark
        Optimizer:
            creates a new problem
            creates 4 residuals
            adds residuals to the problem
            solves the problem, outputs the result and returns the result to the caller
    Draw localized and true point

### To-do:
 - Write a Ceres optimizer for one step. From P1 -> P2. DONE
     * Problem: Optimizer doesn't work well for some number of landmarks i.e. when the two landmarks are on the same line the optimizer finds the wrong direction. **Derive a robust error term**
 - Write the optimizer for an arbitary number of steps. 
 - Write the optimizer to work interacitvely in command line. 
     - Causing to call the optimizer on each command.
 - Write a text based visualizer of robot moving in a 2D plane
