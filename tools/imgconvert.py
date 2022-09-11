from PIL import Image
from PIL.ImageOps import flip
from os.path import exists
import sys
import os

def convertimg(imagename):
    texture_path = 'src/textures/'
    name = os.path.basename(imagename).split(".")[0]
    im = flip(Image.open(imagename, "r"))
    width, height = im.size
    pixel_values = list(im.getdata())
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
    for pixel in pixel_values:
        output_c.write('    ')
        output_c.write(', '.join(["0x{:02x}".format(v) for v in pixel]))
        output_c.write(',\n')
    output_c.write('};\n')
    output_c.write("""
Texture texture_{0} = {{
    {1},
    {2},
    0,
    texture_data
}};
""".format(name, width, height))

    output_c.close()

if __name__ == "__main__":
    convertimg(sys.argv[1])