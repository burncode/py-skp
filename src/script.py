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
instances = model.entities.instances
print(instances)
ins = instances[0]
print("name: %s" % ins.name)
ins.name = 'askdjflkajsdkfj'
print("guid: %s" % ins.guid)
ins.guid = '3tTEWifL1BbgYzXCAQzCA0'
print(ins.attached_instances)
print(ins.locked)
ins.locked = True
print(ins.locked)
model.save()
