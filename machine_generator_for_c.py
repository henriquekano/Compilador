# -*- encoding:utf-8 -*-
import sys
import os
import time
import shutil
import re

def main(argv):
	transition_table_input = "submaquinas_geradas_online.txt"

	machine_output = "machine_generator_for_c_output.txt"

	dont_replace = ["ID", "D", "ANY", "TIPO", "COMPARADOR_BOOL", "BOOL"]

	machine_translations = {}
	machine_translations["PROGRAMA"] = "program"
	machine_translations["COMANDO"] = "command"
	machine_translations["DECLARACAO"] = "declaration"
	machine_translations["CONDICAO"] = "condition"
	machine_translations["EXPRESSAO"] = "expression"
	machine_translations["EXPRESSAO_ARIT"] = "expression_arit"
	machine_translations["EXPRESSAO_BOOL"] = "expression_bool"
	machine_translations["VALOR"] = "value"

	machine_types = {}
	machine_types["PROGRAMA"] = "MTYPE_PROGRAM"
	machine_types["COMANDO"] = "MTYPE_COMMAND"
	machine_types["DECLARACAO"] = "MTYPE_DECLARATION"
	machine_types["CONDICAO"] = "MTYPE_CONDITION"
	machine_types["EXPRESSAO"] = "MTYPE_EXPRESSION"
	machine_types["EXPRESSAO_ARIT"] = "MTYPE_EXPRESSION_ARIT"
	machine_types["EXPRESSAO_BOOL"] = "MTYPE_EXPRESSION_BOOL"
	machine_types["VALOR"] = "MTYPE_VALUE"

	machine_token_types = {}
	machine_token_types["begin"] = "MTTYPE_BEGIN" 				
	machine_token_types["end"] = "MTTYPE_END" 					
	machine_token_types["do"] = "MTTYPE_DO" 					
	machine_token_types["if"] = "MTTYPE_IF" 					
	machine_token_types["elsif"] = "MTTYPE_ELSIF" 				
	machine_token_types["endif"] = "MTTYPE_ENDIF" 				
	machine_token_types["else"] = "MTTYPE_ELSE" 				
	machine_token_types["while"] = "MTTYPE_WHILE" 				
	machine_token_types["endwhile"] = "MTTYPE_ENDWHILE" 			
	machine_token_types["when"] = "MTTYPE_WHEN" 				
	machine_token_types["endwhen"] = "MTTYPE_ENDWHEN" 				
	machine_token_types["is"] = "MTTYPE_IS" 					
	machine_token_types["continue"] = "MTTYPE_CONTINUE" 			
	machine_token_types["function"] = "MTTYPE_FUNCTION" 			
	machine_token_types["return"] = "MTTYPE_RETURN" 				
	machine_token_types["endfunction"] = "MTTYPE_ENDFUNCTION" 			
	machine_token_types["scan"] = "MTTYPE_SCAN" 				
	machine_token_types["print"] = "MTTYPE_PRINT" 				
	machine_token_types[";"] = "MTTYPE_SEMICOLON" 			
	machine_token_types[","] = "MTTYPE_COMMA" 				
	machine_token_types["."] = "MTTYPE_DOT" 					
	machine_token_types["["] = "MTTYPE_LEFT_BRACKET" 		
	machine_token_types["]"] = "MTTYPE_RIGHT_BRACKET" 		
	machine_token_types["("] = "MTTYPE_LEFT_PARENTHESIS" 	
	machine_token_types[")"] = "MTTYPE_RIGHT_PARENTHESIS" 
	machine_token_types["="] = "MTTYPE_EQUAL" 				
	machine_token_types["+"] = "MTTYPE_PLUS" 				
	machine_token_types["-"] = "MTTYPE_MINUS" 				
	machine_token_types["*"] = "MTTYPE_MULTIPLICATION" 		
	machine_token_types["/"] = "MTTYPE_DIVISION" 			
	machine_token_types["&&"] = "MTTYPE_AND" 					
	machine_token_types["||"] = "MTTYPE_OR" 					
	machine_token_types["'"] = "MTTYPE_SINGLE_QUOTE" 		
	machine_token_types['"'] = "MTTYPE_DOUBLE_QUOTE" 		
	machine_token_types["ID"] = "MTTYPE_ID" 					
	machine_token_types["D"] = "MTTYPE_D" 					
	machine_token_types["ANY"] = "MTTYPE_ANY" 					
	machine_token_types["TIPO"] = "MTTYPE_TYPE" 				
	machine_token_types["BOOL"] = "MTTYPE_BOOL" 				
	machine_token_types["COMPARADOR"] = "MTTYPE_COMPARATOR" 			
	machine_token_types["COMPARADOR_BOOL"] = "MTTYPE_COMPARATOR_BOOL" 		

	transition_table_file = open(transition_table_input, "r")

	machine_type_br = ""
	machine_var = ""
	machine_type = ""
	buffer = ""

	for line in transition_table_file:

		if line.strip().startswith("Sub-maquina"):
			machine_type_br = line.split(" ")[1].replace(":","")
			machine_var = machine_translations[machine_type_br]
			machine_type = machine_types[machine_type_br]

			buffer += "\n// %s ||||||||||||||||||||||||||||||||||||||||\n" % machine_type
			buffer += "setup_machine(&%s);\n\n" % machine_var
			buffer += "%s.id = %s;\n" % (machine_var, machine_type)

		elif line.strip().startswith("initial"):
			initial_state = line.strip().split(" ")[1]
			buffer += "%s.current_state = %s;\n" % (machine_var, initial_state)

		elif line.strip().startswith("final"):
			final_states = line.strip().split(":")[1].replace(" ","")
			final_states = final_states.split(",")

			for index, state in enumerate(final_states):
				buffer += "%s.final_state[%d] = %s;\n" % (machine_var, index, state)

			buffer += "\n// TRANSITION TABLE --------------------------------------\n"

		elif line.strip().startswith("("):
			info = line.strip().replace(" ->","")
			infos = info.split(" ")
			current_state = infos[0][1:-1]
			next_state = infos[2]
			token = infos[1][:-1]

			if token in dont_replace:
				machine_token_type = machine_token_types[token]
				buffer += "%s.transition_table[%s][%s] = %s;\n" % (machine_var, current_state, machine_token_type, next_state)
			# para pegar o caso """
			elif token == '"""':
				machine_token_type = machine_token_types['"']
				buffer += "%s.transition_table[%s][%s] = %s;\n" % (machine_var, current_state, machine_token_type, next_state)
			# para pegar o caso "'"
			elif token.replace('"','') == "'":
				machine_token_type = machine_token_types["'"]
				buffer += "%s.transition_table[%s][%s] = %s;\n" % (machine_var, current_state, machine_token_type, next_state)

			elif token in machine_translations.keys():
				machine_type = machine_types[token]
				buffer += "\n%s.submachine_call[%s][%s] = %s;\n\n" % (machine_var, current_state, machine_type, next_state)
				
			else:
				machine_token_type = machine_token_types[token.replace('"','')]
				buffer += "%s.transition_table[%s][%s] = %s;\n" % (machine_var, current_state, machine_token_type, next_state)
			
	machine_file = open(machine_output, "w")
	machine_file.write(buffer)
	machine_file.close()

	transition_table_file.close()

if __name__ == '__main__':
	main(sys.argv)
