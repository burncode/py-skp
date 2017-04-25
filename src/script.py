# -*- coding: utf-8 -*-

import os

import skp

class Point(skp.Point3d):
    def __init__(self, *args):
        if len(args) == 3:
            super(Point, self).__init__(*args)
        elif len(args) == 1:
            arg = list(*args)
            super(Point, self).__init__(arg[0], arg[1], arg[2])
        else:
            pass

#model = skp.create_model()
#entities = model.entities
#
#pts = [
#   Point([0,   0,   0   ]),
#   Point([100, 100, 0   ]),
#   Point([100, 100, 100 ]),
#   Point([0,   0,   100 ]),
#]
#
#face = entities.create_face(pts)
#edges = face.edges
#v = None
#print(face.entityID)
#print(face.outer_loop.entityID)
#for e in edges:
#    print(e.entityID)
#    v = e.start
#    print(v.entityID)
#
#for e in v.edges:
#    print(e.start.entityID)
#
#for f in v.faces:
#    print(f)
#    print(f.entityID)
#
#for l in v.loops:
#    print(l)
#    print(l.entityID)
#
#model.save()

#folder = os.path.dirname(os.path.abspath(__file__))
path = os.path.expandvars(
         os.path.join('%homedrive%', '%homepath%', 'Documents', 'model.skp'))

model = skp.read_model(path)
entities = model.entities
#face = entities.faces[0]
#print(face.attribute_dictionaries)
#print(face.attribute_dictionaries[0].entityID)
#print(face.attribute_dictionaries[0].name)
#attr_dict = face.attribute_dictionaries[0]
#print(attr_dict.keys)
#for k in attr_dict.keys:
#    print("%s: %s" % (k, attr_dict.get_value(k)))

for mat in model.materials:
    print(mat.name)
    print(mat.use_alpha)
