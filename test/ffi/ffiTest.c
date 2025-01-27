#include <stdlib.h>
#include <stdio.h>
#include "../../include/bqnffi.h"

void do_nothing() { }

int32_t getType(BQNV v) {
  int32_t i = bqn_type(v);
  bqn_free(v);
  return i;
}

BQNV timesTen(BQNV v) {
  size_t len = bqn_bound(v);
  int32_t* buf = malloc(len*4);
  bqn_readI32Arr(v, buf);
  for (int i = 0; i < len; i++) buf[i] = buf[i] * 10;
  BQNV res = bqn_makeI32Vec(len, buf);
  free(buf);
  bqn_free(v);
  return res;
}

BQNV readAtoms(BQNV num, BQNV chr) {
  uint32_t c1 = bqn_readChar(chr); uint32_t c2 = bqn_toChar(chr);
  double   f1 = bqn_readF64 (num); double   f2 = bqn_toF64 (num);
  printf("%u %u %.18f %.18f\n", c1, c2, f1, f2);
  return bqn_makeChar(c1+1);
}

BQNV readTyped(BQNV x) {
  BQNV objs[7];
  bqn_readObjArr(x, objs);
  
  BQNV pick3 = bqn_pick(x, 3);
  BQNV equal = bqn_evalCStr("≡");
  if (!bqn_toF64(bqn_call2(equal, pick3, objs[3]))) printf("bqn_pick didn't give the same element as bqn_readObjArr!\n");
  bqn_free(equal);
  bqn_free(pick3);
  
  double res = 0;
  int8_t   bufI8 [10]; bqn_readI8Arr (objs[0], bufI8 ); bqn_free(objs[0]); for (int i=0; i<10; i++) res+= bufI8 [i];
  int16_t  bufI16[10]; bqn_readI16Arr(objs[1], bufI16); bqn_free(objs[1]); for (int i=0; i<10; i++) res+= bufI16[i];
  int32_t  bufI32[10]; bqn_readI32Arr(objs[2], bufI32); bqn_free(objs[2]); for (int i=0; i<10; i++) res+= bufI32[i];
  double   bufF64[10]; bqn_readF64Arr(objs[3], bufF64); bqn_free(objs[3]); for (int i=0; i<10; i++) res+= bufF64[i];
  uint8_t  bufC8 [10]; bqn_readC8Arr (objs[4], bufC8 ); bqn_free(objs[4]); for (int i=0; i<10; i++) res+= bufC8 [i];
  uint16_t bufC16[10]; bqn_readC16Arr(objs[5], bufC16); bqn_free(objs[5]); for (int i=0; i<10; i++) res+= bufC16[i];
  uint32_t bufC32[10]; bqn_readC32Arr(objs[6], bufC32); bqn_free(objs[6]); for (int i=0; i<10; i++) res+= bufC32[i];
  
  bqn_free(x);
  return bqn_makeF64(res);
}

BQNV getField(BQNV ns, BQNV name, BQNV def) {
  BQNV res;
  if (bqn_hasField(ns, name)) {
    res = bqn_getField(ns, name);
    bqn_free(def);
  } else {
    res = def;
  }
  bqn_free(ns);
  bqn_free(name);
  return res;
}

BQNV getShape(BQNV x) {
  size_t n = bqn_rank(x);
  size_t sh[n];
  
  bqn_shape(x, sh);
  bqn_free(x);
  
  int16_t res[n];
  for (int i = 0; i < n; i++) res[i] = sh[i];
  
  return bqn_makeI16Vec(n, res);
}

BQNV evalBQN(BQNV x) {
  BQNV r = bqn_eval(x);
  bqn_free(x);
  return r;
}

BQNV makeArrays() {
  BQNV res[16];
  size_t shape[3] = {2,1,3};
  res[ 0] = bqn_makeI8Arr (3, shape, (int8_t  []){1,2,3,4,5,6});
  res[ 1] = bqn_makeI16Arr(3, shape, (int16_t []){1,2,3,4,500,-600});
  res[ 2] = bqn_makeI32Arr(3, shape, (int32_t []){1,2,3,4,500000000,-600000000});
  res[ 3] = bqn_makeF64Arr(3, shape, (double  []){1,2,3,4,5.25,6.9765625});
  res[ 4] = bqn_makeC8Arr (3, shape, (uint8_t []){48,49,50,51,52,53});
  res[ 5] = bqn_makeC16Arr(3, shape, (uint16_t[]){48,49,50,51,52,9033});
  res[ 6] = bqn_makeC32Arr(3, shape, (uint32_t[]){48,49,50,51,52,120169});
  res[ 7] = bqn_makeObjArr(2, (size_t[]){2,2}, (BQNV[]){
    bqn_makeChar(120169),
    bqn_makeC8Arr(2, shape, (uint8_t[]){48,49,50}),
    bqn_makeC8Arr(1, shape, (uint8_t[]){48,49,50}),
    bqn_makeC8Arr(0, shape, (uint8_t[]){48})
  });
  res[ 8] = bqn_makeI8Vec (7, (int8_t  []){3,1,4,1,5,9,7});
  res[ 9] = bqn_makeI16Vec(7, (int16_t []){3,1,4,1,5,9,7});
  res[10] = bqn_makeI32Vec(7, (int32_t []){3,1,4,1,5,9,7});
  res[11] = bqn_makeF64Vec(7, (double  []){3,1,4,1,5,9,7});
  res[12] = bqn_makeC8Vec (7, (uint8_t []){97,98,99,65,66,67,59});
  res[13] = bqn_makeC16Vec(7, (uint16_t[]){97,98,99,65,66,67,59});
  res[14] = bqn_makeC32Vec(7, (uint32_t[]){97,98,99,65,66,67,59});
  res[15] = bqn_makeUTF8Str(11, "{𝕨+𝕩}");
  
  return bqn_makeObjVec(16, res);
}

