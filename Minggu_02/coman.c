#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

void calculate(int argc, char** argv) {
  int a, b, c, d, e, f;
  int total = 0;
  clock_t start, end;
  double timelapse;
  srand(time(NULL));
  
  start = clock();
  if (argc > 1) {
    for (a = 0; a < atoi(argv[1]); a++) {
      if (argc > 2) {
        for (b = 0; b < atoi(argv[2]); b++) {
          if (argc > 3) {
            for (c = 0; c < atoi(argv[3]); c++) {
              if (argc > 4) {
                for (d = 0; d < atoi(argv[4]); d++) {
                  if (argc > 5) {
                    for (e = 0; e < atoi(argv[5]); e++) {
                      float x = rand();
                      total++;
                    }
                  }
                  float x = rand();
                  total++;
                }
              }
              float x = rand();
              total++;
            }
          }
          float x = rand();
          total++;
        }
      }
      float x = rand();
      total++;
    }
  }
  end = clock();
  timelapse = end - start;
  
  printf("total process n = %d with t = %3.4f seconds.\n", total, timelapse);
}

int main(int argc, char** argv) {
  
  calculate(argc, argv);

  return 0;
}
