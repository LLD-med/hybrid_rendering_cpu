#include "BaryFuncs.h"


float interpolateCoord(float val1, float val2,
                      float val3, const VecD &vec)
{
    float res = val1 * vec.getX() + val2 * vec.getY() + val3 * vec.getZ();
    return res;
}

VecD baryCentricInterpolation(const VecD &a, const VecD& b,
                              const VecD &c, const VecD &bary)
{
    float x_val = interpolateCoord(a.getX(), b.getX(), c.getX(), bary);
    float y_val = interpolateCoord(a.getY(), b.getY(), c.getY(), bary);
    float z_val = interpolateCoord(a.getZ(), b.getZ(), c.getZ(), bary);

    return { x_val, y_val, z_val };
}

float calcBar(VecD  &a, VecD &b, VecD &p)
{
    float tmp = (b.getX() - a.getX()) * p.getY();
    tmp += (a.getY() - b.getY()) * p.getX();
    tmp += a.getX() * b.getY();
    tmp -= b.getX() * a.getY();
    return tmp;
}

VecD toBarycentric(VecD &a, VecD &b, VecD &c, VecD p)
{
    float A_num = calcBar(c, b, p);
    float B_num = calcBar(a, c, p);
    float C_num = calcBar(a, b, p);

    float A_invnum = calcBar(c, b, a);
    float B_invnum = calcBar(a, c, b);
    float C_invnum = calcBar(a, b, c);

    auto val1 = A_num / A_invnum;
    auto val2 = B_num / B_invnum;
    auto val3 = C_num / C_invnum;

    return { val1, val2, val3 };
}
