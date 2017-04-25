#ifndef SKP_HELPER_MATERIAL_HPP
#define SKP_HELPER_MATERIAL_HPP

#include <SketchUpAPI/model/material.h>

static bool SUMaterialTypeIntValid(int type) {
  return !(type < SUMaterialType_Colored || type > SUMaterialType_ColorizedTexture);
}

#endif
