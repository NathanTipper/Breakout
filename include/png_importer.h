#ifndef PNG_IMPORTER_H
#define PNG_IMPORTER_H

#include "utils.h"
#include <stdint.h>

struct PNG_FF
{
  // These variables define the IHDR chunk
  uint32_t width;
  uint32_t height;
  uint8_t bd;
  uint8_t ct;
  uint8_t fm;
  uint8_t im;
};
#endif
