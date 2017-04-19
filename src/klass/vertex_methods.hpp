#include "face.hpp"
#include "edge.hpp"

static PyObject* SkpVertex_getedges(SkpVertex *self, void *closure) {
  GET_ELM_BODY(
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
  GET_ELM_BODY(
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
  GET_ELM_BODY(
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
