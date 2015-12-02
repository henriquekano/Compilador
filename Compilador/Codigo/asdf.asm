@     /0000                   ; origem do código
INIT        JP    MAIN
TWO         K     /0002
ZERO        K     /0000
LD_INSTR    LD    /0000       ; para fabricar instrucao de LD 
MM_INSTR    MM    /0000       ; para fabricar instrucao de MM

PARAM_1     K     /0300       ; parametro 1 da funcao
PARAM_2     K     /0100       ; parametro 2 da funcao

FP          K     /0400       ; frame pointer
SP          K     /0400       ; stack pointer

; subrotina SUB ---------------------------------------
F_PARAM_1   K     /0000
F_PARAM_2   K     /0000
F_RESULT    K     /0000
; corpo da subrotina
SUB         K     /0000
            LD    SUB    ; endereco de retorno
            MM    PUSH_P   
            SC    PUSH_RA     ; push ADDR na pilha de ra
            
            LD    SP
            MM    FP          ; fp aponta para o ADDR na pilha de ra

            LV    =6
            MM    GET_P       
            SC    GET_RA      ; carrega param 1 partir de endereco relativo no ra
            MM    F_PARAM_1
            
            LV    =4
            MM    GET_P       
            SC    GET_RA      ; carrega param 2 a partir de endereco relativo no ra
            MM    F_PARAM_2

            LD    F_PARAM_1   ; carrega o primeiro param
            -     F_PARAM_2   ; 
            MM    RTRN_RSLT   ; subtrai e guarda para return

            JP    RETURN

; fim SUB -----------------------------------------------

; RETURN ---------------------------------------
RTRN_RSLT   K     /0000
RTRN_ADDR   K     /0000
; corpo da subrotina
RETURN      LD    RTRN_RSLT
            MM    PUSH_P   
            SC    PUSH_RA     ; push RESULT na pilha de ra

            LV    =0
            MM    GET_P
            SC    GET_RA
            MM    RTRN_ADDR   ; endereco de retorno recuperado da pilha

            LD    TWO
            MM    GET_P
            SC    GET_RA
            MM    SP          ; dropa a ra atual
            MM    FP          ; volta a fp antiga

            RS    RTRN_ADDR   ; retorna para o escopo anterior
; fim RETURN --------------------------------------------

; subrotina PUSH_RA ---------------------------------------
PUSH_P      K     /0000
; corpo da subrotina
PUSH_RA     K     /0000
            LD    MM_INSTR    ; composicao do comando de carregar na pilha
            +     SP
            -     TWO
            MM    _NEW_INSTR1
            LD    PUSH_P
_NEW_INSTR1 K     /0000       ; carrega na pilha de fato  
            LD    SP          
            -     TWO
            MM    SP          ; sp, aponte para o vazio 
            RS    PUSH_RA
; fim PUSH_RA --------------------------------------------

; subrotina GET_RA ---------------------------------------
GET_P       K     /0000       ; endereco relativo na ra
; corpo da subrotina
GET_RA      K     /0000
            LD    LD_INSTR
            +     FP          ; 
            +     GET_P       ;
            MM    _NEW_INSTR2 ;
_NEW_INSTR2 K     /0000       ; carrega valor da ra no acumulador
            RS    GET_RA
; fim GET_RA --------------------------------------------

; corpo do main -----------------------------------------
;MAIN        LD    PARAM_1     
;            MM    PUSH_P   
;            SC    PUSH_RA     ; push PARAM_1 na pilha de ra
;
;            LD    PARAM_2     
;            MM    PUSH_P   
;            SC    PUSH_RA     ; push PARAM_2 na pilha de ra
;
;            LD    FP     
;            MM    PUSH_P         
;            SC    PUSH_RA     ; push old FP na pilha de ra
;
;            SC    SUB    ; chama SUB
;
;            HM    INIT        ; fim do programa inteiro
;fim main -----------------------------------------------





; corpo do main -----------------------------------------
MAIN        LD    VAR_1    

            HM    INIT        ; fim do programa inteiro
;fim main -----------------------------------------------


VAR_1       K     =32767      ; declaracao
# INIT                  ; fim do programa


