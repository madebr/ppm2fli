/****************************************************************
 * uwchunks.c
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

#include <stdio.h>
#include <stdlib.h>

#include "upro.h"

/* ---------------------------------------------------------------- */

int buffer_brun_chunk
(
 unsigned char *pcc, 
 unsigned char *image_cbuff, 
 int image_height,
 int image_width
 )
{
  int packets, size_count;
  int i,j,n;
  unsigned char *pvs, bdata;
  unsigned char *pvsl;

  pvsl=image_cbuff;

  for (j=0; j < image_height; j++)
    {
      packets=(unsigned char) *(pcc++);
      /* printf("j: %d   packets: %d\n",j,packets); */

      pvs = pvsl;
      pvsl += image_width;

      for (i=0; i < packets; i++)
	{
	  size_count=(char) *(pcc++);

	  if (size_count == 0)
	    {
	      fprintf(stdout,"Error in brun chunk!\n");
	      exit(1);
	    }
	  else if (size_count > 0)
	    {
	      bdata=*(pcc++);
	      for (n=0; n < size_count; n++) *(pvs++)=bdata;
	    }
	  else
	    {
	      for (n=0; n < -size_count; n++)
		*(pvs++)=*(pcc++);
	    }
	}

    }

  return(1);
}

/* ---------------------------------------------------------------- */
int buffer_delta_chunk
(
 unsigned char *pcc, 
 unsigned char *image_cbuff,
 int image_height,
 int image_width
 )
{
  int i,j,n;
  unsigned char by0,by1;
  int jnext, skip, packets, lines, size, line_count;
  unsigned char *pvs;
  unsigned char *pvsl;

  by0=*(pcc++);
  by1=*(pcc++);
  lines=by0+ 256*by1;

  line_count=0;
  jnext=0;

  pvsl=image_cbuff;

  for (j=0; j < image_height; j++)
    {
      if (line_count >= lines) break;

      if (j < jnext)
	{
	  pvsl += image_width;
	  continue;
	}
	
      by0=*(pcc++);
      by1=*(pcc++);
      packets=by0+ 256*by1;

      if (packets > 32768)
	{
	  packets -= 65536;
	  jnext = j - packets;
	  pvsl += image_width;
	  continue;
	}

      line_count++;
      pvs = pvsl;

      for (i=0; i < packets; i++)
	{
	  skip=(unsigned char) *(pcc++);
	  pvs += skip;

	  size=(char) *(pcc++);
	  if (size >= 0)
	    {
	      for (n=0; n < size; n++)
		{
		  *(pvs++)=*(pcc++);
		  *(pvs++)=*(pcc++);
		}
	    }
	  else if (size < 0)
	    {
	      by0=*(pcc++);
	      by1=*(pcc++);
	      for (n=0; n < -size; n++)
		{
		  *(pvs++)=by0;
		  *(pvs++)=by1;
		}
	    }
	}
      pvsl += image_width;
    }
  return(1);
}

/* ---------------------------------------------------------------- */
int buffer_lc_chunk
(
 unsigned char *pcc, 
 unsigned char *image_cbuff,
 int image_height,
 int image_width
 )
{
  int i,j,n;
  unsigned char by0,by1;
  int jnext, skip, packets,lines;
  int size, line_count;
  unsigned char *pvs;
  unsigned char *pvsl;

  by0=*(pcc++);
  by1=*(pcc++);
  jnext=by0+ 256*by1;

  by0=*(pcc++);
  by1=*(pcc++);
  lines=by0+ 256*by1;

  line_count=0;

  pvsl=image_cbuff;

  for (j=0; j < image_height; j++)
    {
      if (line_count >= lines) break;

      if (j < jnext)
	{
	  pvsl += image_width;
	  continue;
	}

      by0=*(pcc++);
      packets=by0;

      line_count++;
      pvs = pvsl;

      for (i=0; i < packets; i++)
	{
	  skip=(unsigned char) *(pcc++);
	  pvs += skip;

	  size=(char) *(pcc++);
	  if (size >= 0)
	    {
	      for (n=0; n < size; n++)
		{
		  *(pvs++)=*(pcc++);
		}
	    }
	  else if (size < 0)
	    {
	      by0=*(pcc++);
	      for (n=0; n < -size; n++)
		{
		  *(pvs++)=by0;
		}
	    }
	}

      pvsl += image_width;
    }

  return(1);
}
