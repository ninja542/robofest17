#pragma config(Sensor, S1,     upLight,        sensorLightActive)
#pragma config(Sensor, S2,     leftLight,      sensorEV3_Color)
#pragma config(Sensor, S4,     rightLight,     sensorEV3_Color)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
void resetEncoder(){
	/* reset motor encoder */
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
}
void bathit(){
	nMotorEncoder[motorA] = 0;
	while(nMotorEncoder[motorA] < 90){
		motor[motorA] = 75;
	}
	motor[motorA] = 0;
	while(nMotorEncoder[motorA] > 0){
		motor[motorA] = -15;
	}
	motor[motorA] = 0;
}
void push(int millisec){
	//pushing bases part
	motor[motorB] = 30;
	motor[motorC] = 30;
	wait1Msec(millisec);
	motor[motorB] = -30;
	motor[motorC] = -30;
	wait1Msec(millisec);
}
void brake(){
	motor[motorB] = 0;
	motor[motorC] = 0;
}
void numbturns(int turns){
	while(turns > 0){
		nMotorEncoder[motorB] = 0;
		while(nMotorEncoder[motorB] > -176){                   //trying to turn left 90 degrees
			motor[motorB] = -25;
			motor[motorC] = 25;
		}
		brake();
		wait1Msec(250);
		turns--;
	}
}
void numbright(int turns){
	while(turns > 0){
		nMotorEncoder[motorB] = 0;
		while(nMotorEncoder[motorB] < 176){
			motor[motorB] = 25;
			motor[motorC] = -25;
		}
		brake();
		turns--;
	}
}
float measuredist(){
	/*Floaty tings */
	float circum = 5.6 * 3.14159;
	float degdist = circum / 360;
	float distance = degdist * nMotorEncoder[motorB];
	return distance;
}
void untildist(float travel){
	float x = 0.0;
	resetEncoder();
	if(travel > 0){
		while (x < travel){
			motor[motorB] = 30;
			motor[motorC] = 30;
			x = measuredist();
		}
	}
	if(travel < 0){
		while (x > travel){
			motor[motorB] = -30;
			motor[motorC] = -30;
			x = measuredist();
		}
	}
}
void alignment(int lightThresh){
	while( (SensorValue(leftLight) > lightThresh) && (SensorValue(rightLight) > lightThresh) ){
		nMotorEncoder[motorB] = 0;
		while(nMotorEncoder[motorB] < 20){
			motor[motorB] = 25;
			motor[motorC] = 0;
		}
		nMotorEncoder[motorC] = 0;
		while(nMotorEncoder[motorC] < 20){
			motor[motorB] = 0;
			motor[motorC] = 25;
		}
	}
	if(SensorValue(leftLight) < lightThresh){
		while(SensorValue(rightLight) > lightThresh){
			motor[motorB] = 0;
			motor[motorC] = 25;
		}
	}
	else{
		while(SensorValue(leftLight) > lightThresh){
			motor[motorB] = 25;
			motor[motorC] = 0;
		}
	}
}
void linefollowccw(int lightThresh){
	if(SensorValue(rightLight) > lightThresh){
			motor[motorB] = 50;
			motor[motorC] = 0;
		}
	if(SensorValue(rightLight) < lightThresh){
		motor[motorC] = 50;
		motor[motorB] = 0;
	}
}
void linefollowcw(int lightThresh){
	if(SensorValue(rightLight) > lightThresh){
			motor[motorB] = 0;
			motor[motorC] = 50;
		}
	if(SensorValue(rightLight) < lightThresh){
		motor[motorC] = 0;
		motor[motorB] = 50;
	}
}
task main()
{
//INPUTS GO HERE TADAAA
int lightThresh = 40;
int aluminumfoil = 90;
float width = 90;          /*WIDTH  Distance INPUT in CM HEIGHT to line up with the waterbottle to go over to hit it*/
float height = 110;         //HEIGHT travel half width backwards (to hit the ball)
float ratio_width = 0.3;
float ratio_height = 0.35;
float scythe = 11.0; //length of scythe in cm
float robot_width = 14.0; //how fat the robot is in cm
//activate PID motor control
nMotorPIDSpeedCtrl[motorB] = mtrSpeedReg;
nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
//lightfollowpush
numbturns(1);   					// North: 0, East: 1, South: 2, West: 3 FOR CHANGING STARTING ORIENTATION
motor[motorB] = 50;
motor[motorC] = 50;
wait1Msec(1000);
while(SensorValue(rightLight) > lightThresh){
	motor[motorB] = 50;
	motor[motorC] = -50;
}
//corners to turn around on
for(int corners = 0; corners < 4; corners++){
	while(SensorValue(upLight) > lightThresh){          //line following
		linefollowccw(lightThresh);
	}
	if (corners==3){
		push(1000);
	}
	else {
		push(650);
	}
	numbturns(1);
	// sweeping the long sides
	if (corners == 2){
		untildist(-width * ratio_width);
		numbturns(1);
		while(SensorValue(upLight) > lightThresh){
			motor[motorB] = 50;
			motor[motorC] = 50;
		}
	}
}
numbright(1);
//distance stuff
//new function implementation
untildist(-width * ratio_width);
numbright(1);
motor[motorB] = -15; //so alignment doesn't read outside
motor[motorC] = -15;
wait1Msec(500);
alignment(lightThresh);
untildist(-height * ratio_height);
brake();
bathit();
while (SensorValue(rightLight) > lightThresh){
	motor[motorB] = 50;
	motor[motorC] = 50;
}
numbturns(1);
while(SensorValue(rightLight) < aluminumfoil){          //line following
	linefollowccw(lightThresh);
}
brake();
}
