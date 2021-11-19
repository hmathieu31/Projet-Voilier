#include "set_Sail.h"
#include "Acquisition_Girouette.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

int sSail_calc_angle(int girAngle) {
    int a;               /* Gir Angle in between 0 and 180 */
    int sailsAngle;      /* Sails angle between 0 and 90 */
    if (girAngle < 180)  // 1st half of the angles
    {
        a = girAngle;
    } else {            // 2nd half of the angles
        a = 360 - girAngle;
    }

    if (a < 45)
        sailsAngle = 0;  // Cases where the sail must be fully trimmed
    else
        sailsAngle = (2 * a) / 3 - 30;  // Affine func : x -> 2/3 x - 30 for sailsAngle

    return sailsAngle;
}

void sSail_set_servo(int sailsAngle) {
    unsigned short dc; /* Duty cycle to set the servo angle */

    /* Setup of PWM and corresponding output Pin*/
    MyGPIO_Init(GPIO_PWM, PIN_PWM, AltOut_Ppull);

    MyTimer_Base_Init(TIMER_PWM, 1440, 1000);  // Init the PWM with a period of 20ms
    Init_MyTimer_PWM(TIMER_PWM, CHANNEL_PWM);
    MyTimer_Base_Start(TIMER_PWM);

    dc = (5 * sailsAngle) / 90 + 5;  // The duty cycle (in %) is func : x -> 5/90 x + 5
    Set_Duty_PWM(TIMER_PWM, CHANNEL_PWM, dc);
}
