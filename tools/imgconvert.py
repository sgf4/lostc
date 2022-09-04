from PIL import Image
from PIL.ImageOps import flip
import argparse
import os

parser = argparse.ArgumentParser(description="Convert img to pixel data C")
parser.add_argument("file", metavar="FILE", type=str, help="Path file")

texture_path = 'src/textures/'
args = parser.parse_args()
name = os.path.basename(args.file).split(".")[0]
im = flip(Image.open(args.file, "r"))
width, height = im.size
pixel_values = list(im.getdata())
output_h = open(texture_path + name + '.h', 'w')
output_c = open(texture_path + name + '.c', 'w')

output_h.write("""#pragma once
#include "texture.h"

extern Texture texture_{0};
extern const unsigned char texture_{0}_data[];
""".format(name))
output_h.close()

output_c.write("""#include "{0}.h"

Texture texture_{0} = {{
    {1},
    {2},
    0,
    texture_{0}_data
}};
const unsigned char texture_{0}_data[] = {{
""".format(name, width, height))
for pixel in pixel_values:
    output_c.write('    ')
    output_c.write(', '.join(["0x{:02x}".format(v) for v in pixel]))
    output_c.write(',\n')
output_c.write('};')
output_c.close()

