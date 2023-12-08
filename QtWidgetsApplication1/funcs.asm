.686P
.model flat, c


.data
node_prev dd 0
node_curr dd 0
node_max_in_left dd 0
left_node_rot dd 0

.code

;--------------------------------------------------------------------------------


set_node proc         ; установка значений в вершину
push ebp              ; параметры: uint node_ptr, int key, int data 
push ebx              ;                  8           12       16
mov ebp, esp
add ebp, 4


mov ebx, dword ptr [ebp + 8]
mov [ebx], dword ptr 0
mov [ebx + 4], dword ptr 0
mov [ebx + 16], dword ptr 0
mov eax, dword ptr [ebp + 12]
mov [ebx + 8], dword ptr eax
mov eax, dword ptr [ebp + 16]
mov [ebx + 12], dword ptr eax

mov eax, ebx

pop ebx
pop ebp
ret
set_node endp


;--------------------------------------------------------------------------------


add_node proc           ; добавление элемента в дерево 
push ebp                ; параметры: uint root_ptr, uint node_ptr, int key, int data 
push ebx                ;                  8             12           16       20
mov ebp, esp
add ebp, 4


mov eax, dword ptr [ebp + 16]     ; current key
mov ebx, dword ptr [ebp + 8]      ; root_node
mov edx, dword ptr [ebx + 8]      ; root_node.key

cmp edx, eax
jg go_left
jmp go_right

go_left:
	cmp dword ptr [ebx], 0
	je set_node_left
	jmp go_rec_left

	set_node_left:
		mov eax, dword ptr [ebp + 20]
		push eax
		mov eax, dword ptr [ebp + 16]
		push eax
		mov eax, dword ptr [ebp + 12]
		push eax
		call set_node
		add esp, 12
		
		mov eax, dword ptr [ebp + 12]
		mov [ebx], eax
		jmp end_func
		
	go_rec_left:
		mov eax, dword ptr [ebp + 20]
		push eax
		mov eax, dword ptr [ebp + 16]
		push eax
		mov eax, dword ptr [ebp + 12]
		push eax
		mov esi, dword ptr [ebp + 8]
		mov eax, dword ptr [esi]
		push eax
		call add_node
		add esp, 16
		jmp end_func

go_right:
	cmp dword ptr [ebx + 4], 0
	je set_node_right
	jmp go_rec_right

	set_node_right:
		mov eax, dword ptr [ebp + 20]
		push eax
		mov eax, dword ptr [ebp + 16]
		push eax
		mov eax, dword ptr [ebp + 12]
		push eax
		call set_node
		add esp, 12
		
		mov eax, dword ptr [ebp + 12]
		mov [ebx + 4], eax
		jmp end_func
		
	go_rec_right:
		mov eax, dword ptr [ebp + 20]
		push eax
		mov eax, dword ptr [ebp + 16]
		push eax
		mov eax, dword ptr [ebp + 12]
		push eax
		mov esi, dword ptr [ebp + 8]
		mov eax, dword ptr [esi + 4]
		push eax
		call add_node
		add esp, 16


end_func:


mov eax, [ebp + 8]
push eax
call update_height
add esp, 4

mov eax, [ebp + 8]
push eax
call balance_node
add esp, 4



mov eax, 1
pop ebx
pop ebp
ret
add_node endp


;--------------------------------------------------------------------------------


SetRoot proc          ; установка значений в корень дерева
push ebp              ; парметры: uint root_ptr, int key, int data 
push ebx              ;                 8           12       16
mov ebp, esp
add ebp, 4


mov ebx, dword ptr [ebp + 8]
mov eax, dword ptr [ebp + 12]
mov [ebx + 8], dword ptr eax
mov eax, dword ptr [ebp + 16]
mov [ebx + 12], dword ptr eax
mov [ebx], dword ptr 0
mov [ebx + 4], dword ptr 0
mov [ebx + 16], dword ptr 0

pop ebx
pop ebp
mov eax, 1
ret
SetRoot endp


;--------------------------------------------------------------------------------


update_height proc       ; обновление высоты
push ebp                 ; параметры uint node_ptr
push ebx                 ;                8
mov ebp, esp
add ebp, 4

mov ebx, dword ptr [ebp + 8]

mov eax, dword ptr [ebx]
cmp eax, 0
je left_node_null
mov ebx, eax
mov eax, dword ptr [ebx + 16]
jmp skip_left_node
left_node_null:
	mov eax, -1
