

unsigned int32 hash(int32 x) {
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) *0x45d9f3b;
  x = (x >> 16) ^ x;
}
