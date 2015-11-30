# -*- encoding:utf-8 -*-
import sys
import os
import time
import shutil

def main(argv):
	file_from_console_name = "entrada.txt"

	file_from_console = open(file_from_console_name, "r")

	format = ".jff\n"

	buffer = ""
	new_jff_name = ""

	for line in file_from_console:

		if line.endswith(format):
			new_jff_name = line.strip("\n")

			if line.startswith("VM"):
				new_jff_name = line.split(" ")[1].strip("\n")

		elif line.strip().startswith("<?xml"):
			buffer = line.strip()

		elif line.strip().startswith("</structure>"):
			buffer += line

			new_jff = open("jffs/"+new_jff_name, "w")
			new_jff.write(buffer)
			new_jff.close()

		elif line.strip().startswith("<"):
			buffer += line

	file_from_console.close()

if __name__ == '__main__':
	main(sys.argv)
