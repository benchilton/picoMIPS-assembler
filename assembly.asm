;Main Program
main:

  MULI $3 , $1 , 0.50 ; $v1 = 0.5 * $1
  ADD  $2 , $3 
  ADDI $2 , $2 , 10 ; add B_1
  MULI $2 , $0 , 0.75 ; $v1 = 0.5 * $1
  MULI $3 , $1 , 0.6 ; $at = 0.75 * $0
  ADDI $2 , $2 , 100 ; add B_1
  BEQ $0 , $0 , main
