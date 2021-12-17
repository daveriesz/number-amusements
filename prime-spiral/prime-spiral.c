#include <stdio.h>

#define DIM_X 751
#define DIM_Y 751

#define OUTFILE "prime-spiral.xbm"

static char bits[DIM_X][DIM_Y];

int isprime(unsigned long long val);

int main(int argc, char **argv)
{
  unsigned long long ii;
  int xx, yy;
  FILE *fp;

  for(xx=0 ; xx<DIM_X ; xx++) { for(yy=0 ; yy<DIM_Y ; yy++) { bits[xx][yy] = 0x00; } }
  
  for(ii=0 ; ii<(DIM_X*DIM_Y) ; ii++)
  {
  }

  fp = fopen(OUTFILE, "w");
  fprintf(fp, "#define prime-spiral_width %d\n", DIM_X);
  fprintf(fp, "#define prime-spiral_height %d\n", DIM_Y);
  fprintf(fp, "static char prime-spiral_bits[] = {\n");
  ii = 0;
  for(yy=0 ; yy<DIM_Y ; yy++)
  {
    for(xx=0 ; xx<DIM_X ; xx++)
    {
      if(isprime(ii)) { bits[xx][yy] = 0xff; }
      printf("\r%3d,%3d: 0x%.2hhx, ", xx,yy, bits[xx][yy]); fflush(stdout);
      ii++;
    }
  }
  printf("\n");
  fprintf(fp, "};\n");
  return 0;
}

int isprime(unsigned long long val)
{
  unsigned long long ii;
  if(val == 1) { return 1; }
  if(val == 2) { return 1; }
  for(ii=2 ; ii<val ; ii++)
  {
    if(((val / ii) * ii) == val) { return 0; }
  }
  return 1;  
}
