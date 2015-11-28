    @   /0000 ; Início do programa
    JP    MAIN  ; Jump para o código que invocará a subrotina
IN    K   /8123 ; Entrada com o número a ser decomposto
OUT1  K   /0000 ; Possuirá o valor dos dois dígitos mais significativos
OUT2  K   /0000 ; Possuirá o valor dos dois dígitos menos significativos
VAR   K   /100  ; Constante utilizada nas operações de multiplicação e divisão

_TRUE       K   /0
_FALSE      K   /-1

_NEGATIVE_ONE K   /FFFF
_NEGATIVE  K   /8000

_RESERVED_BITS_ON_WORD  K   /10
_RESERVED_TEMP_1  K   /0
_RESERVED_TEMP_2  K   /0
_RESERVED_TEMP_3  K   /0
_RESERVED_TEMP_4  K   /0


HIGH_MASK K   /FF00
LOW_MASK  K   /00FF



UNPACK  K   /0000 ; Início de subrotina
    MM  _RESERVED_TEMP_3
    JN  UNPACK_NEG
    JP  UNPACK_POS
;Levanta uma flag se for negativo

UNPACK_NEG  LD  _RESERVED_TEMP_3
    -   _NEGATIVE
    MM  _RESERVED_TEMP_3
    LD  _TRUE
    MM  _RESERVED_TEMP_4
    JP  UNPACK_CORE
UNPACK_POS  LD  _FALSE
    MM  _RESERVED_TEMP_4

UNPACK_CORE LD _RESERVED_TEMP_3
    /   VAR   ; Toma-se os dois dígitos mais a esquerda da entrada
    *   VAR   ; Multiplica-se por /100 para se obter os dois dígitos mais a direita, em OUT1 teremos agora /XX00
    MM  _RESERVED_TEMP_1  ; Salva /XX00 em OUT1
    LD  _RESERVED_TEMP_3    ; Recarrega o valor da entrada no acumulador
    -   _RESERVED_TEMP_1  ; Obtém-se os dois dígitos mais a direita
    MM  _RESERVED_TEMP_2  ; Salva o valor dos dois digitos mais a direita em OUT2
    LD  _RESERVED_TEMP_1  ; Recarrega o valor de OUT1 para que o valor verdadeiro de OUT1 seja recuperado
    /   VAR   ; Agora tem-se /00XX no acumulador
    MM  _RESERVED_TEMP_1  ; Salva o valor dos dois dígitos mais a esquerda em OUT1

    LD  _RESERVED_TEMP_4
    JN  UNPACK_NEG_END
    JP  UNPACK_POS_END
UNPACK_NEG_END LV  /80
    +   _RESERVED_TEMP_1
    MM  _RESERVED_TEMP_1
UNPACK_POS_END RS  UNPACK  ; Fim de subrotina
    
MAIN LD   IN 
    SC    UNPACK  ; Chamada da subrotina UNPACK
    HM    /0000 ; Término de programa
    #   MAIN  ; Fim do programa físico