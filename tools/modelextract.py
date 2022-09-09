from os import access
from pygltflib import GLTF2
import base64
import struct
from numpy import array as nparray
import pathlib
import sys
fname = pathlib.Path(sys.argv[1])
gltf = GLTF2().load(fname)
print(gltf.to_json(indent=4))

print("meshes:", len(gltf.meshes))
models = {}

for scene in gltf.scenes:
    for node in scene.nodes:
        node = gltf.nodes[node]
        print("--", node.name, "--")
        name = node.name.lower()
        
        for primitive in gltf.meshes[node.mesh].primitives:
            print(primitive)
            mode = primitive.mode
            attrs = primitive.attributes
            accessors = {
                'pos': gltf.accessors[attrs.POSITION],
                'normal': gltf.accessors[attrs.NORMAL],
                'texcoord': gltf.accessors[attrs.TEXCOORD_0],
                'indices': gltf.accessors[primitive.indices]
            }
            model_data = {
                'pos': [],
                'normal': [],
                'texcoord': [],
                'indices': [],
                'faces': []
            }

            for name, accessor in accessors.items():
                if accessor == None:
                    continue
                size = 0
                fmt = ""
                if accessor.type == 'VEC3':
                    size = 4*3
                    fmt = "<fff"
                elif accessor.type == 'VEC2':
                    size = 4*2
                    fmt = "<ff"
                elif accessor.type == 'SCALAR':
                    size = 2
                    fmt = "<H"

                bufferview = gltf.bufferViews[accessor.bufferView]
                buffer = gltf.buffers[bufferview.buffer]

                buffer_data = gltf.get_data_from_buffer_uri(buffer.uri)
                bufferview_data = memoryview(buffer_data)[bufferview.byteOffset:bufferview.byteOffset+bufferview.byteLength]
                accessor_data = memoryview(bufferview_data)[accessor.byteOffset:accessor.byteOffset+accessor.count*size]
                v_arr = []
                for i in range(0, accessor.count):
                    data = accessor_data[i*size:i*size+size]
                    model_data[name].append([round(n, 5) for n in struct.unpack(fmt, data)])
            if len(model_data['indices'])%3 != 0:
                print('error')
                exit()

            model_data['indices'] = [i[0] for i in model_data['indices'] ]
            model_data['indices'] = [model_data['indices'][i:i+3] for i in range(0, len(model_data['indices']), 3)]
            for i in model_data['indices']:
                model_data['faces'].append(
                    [[model_data['pos'][n], model_data['normal'][n], model_data['texcoord'][n]] for n in i]
                )

            models[node.name] = model_data

for name, model_data in models.items():
    name = name.lower()
    outputc = open('src/models/' + name + '.c', 'w')
    outputh = open('src/models/' + name + '.h', 'w')
    outputh.write("""#pragma once
#include "model.h"
extern Model {0}_model;
extern Face {0}_faces[];
""".format(name))

    outputc.write("""#include "{0}.h"
Model {0}_model = {{
    {1},
    {0}_faces
}};
Face {0}_faces[] = {{
""".format(name, len(model_data['indices'])))

    for faces in model_data['faces']:
        outputc.write('    ' + str(faces).replace('(', '{').replace(')', '}').replace('[', '{').replace(']', '}'))
        outputc.write(',\n')

    outputc.write('};\n')
    outputh.close()
    outputc.close()
