            @   /0000 ; Início do programa
            JP    MAIN  ; Jump para o código que invocará a subrotina

IN                K   /00FF
CTE               K   /FF00

LOAD_PREFIX       LD    /0
WRITE_PREFIX      MM    /0

ASCII_MINUS       K     /072D
ASCII_0           k     /30
ASCII_9           k     /39
ASCII_BR          k     /0D0A
ASCII_BELL        k     /000D

SHIFT3            k     /1000
SHIFT2            k     /100
SHIFT1            k     /10
HEX_LETTER_TO_ASCII     K     /37
RA_SIZE           K     =200

ONE               K     /1
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
;----------------------------{
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
;}

;----------------------------
; Faz OR de duas entradas
; IN1: AC
; IN2: _TEMP_1
; VARS: _TEMP_2 (temporario da entrada do AC), _TEMP_3 (construcao da saida), _TEMP_4 (contador para leitura de todos os bits)
; OUT:  AC
;----------------------------{
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
;}

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
; OBS: há dois modos de impressao: as-is e ascii. As-is imprime o valor da word em hexa, adicionando sinal negativo quando necessario. ascci interpreta a entrada como ascii
; GOTCHA: em modo ASCII, eh considerado que a word nunca sera negativo, pois caracteres ASCII vao ate 7E
; GOTCHA2: o tamanho de dados tem significados diferentes nos dois modos: em ASCII, significa numero de bytes e em AS-IS, words
;----------------------------{
      PRINT_BASE              K     /0
      PRINT_TYPE              K     /0

      PRINT_COUNT             k     /0
      PRINT_SIZE              k     /0
      PRINT_DATA              k     /0
      PRINT_FIRST             k     /0
      PRINT_SECOND            k     /0
      PRINT_THIRD             k     /0
      PRINT_FOURTH            k     /0
      PRINT_OFFSET            k     /0

      PRINT                   K     /0
                              
                              MM    PRINT_SIZE

                              LV    /0
                              MM    PRINT_COUNT
                              MM    PRINT_OFFSET


      PRINT_BEGIN             LD    PRINT_BASE
                              +     PRINT_OFFSET
                              +     LOAD_PREFIX
                              MM    PRINT_LOAD_DATA
      PRINT_LOAD_DATA         K     /0
                              MM    PRINT_DATA

                              LD    PRINT_TYPE

                              JZ    PRINT_AS_IS
                              JP    PRINT_AS_ASCII

      ;/---------------------------------------------------\
      PRINT_AS_ASCII          LV    /1
                              +     PRINT_COUNT
                              MM    PRINT_COUNT
                              -     PRINT_SIZE
                              JZ    PRINT_AS_ASCII_ODD

                              LV    /1
                              +     PRINT_COUNT
                              MM    PRINT_COUNT
                              JP    PRINT_AS_ASCII_EVEN

      PRINT_AS_ASCII_ODD      LD    PRINT_DATA                 ;SEPARA OS BYTES
                              /     SHIFT2
                              *     SHIFT2
                              PD    /0100
                              JP    PRINT_END

      PRINT_AS_ASCII_EVEN     LD    PRINT_DATA
                              PD    /0100

                              LV    /2
                              +     PRINT_OFFSET
                              MM    PRINT_OFFSET

                              LD    PRINT_COUNT
                              -     PRINT_SIZE
                              JZ    PRINT_END
                              JP    PRINT_BEGIN
      ;\---------------------------------------------------/
      ;/---------------------------------------------------\
      PRINT_AS_IS             LD    PRINT_DATA
                              JN    PRINT_NEG
                              JP    PRINT_POS
      PRINT_NEG               LD    ASCII_MINUS
                              PD    /0100
                              LD    PRINT_DATA
                              *     FFFF
                              MM    PRINT_DATA

      PRINT_POS               /     SHIFT3            ;Separa todos os numeros
                              *     SHIFT3
                              MM    PRINT_FIRST

                              LD    PRINT_DATA
                              -     PRINT_FIRST
                              /     SHIFT2
                              *     SHIFT2
                              MM    PRINT_SECOND

                              LD    PRINT_DATA
                              -     PRINT_FIRST
                              -     PRINT_SECOND
                              /     SHIFT1
                              *     SHIFT1
                              MM    PRINT_THIRD

                              LD    PRINT_DATA
                              -     PRINT_FIRST
                              -     PRINT_SECOND
                              -     PRINT_THIRD
                              MM    PRINT_FOURTH           ;separado (0x1234 viraria: 0x1000, 0x0200, 0x0030 e 0x0004)
                              
                              LD    PRINT_FIRST
                              /     SHIFT3
                              MM    PRINT_FIRST
                              -     A
                              JN    PRINT_SUM_NUMBER_1
                              JP    PRINT_SUM_LETTER_1
      PRINT_SUM_NUMBER_1      LD    PRINT_FIRST 
                              +     ASCII_0
                              MM    PRINT_FIRST
                              JP    PRINT_AS_IS_1
      PRINT_SUM_LETTER_1      LD    PRINT_FIRST 
                              +     HEX_LETTER_TO_ASCII
                              MM    PRINT_FIRST
      PRINT_AS_IS_1           LD    PRINT_SECOND
                              /     SHIFT2
                              MM    PRINT_SECOND
                              -     A
                              JN    PRINT_SUM_NUMBER_2
                              JP    PRINT_SUM_LETTER_2
      PRINT_SUM_NUMBER_2      LD    PRINT_SECOND
                              +     ASCII_0
                              MM    PRINT_SECOND
                              JP    PRINT_AS_IS_2
      PRINT_SUM_LETTER_2      LD    PRINT_SECOND
                              +     HEX_LETTER_TO_ASCII
                              MM    PRINT_SECOND
      PRINT_AS_IS_2           LD    PRINT_FIRST
                              *     SHIFT2
                              +     PRINT_SECOND
                              PD    /0100

                              LD    PRINT_THIRD
                              /     SHIFT1
                              MM    PRINT_THIRD
                              -     A
                              JN    PRINT_SUM_NUMBER_3
                              JP    PRINT_SUM_LETTER_3
      PRINT_SUM_NUMBER_3      LD    PRINT_THIRD 
                              +     ASCII_0
                              MM    PRINT_THIRD
                              JP    PRINT_AS_IS_3
      PRINT_SUM_LETTER_3      LD    PRINT_THIRD 
                              +     HEX_LETTER_TO_ASCII
                              MM    PRINT_THIRD
      PRINT_AS_IS_3           LD    PRINT_FOURTH
                              -     A
                              JN    PRINT_SUM_NUMBER_4
                              JP    PRINT_SUM_LETTER_4
      PRINT_SUM_NUMBER_4      LD    PRINT_FOURTH
                              +     ASCII_0
                              MM    PRINT_FOURTH
                              JP    PRINT_AS_IS_4
      PRINT_SUM_LETTER_4      LD    PRINT_FOURTH
                              +     HEX_LETTER_TO_ASCII
                              MM    PRINT_FOURTH
      PRINT_AS_IS_4           LD    PRINT_THIRD
                              *     SHIFT2
                              +     PRINT_FOURTH
                              PD    /0100

                              LV    /1
                              +     PRINT_COUNT
                              MM    PRINT_COUNT
                              -     PRINT_SIZE
                              JZ    PRINT_END

                              LV    /2
                              +     PRINT_OFFSET
                              MM    PRINT_OFFSET

                              JP    PRINT_BEGIN
      ;\---------------------------------------------------/

      PRINT_END               RS    PRINT
;}

