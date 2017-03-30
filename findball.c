#pragma config(Sensor, S1,     upLight,        sensorLightActive)
#pragma config(Sensor, S2,     leftLight,      sensorEV3_Color)
#pragma config(Sensor, S3,     Ultrasonic,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     rightLight,     sensorEV3_Color)
void resetEncoder(){
	/* reset motor encoder */
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
}
void bathit(){
	nMotorEncoder[motorA] = 0;
	while(nMotorEncoder[motorA] < 40){
		motor[motorA] = 75;
	}
	motor[motorA] = 0;
	nMotorEncoder[motorA] = 0; //reset motor encoder
	while(nMotorEncoder[motorA] > -40){
		motor[motorA] = -5;
	}
}
void numbturns(int turns){
	while(turns>0){
		nMotorEncoder[motorB] = 0;
		while(nMotorEncoder[motorB]>-180){                   //trying to turn left 90 degrees
			motor[motorB]=-25;
			motor[motorC]=25;
		}
		motor[motorB]=0;
		motor[motorC]=0;
		wait1Msec(250);
		turns--;
	}
}
float measuredist(){
	/*Floaty tings */
	float circum = 5.6 * 3.14159;
	float degdist = circum/360;
	float distance = degdist*((nMotorEncoder[motorB]+nMotorEncoder[motorC])/2);
	return distance;
}
void alignment(){
	int lightThresh = 25;                                                                    //THRESHOLD FOR LINE FOLLOWING
		//orientation against a line (not too angled)
	if((SensorValue(leftLight)>lightThresh) && (SensorValue(rightLight)>lightThresh)){
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
	else {
		while((SensorValue(leftLight)<lightThresh) && (SensorValue(rightLight)<lightThresh)){
			nMotorEncoder[motorB]=0;
			while(nMotorEncoder[motorB]<30){
				motor[motorB] = -25;
				motor[motorC] = 0;
			}
			nMotorEncoder[motorC]=0;
			while(nMotorEncoder[motorC]<30){
				motor[motorB] = 0;
				motor[motorC] = -25;
			}
		}
		if(SensorValue(leftLight)>lightThresh){
			while(SensorValue(rightLight)<lightThresh){
				motor[motorB] = 0;
				motor[motorC] = -25;
			}
		}
		else{
			while(SensorValue(leftLight)<lightThresh){
				motor[motorB] = -25;
				motor[motorC] = 0;
			}
		}
	}
}
task main()
{
	//distance stuff
	float length = 99.2;         /* Distance INPUT in CM HEIGHT to line up with the waterbottle to go over to hit it*/
	float x = 0.0;
	resetEncoder();
	while (x > -(length * 0.25 )) /* 0.5 is ratio */
	{
		motor[motorB] = -50;
		motor[motorC] = -50;
		x = measuredist();
	}
	numbturns(3);        //right turn
	motor[motorB] = -15; //so alignment doesn't read outside
	motor[motorC] = -15;
	wait1Msec(500);
	alignment();
	float width = -91.0;         //travel half width (to hit the ball)
	x = 0.0;
	resetEncoder();
	while (x > (width * 0.3 )) /* DECIMAL is ratio */
	{
		motor[motorB] = -50;
		motor[motorC] = -50;
		x = measuredist();
	}
	motor[motorB] = 0;
	motor[motorC] = 0;

	bathit();
}
