#pragma once

#include "symbols/math.h"

#define DV(a, b) PTOS_ZERO_DVIDE(a, b)
#define VEC(n) Vector##n##<T>
#define MAT(n) Matrix##n##<T>
#define TEMPL_T template<typename T>
#define PREFIX TEMPL_T inline
//operator reverse
#define OPRV(RT, OP, ARG1T, ARG1, ARG2T, ARG2) RT operator OP (ARG2T ARG2, ARG1T ARG1) { return ARG1 OP ARG2; }
//operator reverse expanded
#define OPRVE(RT, OP, ARG1, ARG2, ...) RT operator OP (ARG2, ARG1) { return RT(__VA_ARGS__); }
//operator inplace (OPE is needed because intellisense would freak if i had an = next to OP)
#define OPINP(RT, OPE, OP, ARG1T, ARG1, ARG2T, ARG2) RT operator OPE (ARG1T ARG1, ARG2T ARG2) { return (ARG1 = ARG1 OP ARG2); }
//operator define
#define OPRDEF(NAME,N)\
	PREFIX OPRV(NAME(N),*,NAME(N)&,v,T,m)\
	PREFIX OPRV(NAME(N),+,NAME(N)&,v,T,m)\
	PREFIX OPINP(NAME(N),*=,*,NAME(N)&,v,T,m)\
	PREFIX OPINP(NAME(N),/=,/,NAME(N)&,v,T,m)\
	PREFIX OPINP(NAME(N),+=,+,NAME(N)&,v,T,m)\
	PREFIX OPINP(NAME(N),-=,-,NAME(N)&,v,T,m)\
	PREFIX OPINP(NAME(N),*=,*,NAME(N)&,v,NAME(N)&,v2)\
	PREFIX OPINP(NAME(N),/=,/,NAME(N)&,v,NAME(N)&,v2)\
	PREFIX OPINP(NAME(N),+=,+,NAME(N)&,v,NAME(N)&,v2)\
	PREFIX OPINP(NAME(N),-=,-,NAME(N)&,v,NAME(N)&,v2)

//operator define expanded
#define OPRDEFE(NAME,N,OP,...) PREFIX OPRVE(NAME(N),OP,NAME(N)& v,T m,__VA_ARGS__)
#define VECDEF(...) OPRDEF(VEC,__VA_ARGS__) 
#define VECDEFE(N,OP,...) OPRDEFE(VEC,N,OP,__VA_ARGS__)
#define MATDEF(...) OPRDEF(MAT,__VA_ARGS__) 
#define MATDEFE(N,OP,...) OPRDEFE(MAT,N,OP,__VA_ARGS__)
//matrix define vector
#define MATDEFVEC(N)\
	PREFIX OPRV(VEC(N),*,VEC(N)&,v,MAT(N)&,mat)\
	PREFIX OPRV(VEC(N),/,VEC(N)&,v,MAT(N)&,mat)\
	PREFIX OPINP(VEC(N),*=,*,VEC(N)&,v,MAT(N)&,mat)\
	PREFIX OPINP(VEC(N),/=,/,VEC(N)&,v,MAT(N)&,mat)

namespace PTOS {

	//vector operators

	VECDEF(2)
	VECDEFE(2, /, DV(m, v[0]), DV(m, v[1]))
	VECDEFE(2, -, m - v[0], m - v[1])

	VECDEF(3)
	VECDEFE(3, /, DV(m, v[0]), DV(m, v[1]), DV(m, v[2]))
	VECDEFE(3, -, m - v[0], m - v[1], m - v[2])

	VECDEF(4)
	VECDEFE(4, /, DV(m, v[0]), DV(m, v[1]), DV(m, v[2]), DV(m, v[3]))
	VECDEFE(4, -, m - v[0], m - v[1], m - v[2], m - v[3])

	//matrix operators

	MATDEF(2)
	MATDEFVEC(2)
	MATDEFE(2, /, {{ DV(m, v[0][0]), DV(m, v[0][1]) },{ DV(m, v[1][0]), DV(m, v[1][1]) }})
	MATDEFE(2, -, {{ m - v[0][0], m - v[0][1] },{ m - v[1][0], m - v[1][1] }})

	MATDEF(3)
	MATDEFVEC(3)
	MATDEFE(3, /, {{ DV(m, v[0][0]), DV(m, v[0][1]), DV(m, v[0][2]) },{ DV(m, v[1][0]), DV(m, v[1][1]), DV(m, v[1][2]) },{ DV(m, v[2][0]), DV(m, v[2][1]), DV(m, v[2][2]) }})
	MATDEFE(3, -, {{ m - v[0][0], m - v[0][1], m - v[0][2] },{ m - v[1][0], m - v[1][1], m - v[1][2] },{ m - v[2][0], m - v[2][1], m - v[2][2] }})

	MATDEF(4)
	MATDEFVEC(4)
	MATDEFE(4, /, { { DV(m, v[0][0]), DV(m, v[0][1]), DV(m, v[0][2]), DV(m, v[0][3]) },{ DV(m, v[1][0]), DV(m, v[1][1]), DV(m, v[1][2]), DV(m, v[1][3]) },{ DV(m, v[2][0]), DV(m, v[2][1]), DV(m, v[2][2]), DV(m, v[2][3]) },{ DV(m, v[3][0]), DV(m, v[3][1]), DV(m, v[3][2]), DV(m, v[3][3]) } } )
	MATDEFE(4, -, { { m - v[0][0], m - v[0][1], m - v[0][2], m - v[0][3] },{ m - v[1][0], m - v[1][1], m - v[1][2], m - v[1][3] },{ m - v[2][0], m - v[2][1], m - v[2][2], m - v[2][3] },{ m - v[3][0], m - v[3][1], m - v[3][2], m - v[3][3] } } )
}

//make sure macros only exist in this file

#undef DV
#undef VEC
#undef MAT
#undef TEMPL_T
#undef PREFIX
#undef OPRV
#undef OPRVE
#undef OPINP
#undef OPRDEF
#undef OPRDEFE
#undef VECDEF
#undef VECDEFE
#undef MATDEF
#undef MATDEFE
#undef MATDEFVEC