skip_left_node:

mov edx, dword ptr [ebx + 4]
cmp edx, 0
je right_node_null
mov ebx, edx
mov edx, dword ptr [ebx + 16]
jmp skip_right_node
right_node_null:
	mov edx, -1
skip_right_node:

cmp eax, edx
jge right_bigger
left_bigger:
	mov eax, edx

right_bigger:
	add eax, 1
	mov ebx, dword ptr [ebp + 8]
	mov [ebx + 16], eax


pop ebx
pop ebp
ret
update_height endp


;--------------------------------------------------------------------------------


go_pre_order proc       ; прямой обход дерева и запись его в память
push ebp                ; параметры uint root_ptr, memory_ptr
push ebx                ;                8             12
mov ebp, esp
add ebp, 4

mov eax, -1
push eax

mov ecx, 0
mov ebx, dword ptr [ebp + 8]
push ebx

mov edi, 0

while_stack_isnt_empty:
	pop ebx
	cmp ebx, -1
	je end_func

	mov eax, dword ptr [ebx + 8]
	mov edx, dword ptr [ebx + 12]
	mov esi, ebx

	mov ebx, dword ptr [ebp + 12]
	mov [ebx + edi], eax
	mov [ebx + edi + 4], edx
	mov [ebx + edi + 8], dword ptr 0

	mov eax, [esi + 4]
	cmp eax, 0
	je no_push_right
	push eax
	no_push_right:

	mov eax, [esi]
	cmp eax, 0
	je no_push_left
	push eax
	no_push_left:

	inc ecx
	add edi, 12

	jmp while_stack_isnt_empty


end_func:
mov eax, ecx
pop ebx
pop ebp
ret
go_pre_order endp


;--------------------------------------------------------------------------------


balance_tree proc       ; балансировка всего дерева
push ebp                ; параметры uint root_ptr
push ebx                ;                8
mov ebp, esp
add ebp, 4

mov eax, dword ptr [ebp + 8]
mov node_curr, eax
mov node_prev, dword ptr 0


mov eax, -1
push eax

while_isnt_balanced:
	
	while_curr_isnt_null:
		mov ebx, node_curr
		push ebx
		mov eax, [ebx]
		mov node_curr, eax
		cmp node_curr, 0
		jne while_curr_isnt_null

	pop eax
	mov node_curr, eax

	cmp node_prev, 0
	je end_while
	
	mov eax, node_curr
	push eax
	call get_balance_factor
	add esp, 4

	cmp eax, -2
	je right_balance
	jmp check_cond

	right_balance:

	mov ebx, node_curr
	mov eax, [ebx]
	push eax
	call get_balance_factor
	add esp, 4

	cmp eax, 1
	jne only_right_rot

	mov ebx, node_curr
	mov eax, [ebx]
	push eax
	call left_rotate
	add esp, 4

	only_right_rot:
		mov eax, node_curr
		push eax
		call right_rotate
		add esp, 4


	check_cond:
	cmp eax, 2
	je left_balance
	jmp end_while

	left_balance:

	mov ebx, node_curr
	mov eax, [ebx]
	push eax
	call get_balance_factor
	add esp, 4

	cmp eax, 1
	jne only_left_rot

	mov ebx, node_curr
	mov eax, [ebx]
	push eax
	call left_rotate
	add esp, 4

	only_left_rot:
		mov eax, node_curr
		push eax
		call right_rotate
		add esp, 4


	end_while:

	mov eax, node_curr
	mov node_prev, eax

	mov ebx, node_curr
	mov eax, [ebx + 4]
	mov node_curr, eax

	mov ebx, esp
	mov eax, [ebx]
	cmp eax, -1
	je check_end_while
	jmp while_isnt_balanced

	check_end_while:
		cmp node_curr, 0
		je end_func
		jmp while_isnt_balanced


end_func:
pop ebx
pop ebp
ret
balance_tree endp


;--------------------------------------------------------------------------------


balance_node proc       ; балансировка по вершине
push ebp                ; параметры uint node_ptr
push ebx                ;                8
mov ebp, esp
add ebp, 4

mov eax, dword ptr [ebp + 8]
mov node_curr, eax

push eax
call get_balance_factor
add esp, 4

cmp eax, -2
je right_balance
jmp check_cond

