import cv2
import glob

paths = [p for p in glob.glob("pic/im_Distort/*.jpg")]

for p in paths:
	d_img = cv2.imread(p, 1)
	cv2.imshow("distort", d_img)
	
	p_img = cv2.imread(p.replace("im_Distort", "im_Perspective"), 1)
	cv2.imshow("Perspective", p_img)

	s_img = cv2.imread(p.replace("im_Distort", "im_Stretch"), 1)
	cv2.imshow("Stretch", s_img)
	cv2.waitKey(50)