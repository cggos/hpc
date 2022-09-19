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
func 1024 ; __OpenCL_VectorAdd_kernel
mov r1013, cb0[8].x
mov r1019, l1.0000
dcl_max_thread_per_group 256 
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
dcl_literal l11, 0x00000002, 0x00000002, 0x00000002, 0x00000002; f32:i32 2
dcl_cb cb1[3]
; Kernel arg setup: a
mov r1.x, cb1[0].x
; Kernel arg setup: b
mov r1.y, cb1[1].x
; Kernel arg setup: c
mov r1.z, cb1[2].x
call 1028 ; VectorAdd
ret
endfunc ; __OpenCL_VectorAdd_kernel
;ARGSTART:__OpenCL_VectorAdd_kernel
;version:2:0:88
;device:redwood
;uniqueid:1024
;memory:hwprivate:0
;memory:hwregion:0
;memory:hwlocal:0
;pointer:a:float:1:1:0:uav:11:4:RO
;pointer:b:float:1:1:16:uav:11:4:RO
;pointer:c:float:1:1:32:uav:11:4:RW
;function:1:1028
;uavid:11
;privateid:1
;ARGEND:__OpenCL_VectorAdd_kernel
func 1028 ; VectorAdd                   ; @__OpenCL_VectorAdd_kernel
; BB#0:                                 ; %entry
	mov r66, r1021.xyz0
	mov r65.___w, r66.000y
	mov r67, cb0[0].xyz0
	mov r67.x___, r67.x000
	imul r65.___w, r67.x, r65.w
	mov r66.x___, r66.x000
	iadd r65.___w, r65.w, r66.x
	mov r66.x___, l11
	ishl r65.___w, r65.w, r66.x
	iadd r65._y__, r1.y, r65.w
	mov r1010.x___, r65.y
	uav_raw_load_id(11)_cached r1011.x___, r1010.x
	mov r65._y__, r1011.x
	iadd r65.__z_, r1.x, r65.w
	mov r1010.x___, r65.z
	uav_raw_load_id(11)_cached r1011.x___, r1010.x
	mov r65.__z_, r1011.x
	add r65._y__, r65.z, r65.y
	iadd r65.x___, r1.z, r65.w
	mov r1011, r65.y
	mov r1010.x___, r65.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	ret
endfunc ; VectorAdd
;ARGSTART:VectorAdd
;uniqueid:1028
;ARGEND:VectorAdd

end
