#include "set_Sail.h"

int calcSailsAngle(int girAngle) {
    int a; /* Gir Angle in between 0 and 180 */
    int sailsAngle; /* Sails angle between 0 and 90 */
    if (girAngle < 180) // 1st half of the angle
    {
        a = girAngle;
    } else {
        a = 360 - girAngle;
    }

    if(a < 45) sailsAngle = 0; // Cases where the sail must be fully trimmed
    else sailsAngle = (2 * a)/3 - 30; // Affine func : x -> 2/3 x - 30 for sailsAngle

    return sailsAngle;
}

void setServo(int sailsAngle) {
    ;
}