;----------------------------
; Faz o carregamento de um valor a partir de um endereco base e um offset
; IN1: LOAD_BASE (endereco base da entrada)
; IN2: AC (offset)
; OUT: Valor no AC
;----------------------------{
      LOAD_BASE   K     /0
      LOAD        K     /0
                  +    _TEMP_1
                  +     LOAD_PREFIX
                  MM    LOAD_DO
      LOAD_DO     K     /0
                  RS    LOAD
;}

;----------------------------
; Faz a escrita de um valor em um endereco base e um offset
; IN1: WRITE_BASE (endereco base da entrada)
; IN2: AC (offset)
; IN3: WRITE_DATA
;----------------------------{
      WRITE_BASE  K     /0
      WRITE_DATA  K     /0
      WRITE       K     /0
                  +     WRITE_BASE
                  +     WRITE_PREFIX
                  MM    WRITE_DO
                  LD    WRITE_DATA
      WRITE_DO    K     /0
                  RS    WRITE
;}

;----------------------------
; Faz a separação de bytes de uma word
; IN1: AC (word)
; OUT1: BYTIFY_FIRST - primeiro byte
; OUT2: BYTIFY_SECOND - segundo byte
;----------------------------{
      BYTIFY_ORIGINAL   K     /0
      BYTIFY_FIRST      K     /0
      BYTIFY_SECOND      K     /0


      
      BYTIFY      K     /0
                  MM    BYTIFY_ORIGINAL
                  JN    BYTIFY_NEG
                  JP    BYTIFY_POS
      BYTIFY_NEG  *     FFFF
                  /     SHIFT2
                  +     ONE
                  *     SHIFT2
                  MM    BYTIFY_FIRST
                  JP    BYTIFY_SB
      BYTIFY_POS  /     SHIFT2
                  *     SHIFT2
                  MM    BYTIFY_FIRST
      BYTIFY_SB   LD    BYTIFY_ORIGINAL
                  -     BYTIFY_FIRST
                  MM    BYTIFY_SECOND
                  LD    BYTIFY_FIRST
                  /     SHIFT2
                  MM    BYTIFY_FIRST
                  RS    BYTIFY
;}

