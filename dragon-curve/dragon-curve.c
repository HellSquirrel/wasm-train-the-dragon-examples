#ifndef DRAGON_CURVE
#define DRAGON_CURVE

// Trigonometric functions and PI constant
#include <math.h>

struct point { double x, y; };

static int pos;
static double x, y, angle;

// Helper function to convert degrees to radians (sad there is no one in the standard library)
double deg2rad(double degrees) {
  return degrees * M_PI / 180.0;
}

void dragon_curve_recursive(int order, double length, int sign, struct point sequence[]) {
  if (order == 0) {
    // Add next point to result set
    x = x + length * cos(angle);
    y = y + length * sin(angle);
    sequence[pos++] = (struct point){ .x = x, .y = y };
  } else {
    dragon_curve_recursive(order - 1, length * sqrt(0.5), 1, sequence);
    angle = angle + sign * deg2rad(-90); // Turn the line
    dragon_curve_recursive(order - 1, length * sqrt(0.5), -1, sequence);
  }
}

void dragon_curve(int order, double length, struct point sequence[]) {
  pos = 0;
  x = 0.0;
  y = 0.0;
  angle = 0.0; // order * deg2rad(45);
  sequence[pos++] = (struct point){ .x = x, .y = y };
  dragon_curve_recursive(order, length, 1, sequence);
}

#endif
