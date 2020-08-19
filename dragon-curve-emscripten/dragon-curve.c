#ifndef DRAGON_CURVE
#define DRAGON_CURVE

// helper for transforming turns into coordinates
// 0 1 0 -1....
int sign(int x) { return (x % 2) * (2 - (x % 4)); }

// -1 for left and 1 for right
// see https://en.wikipedia.org/wiki/Dragon_curve
int getTurn(int n)
{
  int turnFlag = (((n + 1) & -(n + 1)) << 1) & (n + 1);
  return turnFlag != 0 ? -1 : 1;
}

// fills source with x and y points [x0, y0, x1, y1,...]
void dragonCurve(double source[], int size, int len, double x0, double y0)
{
  int i, angle = 0;
  double x = x0, y = y0;
  for (i = 0; i < size; i++)
  {
    int turn = getTurn(i);
    angle = angle + turn;
    x = x - len * sign(angle);
    y = y - len * sign(angle + 1);
    source[2 * i] = x;
    source[2 * i + 1] = y;
  }
}
#endif
