#include <Python.h>
#include "structmember.h"

#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/model/entity.h>

#include "../util/checkerror.h"

// Macros

#include "m_get_elm.hpp"

#define GET_ENTITY_BODY(ref, proc) { \
  SUEntityRef su_entity = proc(self->ref); \
  int32_t entity_id = 0; \
  SUResult res = SUEntityGetID(su_entity, &entity_id); \
  if (checkerror(res, "Cannot get entityID")) return NULL; \
  \
  return PyLong_FromLong((long)entity_id); \
}
