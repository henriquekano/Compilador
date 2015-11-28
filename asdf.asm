@     /0000                   ; origem do código
INIT        JP    MAIN
TWO         K     /0002
ZERO        K     /0000
LD_INSTR    LD    /0000       ; para fabricar instrucao de LD 
MM_INSTR    MM    /0000       ; para fabricar instrucao de MM

PARAM_1     K     /0300       ; parametro 1 da funcao
PARAM_2     K     /0100       ; parametro 2 da funcao

BP          K     /0400       ; base pointer
FP          K     /0000       ; frame pointer
SP          K     /0400       ; stack pointer

RV_SIZE     K     =0008       ; tamanho do valor retornado da função

; subrotina FUNCTION ---------------------------------------
F_PARAM_1   K     /0000
F_PARAM_2   K     /0000
; corpo da subrotina
FUNCTION    K     /0000
            
            

            LD    F_PARAM_1   ; carrega o primeiro param
            -     F_PARAM_2   ; subtrai, resultado no acumulador

            MM    POR_PARAM   ; guardo o valor de retorno para o pop do RA

            RS    FUNCTION    ; retornando
; fim FUNCTION -----------------------------------------------

; subrotina PUSH_RA ---------------------------------------
PUR_PARAM    K     /0000
; corpo da subrotina
PUSH_RA     K     /0000
            LD    MM_INSTR    ; composicao do comando de carregar na pilha
            +     SP
            -     TWO
            MM    _NEW_INSTR1
            LD    PUR_PARAM
_NEW_INSTR1 K     /0000       ; carrega na pilha de fato  
            LD    SP          
            -     TWO
            MM    SP          ; sp, aponte para o vazio 
            RS    PUSH_RA
; fim PUSH_RA --------------------------------------------

; subrotina POP_RA ---------------------------------------
; corpo da subrotina
POP_RA      K     /0000
            LD    MM_INSTR    ; composicao do comando de carregar na pilha
            +     SP
            -     TWO
            MM    _NEW_INSTR1
            LD    PUR_PARAM
_NEW_INSTR1 K     /0000       ; carrega na pilha de fato  
            LD    SP          
            -     TWO
            MM    SP          ; sp, aponte para o vazio 
            RS    POP_RA
; fim POP_RA --------------------------------------------

; corpo do main -----------------------------------------
MAIN        LD    SP
            MM    FP_AUX      ; carrega a possivel nova FP 

            LD    PARAM_1     
            MM    PUR_PARAM   
            SC    PUSH_RA     ; push PARAM_1 na pilha de ra

            LD    PARAM_2     
            MM    PUR_PARAM   
            SC    PUSH_RA     ; push PARAM_2 na pilha de ra

            LD    FP     
            MM    PUR_PARAM         
            SC    PUSH_RA     ; push PARAM_2 na pilha de ra

            LD    FP_AUX
            MM    FP          ; atualizo a FP

            SC    FUNCTION    ; chama FUNCTION

            HM    INIT        ; fim do programa inteiro
;fim main -----------------------------------------------

# INIT                  ; fim do programa


