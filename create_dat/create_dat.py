"""
Created on Thu Jun 13 10:23:16 2019

@author: matthew
"""
from PIL import Image
import numpy as numpy
import matplotlib.pyplot as pyplot

# convert the colored png to greyscale png
img = Image.open('./face_2.png').convert('L')
img.save('./face_2_grey.png')
img = Image.open('./face_2_grey.png')

# convert greyscale png to pixel array
width, height = img.size
data = list(img.getdata())

# save the greyscale intensity image
greyscale_img_dat_file = open("./face_2_grey.dat", "wb")
data_as_bytes = bytes(data)
greyscale_img_dat_file.write(data_as_bytes)

# show the pixel array
img = numpy.array(data).reshape(height, width)
pyplot.imshow(img, cmap = 'gray')
pyplot.show()

