#include "edge.hpp"

static PyObject* SkpCurve_getedges(SkpCurve *self, void *closure) {
  SKP_GET_ELEMENTS(
    SUCurveGetNumEdges,
    SUCurveGetEdges,
    SUEdgeRef,
    _su_curve,
    _su_edge,
    "cannot get edges",
    SkpEdge,
    SkpEdgeType
  )
}
