unsigned long djb2(const char *str) {
//   unsigned long key = 5381;

//   for(int i = 0; str[i] != '\0'; i++) {
//     int ascii = int(str[i]);
//     key = (key << 5) + key + ascii;
//   }

//   return key % 20;
// }