from PIL import Image
from PIL.ImageOps import flip
from os.path import exists
import sys
import os

def convertimg(imgpath):
    texture_path = 'src/textures/'
    name = os.path.basename(imgpath).split(".")[0]
    imgf = open(imgpath, 'rb')
    hpath = texture_path + name + '.h'
    cpath = texture_path + name + '.c'

    output_c = open(cpath, 'w')
    if not exists(hpath):
        output_h = open(hpath, 'w')
        output_h.write("""#pragma once
#include "texture.h"

extern Texture texture_{0};
""".format(name))
        output_h.close()

    output_c.write("""#include "{0}.h"

static const unsigned char texture_data[] = {{
""".format(name))
    byte = imgf.read(1)
    while byte:
        output_c.write(str(ord(byte)) + ',')
        byte = imgf.read(1)
        
    output_c.write('};\n')
    output_c.write("""
Texture texture_{0} = {{
    0,
    0,
    0,
    texture_data
}};
""".format(name))

    output_c.close()

if __name__ == "__main__":
    convertimg(sys.argv[1])