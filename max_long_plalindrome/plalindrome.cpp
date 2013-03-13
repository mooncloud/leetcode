#include <stdio.h>
#include <string>
#include <algorithm>

#ifndef DEBUG
#define DEBUG
#endif

int max_long_plalindrome(const char*str) {
  if ( NULL == str || 0 == str[0] ) {
    return 0;
  }
  std::string s;
  s += '#';
  int m_size = strlen(str);
  for ( int i = 0; i < m_size; ++i ) {
    s += str[i];
    s += '#';
  }
  
#ifdef DEBUG
  fprintf(stderr, "%s\n", s.c_str());
#endif
  int m_new_size = s.size();
  int *p = new int[m_new_size];
  memset(p, 0, sizeof(p[0])*m_new_size);
  int max_right_pos = 0;
  int id = 0;
  for ( int i = 0; i < m_new_size; ++i ) {
    if ( max_right_pos > i ) {
      p[i] = std::min(p[2*id-i], max_right_pos-i);
    } else {
      p[i] = 1;
    }
    while ( i-p[i] >= 0 && s[i+p[i]] == s[i-p[i]] ) {
      p[i]++;
    }
    if ( p[i]+i > max_right_pos ) {
      max_right_pos = p[i]+i;
      id = i;
    }
  }
#ifdef  DEBUG
  for ( int i = 0; i < m_new_size; ++i ) {
    printf("%d\t", p[i]);
  }
  printf("\n");
#endif
  max_right_pos = 0;
  for ( int i = 0; i < m_new_size; ++i ) {
    if ( max_right_pos < p[i] ) {
      max_right_pos = p[i];
      id = i;
    }
  }
  int m_rev = 0;
  for ( int i = id-max_right_pos+1; i <= id+max_right_pos-1; ++i ) {
    if ( s[i] != '#' ) {
      m_rev++;
    }
  }
  delete[]p;
  
  return m_rev;
}

int main(int argc, char**args) {
  if ( argc <= 1 ) {
    fprintf(stderr, "input string\n");
    exit(1);
  }
  int m_rev = max_long_plalindrome(args[1]);
  printf("%d\n", m_rev);
}
