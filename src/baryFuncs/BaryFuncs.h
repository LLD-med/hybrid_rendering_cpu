#ifndef BARYFUNCS_H
#define BARYFUNCS_H

#include "Vector.hpp"

float interpolateCoord(float val1, float val2,
                      float val3, const VecD &vec);

VecD baryCentricInterpolation(const VecD &a, const VecD& b,
                              const VecD &c, const VecD &bary);

float calcBar(VecD &a, VecD &b, VecD &p);

VecD toBarycentric(VecD &a, VecD &b, VecD &c, VecD p);


#endif // BARYFUNCS_H
