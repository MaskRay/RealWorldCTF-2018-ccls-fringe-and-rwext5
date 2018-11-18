#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

int main() {
  const int bs = 1024;
  mt19937 gen{random_device()()};
  uniform_int_distribution<> dis(0, 255);
  vector<char> plain(bs * 1111);
  for (char &b: plain)
    b = dis(gen);
  const char s[] = "The flag is rwctf{ext4 adds extent tree to ext3}";
  copy(begin(s), end(s)-1, &plain[bs * 555]);
  for (char b : plain) cout << b;
}
