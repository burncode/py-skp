#include "face.hpp"
#include "edge.hpp"

SUResult SUEntitiesGetNumEdgesAll(SUEntitiesRef entities, size_t* count) {
  return SUEntitiesGetNumEdges(entities, false, count);
}

SUResult SUEntitiesGetEdgesAll(SUEntitiesRef entities, size_t len, SUEdgeRef edges[], size_t* c) {
  return SUEntitiesGetEdges(entities, false, len, edges, c);
}

static PyObject* SkpEntities_getedges(SkpEntities *self, void *closure) {
  SKP_GET_ELEMENTS(
    SUEntitiesGetNumEdgesAll,
    SUEntitiesGetEdgesAll,
    SUEdgeRef,
    _su_entities,
    _su_edge,
    "cannot get edges",
    SkpEdge,
    SkpEdgeType
  )
}

static PyObject* SkpEntities_getfaces(SkpEntities *self, void *closure) {
  SKP_GET_ELEMENTS(
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
