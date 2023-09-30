#ifndef LXMATH_H
#define LXMATH_H

#include <raymath.h>

// -----------------------------------------------------------------------------
// LENGTHDIR
//
// Idea 'stolen' from GML
// -----------------------------------------------------------------------------
float LengthDirectionX (float length, float direction);
float LengthDirectionY (float length, float direction);

Vector2 LengthDirection (float length, float direction);

// -----------------------------------------------------------------------------
// LINEAR INTERPOLATION
// -----------------------------------------------------------------------------
float SmoothLerp (float start, float end, float value);

#endif // LXMATH_H
