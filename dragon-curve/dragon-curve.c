#ifndef DRAGON_CURVE
#define DRAGON_CURVE

int sign(int x) { return (x % 2) * (2 - (x % 4)); }

int getTurn(int n)
{
  int turnFlag = (((n + 1) & -(n + 1)) << 1) & (n + 1);
  return turnFlag != 0 ? -1 : 1;
}

void dragonCurve(double source[], int size, int len, double x0, double y0)
{
  int i, angle = 0;
  double x = x0, y = y0;
  for (i = 0; i < size; i++)
  {
    int turn = getTurn(i);
    angle = angle + turn;
    x = x + len * sign(angle);
    y = y + len * sign(angle + 1);
    source[2 * i] = x;
    source[2 * i + 1] = y;
  }
}
#endif
