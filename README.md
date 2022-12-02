# POB_SLAM
**P**rototype **O**ptimization-**B**ased SLAM. A pet-project.  
### To-do:
 - Write a Ceres optimizer for one step. From P1 -> P2. DONE
     * Problem: Optimizer doesn't work well for some number of landmarks i.e. when the two landmarks are on the same line the optimizer finds the wrong direction. **Derive a robust error term**
 - Write the optimizer for an arbitary number of steps. 
 - Write the optimizer to work interacitvely in command line. 
     - Causing to call the optimizer on each command.
 - Write a text based visualizer of robot moving in a 2D plane
