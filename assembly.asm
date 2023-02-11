;Main Program
;A simple test program to demonstrate the usage of this tool
main:
  ADDI $t0,$0,100   ; $t0 = $0 + 100
  ADDI $t1,$0,50    ; $t1 = $0 + 50
  SUB  $t0,$t1      ; $t0 = $t0 - $t1
  BEQ  $t0,$t1,subroutine
/*/*Subroutine 1 */

subroutine:   ADD $s0,$0
              ADD $s0,$t0
              ADD $s1,$0
              ADD $s1,$t1
              ADDI $t0,$0,32   ; $t0 = $0 + 100
              ADDI $t1,$0,8    ; $t1 = $0 + 50
              OR   $t0,$t1     ; $t0 = $t0 | $t1
              JAL  subroutine2
/*
Subroutine 2
*/
subroutine2:
    ADD $s0,$0
    ADD $s0,$t0
    BEQ $s0,$t1,subroutine
    ADD $s1,$0
    ADD $s1,$t1
    ADDI $t0,$0,32   ; $t0 = $0 + 100
    ADDI $t1,$0,8    ; $t1 = $0 + 50
    OR   $t0,$t1     ; $t0 = $t0 | $t1
