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
func 1024 ; __OpenCL_histogram256_kernel
mov r1013, cb0[8].x
mov r1019, l1.0000
dcl_max_thread_per_group 256 
dcl_lds_id(1) 32768
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
dcl_literal l12, 0x00000000, 0x00000000, 0x00000000, 0x00000000; f32:i32 0
dcl_literal l21, 0x00000001, 0x00000001, 0x00000001, 0x00000001; f32:i32 1
dcl_literal l22, 0x00000002, 0x00000002, 0x00000002, 0x00000002; f32:i32 2
dcl_literal l23, 0x00000003, 0x00000003, 0x00000003, 0x00000003; f32:i32 3
dcl_literal l24, 0x00000004, 0x00000004, 0x00000004, 0x00000004; f32:i32 4
dcl_literal l25, 0x00000005, 0x00000005, 0x00000005, 0x00000005; f32:i32 5
dcl_literal l26, 0x00000006, 0x00000006, 0x00000006, 0x00000006; f32:i32 6
dcl_literal l27, 0x00000007, 0x00000007, 0x00000007, 0x00000007; f32:i32 7
dcl_literal l11, 0x00000008, 0x00000008, 0x00000008, 0x00000008; f32:i32 8
dcl_literal l31, 0x0000000A, 0x0000000A, 0x0000000A, 0x0000000A; f32:i32 10
dcl_literal l34, 0x00000010, 0x00000010, 0x00000010, 0x00000010; f32:i32 16
dcl_literal l33, 0x00000018, 0x00000018, 0x00000018, 0x00000018; f32:i32 24
dcl_literal l30, 0x00000100, 0x00000100, 0x00000100, 0x00000100; f32:i32 256
dcl_literal l29, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00; f32:i32 4294967040
dcl_literal l28, 0xFFFFFFF0, 0xFFFFFFF0, 0xFFFFFFF0, 0xFFFFFFF0; f32:i32 4294967280
dcl_literal l13, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8, 0xFFFFFFF8; f32:i32 4294967288
dcl_literal l14, 0xFFFFFFF9, 0xFFFFFFF9, 0xFFFFFFF9, 0xFFFFFFF9; f32:i32 4294967289
dcl_literal l15, 0xFFFFFFFA, 0xFFFFFFFA, 0xFFFFFFFA, 0xFFFFFFFA; f32:i32 4294967290
dcl_literal l16, 0xFFFFFFFB, 0xFFFFFFFB, 0xFFFFFFFB, 0xFFFFFFFB; f32:i32 4294967291
dcl_literal l17, 0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC, 0xFFFFFFFC; f32:i32 4294967292
dcl_literal l18, 0xFFFFFFFD, 0xFFFFFFFD, 0xFFFFFFFD, 0xFFFFFFFD; f32:i32 4294967293
dcl_literal l19, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE; f32:i32 4294967294
dcl_literal l20, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF; f32:i32 4294967295
dcl_literal l32, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFD; f128:i128 1844674406941458432018446744065119617022
dcl_cb cb1[3]
; Kernel arg setup: data
mov r1.x, cb1[0].x
; Kernel arg setup: sharedArray
mov r1.y, cb1[1].x
; Kernel arg setup: binResult
mov r1.z, cb1[2].x
call 1031 ; histogram256
ret
endfunc ; __OpenCL_histogram256_kernel
;ARGSTART:__OpenCL_histogram256_kernel
;version:2:0:88
;device:redwood
;uniqueid:1024
;memory:hwprivate:0
;memory:hwregion:0
;memory:hwlocal:0
;pointer:data:i8:1:1:0:uav:11:1:RO
;pointer:sharedArray:i8:1:1:16:hl:1:1:RW
;pointer:binResult:i32:1:1:32:uav:11:4:RW
;function:1:1031
;uavid:11
;privateid:1
;ARGEND:__OpenCL_histogram256_kernel
func 1031 ; histogram256                ; @__OpenCL_histogram256_kernel
; BB#0:                                 ; %entry
	mov r65.x___, r1.z
	mov r65._y__, r1.y
	mov r65.__z_, r1.x
	mov r66, r1022.xyz0
	mov r65.___w, r66.000x
	mov r66.x___, l11
	ishl r66._y__, r65.w, r66.x
	iadd r66.__z_, r66.y, r65.y
	iadd r66.x___, r66.z, r66.x
	mov r66.__z_, l12
	mov r67, cb0[1].xyz0
	mov r68, r1023.xyz0
	whileloop
	inegate r66.___w, r66.z
	iadd r69.__z_, r66.x, r66.w
	mov r66.___w, l13
	iadd r66.___w, r69.z, r66.w
	mov r69.___w, l12
	mov r1011, r69.w
	mov r1010.x___, r66.w
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r66.___w, l14
	iadd r66.___w, r69.z, r66.w
	mov r1011, r69.w
	mov r1010.x___, r66.w
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r66.___w, l15
	iadd r66.___w, r69.z, r66.w
	mov r1011, r69.w
	mov r1010.x___, r66.w
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r66.___w, l16
	iadd r66.___w, r69.z, r66.w
	mov r1011, r69.w
	mov r1010.x___, r66.w
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r66.___w, l17
	iadd r66.___w, r69.z, r66.w
	mov r1011, r69.w
	mov r1010.x___, r66.w
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r66.___w, l18
	iadd r66.___w, r69.z, r66.w
	mov r1011, r69.w
	mov r1010.x___, r66.w
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r66.___w, l19
	iadd r66.___w, r69.z, r66.w
	mov r1011, r69.w
	mov r1010.x___, r66.w
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r66.___w, l20
	iadd r66.___w, r69.z, r66.w
	mov r1011, r69.w
	mov r1010.x___, r66.w
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r1011, r69.w
	mov r1010.x___, r69.z
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r66.___w, l21
	iadd r69.x___, r69.z, r66.w
	mov r1011, r69.w
	mov r1010.x___, r69.x
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r69.x___, l22
	iadd r69._y__, r69.z, r69.x
	mov r1011, r69.w
	mov r1010.x___, r69.y
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r69._y__, l23
	iadd r70.x___, r69.z, r69.y
	mov r1011, r69.w
	mov r1010.x___, r70.x
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r70.x___, l24
	iadd r70.x___, r69.z, r70.x
	mov r1011, r69.w
	mov r1010.x___, r70.x
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r70.x___, l25
	iadd r70.x___, r69.z, r70.x
	mov r1011, r69.w
	mov r1010.x___, r70.x
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r70.x___, l26
	iadd r70.x___, r69.z, r70.x
	mov r1011, r69.w
	mov r1010.x___, r70.x
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r70.x___, l27
	iadd r69.__z_, r69.z, r70.x
	mov r1011, r69.w
	mov r1010.x___, r69.z
	lds_store_byte_id(1) r1010.x, r1011.x
	mov r69.__z_, l28
	iadd r66.__z_, r66.z, r69.z
	mov r69.__z_, l29
	ieq r69.__z_, r66.z, r69.z
	break_logicalnz r69.z
	endloop
	mov r66.x___, l12
	fence_threads_lds
	mov r66.__z_, r67.00x0
	ishl r67.x___, r66.z, r69.x
	mov r67._y__, r68.0x00
	imul r67.__z_, r67.y, r66.z
	mov r67.___w, l11
	ishl r67.__z_, r67.z, r67.w
	iadd r67.__z_, r65.w, r67.z
	iadd r67.__z_, r65.z, r67.z
	ishl r67.___w, r67.y, r67.w
	ior r66.___w, r67.w, r66.w
	imul r66.___w, r66.z, r66.w
	iadd r66.___w, r65.w, r66.w
	iadd r66.___w, r65.z, r66.w
	ior r69.x___, r67.w, r69.x
	imul r69.x___, r66.z, r69.x
	iadd r69.x___, r65.w, r69.x
	iadd r69.x___, r65.z, r69.x
	ior r69._y__, r67.w, r69.y
	imul r69._y__, r66.z, r69.y
	iadd r69._y__, r65.w, r69.y
	iadd r65.__z_, r65.z, r69.y
	mov r69._y__, l30
	mov r67.___w, r66.x
	whileloop
	iadd r68.x___, r67.z, r67.w
	mov r1010.x___, r68.x
	iand r1008.x___, r1010.x, l23
	iand r1010.x___, r1010.x, l17
	iadd r1008, r1008.x, l32
	ieq r1012, r1008, l12
	cmov_logical r1008.x___, r1012.x, l12, l33
	cmov_logical r1008.x___, r1012.y, l11, r1008.x
	cmov_logical r1008.x___, r1012.z, l34, r1008.x
	uav_raw_load_id(11)_cached r1011.x___, r1010.x
	ishr r1011, r1011.x, r1008.x
	ishl r1011.x___, r1011.x, l33
	ushr r1011.x___, r1011.x, l33
	mov r68.x___, r1011.x
	ior r68.x___, r68.x, r66.y
	iadd r68.x___, r65.y, r68.x
	mov r1010.x___, r68.x
	lds_load_byte_id(1) r1011.x, r1010.x
	mov r68._y__, r1011.x
	mov r68.__z_, l21
	iadd r68._y__, r68.y, r68.z
	mov r1011, r68.y
	mov r1010.x___, r68.x
	lds_store_byte_id(1) r1010.x, r1011.x
	iadd r68.x___, r66.w, r67.w
	mov r1010.x___, r68.x
	iand r1008.x___, r1010.x, l23
	iand r1010.x___, r1010.x, l17
	iadd r1008, r1008.x, l32
	ieq r1012, r1008, l12
	cmov_logical r1008.x___, r1012.x, l12, l33
	cmov_logical r1008.x___, r1012.y, l11, r1008.x
	cmov_logical r1008.x___, r1012.z, l34, r1008.x
	uav_raw_load_id(11)_cached r1011.x___, r1010.x
	ishr r1011, r1011.x, r1008.x
	ishl r1011.x___, r1011.x, l33
	ushr r1011.x___, r1011.x, l33
	mov r68.x___, r1011.x
	ior r68.x___, r68.x, r66.y
	iadd r68.x___, r65.y, r68.x
	mov r1010.x___, r68.x
	lds_load_byte_id(1) r1011.x, r1010.x
	mov r68._y__, r1011.x
	iadd r68._y__, r68.y, r68.z
	mov r1011, r68.y
	mov r1010.x___, r68.x
	lds_store_byte_id(1) r1010.x, r1011.x
	iadd r68.x___, r69.x, r67.w
	mov r1010.x___, r68.x
	iand r1008.x___, r1010.x, l23
	iand r1010.x___, r1010.x, l17
	iadd r1008, r1008.x, l32
	ieq r1012, r1008, l12
	cmov_logical r1008.x___, r1012.x, l12, l33
	cmov_logical r1008.x___, r1012.y, l11, r1008.x
	cmov_logical r1008.x___, r1012.z, l34, r1008.x
	uav_raw_load_id(11)_cached r1011.x___, r1010.x
	ishr r1011, r1011.x, r1008.x
	ishl r1011.x___, r1011.x, l33
	ushr r1011.x___, r1011.x, l33
	mov r68.x___, r1011.x
	ior r68.x___, r68.x, r66.y
	iadd r68.x___, r65.y, r68.x
	mov r1010.x___, r68.x
	lds_load_byte_id(1) r1011.x, r1010.x
	mov r68._y__, r1011.x
	iadd r68._y__, r68.y, r68.z
	mov r1011, r68.y
	mov r1010.x___, r68.x
	lds_store_byte_id(1) r1010.x, r1011.x
	iadd r68.x___, r65.z, r67.w
	mov r1010.x___, r68.x
	iand r1008.x___, r1010.x, l23
	iand r1010.x___, r1010.x, l17
	iadd r1008, r1008.x, l32
	ieq r1012, r1008, l12
	cmov_logical r1008.x___, r1012.x, l12, l33
	cmov_logical r1008.x___, r1012.y, l11, r1008.x
	cmov_logical r1008.x___, r1012.z, l34, r1008.x
	uav_raw_load_id(11)_cached r1011.x___, r1010.x
	ishr r1011, r1011.x, r1008.x
	ishl r1011.x___, r1011.x, l33
	ushr r1011.x___, r1011.x, l33
	mov r68.x___, r1011.x
	ior r68.x___, r68.x, r66.y
	iadd r68.x___, r65.y, r68.x
	mov r1010.x___, r68.x
	lds_load_byte_id(1) r1011.x, r1010.x
	mov r68._y__, r1011.x
	iadd r68._y__, r68.y, r68.z
	mov r1011, r68.y
	mov r1010.x___, r68.x
	lds_store_byte_id(1) r1010.x, r1011.x
	iadd r67.___w, r67.w, r67.x
	mov r68.x___, l17
	iadd r69._y__, r69.y, r68.x
	ieq r68.x___, r69.y, r66.x
	break_logicalnz r68.x
	endloop
	mov r65.__z_, l30
	udiv r65.__z_, r65.z, r66.z
	mov r66.x___, l12
	ieq r66.x___, r65.z, r66.x
	mov r66._y__, l21
	fence_threads_lds
	if_logicalnz r66.x
	else
	mov r66.x___, l31
	ishl r66.x___, r67.y, r66.x
	iadd r65.x___, r65.x, r66.x
	whileloop
	iadd r66.x___, r65.y, r65.w
	mov r66._y__, l12
	ieq r66.___w, r66.z, r66.y
	mov r67.x___, r66.y
	mov r67._y__, r66.z
	if_logicalnz r66.w
	else
	whileloop
	mov r66.___w, l30
	iadd r66.___w, r66.x, r66.w
	mov r1010.x___, r66.x
	lds_load_ubyte_id(1) r1011.x, r1010.x
	ishl r1011.x___, r1011.x, l33
	ushr r1011.x___, r1011.x, l33
	mov r66.x___, r1011.x
	iadd r67.x___, r66.x, r67.x
	mov r66.x___, l20
	iadd r67._y__, r67.y, r66.x
	ieq r67.__z_, r67.y, r66.y
	mov r66.x___, r66.w
	break_logicalnz r67.z
	endloop
	endif
	mov r66.x___, l22
	ishl r66.x___, r65.w, r66.x
	iadd r66.x___, r65.x, r66.x
	mov r1011, r67.x
	mov r1010.x___, r66.x
	uav_raw_store_id(11) mem0.x___, r1010.x, r1011.x
	iadd r65.___w, r65.w, r66.z
	mov r66.x___, l20
	iadd r65.__z_, r65.z, r66.x
	ieq r66.x___, r65.z, r66.y
	break_logicalnz r66.x
	endloop
	endif
	ret
endfunc ; histogram256
;ARGSTART:histogram256
;uniqueid:1031
;ARGEND:histogram256

end