right_balance:

	mov ebx, node_curr
	mov eax, [ebx]
	push eax
	call get_balance_factor
	add esp, 4

	cmp eax, 1
	jne only_right_rot

	mov ebx, node_curr
	mov eax, [ebx]
	push eax
	call left_rotate
	add esp, 4

	only_right_rot:
		mov eax, node_curr
		push eax
		call right_rotate
		add esp, 4

	jmp end_func


check_cond:
	cmp eax, 2
	je left_balance
	jmp end_func

left_balance:

	mov ebx, node_curr
	mov eax, [ebx + 4]
	push eax
	call get_balance_factor
	add esp, 4

	cmp eax, -1
	jne only_left_rot

	mov ebx, node_curr
	mov eax, [ebx + 4]
	push eax
	call right_rotate
	add esp, 4

	only_left_rot:
		mov eax, node_curr
		push eax
		call left_rotate
		add esp, 4

	jmp end_func

end_func:
pop ebx
pop ebp
ret
balance_node endp


;--------------------------------------------------------------------------------


get_balance_factor proc    ; получаение баланс-фактора для вершины
push ebp                   ; параметры uint root_ptr
push ebx                   ;                8
mov ebp, esp
add ebp, 4

mov ebx, dword ptr [ebp + 8]
mov eax, 0
cmp ebx, 0
je end_func

mov esi, [ebx + 4]
cmp esi, 0
je right_node_null_gbf
mov eax, [esi + 16]
jmp check_left_node_gbf

right_node_null_gbf:
	mov eax, -1

check_left_node_gbf:
mov esi, [ebx]
cmp esi, 0
je left_node_null_gbf
mov edx, [esi + 16]
jmp check_sub

left_node_null_gbf:
	mov edx, -1

check_sub:
sub eax, edx


end_func:
pop ebx
pop ebp
ret
get_balance_factor endp


;--------------------------------------------------------------------------------


right_rotate proc            ; правый поворот
push ebp                     ; параметры uint node_ptr
push ebx                     ;                8
mov ebp, esp
add ebp, 4


mov ebx, dword ptr [ebp + 8]
mov eax, [ebx]
mov esi, eax

mov eax, dword ptr [ebx + 8]    ; swap key
mov edx, dword ptr [esi + 8]
mov dword ptr [esi + 8], eax
mov dword ptr [ebx + 8], edx

mov eax, dword ptr [ebx + 12]    ; swap value
mov edx, dword ptr [esi + 12]
mov dword ptr [esi + 12], eax
mov dword ptr [ebx + 12], edx


mov eax, [ebx + 4]
mov edx, eax

mov eax, [ebx]
mov [ebx + 4], eax

mov esi, [ebx + 4]
mov eax, [esi]
mov [ebx], eax

mov esi, [ebx + 4]
mov eax, [esi + 4]
mov [esi], eax

mov [esi + 4], edx


mov eax, [ebx + 4]
push eax
call update_height
add esp, 4


push ebx
call update_height
add esp, 4


mov eax, [ebx]

end_func:
pop ebx
pop ebp
ret
right_rotate endp


;--------------------------------------------------------------------------------


left_rotate proc            ; левый поворот
push ebp                    ; параметры uint node_ptr
push ebx                    ;                8
mov ebp, esp
add ebp, 4

mov ebx, dword ptr [ebp + 8]
mov eax, [ebx + 4]
mov esi, eax

mov eax, dword ptr [ebx + 8]     ; swap key
mov edx, dword ptr [esi + 8]
mov dword ptr [esi + 8], eax
mov dword ptr [ebx + 8], edx

mov eax, dword ptr [ebx + 12]     ; swap value
mov edx, dword ptr [esi + 12]
mov dword ptr [esi + 12], eax
mov dword ptr [ebx + 12], edx


mov eax, [ebx]
mov edx, eax

mov eax, [ebx + 4]
mov [ebx], eax

mov esi, [ebx]
mov eax, [esi + 4]
mov [ebx + 4], eax

mov esi, [ebx]
mov eax, [esi]
mov [esi + 4], eax

mov [esi], edx

mov eax, [ebx]
push eax
call update_height
add esp, 4


push ebx
call update_height
add esp, 4


mov eax, [ebx + 4]

end_func:
pop ebx
pop ebp
ret
left_rotate endp


;--------------------------------------------------------------------------------


get_max_node proc           ; поиск максимальной вершины
push ebp                    ; параметры uint node_ptr
push ebx                    ;                8
mov ebp, esp
add ebp, 4

mov edx, dword ptr [ebp + 8]
mov eax, 0
cmp edx, 0
je end_func

