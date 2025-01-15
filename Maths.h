#pragma once

#include <math.h>

# define M_PI           3.14159265358979323846 

#define Rad2Deg(r) (((r)*180)/M_PI)
#define Deg2Rad(r) (((r)/180)*M_PI)

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


#define MClamp(value,vmin,vmax)  (std::min(std::max(value, vmin), vmax));
