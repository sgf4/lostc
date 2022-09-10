from pygltflib import GLTF2
import struct
import pathlib
import sys
fname = pathlib.Path(sys.argv[1])
gltf = GLTF2().load(fname)
print(gltf.to_json(indent=4))

print('meshes:', len(gltf.meshes))
models = {}

for scene in gltf.scenes:
    for node in scene.nodes:
        node = gltf.nodes[node]
        print('--', node.name, '--')
        name = node.name.lower()
        models[node.name] = []
        
        for primitive in gltf.meshes[node.mesh].primitives:
            print(primitive)
            mode = primitive.mode
            attrs = primitive.attributes
            material = gltf.materials[primitive.material] if primitive.material != None else None
            accessors = {
                'pos': gltf.accessors[attrs.POSITION],
                'normal': gltf.accessors[attrs.NORMAL],
                'texcoord': gltf.accessors[attrs.TEXCOORD_0],
                'indices': gltf.accessors[primitive.indices]
            }
            primitive_data = {
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
                fmt = ''
                if accessor.type == 'VEC3':
                    size = 4*3
                    fmt = '<fff'
                elif accessor.type == 'VEC2':
                    size = 4*2
                    fmt = '<ff'
                elif accessor.type == 'SCALAR':
                    size = 2
                    fmt = '<H'

                bufferview = gltf.bufferViews[accessor.bufferView]
                buffer = gltf.buffers[bufferview.buffer]

                buffer_data = gltf.get_data_from_buffer_uri(buffer.uri)
                bufferview_data = memoryview(buffer_data)[bufferview.byteOffset:bufferview.byteOffset+bufferview.byteLength]
                accessor_data = memoryview(bufferview_data)[accessor.byteOffset:accessor.byteOffset+accessor.count*size]
                v_arr = []
                for i in range(0, accessor.count):
                    data = accessor_data[i*size:i*size+size]
                    primitive_data[name].append([round(n, 5) for n in struct.unpack(fmt, data)])
            if len(primitive_data['indices'])%3 != 0:
                print('error')
                exit()

            primitive_data['indices'] = [i[0] for i in primitive_data['indices'] ]
            primitive_data['indices'] = [primitive_data['indices'][i:i+3] for i in range(0, len(primitive_data['indices']), 3)]
            for i in primitive_data['indices']:
                primitive_data['faces'].append(
                    [[primitive_data['pos'][n], primitive_data['normal'][n], primitive_data['texcoord'][n]] for n in i]
                )

            models[node.name].append(primitive_data)

for name, primitives in models.items():
    name = name.lower()
    outputc = open('src/models/' + name + '.c', 'w')
    outputh = open('src/models/' + name + '.h', 'w')
    outputh.write('''#pragma once
#include "model.h"
extern Model {0}_model;
'''.format(name))
    outputc.write('''#include "{0}.h"\n\n'''.format(name))
    i = 0
    for primitive in primitives:
        outputc.write('''static Face faces_{0}[{1}] = {{
    {2}
}};
'''.format(i, len(primitive['indices']), ',\n    '.join([str(face).replace('(', '{').replace(')', '}').replace('[', '{').replace(']', '}') for face in primitive['faces']])))
        i+=1
    outputc.write('''static Primitive primitives[{0}] = {{
{1}
}};
    '''.format(len(primitives), ',\n'.join(['    {faces_' + str(i) + ', ' + str(len(primitives[i]['faces'])) + '}' for i in range(len(primitives))])))

    outputc.write('''
Model {0}_model = {{
    primitives,
    {1}
}};
'''.format(name, len(primitives)))
    outputh.close()
    outputc.close()
