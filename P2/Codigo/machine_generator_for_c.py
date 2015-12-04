# -*- encoding:utf-8 -*-
import sys
import os
import time
import shutil
import re

def main(argv):
	transition_table_input = "submaquinas_geradas_online.txt"

	machine_output = "machine_generator_for_c_output.txt"

	dont_replace = []	

	machine_types = {}
	machine_types["Program"] = "MTYPE_PROGRAM"
	machine_types["Expr"] = "MTYPE_EXPR"
	machine_types["IotaExpr"] = "MTYPE_IOTAEXPR"

	machine_translations = {}
	machine_translations["Program"] = "program"
	machine_translations["Expr"] = "expression"
	machine_translations["IotaExpr"] = "iotaExpression"

	machine_token_types = {}
	machine_token_types["i"] = "MTTYPE_i"
	machine_token_types["I"] = "MTTYPE_I"
	machine_token_types["K"] = "MTTYPE_k"
	machine_token_types["k"] = "MTTYPE_K"
	machine_token_types["S"] = "MTTYPE_S"
	machine_token_types["s"] = "MTTYPE_s"
	machine_token_types["1"] = "MTTYPE_1"
	machine_token_types["0"] = "MTTYPE_0"
	machine_token_types["`"] = "MTTYPE_S_QUOTE"
	machine_token_types["*"] = "MTTYPE_ASTERISK"
	machine_token_types["("] = "MTTYPE_L_PARENTHESIS"
	machine_token_types[")"] = "MTTYPE_R_PARENTHESIS"

	transition_table_file = open(transition_table_input, "r")

	machine_type_br = ""
	machine_var = ""
	machine_type = ""
	buffer = ""

	for line in transition_table_file:
		if line.strip().startswith("Sub-maquina"):
			machine_type_br = line.split(" ")[1].replace(":","")
			machine_type = machine_types[machine_type_br]

			buffer += "\n// %s ||||||||||||||||||||||||||||||||||||||||\n" % machine_type

		elif line.strip().startswith("final"):
			final_states = line.strip().split(":")[1].replace(" ","")
			final_states = final_states.split(",")

			for index, state in enumerate(final_states):
				buffer += "rawFinalStatesTables[%s][%d] = %s;\n" % (machine_type, index, state)

			buffer += "\n// TRANSITION TABLE --------------------------------------\n"

		elif line.strip().startswith("("):
			info = line.strip().replace(" ->","")
			infos = info.split(" ")
			current_state = infos[0][1:-1]
			next_state = infos[2]
			token = infos[1][:-1]

			if token in dont_replace:
				machine_token_type = machine_token_types[token]
				buffer += "rawTransitionTables[%s][%s][%s] = %s;\n" % (machine_type, current_state, machine_token_type, next_state)
			# para pegar o caso """
			elif token == '"""':
				machine_token_type = machine_token_types['"']
				buffer += "rawTransitionTables[%s][%s][%s] = %s;\n" % (machine_type, current_state, machine_token_type, next_state)
			# para pegar o caso "'"
			elif token.replace('"','') == "'":
				machine_token_type = machine_token_types["'"]
				buffer += "rawTransitionTables[%s][%s][%s] = %s;\n" % (machine_type, current_state, machine_token_type, next_state)

			elif token in machine_translations.keys():
				next_machine_type = machine_types[token]
				buffer += "rawSubmachineCallTables[%s][%s] = %s;\n" % (machine_type, current_state, next_machine_type)
				buffer += "rawAfterCallTables[%s][%s][%s] = %s;\n\n" % (machine_type, current_state, next_machine_type, next_state)
				
			else:
				machine_token_type = machine_token_types[token.replace('"','')]
				buffer += "rawTransitionTables[%s][%s][%s] = %s;\n" % (machine_type, current_state, machine_token_type, next_state)
			
	machine_file = open(machine_output, "w")
	machine_file.write(buffer)
	machine_file.close()

	transition_table_file.close()

if __name__ == '__main__':
	main(sys.argv)
