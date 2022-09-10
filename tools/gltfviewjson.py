from pygltflib import GLTF2
import pathlib
import sys

fname = pathlib.Path(sys.argv[1])
gltf = GLTF2().load(fname)
print(gltf.to_json(indent=4))

