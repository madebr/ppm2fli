/************************************************************************
 * apro.h
 * 
 * Copyright (C) 1995-2002 Klaus Ehrenfried
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *************************************************************************/

#define UBYTE unsigned char
#define SHORT short
#define USHORT unsigned short
#define LONG long
#define ULONG unsigned long

#define FLI_MAX_X  1280
#define FLI_MAX_Y  1024
#define FLI_MAX_COLORS 256
#define FLI_MAX_FRAMES 4000
#define FLI_FILE_OLD_MAGIC 0xaf11	/* File header old Magic */
#define FLI_FILE_MAGIC 0xaf12		/* File header Magic */
#define FLI_FRAME_MAGIC 0xf1fa		/* Frame Magic */

#define FLI_FILE_HEADER_SIZE 128
#define FLI_FRAME_HEADER_SIZE 16

/* types of chunk in a fli_frame */
#define FLI_256_COLOR 4
#define FLI_DELTA 7
#define FLI_64_COLOR 11
#define FLI_LC	12
#define FLI_BLACK 13
#define FLI_BRUN 15
#define FLI_COPY 16

#define IOM_SBYTE  1
#define IOM_UBYTE  2
#define IOM_SWORD  3
#define IOM_UWORD  4
#define IOM_LONG  5

#define MAP_FIRST_FRAME 1
#define MAP_NEXT_FRAME 2
#define MAP_CLOSE_LOOP 3

#define MIN_NODE_LIMIT 16
#define MAX_NODE_LIMIT 2048
#define MAXDEPTH 7

/* structures */

typedef struct pixmap_struct
{
  int width;
  int height;
  int len;
  UBYTE *pixels;
} PMS;

typedef struct image_store_struct
{
  UBYTE *pixels;                 /* pixels of quantized image */
  LONG color[FLI_MAX_COLORS];    /* color map */
} ISS;

/* main or not */

#ifndef MAIN
#define EXT extern
#else
#define EXT
#endif

/* #define BORDER_COLOR 0xFF */

/* external variables */

EXT LONG mem_color[FLI_MAX_COLORS];
EXT int free_count[FLI_MAX_COLORS];
EXT UBYTE *pixel_chunk_buffer;
EXT UBYTE color_chunk_buffer[3 * FLI_MAX_COLORS + 10];
EXT int fli_width, fli_height, fli_size, fli_speed;
EXT int border_color, double_buffer;
EXT int Xorigin, Yorigin, Xorigin_flag, Yorigin_flag;
EXT int map_color_flag, use_next_flag, individual_flag;
EXT int wobbel_flag;
EXT FILE *input, *output;
EXT int old_format_flag;
EXT int node_limit, reduce_dynamics, color_depth;
EXT int verbose_flag,max_colors;
EXT int write_pal_flag;
EXT int filter_flag, test_magic_flag;
EXT char *filter_name, *tmp_file_name;

/* prototypes */

int exitialise(int);

void get_image(char *fname, UBYTE *data, LONG color[]);

int make_fli();

int fli_write_frame(ISS *diff, ISS *prev, ISS *curr);

void add_bytes(UBYTE record[], int *ipos, int value, int mode);

int make_color_chunk(ISS *diff, ISS *prev, ISS *curr);
int make_brun_chunk(UBYTE *image);
int make_delta_chunk(UBYTE *preprevious, UBYTE *previous, UBYTE *current);
int make_lc_chunk(UBYTE *preprevious, UBYTE *previous, UBYTE *current);

int get_next_line(FILE *input, char buff[], int len);

int clr_quantize(PMS *input, UBYTE *p_output, LONG color[]);
void prepare_quantize();
void scan_rgb_image(char *file_name);
void add_to_large_octree(PMS *image);
void clear_octree();
int output_palette();

int read_image(PMS *image, char *file_name);
int free_pms(PMS *image);
int check_exist(char *file_name);
int read_raw(FILE *fp, unsigned char *buffer, int len);

int get_fbm_data(PMS *image, FILE *fp);
int get_ppm_data(PMS *image, FILE *fp, int type);
/* -- FIN -- */