BQNV makeThree(BQNV x) {
  return bqn_makeObjVec(3, (BQNV[]){bqn_copy(x), bqn_copy(x), x});
}

int32_t directAccess(BQNV x) {
  BQNElType e = bqn_directArrType(x);
  uint32_t res = 0;
  if (e==elt_i32) {
    size_t bound = bqn_bound(x);
    const int32_t* els = bqn_directI32(x);
    for (size_t i = 0; i < bound; i++) res = res*31 + (uint32_t)els[i];
  } else {
    printf("not elt_i32!\n");
  }
  bqn_free(x);
  return res;
}

static BQNV add_args(BQNV t, BQNV x) {
  return bqn_makeF64(bqn_toF64(t) + bqn_toF64(x));
}
BQNV bindAdd(BQNV x) {
  BQNV r = bqn_makeBoundFn1(add_args, x);
  bqn_free(x);
  return r;
}

void printArgs(int8_t i8, int16_t i16, int32_t i32, uint8_t u8, uint16_t u16, uint32_t u32, float f, double d) {
  printf("args: %d %d %d %u %u %u %.18f %.18f\n", i8, i16, i32, u8, u16, u32, f, d);
}
void noopArgs(int8_t i8, int16_t i16, int32_t i32, uint8_t u8, uint16_t u16, uint32_t u32, float f, double d) { }

void printPtrArgs(int8_t* i8, int16_t* i16, int32_t* i32, uint8_t* u8, uint16_t* u16, uint32_t* u32, float* f, double* d) {
  printf("args: %d %d %d %u %u %u %.18f %.18f\n", *i8, *i16, *i32, *u8, *u16, *u32, *f, *d);
}

float printU64s(uint64_t a, uint64_t* b) {
  printf("%llx %llx %llx %llx\n", (long long)a, (long long)b[0], (long long)b[1], (long long)b[2]);
  return 12345678;
}



int32_t multiplyI32Ptrs(int32_t* a, int32_t* b, int32_t len) {
  int32_t r = 0;
  for (int i = 0; i < len; i++) {
    r+= a[i]*b[i];
  }
  return r;
}
float sumF32Arr(float* f, int len) {
  float r = 0;
  for (int i = 0; i < len; i++) r+= f[i];
  return r;
}


void incI32s(int32_t* a, int32_t len) {
  for (int i = 0; i < len; i++) a[i]++;
}

void incInts(int32_t* a, int16_t* b, int8_t* c) {
  printf("%d %d %d\n", *a, *b, *c);
  (*a)++;
  (*b)++;
  (*c)++;
}

uint64_t ident_u64(uint64_t x) { return x; }
int64_t ident_i64(int64_t x) { return x; }
double ident_f64(double a) { return a; }

void* pick_ptr(void** arr, int idx) {
  return arr[idx];
}
uint64_t pick_u64(uint64_t* arr, int idx) {
  return arr[idx];
}


typedef struct {
  uint8_t u8v;
  int32_t i32v;
  int16_t u16v;
  uint64_t u64v;
  double f64v;
} S1;

int16_t thirdMember(S1 s) {
  return s.u16v;
}

S1 incMembers(S1 s) {
  s.u8v++;
  s.u16v++;
  s.i32v++;
  s.u64v++;
  s.f64v++;
  return s;
}

typedef struct {
  S1 a, b;
} S2;

S1 printAndInc(S1 s) {
  s = incMembers(s);
  printf("%u %d %d %lx %.17g\n", s.u8v, s.i32v, s.u16v, s.u64v, s.f64v);
  return s;
}

void incMany(S2* list, uint64_t count) {
  for (uint64_t i = 0; i < count; i++) {
    list[i].a = printAndInc(list[i].a);
    list[i].b = printAndInc(printAndInc(list[i].b));
  }
}

typedef struct {
  uint32_t* arr;
  uint64_t sz;
} U32Arr;

uint32_t arrayOp(U32Arr a) {
  uint32_t r = 0;
  for (uint64_t i = 0; i < a.sz; i++) {
    r+= a.arr[i];
    a.arr[i]++;
  }
  return r;
}
uint32_t arrayRefOp(U32Arr* a) {
  uint32_t res = arrayOp(*a);
  a->arr++;
  return res;
}

int plusone(int x) {
  return x + 1;
}



int32_t arrarg(int32_t a[3]) {
  return a[0] + a[1] + a[2];
}

typedef struct {
  int32_t a[1];
} ArrStruct1;

int32_t arrstruct1(ArrStruct1 a, ArrStruct1* b) {
  return a.a[0] + b->a[0];
}

int32_t ptrToArr(int32_t (*a)[2]) {
  return a[3][0]+a[4][1];
}

typedef struct {
  int32_t a[1];
  ArrStruct1 b[2];
  double c[3];
} ArrStruct2;

ArrStruct2 arrstruct2(ArrStruct2 a, ArrStruct2* b) {
  return (ArrStruct2){
    .a = {a.a[0] + b->a[0]},
    .b = {{a.b[0].a[0] + b->b[1].a[0]}, {a.b[1].a[0] + b->b[0].a[0]}},
    .c = {1.0, 2.0, a.c[0] + a.c[2] + b->c[1] + b->c[2]}
  };
}
void arrstruct2Inc(ArrStruct2* b) {
  for (int i = 0; i < 2; i++) {
    b[i].a[0]++;
    b[i].b[1].a[0]++;
    b[i].c[1]++;
    b[i].c[2]++;
  }
}