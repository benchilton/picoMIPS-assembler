;Main Program
;A simple test program to demonstrate the usage of this tool
;Our two pixel coords
;A_1 = 0.75 A_2 = 0.5 
;A_3 = -0.5 A_4 = 0.75 
;B_1 = 20 , B_2 = -20;
main:
;Set $2 to be a temporary register of 0
;Done using the fact that 0*N = 0, means we don't need the $0 = 0 register MIPs usually uses
  MULI $2 , $0 , 0 ;set $2 to 0 by multiplying it by 0.
load_x:
  ADDI $0 , $2 , 0 ;y , This will add 0 to $2 and place it in register $1
;The only way the code could possibly not branch here is if there was external modification of the immediate
  BEQ  $0 , $2 , load_x
load_y:
;The only way the code could possibly not branch here is if there was external modification of the immediate
  ADDI $1 , $2 , 0 ;x , This will add 0 to $2 and place it in register $0
  BEQ  $1 , $2 , load_y
;At this point $0 = x , $1 = y
  MULI $2 , $0 , 0.75 ; $at = 0.75 * $0
  MULI $3 , $1 , 0.50 ; $v1 = 0.5 * $1
  ADD  $2 , $3 
  ADDI $2 , $2 , 20 ; add B_1

;present x

  MULI $2 , $0 , -0.5 ; $v1 = 0.5 * $1
  MULI $3 , $1 , 0.75 ; $at = 0.75 * $0
  ADD  $2 , $3 
  ADDI $2 , $2 , -20 ; add B_1

;present y

  BEQ $0 , $0 , main
