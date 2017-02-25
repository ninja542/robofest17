task main()
{
nMotorEncoder[motorB] = 0;
nMotorEncoder[motorC] = 0;
float circum = 5.6 * 3.14159;
float degdist = circum/360;
motor[motorB] = 50;
motor[motorC] = 50;
wait1Msec(1000);
motor[motorB] = 0;
motor[motorC] = 0;
float distance = degdist*(nMotorEncoder[motorB]);
displayTextLine(3, "distance:%f", distance);
wait1Msec(3000);

}
