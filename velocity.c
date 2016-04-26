//velocity control task for preloads in driver
void velocityControl()
{
    motor(leftOuterFlywheel) = motor(leftInnerFlywheel) = motor(rightOuterFlywheel) = motor(rightInnerFlywheel); //syncs the flywheel motors
    //additive offsets to change target
    if(vexRT(Btn8U) == 1 && pressedFlag == false) //8U increases the offset by 2
    {
        offset = offset + 2;
        pressedFlag = true;
    }

    if(vexRT(Btn8D) == 1 && pressedFlag == false) //8D decreases the offset by 2
    {
        offset = offset - 2;
        pressedFlag = true;
    }

    if(vexRT(Btn8U) == 0 && vexRT(Btn8D) == 0) //the buttons will only increase or decrease the offset once until released and pressed again
    {
        pressedFlag = false; //pressed flag turns off if buttons aren't pressed
    }
    int idealTicks = 149 + offset; //sets the target
    SensorValue[flywheelEncoder] = 0; //clears the encoder
    delay(20); //calculates the velocity
    int error = (idealTicks - SensorValue[flywheelEncoder]) * 0.5; //error is gap between target and actual: multiplied by half to TBH for less oscillation

    //sets motors to lower speed if current speed is too high
    if(SensorValue[flywheelEncoder] > idealTicks + 4)
    {
        motor(rightInnerFlywheel) = 38;
    }


    //sets motors to 127 if speed is too low
    else if(SensorValue[flywheelEncoder] < idealTicks - 4)
    {
        motor(rightInnerFlywheel) = 115;
    }

    //TBH if speed is within +-4 of target

    else if(SensorValue[flywheelEncoder] < idealTicks + 4 && SensorValue[flywheelEncoder] > idealTicks - 4)
    {
        motor(rightInnerFlywheel) = 59 + (offset * 5 / 13.5) + error;
    }
}
