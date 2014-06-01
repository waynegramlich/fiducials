#!/usr/bin/env python

# This little program will extract some images from a bag file
# and write them out in .pnm format.  The usage is:
#
#    bag_images_extract.py bag_file_name [images_directory]

import rosbag
import rospy
import cv
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import sys

# Perform command line argument processing first:
arguments = sys.argv
del arguments[0]
arguments_size = len(arguments)
if arguments_size < 1:
    print("Usage: bag_images_extract.py " + \
      "bag_file_name [topic] [images_directory]")
    print("Default topic: /pgr_camera_node/image_color")
else:
    # Set defaults:
    directory = "."
    topic_name = "/pgr_camera_node/image_color"
    
    # Grab the command line arguments:
    bag_file_name = arguments[0]
    if arguments_size > 1:
	topic_name = arguments[1]
    if arguments_size > 2:
	directory = arguments[2]

    # Open the bag file:
    bag = rosbag.Bag(bag_file_name)
    bridge = CvBridge()

    # Sweep through messages that match *topic_name*:
    index = 0
    previous_time = None
    for topic, msg, t in bag.read_messages(topic_name):
	# Extract *cv_image* in RGB8 mode:
	index += 1
	try:
	    cv_image = bridge.imgmsg_to_cv(msg, desired_encoding="rgb8")
	except CvBridgeError, e:
	    print e

	# Save the image
	cv.SaveImage("{0}/Image{1:03d}.pnm".format(directory, index), cv_image)

	# Print out time changes:
	if previous_time == None:
	    previous_time = t
	dt = t - previous_time
	previous_time = t
	print("[{0}]:{1}".format(index, dt))

