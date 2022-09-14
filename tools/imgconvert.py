import subprocess
from os import remove
import sys
import os

def convertimg(imgpath):
    name = os.path.basename(imgpath).split(".")[0]
    imgf = open(imgpath, 'rb')

    output_c = open('a.c', 'w')
    output_c.write("""#include "src/texture.h"
static const unsigned char texture_data[] = {
""")
    byte = imgf.read(1)
    while byte:
        output_c.write(str(ord(byte)) + ',')
        byte = imgf.read(1)
        
    output_c.write('};\n')
    output_c.write("""
Texture texture_{0} = {{
    texture_data
}};
""".format(name))

    output_c.close()


if __name__ == "__main__":
    convertimg(sys.argv[1])