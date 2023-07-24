# Step-Motor-Control-Class
Developed virtual base class called Motorbase consisting of pure virtual functions. Serves as base for derived child classes for different types of motors such as step motor and large motors. Class consists of different functions, each invoking a different control to the motors. motorClassControl file sends the instructions to the specified motor. 
Motor instructions follow code: 
First two digits specify motor, last 3 digits specify function
Example: 01-002 states send instruction to motor 1, and 002 tells motor to rotate counterclockwise. 
Instructions: 
000 = stop rotating
001 = rotate clockwise
002 = rotate Anticlockwise
003 = Speed1 (speed 5)
004 = Speed2 (speed 8)
005 = speed3 (speed 10)
006 = sleep1 (sleep 1000MS and stop operation)
007 = sleep1 (sleep 3000MS and stop operation)
008 = sleep1 (sleep 5000MS and stop operation)

01001 - start motor1 rotate clockwise
01008 - stop rotate after 5 seconds
01006 - idle for 1 second
01002 - start motor2 anticlockwise
