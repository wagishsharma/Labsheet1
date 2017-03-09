/* @author Wagish Sharma
 * Computes the transition table (automaton) for the given string over the defined alphabet.
 */

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MIN_ALPHA 'a'
#define MAX_ALPHA 'z'
#define min(x, y)   (x < y ? x : y)
int rows;
int **transitionTable;

int tableHeader(char c) {
  return (int) (c - MIN_ALPHA);
}

bool isSuf(string x, string y) {
  if (x.length() == 0)
    return true;
  
  if (x.length() > y.length())
    return false;
  
  return x == y.substr(y.length() - x.length(), x.length());
}

void printTransitionTable() {
  int row;
  char column;
  printf("    Q |");
  for (column = MIN_ALPHA; column <= MAX_ALPHA; column++)
    printf("  %c", column);
  printf("\n");
  printf("   ---+");
  for (column = MIN_ALPHA; column <= MAX_ALPHA; column++)
    printf("---");
  printf("\n");
  for (row = 0; row < rows; row++) {
    printf("   %2d |", row);
    for (column = MIN_ALPHA; column <= MAX_ALPHA; column++)
      printf(" %2d", transitionTable[row][tableHeader(column)]);
    printf("\n");
  }
  printf("\n");
}

/* function to build aumotata. */
void computeTransitionTable(string p) {
  int m = p.length();
  string Pq;
  int k, q;

  rows = m + 1;
  transitionTable = (int **) malloc(rows * sizeof(int *));
  for (k = 0; k <= m; k++)
    transitionTable[k] = (int *) malloc(((int)(MAX_ALPHA - MIN_ALPHA) + 1) * sizeof(int));
  
  for (q = 0; q <= m; q++) {
    Pq = p.substr(0, q);
    for (char a = MIN_ALPHA; a <= MAX_ALPHA; a++) {
      k = min(m + 1, q + 2);
      do { k--; } while (!isSuf(p.substr(0, k), Pq + a));
      transitionTable[q][tableHeader(a)] = k;
    }
  }
}

/* function to match finite automata. */
void match(string T, int m) {
  int n = T.length();
  int q = 0;
  for (int i = 0; i < n; i++) {
    q = transitionTable[q][tableHeader(T[i])];
    if (q == m)
      cout << "Pattern occurs with shift " << i - m << endl;
  }
}

int main(int argc, char **argv) {
  if (argc != 2 && argc != 3) {
    printf("Please use this format to test this code : ./a.out pattern [string]\n");
    return 1;
  }
  
  string pattern = argv[1];
  computeTransitionTable(pattern);
  printTransitionTable();
  
  if (argc == 3)
    match(argv[2], pattern.length());
}
