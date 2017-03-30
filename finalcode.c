#pragma config(Sensor, S1,     upLight,        sensorLightActive)
#pragma config(Sensor, S2,     leftLight,      sensorEV3_Color)
#pragma config(Sensor, S3,     Ultrasonic,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     rightLight,     sensorEV3_Color)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
void resetEncoder(){
	/* reset motor encoder */
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
}
void bathit(){
	nMotorEncoder[motorA] = 0;
	while(nMotorEncoder[motorA] < 50){
		motor[motorA] = 75;
	}
	motor[motorA] = 0;
	nMotorEncoder[motorA] = 0; //reset motor encoder
	while(nMotorEncoder[motorA] > -50){
		motor[motorA] = -5;
	}
}
void numbturns(int turns){
	while(turns>0){
		nMotorEncoder[motorB] = 0;
		while(nMotorEncoder[motorB]>-176){                   //trying to turn left 90 degrees
			motor[motorB]=-25;
			motor[motorC]=25;
		}
		motor[motorB]=0;
		motor[motorC]=0;
		wait1Msec(250);
		turns--;
	}
}
void numbright(int turn){
	while(turn>0){
		nMotorEncoder[motorB] = 0;
		while(nMotorEncoder[motorB]<176){
			motor[motorB]=25;
			motor[motorC]=-25;
		}
		motor[motorB]=0;
		motor[motorC]=0;
		turn--;
	}
}
float measuredist(){
	/*Floaty tings */
	float circum = 5.6 * 3.14159;
	float degdist = circum/360;
	float distance = degdist*(nMotorEncoder[motorB]);
	return distance;
}
void alignment(){
	int lightThresh = 40;
		//orientation against a line (not too angled)
	while((SensorValue(leftLight)>lightThresh) && (SensorValue(rightLight)>lightThresh)){
		nMotorEncoder[motorB]=0;
		while(nMotorEncoder[motorB]<30){
			motor[motorB] = 25;
			motor[motorC] = 0;
		}
		nMotorEncoder[motorC]=0;
		while(nMotorEncoder[motorC]<30){
			motor[motorB] = 0;
			motor[motorC] = 25;
		}
	}
	if(SensorValue(leftLight)<lightThresh){
		while(SensorValue(rightLight)>lightThresh){
			motor[motorB] = 0;
			motor[motorC] = 25;
		}
	}
	else{
		while(SensorValue(leftLight)>lightThresh){
			motor[motorB] = 25;
			motor[motorC] = 0;
		}
	}
}
task main()
{
	//INPUTS GO HERE TADAAA
int lightThresh = 35;
float length = 100.3;         /* Distance INPUT in CM HEIGHT to line up with the waterbottle to go over to hit it*/
float width = -91.4;         //travel half width backwards (to hit the ball)
float ratio_length = 0.3;
float ratio_width = 0.3;
	//activate PID motor control
nMotorPIDSpeedCtrl[motorB] = mtrSpeedReg;
nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;

	//lightfollowpush
numbturns(2);   																	  // North: 0, East: 1, South: 2, West: 3
	while(SensorValue(leftLight)<lightThresh){
		motor[motorB] = 50;
		motor[motorC] = 50;
	}
int corners = 0;                                    //corners to turn around on
while(corners < 3){
	while(SensorValue(upLight)>lightThresh){          //line following
		if(SensorValue(rightLight)>lightThresh){
			motor[motorB]=50;
			motor[motorC]=0;
		}
		if(SensorValue(rightLight)<lightThresh){
			motor[motorC]=50;
			motor[motorB]=0;
		}
	}
	corners += 1;
	motor[motorB]=30;                                    //pushing bases part
	motor[motorC]=30;
	wait1Msec(650);
	motor[motorB]=-30;
	motor[motorC]=-30;
	wait1Msec(650);
	numbturns(1);
}
	numbright(1);
	//distance stuff
	float x = 0.0;
	resetEncoder();
	while (x > -(length * ratio_length )) /* 0.5 is RATIO */
	{
		motor[motorB] = -30;
		motor[motorC] = -30;
		x = measuredist();
	}
	numbright(1);        //right turn
	motor[motorB] = -15; //so alignment doesn't read outside
	motor[motorC] = -15;
	wait1Msec(500);
	alignment();
	x = 0.0;
	resetEncoder();
	while (x > (width * ratio_width )) /* DECIMAL is ratio */
	{
		motor[motorB] = -50;
		motor[motorC] = -50;
		x = measuredist();
	}
	motor[motorB] = 0;
	motor[motorC] = 0;

	bathit();
}