#include <Python.h>
#include "structmember.h"

#include <vector>

#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/unicodestring.h>
#include <SketchUpAPI/model/typed_value.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/model/entity.h>

#include "../util/checkerror.h"

// Macros

#include "../macro/get_element.hpp"
#include "../macro/get_elements.hpp"
#include "../macro/get_string.hpp"
#include "../macro/set_name.hpp"

// Helpers

#include "../helper/material.hpp"
#include "../helper/string.hpp"
#include "../helper/value.hpp"
