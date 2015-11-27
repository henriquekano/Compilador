            @   /0000 ; Início do programa
            JP    MAIN  ; Jump para o código que invocará a subrotina

IN                K   /00FF
CTE               K   /FF00

LOAD_PREFIX       LD    /0

ASCII_MINUS       K     /2D
ASCII_0           k     /30
ASCII_9           k     /39

SHIFT3            k     /1000
SHIFT2            k     /100
SHIFT1            k     /10
HEX_LETTER_TO_ASCII     K     /37

UM                K     /1
A                 K     /a
8MIL              K     /8000
TRTR              K     /3132
FFFF              K     /FFFF


_RESERVED_BITS_ON_WORD  K   /10

;
;  Espaco reservado para funcoes internas, tambem servem de entrada e saida das mesmas (ver def de cada funcao)
;
_TEMP_1     K   /0
_TEMP_2     K   /0
_TEMP_3     K   /0
_TEMP_4     K   /0
_TEMP_5     K   /0
_TEMP_6     K   /0
_TEMP_7     K   /0
_TEMP_8     K   /0
_TEMP_9     K   /0
_TEMP_10     K   /0
_TEMP_11     K   /0
_TEMP_12     K   /0


_GD_INPUT   $     =50


;----------------------------
; Faz AND de duas entradas
; IN1: AC
; IN2: _TEMP_1
; VARS: _TEMP_2 (temporario da entrada do AC), _TEMP_3 (construcao da saida), _TEMP_4 (contador para leitura de todos os bits)
; OUT:  AC
;----------------------------
AND         K   /0
            MM  _TEMP_2
            LV  /0
            MM  _TEMP_3
            MM  _TEMP_4
            MM  _TEMP_4

AND_BEGIN   LV  /2
            *   _TEMP_3
            MM  _TEMP_3
            LD  _TEMP_2
            JN  AND_AC_NEG
            JP  AND_AC_POS
AND_AC_NEG  LD  _TEMP_1
            JN  AND_ONE
            JP  AND_ZERO
AND_AC_POS  JP  AND_ZERO
AND_ZERO    JP  AND_END
AND_ONE     LV  /1
            +   _TEMP_3
            MM  _TEMP_3
            JP  AND_END
AND_END     LV  /2
            *   _TEMP_2
            MM  _TEMP_2
            LV  /2
            *   _TEMP_1
            MM  _TEMP_1
            LV  /1
            +   _TEMP_4
            MM  _TEMP_4
            -   _RESERVED_BITS_ON_WORD
            JN  AND_BEGIN
            LD  _TEMP_3
            RS  AND

;----------------------------
; Faz OR de duas entradas
; IN1: AC
; IN2: _TEMP_1
; VARS: _TEMP_2 (temporario da entrada do AC), _TEMP_3 (construcao da saida), _TEMP_4 (contador para leitura de todos os bits)
; OUT:  AC
;----------------------------
OR         K   /0
            MM  _TEMP_2
            LV  /0
            MM  _TEMP_3
            MM  _TEMP_4
            MM  _TEMP_4

OR_BEGIN    LV  /2
            *   _TEMP_3
            MM  _TEMP_3
            LD  _TEMP_2
            JN  OR_AC_NEG
            JP  OR_AC_POS
OR_AC_NEG   JP  OR_ONE
OR_AC_POS   LD  _TEMP_1
            JN  OR_ONE
            JP  OR_ZERO
OR_ZERO     JP  OR_END
OR_ONE      LV  /1
            +   _TEMP_3
            MM  _TEMP_3
            JP  OR_END
OR_END      LV  /2
            *   _TEMP_2
            MM  _TEMP_2
            LV  /2
            *   _TEMP_1
            MM  _TEMP_1
            LV  /1
            +   _TEMP_4
            MM  _TEMP_4
            -   _RESERVED_BITS_ON_WORD
            JN  OR_BEGIN
            LD  _TEMP_3
            RS  OR

