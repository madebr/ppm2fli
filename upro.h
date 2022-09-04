/****************************************************************
 * upro.h
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

#define FLI_MAXFRAMES (4000)	  /* Max number of frames... */

#define FLI_FILE_MAGIC 0xaf11	  /* File header Magic old FLI */
#define FLC_FILE_MAGIC 0xaf12	  /* File header Magic new FLC */

#define FLI_FRAME_MAGIC 0xf1fa		/* Frame Magic FLI/FLC */

#define FILE_HEAD_SIZE 128
#define FRAME_HEAD_SIZE 16
#define CHUNK_HEAD_SIZE 6

/* types of chunk in a fli_frame */

#define FLI_256_COLOR 4
#define FLI_DELTA 7
#define FLI_COLOR 11
#define FLI_LC	12
#define FLI_BLACK 13
#define FLI_BRUN 15
#define FLI_COPY 16

#define MAXCOLORS 256

#define PPM_RAW    6
#define PPM_ASCII  3
#define FBM_MAPPED 101

int unfli(FILE *input,char *out_name_base,char *out_name_ext,int outtype,\
	  int start_frame,int end_frame,int verbose, char *filter);

int buffer_brun_chunk(unsigned char *pcc, unsigned char *image_cbuff,\
		      int image_height, int image_width);
int buffer_delta_chunk(unsigned char *pcc, unsigned char *image_cbuff,\
		      int image_height, int image_width);
int buffer_lc_chunk(unsigned char *pcc, unsigned char *image_cbuff,\
		      int image_height, int image_width);

int out_image(unsigned char *image_buffer, unsigned char *color_table,\
	    int width, int height, int outtype, char *name_base,\
	    char *name_ext, int digits, int num, char *filter);
