import pygltflib
from os.path import exists
from os import remove
import struct
import pathlib
import argparse
from imgconvert import convertimg


parser = argparse.ArgumentParser(description="Convert gltf to C model")
parser.add_argument("file", metavar="FILE", type=str, help="Path file")
args = parser.parse_args()

fname = pathlib.Path(args.file)
gltf = pygltflib.GLTF2().load(fname)
#print(gltf.to_json(indent=4))


def bufferview_data(bufferview: pygltflib.BufferView) -> memoryview:
    buffer = gltf.buffers[bufferview.buffer]
    buffer_data = gltf.get_data_from_buffer_uri(buffer.uri)
    return memoryview(buffer_data)[bufferview.byteOffset:bufferview.byteOffset+bufferview.byteLength]

def accessor_data(accessor: pygltflib.Accessor) -> memoryview:
    bufferview = gltf.bufferViews[accessor.bufferView]
    bv_data = bufferview_data(bufferview)
    return memoryview(bv_data)[accessor.byteOffset:accessor.byteOffset+accessor.count*size]

print('meshes:', len(gltf.meshes))
# process images
for image in gltf.images:
    print('-- image', image.name, '--')
    bv = gltf.bufferViews[image.bufferView]
    bv_data = bufferview_data(bv)
    imgpath = 'tools/' + image.name + '.png'
    f = open(imgpath, 'wb')
    f.write(bv_data)
    f.close()
    convertimg(imgpath)
    remove(imgpath)

# process all objects in the scene
for scene in gltf.scenes:
    for node in scene.nodes:
        node = gltf.nodes[node]
        print('--', node.name, '--')
        m_name = node.name.lower()
        primitives = []
        m_cpath = 'src/models/' + m_name + '.c'
        m_hpath = 'src/models/' + m_name + '.h'
        m_outputc = open(m_cpath, 'w')
        if not exists(m_hpath):
            outputh = open(m_hpath, 'w')
            outputh.write('''#pragma once
#include "model.h"
extern Model {0}_model;
'''.format(m_name))
            outputh.close()

        m_outputc.write('''#include "{0}.h"\n\n'''.format(m_name))
        primitive_count = 0
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
                'indices': []
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

                acc_data = accessor_data(accessor)
 
                for i in range(0, accessor.count):
                    data = acc_data[i*size:i*size+size]
                    primitive_data[name].append([round(n, 5) for n in struct.unpack(fmt, data)])

            if len(primitive_data['indices'])%3 != 0:
                print('error')
                exit()

            primitive_data['indices'] = [i[0] for i in primitive_data['indices'] ]
            primitive_data['indices'] = [primitive_data['indices'][i:i+3] for i in range(0, len(primitive_data['indices']), 3)]
            m_outputc.write('static Face faces_{0}[{1}] = {{\n'.format(primitive_count, len(primitive_data['indices'])))

            for i in primitive_data['indices']:
                face = [[primitive_data['pos'][n], primitive_data['normal'][n], primitive_data['texcoord'][n]] for n in i]
                m_outputc.write('    ' + str(face).replace('(', '{').replace(')', '}').replace('[', '{').replace(']', '}') + ',\n')

            m_outputc.write('};\n')
            primitive_count += 1

        m_outputc.write('static Primitive primitives[] = {{\n{1}\n}};\n'.format(primitive_count, ',\n'.join(['    {{0, faces_{0}, sizeof(faces_{0})/sizeof(Face)}}'.format(i) for i in range(primitive_count)])))
        m_outputc.write('Model {0}_model = {{ primitives, {1} }};\n'.format(m_name, primitive_count))
        
        m_outputc.close()
