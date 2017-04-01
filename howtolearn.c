//learning robotC document
//DO NOT RUN JUST EXAMPLES
task main(){
/*basic tenants of RobotC:
semicolon after every line
parantheses and brackets must be paired up*/

/* MOVEMENT */

motor[motorA] = 50;
//motor name goes inside square brackets
//set motor to a power

//when you set a motor power, it doesn't do anything, so you have to type in a wait
wait1Msec(1000);
//the number that goes inside the parantheses is the number of milliseconds

/* VARIABLES */

//to make a variable, you tell the computer what type of variable it is, and then type the variable name
//this is called declaring a variable
//you can then use "=" to set the variable to a value. This is called "assignment"
//you don't have to assign the variable when you declare the variable, you can just only declare the variable

int turns = 4;
//int is for integers

float distance = 0.0
//float is for decimals

double precise_distance = 0.0;
//double is for super precise decimals

/* SENSING */

//the robot can sense stuff.
//you have to link the sensors inside the program first

//first go into the menu of Robot > Motors and Sensors Setup
//fill out the blanks (self explanatory)



/* HOW TO MAKE ROBOT THINK */

//there are two main things that make the robot think

//while loop
//if statement

//the while loop checks if the statement inside is true
//if it's true, then what's inside the while loop
//until the statement is false

while(SensorValue[Light]<50){
  motor[motorA] = 50;
  motor[motorB] = 50;
}
//there is a way to precisely control the number of degrees the motor turns:
//It is called the motor encoder, and it measures how far the motor has traveled in degrees.

nMotorEncoder[motorB] = 0;
//this resets the motor encoder so it starts reading from 0


}
