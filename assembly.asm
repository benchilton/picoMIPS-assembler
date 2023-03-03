;Main Program
;A simple test program to demonstrate the usage of this tool
main:
  ADDI $v0,$0,100   ; $t0 = $0 + 100
  ADDI $v1,$0,-0.25 ; $t1 = $0 + 50
  ADD  $v0,$v1      ; $t0 = $t0 - $t1
  ADDI $v0,$0,0.75  ; $t0 = $0 + 100
  ADDI $v1,$0,50    ; $t1 = $0 + 50
  SUB  $v0,$v1      ; $t0 = $t0 - $t1
  ADDI $v0,$0,100   ; $t0 = $0 + 100
  ADDI $v1,$0,0.5    ; $t1 = $0 + 50
  MUL  $v0,$v1      ; $t0 = $t0 - $t1
  BEQ  $0,$0,main
