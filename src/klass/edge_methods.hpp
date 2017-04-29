#include "curve.hpp"

static PyObject* SkpEdge_getcurve(SkpEdge *self, void *closure) {
  SKP_GET_SINGLE_ELEMENT(
    SkpCurve,
    SkpCurveType,
    SUEdgeGetCurve,
    _su_edge,
    _su_curve,
    "cannot get curve"
  )
}