;----------------------------
; Faz a unificacao de bytes em uma word
; IN1: AC (high byte)
; IN2: WORDFY_LOW_BYTE (low byte) 
; OUT: AC
;----------------------------{
      WORDFY_LOW_BYTE      K     /0
      
      WORDFY      K     /0
                  *     SHIFT2
                  +     WORDFY_LOW_BYTE
                  RS    WORDFY
;}

;----------------------------
; Faz o carregamento de dados do programador
; IN1: _TEMP_1: endereço base do buffer
; IN2: AC: buffer limit em words
; VAR: _TEMP_2 (buffer limit temp), _TEMP_3 (contagem de inputs recebidos), _TEMP_4(dado recebido)
; OUT: dados no buffer
; OBS: Premissa: todas as entradas do teclado são e serão "positivas"
;----------------------------{
      READ_BUFFER_LIMIT K           /0
      READ_COUNT        K           /0
      READ_DATA         K           /0
      READ_BASE         K           /0

      READ              K           /0
                        MM          READ_BUFFER_LIMIT
                        LV          /0
                        MM          READ_COUNT
                        MM          READ_DATA
                        

      READ_DO           GD          /0000
                        MM          READ_DATA
                        -           ASCII_BR
                        JZ          READ_END
                        LD          READ_DATA
                        SC          BYTIFY
                        LD          BYTIFY_SECOND     
                        -           ASCII_BELL
                        JZ          READ_FIRST
                        JP          READ_ALL

      READ_FIRST        LD          READ_BUFFER_LIMIT
                        MM          WRITE_BASE
                        LD          BYTIFY_FIRST
                        MM          WRITE_DATA
                        LV          /2
                        *           READ_COUNT
                        SC          WRITE
                        LV          /1
                        +           READ_COUNT
                        MM          READ_COUNT
                        JP          READ_TEST_LIMIT

      READ_ALL          LD          READ_BASE
                        MM          WRITE_BASE
                        LD          READ_DATA
                        MM          WRITE_DATA
                        LV          /2
                        *           READ_COUNT
                        SC          WRITE
                        LV          /1
                        +           READ_COUNT
                        MM          READ_COUNT
                        JP          READ_TEST_LIMIT

      READ_TEST_LIMIT   LD          READ_COUNT
                        -           READ_BUFFER_LIMIT
                        JZ          READ_END
                        JP          READ_DO

      READ_END          RS          READ
;}
      
;----------------------------
; Faz a reserva de espaço para um registro de ativação a partir de um endereco base (base da "pilha")
; IN1: AC base da pilha
; IN2: RA_TAM - tamanho do RA
;----------------------------{
      RA_TAM            K           /0
      END               K           /0 ; valor do fim da pilha

      RA_CREATE         K           /0
                        
;}

SOME.yay  k /1
k /2
k /3
k /4
k /5
k /6
k /7
k /8
k /9
k /a
k /b
k /c
k /d
k /e
k /f
k /10
k /11
k /12
k /13
k /14
k /15
k /16
k /17
k /18
k /19
k /1a
k /1b
k /1c
k /1d
k /1e
k /1f
k /20
k /21
k /22
k /23
k /24
k /25
k /26
k /27
k /28
k /29
k /2a
k /2b
k /2c
k /2d
k /2e
k /2f
k /30
k /31
k /32
k /33
k /34
k /35
k /36
k /37
k /38
k /39
k /3a
k /3b
k /3c
k /3d
k /3e
k /3f
k /40
k /41
k /42
k /43
k /44
k /45
k /46
k /47
k /48
k /49
k /4a
k /4b
k /4c
k /4d
k /4e
k /4f
k /50
k /51
k /52
k /53
k /54
k /55
k /56
k /57
k /58
k /59
k /5a
k /5b
k /5c
k /5d
k /5e
k /5f
k /60
k /61
k /62
k /63
k /64
k /65
k /66
k /67
k /68
k /69
k /6a
k /6b
k /6c
k /6d
k /6e
k /6f
k /70
k /71
k /72
k /73
k /74
k /75
k /76
k /77
k /78
k /79
k /7a
k /7b
k /7c
k /7d
k /7e

buffer      $           =10

yaya  K     /8020
FF00  K     /FF00      
MAIN  LD    TRTR
      ;LD  CTE
      ;MM  _TEMP_1
      ;LD  IN
      ;SC  OR
      ;JP    LOL
      ;GD     /0000
      
      ;GD    /0000

      LV    buffer
      MM    READ_BASE
      LV    =4
      SC    READ

      LV    buffer
      MM    _TEMP_1
      LV    FFFF
      MM    _TEMP_7
      LV    =252
      SC    PRINT

      HM    /0000 ; Término de programa
      #   MAIN  ; Fim do programa físico