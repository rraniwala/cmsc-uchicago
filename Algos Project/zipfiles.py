import os
import sys
import zipfile

zip = zipfile.ZipFile('new_outputs.zip', 'w')
for f in os.listdir(sys.argv[1]):
    zip.write(os.path.join(sys.argv[1], f), f)
zip.close()