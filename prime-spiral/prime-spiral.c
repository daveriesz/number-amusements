#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#define DIM 500

#define DIM_W DIM
#define DIM_H DIM

#define OUTFILE "prime-spiral.png"

//#define DO_AMUSING_GRADIENT

int isprime(unsigned long long val);
void write_pixel(png_bytep *row_pointers, unsigned long xx, unsigned long yy, unsigned char rr, unsigned char gg, unsigned char bb);

int main(int argc, char **argv)
{
  unsigned long long ii, prime_count;
  int xx, yy, incr, cnt, cur;
  const int midx=DIM_W/2, midy=DIM_H/2;
  FILE *fp;
  png_structp png;
  png_infop info;
  png_bytep *row_pointers = NULL;
  unsigned char val;
  
  // prep the PNG output file
  fp = fopen(OUTFILE, "wb");
  png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info = png_create_info_struct(png);
  png_init_io(png, fp);
  png_set_IHDR(png, info, DIM_W, DIM_H, 8,
    PNG_COLOR_TYPE_RGB,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);
  row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * DIM_H);

  // initialize the image data;
  for(yy=0 ; yy<DIM_H ; yy++)
  {
    row_pointers[yy] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }
  for(yy=0 ; yy<DIM_H ; yy++) { for(xx=0 ; xx<DIM_W ; xx++) { write_pixel(row_pointers, xx, yy, 0x88, 0xff, 0x88); } }

  // draw the spiral into the image
  prime_count = 0;
  for(ii=0, xx=midx, yy=midy, incr=1, cur=0, cnt=0 ; ii<DIM_H*DIM_W ; ii++)
  {
    printf("\r%7lld/%d x,y=%3d,%3d", ii, DIM_H*DIM_W, xx, yy);
#ifdef DO_AMUSING_GRADIENT
    val = (char)((double)(0xff)) * (((double)ii)/((double)(DIM_W*DIM_H)));
#else
    if(isprime(ii+1)) { val = 0x00; prime_count++; }
    else { val = 0xff; }
#endif
    write_pixel(row_pointers, xx, yy, val, val, val);

    if     (((incr%2) == 1) && (cnt == 0)) { yy--; }
    else if(((incr%2) == 1) && (cnt == 1)) { xx--; }
    else if(((incr%2) == 0) && (cnt == 0)) { yy++; }
    else if(((incr%2) == 0) && (cnt == 1)) { xx++; }
    cur++;
    if(cur == (incr)) { cur = 0 ; cnt++; }
    if(cnt == 2) { cnt = 0; incr++; }

    printf(" "); fflush(stdout);
  }
  printf("\n");
  printf("found %lld primes / %lld integers\n", prime_count, ii);

  // finalize the PNG
  png_write_image(png, row_pointers);
  png_write_end(png, NULL);  
  for(yy=0 ; yy<DIM_H ; yy++)
  {
    free(row_pointers[yy]);
  }
  free(row_pointers);
  fclose(fp);
  png_destroy_write_struct(&png, &info);
  return 0;
}

int isprime(unsigned long long val)
{
  unsigned long long ii;
  if(val == 0) { return 0; }
  if(val == 1) { return 1; }
  if(val == 2) { return 1; }
  for(ii=2 ; ii<val ; ii++)
  {
    if(((val / ii) * ii) == val) { return 0; }
  }
  return 1;  
}

void write_pixel(png_bytep *row_pointers, unsigned long xx, unsigned long yy, unsigned char rr, unsigned char gg, unsigned char bb)
{
  row_pointers[yy][(xx*3)+0] = rr;
  row_pointers[yy][(xx*3)+1] = gg;
  row_pointers[yy][(xx*3)+2] = bb;
}

