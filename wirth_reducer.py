# -*- encoding:utf-8 -*-
import sys
import os
import time
import shutil
import pprint
from collections import OrderedDict

def main(argv):
	wirth_file_name = "wirth_modificado.txt"
	reduced_wirth_file_name = "wirth_reduzido.txt"
	pp = pprint.PrettyPrinter(indent=4)

	wirth_file = open(wirth_file_name, "r")

	buffer = ""
	giant_dict = {}
	machines_list = ["PROGRAMA", "COMANDO", "DECLARACAO", "CONDICAO", "EXPRESSAO"]

	dont_replace_list = machines_list+["L", "D", "SPECIAL", "ESPACO", "ANY", "ID", "TIPO", "STRING", "INT", "FLOAT", "BOOL", "COMPARADOR"]

	for line in wirth_file:
		if line.strip() != "":
			if line.split(" ")[1] == "=":
				split_line = line.split("=",1)
				var_name = split_line[0].strip()
				# tirando o ponto do final
				giant_dict[var_name] = split_line[1].strip()[:-1]

	giant_dict_ordered_by_biggest_name_list = OrderedDict(sorted(giant_dict.items(), key=lambda t: len(t[0]), reverse=True))

	def recursive_substitution(updated_list, updated_dict):
		current_key = updated_list[0]
		if current_key not in dont_replace_list:
			value_to_replace = updated_dict[current_key]

			for others_key, others_value in updated_dict.items():
				if current_key in others_value:
					updated_dict[others_key] = others_value.replace(current_key, "(%s)" % value_to_replace)

			# print "\n\nkey_to_replace: %s\n" % (current_key)
			# pp.pprint(dict(updated_dict))

		updated_list = updated_list[1:]
		if len(updated_list) > 0:
			return_value = recursive_substitution(updated_list, updated_dict)

		return updated_dict

	returned = recursive_substitution(giant_dict_ordered_by_biggest_name_list.keys(), giant_dict_ordered_by_biggest_name_list)

	for key in machines_list:
		buffer += "%s = %s.\n\n" % (key, returned[key])

	reduced_file = open(reduced_wirth_file_name, "w")
	reduced_file.write(buffer)
	reduced_file.close()
	wirth_file.close()

if __name__ == '__main__':
	main(sys.argv)
