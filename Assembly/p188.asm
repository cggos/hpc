assume cs:codesg,ds:datasg

datasg segment
 db 'welcom'
datasg ends

codesg segment

 start:	mov dx,datasg
	mov ds,dx

	mov al,[0]
	mov ah,02h

	mov dx,0b800h
	mov ds,dx
	mov ds:[0],ax

	mov ax,4c00h
	int 21h

codesg ends

end start