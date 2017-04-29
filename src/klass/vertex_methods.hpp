#include "face.hpp"
#include "edge.hpp"

static PyObject* SkpVertex_getedges(SkpVertex *self, void *closure) {
  SKP_GET_ELEMENTS(
    SUVertexGetNumEdges,
    SUVertexGetEdges,
    SUEdgeRef,
    _su_vertex,
    _su_edge,
    "cannot get edges",
    SkpEdge,
    SkpEdgeType
  )
}

static PyObject* SkpVertex_getfaces(SkpVertex *self, void *closure) {
  SKP_GET_ELEMENTS(
    SUVertexGetNumFaces,
    SUVertexGetFaces,
    SUFaceRef,
    _su_vertex,
    _su_face,
    "cannot get faces",
    SkpFace,
    SkpFaceType
  )
}

static PyObject* SkpVertex_getloops(SkpVertex *self, void *closure) {
  SKP_GET_ELEMENTS(
    SUVertexGetNumLoops,
    SUVertexGetLoops,
    SULoopRef,
    _su_vertex,
    _su_loop,
    "cannot get loops",
    SkpLoop,
    SkpLoopType
  )
}
