#include "face.hpp"

static PyObject* SkpEntities_getfaces(SkpEntities *self, void *closure) {
  GET_ELM_BODY(
    SUEntitiesGetNumFaces,
    SUEntitiesGetFaces,
    SUFaceRef,
    _su_entities,
    _su_face,
    "cannot get faces",
    SkpFace,
    SkpFaceType
  )
}