mov ebx, dword ptr [ebp + 8]
mov edx, dword ptr [ebx + 4]
mov eax, ebx
cmp edx, 0
je end_func

mov ebx, dword ptr [ebp + 8]
mov eax, dword ptr [ebx + 4]
push eax
call get_max_node
add esp, 4

end_func:
pop ebx
pop ebp
ret
get_max_node endp


;--------------------------------------------------------------------------------


delete_node proc            ; удаление вершины
push ebp                    ; параметры uint node_ptr, int key
push ebx                    ;                8            12
mov ebp, esp
add ebp, 4

mov eax, dword ptr [ebp + 8]
cmp eax, 0
jne check_left
node_null:
	xor eax, eax
	jmp end_func

check_left:
mov eax, dword ptr [ebp + 12]
mov ebx, dword ptr [ebp + 8]
mov edx, dword ptr [ebx + 8]
cmp eax, edx
jge check_right
go_left:
	mov eax, dword ptr [ebp + 12]
	push eax
	mov ebx, dword ptr [ebp + 8]
	mov eax, dword ptr [ebx]
	push eax
	call delete_node
	add esp, 8
	mov ebx, dword ptr [ebp + 8]
	mov dword ptr [ebx], eax
	jmp end_func

check_right:
mov eax, dword ptr [ebp + 12]
mov ebx, dword ptr [ebp + 8]
mov edx, dword ptr [ebx + 8]
cmp eax, edx
jle find_node
go_right:
	mov eax, dword ptr [ebp + 12]
	push eax
	mov ebx, dword ptr [ebp + 8]
	mov eax, dword ptr [ebx + 4]
	push eax
	call delete_node
	add esp, 8
	mov ebx, dword ptr [ebp + 8]
	mov dword ptr [ebx + 4], eax
	jmp end_func
	

find_node:
	mov ebx, dword ptr [ebp + 8]
	mov eax, dword ptr [ebx]
	cmp eax, 0
	je check_side
	mov eax, dword ptr [ebx + 4]
	cmp eax, 0
	jne go_search_max

	check_side:
		mov eax, dword ptr [ebx]
		cmp eax, 0
		jne node_node_left

		node_node_right:
			mov esi, dword ptr [ebx + 4]
			cmp esi, 0
			je set_null_right
			jmp node_node_right_1

			set_null_right:
				mov dword ptr [ebp + 8], 0
				jmp end_func

			node_node_right_1:	

			mov ebx, dword ptr [ebp + 8]
			mov dword ptr [ebp + 8], esi
			mov eax, dword ptr [esi + 8]
			mov dword ptr [ebx + 8], eax
			mov eax, dword ptr [esi + 12]
			mov dword ptr [ebx + 12], eax
			mov dword ptr [ebx + 4], 0
			jmp end_func

		node_node_left:
			mov esi, dword ptr [ebx]
			cmp esi, 0
			je set_null_left
			jmp node_node_left_1
			
			set_null_left:
				mov dword ptr [ebp + 8], 0
				jmp end_func

			node_node_left_1:

			mov ebx, dword ptr [ebp + 8]
			mov dword ptr [ebp + 8], esi
			mov eax, dword ptr [esi + 8]
			mov dword ptr [ebx + 8], eax
			mov eax, dword ptr [esi + 12]
			mov dword ptr [ebx + 12], eax
			mov dword ptr [ebx], 0
			jmp end_func

	go_search_max:
		mov ebx, dword ptr [ebp + 8]
		mov eax, dword ptr [ebx]
		push eax
		call get_max_node
		add esp, 4

		mov esi, eax
		mov ebx, dword ptr [ebp + 8]
		mov edx, dword ptr [esi + 8]
		mov [ebx + 8], edx
		mov edx, dword ptr [esi + 12]
		mov [ebx + 12], edx

		mov eax, dword ptr [esi + 8]
		push eax
		mov eax, dword ptr [ebx]         ; edited to node.left
		push eax
		call delete_node
		add esp, 8

		mov ebx, dword ptr [ebp + 8]
		mov dword ptr [ebx], eax             ; edited to node.left


end_func:

mov ebx, dword ptr [ebp + 8]
cmp ebx, 0
je end_func_1
push ebx
call update_height
add esp, 4

mov ebx, dword ptr [ebp + 8]
push ebx
call balance_node
add esp, 4


end_func_1:
	mov eax, dword ptr [ebp + 8]

pop ebx
pop ebp
ret
delete_node endp

end