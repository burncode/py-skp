#include "entities.hpp"
#include "component_instance.hpp"

static PyObject* SkpComponentDefinition_getentities(SkpComponentDefinition *self, void *closure) {
  SKP_GET_SINGLE_ELEMENT(
    SkpEntities,
    SkpEntitiesType,
    SUComponentDefinitionGetEntities,
    _su_def,
    _su_entities,
    "cannot get entities"
  )
}

static PyObject* SkpComponentDefinition_getinstances(SkpComponentDefinition *self, void *closure) {
  // 17+
  SKP_GET_ELEMENTS(
    SUComponentDefinitionGetNumInstances,
    SUComponentDefinitionGetInstances,
    SUComponentInstanceRef,
    _su_def,
    _su_ins,
    "cannot get instances",
    SkpComponentInstance,
    SkpComponentInstanceType
  )
}
