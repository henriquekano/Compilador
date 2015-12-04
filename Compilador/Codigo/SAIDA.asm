begin		OS		=0
		JN		elsif_1_1
		JP		do_if_1
do_if_1		OS		=0		
		JP		endif_1
		JN		elsif_1_2		
		OS		=0		
		JN		empty
		JP		do_elsif_1_1
		JP		do_elsif_1_1
do_elsif_1_1		OS		=0		
		OS		=0		
		JP		endif_1
		JN		else_1		
		OS		=0		
		JN		empty
		JP		do_elsif_1_2
		JP		do_elsif_1_2
do_elsif_1_2		OS		=0		
		OS		=0		
		JP		endif_1
		OS		=0		
endif_1		OS		=0
		LV		/0300
		MM		_TEMP_1
		LV		=4
		SC		READ		; scan()
		LV		/FFFF
		MM		_TEMP_7
		LV		/0300
		MM		_TEMP_1
		LV		=4
		SC		PRINT		; print()
		JN		else_21_1
		JP		do_if_2
do_if_2		OS		=0		
		JP		endif_2
		OS		=0		
while_1		OS		=0
		JN		endwhile_1
		JP		do_while_1
do_while_1		OS		=0		
endwhile_1		OS		=0
endif_2		OS		=0
end		OS		=0
