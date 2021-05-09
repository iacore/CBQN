i8 utf8_len(u8 ch) {
  if (ch<128)           return 1;
  if ((ch>>5)==  0b110) return 2;
  if ((ch>>4)== 0b1110) return 3;
  if ((ch>>3)==0b11110) return 4;
  return -1;
}
u32 utf8_p(u8* p) {
  i32 len = utf8_len(*p);
  switch (len) { default: UD;
    case -1: return (u32)-1;
    case  1: return *p;
    case  2: return (0b11111u&*p)<< 6  |  (0b111111u&p[1]);
    case  3: return (0b1111u &*p)<<12  |  (0b111111u&p[2]) | (0b111111u&p[1])<<6;
    case  4: return (0b111u  &*p)<<18  |  (0b111111u&p[3]) | (0b111111u&p[2])<<6 | (0b111111u&p[1])<<12;
  }
}
B fromUTF8(char* s, i64 len) {
  u64 sz = 0;
  i64 j = 0;
  while (true) {
    i8 l = utf8_len((u8)s[j]);
    if (l==-1) thrM("Invalid UTF-8");
    if (j>=len) {
      if (j!=len) thrM("Invalid UTF-8");
      break;
    }
    sz++;
    j+= l;
  }
  B r = m_c32arrv(sz);
  u32* rp = c32arr_ptr(r);
  u64 p = 0;
  // TODO verify
  for (i64 i = 0; i < len; i+= utf8_len((u8)s[i])) rp[p++] = utf8_p((u8*)s+i); // may read after end, eh
  return r;
}

B fromUTF8l(char* s) {
  return fromUTF8(s, strlen(s));
}

void printUTF8(u32 c) {
  if (c<128) printf("%c", c);
  else if (c<=0x07FF) printf("%c%c"    , 0xC0| c>>6 , 0x80| (c      &0x3F)                                    );
  else if (c<=0xFFFF) printf("%c%c%c"  , 0xE0| c>>12, 0x80| (c>>6   &0x3F), 0x80| (c    &0x3F)                );
  else                printf("%c%c%c%c", 0xF0| c>>18, 0x80| (c>>12  &0x3F), 0x80| (c>>6 &0x3F), 0x80| (c&0x3F));
}

u64 snprintUTF8(char* p, u64 l, u32 c) {
  if (c<128) return snprintf(p, l, "%c", c);
  else if (c<=0x07FF) return snprintf(p, l, "%c%c"    , 0xC0| c>>6 , 0x80| (c      &0x3F)                                    );
  else if (c<=0xFFFF) return snprintf(p, l, "%c%c%c"  , 0xE0| c>>12, 0x80| (c>>6   &0x3F), 0x80| (c    &0x3F)                );
  else                return snprintf(p, l, "%c%c%c%c", 0xF0| c>>18, 0x80| (c>>12  &0x3F), 0x80| (c>>6 &0x3F), 0x80| (c&0x3F));
}
