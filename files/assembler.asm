start:
mov ax, 5
mov bx, 8
add ax, bx
cmp ax, bx
ja true_mark
jmp false_mark
true_mark:
push 10
false_mark:
push 1056
