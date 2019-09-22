import MLSTransformer as Augment
import cv2
import numpy as np
import glob
import os
import time

'''
The code is for OpenCV format.
If your data format is PIL.Image, please convert the format by:

import numpy as np
import cv2
from PIL import Image

img = Image.open("The Path to the image")
img = cv2.cvtColor(np.asarray(img), cv2.COLOR_RGB2BGR)
'''

paths = glob.glob("pic/*.png")

# im = cv2.imread("pic/res_00023_10.jpg")
# im = cv2.resize(im, (200, 64))
# cv2.imwrite("im_CV.jpg", im)
# segment = 8
path = "pic/demo.png"
filename = os.path.basename(path)
start = time.time()
im = cv2.imread(path, 1)

for i in range(1000):
	im_Distort = Augment.Distort(im, 8)
	# cv2.imwrite("pic/im_Distort/%s.jpg" % filename, im_Distort)
	im_Stretch = Augment.Stretch(im, 4)
	# cv2.imwrite("pic/im_Stretch/%s.jpg" % filename, im_Stretch)
	im_Perspective = Augment.Perspective(im)
	# cv2.imwrite("pic/im_Perspective/%s.jpg" % filename, im_Perspective)
	# cv2.waitKey(1)
	# print "%d/%d" % (i, len(paths))

end = time.time() - start
print(end / 1000 / 3)
