#include "saturation.h"

#include <stdio.h>

void saturer(unsigned int* rkMin, unsigned int* rkMax, unsigned int n_points) {

  for (unsigned int i = 0; i < n_points; i++) {
    // TODO
    printf("point %d, rang %d/%d", i, rkMin[i], rkMax[i]);
  }

}
