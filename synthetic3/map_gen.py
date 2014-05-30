#!/usr/bin/env python

import glob
import math

def main():
    print("Hello")
    txt_file_names = glob.glob("*.txt")
    print("txt_file_names={0}".format(txt_file_names))

    for txt_file_name in txt_file_names:
	base_file_name = txt_file_name[:-4]
	map_file_name = "{0}.xml".format(base_file_name)
	print("Txt_file_name:{0} Map_file_name:{1}".
	  format(txt_file_name, map_file_name))

	# Read in *txt_contents* form *txt_file_name*:
	txt_file = open(txt_file_name, "r")
	txt_contents = txt_file.read()
	txt_file.close()

	# Break *txt_contents* into *txt_lines*:
	txt_lines = txt_contents.split("\n")

	# Open *map_file* and write out <Map ...> tag:
	map_file = open(map_file_name, "w")
	map_file.write('<Map Tags_Count="{0}" Arcs_Count="0">\n'.
	  format(len(txt_lines) - 2))

	sqrt2 = math.sqrt(2)
	pi = math.pi
	radians_to_degrees = 180.0 / pi
	pi2 = 2.0 * pi 

	# Visit each non empty *txt_line* in *txt_lines*:
	for txt_line in txt_lines:
	    if len(txt_line) > 0:
		# Build a *txt_table* dictionary that contains the fields
		# and their values:
		txt_table = {}
		txt_fields = txt_line.split(" ")
		for txt_field in txt_fields:
		    pair = txt_field.split("=")
		    name = pair[0]
		    value = pair[1]
		    txt_table[name] = float(value)

		#print("{0}".format(txt_table))
		if "id" in txt_table:
		    qx = txt_table["quat_x"]
                    qy = txt_table["quat_y"]
                    qz = txt_table["quat_z"]
                    qw = txt_table["quat_q"]

		    twist_radians = math.atan2(2.0 * qx * qz - qw * qy,
		      qw * qw + qx * qx - qy * qy - qz * qz)
		    twist_radians = -twist_radians

		    #if twist_radians > pi:
		    #	twist_radians -= pi2
		    #elif twist_radians < -pi:
		    #	twist_radians += pi2

		    twist_degrees = twist_radians * radians_to_degrees

		    map_file.write(' <Tag Id="{0}" Diagonal="{1}" Twist="{2}"'.
		      format(int(txt_table["id"]), sqrt2, twist_degrees))
		    map_file.write(' X="{0}" Y="{1}" Hop_Count="0"/>\n'.
		      format(txt_table["pos_x"], -txt_table["pos_z"]))

	# Write out "</Map>" and close *map_file*:
	map_file.write("</Map>\n")
	map_file.close()

main()

