cmp_empl:
mov ax, 5
mov bx, 8
cmp ax, bx
ja true_mark
jmp false_mark
end
true_mark:
push 30
false_mark:
push 40