mdef(16383)_out(1)_in(2)
mov r0, in0
mov r1, in1
div_zeroop(infinity) r0.x___, r0.x, r1.x
mov out0, r0
mend
il_cs_2_0
dcl_cb cb0[15] ; Constant buffer that holds ABI data
dcl_literal l0, 0x00000004, 0x00000001, 0x00000002, 0x00000003
dcl_literal l1, 0x00FFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFD
dcl_literal l2, 0x0000FFFF, 0xFFFFFFFE, 0x000000FF, 0xFFFFFFFC
dcl_literal l3, 0x00000018, 0x00000010, 0x00000008, 0xFFFFFFFF
dcl_literal l4, 0xFFFFFF00, 0xFFFF0000, 0xFF00FFFF, 0xFFFF00FF
dcl_literal l5, 0x00000000, 0x00000004, 0x00000008, 0x0000000C
dcl_literal l6, 0x00000020, 0x00000020, 0x00000020, 0x00000020
dcl_literal l7, 0x00000018, 0x0000001F, 0x00000010, 0x0000001F
dcl_literal l8, 0x80000000, 0x80000000, 0x80000000, 0x80000000
call 1024;$
endmain
func 1024 ; __OpenCL_image_rotate_kernel
mov r1013, cb0[8].x
mov r1019, l1.0000
dcl_max_thread_per_group 256 
dcl_arena_uav_id(13)
dcl_raw_uav_id(11)
dcl_arena_uav_id(8)
mov r0.__z_, vThreadGrpIdFlat0.x
mov r1022.xyz0, vTidInGrp0.xyz
mov r1023.xyz0, vThreadGrpId0.xyz
imad r1021.xyz0, r1023.xyzz, cb0[1].xyzz, r1022.xyzz
iadd r1021.xyz0, r1021.xyz0, cb0[6].xyz0
iadd r1023.xyz0, r1023.xyz0, cb0[7].xyz0
mov r1023.___w, r0.z
ishl r1023.___w, r1023.w, l0.z
mov r1018.x___, l0.0000
udiv r1024.xyz_, r1021.xyzz, cb0[10].xyzz
imad r1025.xyz0, r1023.xyzz, cb0[10].xyzz, r1022.xyzz
dcl_literal l17, 0x00000000, 0x00000000, 0x00000000, 0x00000000; f32:i32 0
dcl_literal l12, 0x00000001, 0x00000001, 0x00000001, 0x00000001; f32:i32 1
dcl_literal l14, 0x00000003, 0x00000003, 0x00000003, 0x00000003; f32:i32 3
dcl_literal l19, 0x00000008, 0x00000008, 0x00000008, 0x00000008; f32:i32 8
dcl_literal l20, 0x00000010, 0x00000010, 0x00000010, 0x00000010; f32:i32 16
dcl_literal l18, 0x00000018, 0x00000018, 0x00000018, 0x00000018; f32:i32 24
dcl_literal l11, 0x0000001F, 0x0000001F, 0x0000001F, 0x0000001F; f32:i32 31
dcl_literal l21, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF; f32:i32 255
dcl_literal l15, 0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC; f32:i32 4294967292
dcl_literal l13, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF; f32:i32 4294967295
dcl_literal l16, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFD; f128:i128 1844674406941458432018446744065119617022
dcl_cb cb1[6]
; Kernel arg setup: src_data
mov r1.x, cb1[0].x
; Kernel arg setup: dest_data
mov r1.y, cb1[1].x
; Kernel arg setup: W
mov r1.z, cb1[2].x
; Kernel arg setup: H
mov r1.w, cb1[3].x
; Kernel arg setup: sinTheta
mov r2.x, cb1[4].x
; Kernel arg setup: cosTheta
mov r2.y, cb1[5].x
call 1027 ; image_rotate
ret
endfunc ; __OpenCL_image_rotate_kernel
;ARGSTART:__OpenCL_image_rotate_kernel
;version:2:0:88
;device:redwood
;uniqueid:1024
;memory:hwprivate:0
;memory:hwregion:0
;memory:hwlocal:0
;pointer:src_data:i8:1:1:0:uav:11:1:RO
;pointer:dest_data:i8:1:1:16:uav:8:1:RW
;value:W:i32:1:1:32
;value:H:i32:1:1:48
;value:sinTheta:float:1:1:64
;value:cosTheta:float:1:1:80
;function:1:1027
;uavid:11
;privateid:1
;ARGEND:__OpenCL_image_rotate_kernel
func 1027 ; image_rotate                ; @__OpenCL_image_rotate_kernel
; BB#0:                                 ; %entry
	mov r65.___w, r1.z
	mov r66.x___, l11
	ushr r66._y__, r1.w, r66.x
	iadd r66._y__, r1.w, r66.y
	mov r66.__z_, l12
	ishr r66._y__, r66.y, r66.z
	inegate r66.___w, r66.y
	mov r67, r1021.xyz0
	mov r68.x___, r67.y000
	iadd r66.___w, r68.x, r66.w
	itof r66.___w, r66.w
	mul_ieee r68._y__, r66.w, r2.x
	ushr r66.x___, r65.w, r66.x
	iadd r66.x___, r65.w, r66.x
	ishr r66.x___, r66.x, r66.z
	inegate r68.__z_, r66.x
	mov r67.x___, r67.x000
	iadd r67._y__, r67.x, r68.z
	itof r67._y__, r67.y
	mul_ieee r67.__z_, r67.y, r2.y
	sub r67.__z_, r67.z, r68.y
	itof r66.x___, r66.x
	add r66.x___, r67.z, r66.x
	ftoi r66.x___, r66.x
	mov r67.__z_, l13
	ilt r67.___w, r67.z, r66.x
	mov r67.___w, r67.w
	ilt r68._y__, r66.x, r65.w
	mov r68._y__, r68.y
	iand r67.___w, r68.y, r67.w
	mul_ieee r65.x___, r66.w, r2.y
	mul_ieee r65._y__, r67.y, r2.x
	add r65.x___, r65.y, r65.x
	itof r65._y__, r66.y
	add r65.x___, r65.x, r65.y
	ftoi r65.x___, r65.x
	ilt r65._y__, r67.z, r65.x
	mov r65._y__, r65.y
	iand r65._y__, r67.w, r65.y
	ilt r65.__z_, r65.x, r1.w
	mov r65.__z_, r65.z
	iand r65._y__, r65.y, r65.z
	iand r65._y__, r65.y, r66.z
	if_logicalnz r65.y
	imul r65.x___, r65.x, r65.w
	iadd r65.x___, r65.x, r66.x
	iadd r65.x___, r1.y, r65.x
	imul r65._y__, r68.x, r65.w
	iadd r65._y__, r65.y, r67.x
	iadd r65._y__, r1.x, r65.y
	mov r1010.x___, r65.y
	iand r1008.x___, r1010.x, l14
	iand r1010.x___, r1010.x, l15
	iadd r1008, r1008.x, l16
	ieq r1012, r1008, l17
	cmov_logical r1008.x___, r1012.x, l17, l18
	cmov_logical r1008.x___, r1012.y, l19, r1008.x
	cmov_logical r1008.x___, r1012.z, l20, r1008.x
	uav_raw_load_id(11)_cached r1011.x___, r1010.x
	ishr r1011, r1011.x, r1008.x
	ishl r1011.x___, r1011.x, l18
	ishr r1011.x___, r1011.x, l18
	mov r65._y__, r1011.x
	mov r1011, r65.y
	mov r1010.x___, r65.x
	iand r1011.x___, r1011.x, l21
	uav_arena_store_id(13)_size(byte) r1010.x, r1011.x
	else
	endif
	ret
endfunc ; image_rotate
;ARGSTART:image_rotate
;uniqueid:1027
;ARGEND:image_rotate

end
