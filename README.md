# Colour-Recognition
Project to recognise the block colour of an object

Abstract

This program establishes the Hue, Saturation and Value range in which a specific block coloured object falls. Images are taken from the webcam on the laptop and converted from BGR to HSV colour space. Once converted this frame is then manipulated in order to filter out the object of choice. Manipulation is conducted through the use of trackbars filtering out specific ranges of Hue, Saturation and Value. This project was created on Mac OS EL Capitan, using tools from OpenCV on XCode 8.2.1 written in C++. How to download OpenCV and link with XCode on a Mac can be found by the following link and reading the guide attached. One mistake noted from the video was in the linking with XCode not all the flags and search paths were correctly noted down so use guide attached. [1]

Procedure

A note before commencing. This program has been developed so that 1 or 2 ranges of a particular value can be used. This is because some values fall at beginning and end of a range. For example, the colour red is located at the beginning and end of the Hue scale. So the variable ‘Hue Minimum 1’ will be 0, ‘Hue Maximum 1 will be 15, ‘Hue Minimum 2’ will be 225 and ‘Hue Maximum 2’ will be 255. There for the values of 0-15 and 225-255 of the Hue scale will be filtered and seen. If two ranges aren’t required then merely use the first variable for each scale of Hue, Saturation and Value.

- Choose the block coloured object to be recognised. (I went with  different coloured balloons)

- Using the HSV scale, locate approximately the values of Hue, Saturation and Value. The scale for Hue is 260 degrees so this will be multiplied by 0.7 so its in the range of 255 bytes. The scale for Saturation and Value are out of 100 so these values will need to multiplied by 2.55 to bring them to the scale of 255 bytes. [2]

- Run Program and adjust the trackbar settings of Hue, Saturation and Value to that determined form the scale. If one range is needed for each then use Hue Min/Max 1, Saturation Min/Max 1 and Value Min/Max 1. If two ranges are need then use both variables of Hue, Saturation and Value.

- Place the object in front of the camera. Adjust the trackbars appropriately so the object is almost completely white and everything else is black.

- Bring the other block coloured objects into the frame one at a time to see if they are picked up too. If so, adjust the trackbars until only the chosen object is visible in white.

- Once satisfied note down the range in which the coloured object is recognised within the HSV colourspace.


Summary

This program can be used to determine the range in which a specific block coloured object falls in the HSV colourspace. This information can be used to create functions within an object detection program to detect certain colours of objects when called.

Reference

[1] Download OpenCV and link with XCode: https://www.youtube.com/watch?v=nuGdNITm5Mw
[2] Colour scale for HSV: http://colorizer.org/
