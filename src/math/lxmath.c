#include <math.h>

#include "lxmath.h"

// -----------------------------------------------------------------------------
// LENGTHDIR
//
// Idea 'stolen' from GML
// -----------------------------------------------------------------------------
float LengthDirectionX (float length, float direction) {
    return length * cosf (direction);
}

float LengthDirectionY (float length, float direction) {
    return length * sin (direction);
}

Vector2 LengthDirection (float length, float direction) {
    return (Vector2){
        .x = LengthDirectionX (length, direction),
        .y = LengthDirectionY (length, direction)
     };
}

// -----------------------------------------------------------------------------
// LINEAR INTERPOLATION
// -----------------------------------------------------------------------------
float SmoothLerp (float start, float end, float value) {
    return start + (sin (end - start) * value);
}
