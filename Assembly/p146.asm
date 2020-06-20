assume cs:codesg,ds:datasg

datasg segment
 db 'BaSic'
 db 'MiNiX'
datasg ends
	
codesg segment
 start:	mov ax,datasg
	mov ds,ax

	mov bx,0

	mov cx,5	;设置循环次数5

     s: mov al,0[bx]	;[bx+0]定位第一个字符串中的字符
        and al,11011111B
	mov [bx],al

	mov al,5[bx]	;[bx+5]定位第一个字符串中的字符
        or al,00100000B
	mov [bx],al

	inc bx
	loop s

	mov ax,4c00h
	int 21h

codesg ends

end start