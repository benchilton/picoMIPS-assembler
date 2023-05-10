;Main Program
;A simple test program to demonstrate the usage of this tool
;Our two pixel coords
;A_1 = 0.75 A_2 = 0.5 
;A_3 = -0.5 A_4 = 0.75 
;B_1 = 20 , B_2 = -20;
main:
;Set $2 to be a temporary register of 0
;Done using the fact that 0*N = 0, means we don't need the $0 = 0 register MIPs usually uses
  LOAD $0 , $0 , 0 ; immediant will get value of the external input
;Wait for SW8 to become 0
  WAIT $2 , $2 , 1 ; wait while SW8 is 1
  LOAD $1 , $1 , 0 ; pause the processor until SW8 = 0, when that happens the value of the switches is kept
  WAIT $2 , $2 , 1 ; wait for SW8 to become 0
;execute affine transform:
;At this point $0 = x , $1 = y
;computing x_2
  MULI $2 , $0 , 0.75 ; $2 = $0 * 0.75
  MULI $3 , $1 , 0.50 ; $3 = $1 * 0.5
  ADD  $3 , $2 ; $3 = $3 + $2
  ADDI $3 , $3 , 20 ; $3 = $3 + 20
;computing y_2
  MULI $0 , $0 , -0.5 ; 
  MULI $1 , $1 , 0.75 ; 
  ADD  $0 , $1 
  ADDI $0 , $0 , -20 ; add B_2
;At this point x_2 = $2, y_2 = $0
;display x2:
  DISP $3 , $3 , 0 ; display x2
  WAIT $2 , $2 , 0 ; wait while SW8 is 0
  DISP $0 , $0 , 0 ; display y2
  WAIT $2 , $2 , 1 ; wait while SW8 is 0