;----------------------------
; Faz o output de entradas ascii
; IN1: _TEMP_1 (endereco base da entrada)
; IN2: AC (Tamanho desses dados)
; IN3: _TEMP_7 (ler como ascii(nao-negativo) ou nao(negativo))
; VARS: 
;      _TEMP_2 (contagem do tamanho para condicao de parada), 
;      _TEMP_3 (temporario para o tamanho dos dados), 
;      _TEMP_4 (DADO ATUAL -> 0x1234), 
;      _TEMP_5 (primeiro byte ou primeiro numero), 
;      _TEMP_6 (segundo byte ou segundo numero), 
;      _TEMP_8, (terceiro numero)
;      _TEMP_9, (quarto numero)
;      _TEMP_10 (offset do endereco base para fazer o load da prox word)
; OUT: Na tela
; OBS: há dois modos de impressao: as-is e ascii. As-is pega o numero, transforma em caracteres ascii e imprime. ascci interpreta a entrada como ascii
; GOTCHA: em modo ASCII, eh considerado que a word nunca sera negativo, pois caracteres ASCII vao ate 7E
;----------------------------{
      PRINT                   K     /0
                              
                              MM    _TEMP_3

                              LV    /0
                              MM    _TEMP_2
                              MM    _TEMP_10


      PRINT_BEGIN             LD    _TEMP_1
                              +     _TEMP_10
                              +     LOAD_PREFIX
                              MM    PRINT_LOAD_DATA
      PRINT_LOAD_DATA         K     /0
                              MM    _TEMP_4

                              LD    _TEMP_7

                              JZ    PRINT_AS_IS
                              JP    PRINT_AS_ASCII

      ;/---------------------------------------------------\
      PRINT_AS_ASCII          LD    _TEMP_4                 ;SEPARA OS BYTES
                              /     SHIFT2
                              *     SHIFT2 
                              MM    _TEMP_5
                              LD    _TEMP_4
                              -     _TEMP_5
                              MM    _TEMP_6
                              LD    _TEMP_5
                              /     SHIFT2
                              MM    _TEMP_5

                              LD    _TEMP_5
                              PD    /0100

                              LV    /1
                              +     _TEMP_2
                              MM    _TEMP_2
                              -     _TEMP_3
                              JZ    PRINT_END

                              LD    _TEMP_6
                              PD    /0100

                              LV    /1
                              +     _TEMP_2
                              MM    _TEMP_2
                              -     _TEMP_3
                              JZ    PRINT_END

                              LV    /2
                              +     _TEMP_10
                              MM    _TEMP_10
                              JP    PRINT_BEGIN
      ;\---------------------------------------------------/
      ;/---------------------------------------------------\
      PRINT_AS_IS             LD    _TEMP_4
                              JN    PRINT_NEG
                              JP    PRINT_POS
      PRINT_NEG               LD    ASCII_MINUS
                              PD    /0100
                              LD    _TEMP_4
                              *     FFFF
                              MM    _TEMP_4

      PRINT_POS               /     SHIFT3            ;Separa todos os numeros
                              *     SHIFT3
                              MM    _TEMP_5

                              LD    _TEMP_4
                              -     _TEMP_5
                              /     SHIFT2
                              *     SHIFT2
                              MM    _TEMP_6

                              LD    _TEMP_4
                              -     _TEMP_5
                              -     _TEMP_6
                              /     SHIFT1
                              *     SHIFT1
                              MM    _TEMP_8

                              LD    _TEMP_4
                              -     _TEMP_5
                              -     _TEMP_6
                              -     _TEMP_8
                              MM    _TEMP_9           ;separado (0x1234 viraria: 0x1000, 0x0200, 0x0030 e 0x0004)
                              
                              LD    _TEMP_5
                              /     SHIFT3
                              MM    _TEMP_5
                              -     A
                              JN    PRINT_SUM_NUMBER_1
                              JP    PRINT_SUM_LETTER_1
      PRINT_SUM_NUMBER_1      LD    _TEMP_5 
                              +     ASCII_0
                              JP    PRINT_AS_IS_1
      PRINT_SUM_LETTER_1      LD    _TEMP_5 
                              +     HEX_LETTER_TO_ASCII
      PRINT_AS_IS_1           PD    /0100
                              LV    /1
                              +     _TEMP_2
                              MM    _TEMP_2
                              -    _TEMP_3
                              JZ    PRINT_END

                              LD    _TEMP_6
                              /     SHIFT2
                              MM    _TEMP_6
                              -     A
                              JN    PRINT_SUM_NUMBER_2
                              JP    PRINT_SUM_LETTER_2
      PRINT_SUM_NUMBER_2      LD    _TEMP_6
                              +     ASCII_0
                              JP    PRINT_AS_IS_2
      PRINT_SUM_LETTER_2      LD    _TEMP_6
                              +     HEX_LETTER_TO_ASCII
      PRINT_AS_IS_2           PD    /0100
                              LV    /1
                              +     _TEMP_2
                              MM    _TEMP_2
                              -    _TEMP_3
                              JZ    PRINT_END

                              LD    _TEMP_8
                              /     SHIFT1
                              MM    _TEMP_8
                              -     A
                              JN    PRINT_SUM_NUMBER_3
                              JP    PRINT_SUM_LETTER_3
      PRINT_SUM_NUMBER_3      LD    _TEMP_8
                              +     ASCII_0
                              JP    PRINT_AS_IS_3
      PRINT_SUM_LETTER_3      LD    _TEMP_8
                              +     HEX_LETTER_TO_ASCII
      PRINT_AS_IS_3           PD    /0100
                              LV    /1
                              +     _TEMP_2
                              MM    _TEMP_2
                              -    _TEMP_3
                              JZ    PRINT_END

                              LD    _TEMP_9
                              -     A
                              JN    PRINT_SUM_NUMBER_4
                              JP    PRINT_SUM_LETTER_4
      PRINT_SUM_NUMBER_4      LD    _TEMP_9
                              +     ASCII_0
                              JP    PRINT_AS_IS_4
      PRINT_SUM_LETTER_4      LD    _TEMP_9
                              +     HEX_LETTER_TO_ASCII
      PRINT_AS_IS_4           PD    /0100
                              LV    /1
                              +     _TEMP_2
                              MM    _TEMP_2
                              -    _TEMP_3
                              JZ    PRINT_END

                              LV    /2
                              +     _TEMP_10
                              MM    _TEMP_10

                              JP    PRINT_BEGIN
      ;\---------------------------------------------------/

      PRINT_END               RS    PRINT
;}

SOME  K     /3132
      K     /3334
      K     /3536
      K     /3738
      K     /3941
      K     /4243
      K     /4243
      k     /4445
      
MAIN  LD    TRTR
      ;LD  CTE
      ;MM  _TEMP_1
      ;LD  IN
      ;SC  OR
      ;JP    LOL
      ;GD     /0000
      
      LV    SOME
      MM    _TEMP_1
      LD    FFFF
      MM    _TEMP_7
      LV    =8
      SC    PRINT
      
      HM    /0000 ; Término de programa
      #   MAIN  ; Fim do programa físico