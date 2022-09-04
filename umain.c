/****************************************************************
 * umain.c
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

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <math.h>
#include <string.h>

#include <stdlib.h>

#include "upro.h"

#define SCANINT(x,y) \
if (sscanf(x,"%d",y) != 1) \
{ fprintf(stderr,"Invalid number '%s' in argument %d\n",x,i);\
 print_hint(); exit(1); }

#define GETNUMBER(x) \
ppa++; \
if (*ppa == '\0') { pending_number = &(x); pp_flag = 1; } \
else { SCANINT(ppa,&(x)); }

#define GETNAME(x) \
ppa++; \
if (*ppa == '\0') { pending_name = &(x); pp_flag = 2; } \
else { x = ppa; }


/****************************************************************
 * print_usage
 ****************************************************************/

static void print_usage()
{
  fprintf(stdout,"UNFLICK version 1.1c by Klaus Ehrenfried (C) 1995,2002\n");
  fprintf(stdout,"Usage: unflick [options] InputFli OutputBase [Ext]\n");
}

/****************************************************************
 * print_hint
 ****************************************************************/

static void print_hint()
{
  fprintf(stderr,"Type 'unflick -h' for help\n");
}

/****************************************************************
 * print_help
 ****************************************************************/

static void print_help()
{
  fprintf(stdout,"Options:\n\
  -a          PPM-ascii output format (default is PPM-raw)\n\
  -m          Mapped FBM output format\n\
  -b<begin>   Begin output at given frame number\n\
  -n<max>     Output not more than given number of frames\n\
  -v          Verbose\n\
  -f<filter>  Postprocess output file with 'filter'\n");

  fprintf(stdout,"Function:\n\
  Extracts the images of <InputFli> and writes them in separated files;\n\
  creates <OutputBase>.001, <OutputBase>.002, .....\n\
  or <OutputBase>001.<Ext>, <OutputBase>002.<Ext>, .....\n");
}

/****************************************************************
 * main
 ****************************************************************/

int main (int argc, char *argv[])
{
  FILE *fopen(), *fpin;
  char *infile, *outbase, *outext, *filter;
  char *ppa, *ppb;
  char **pending_name;
  int *pending_number;
  int i, r;
  int verbose_flag;
  int begin_frame,max_frames;
  int pp_flag;
  int outtype;

  infile = NULL;
  outbase = NULL;
  outext = NULL;
  verbose_flag = 0;
  filter = NULL;
  begin_frame=1;
  max_frames=-1;
  outtype = PPM_RAW;

  /* scan arguments */

  pp_flag = 0;
  pending_number = NULL;
  pending_name = NULL;
  ppa = ppb = NULL;

  if (argc == 1)
    { print_usage(); exit(1); }

  for (i=1; i < argc; i++)
    {
      ppa=argv[i];
      if (pp_flag == 1)
        { SCANINT(ppa, pending_number); pp_flag = 0; }
      else if (pp_flag == 2)
        { *pending_name = ppa; pp_flag = 0; }
      else if (*ppa == '-')
	{
	  ppb = (ppa++);
	  switch (*ppa)
	    {
	    case 'b':   GETNUMBER(begin_frame); break;
	    case 'n':   GETNUMBER(max_frames); break;
	    case 'a':   outtype = PPM_ASCII; break;
	    case 'm':   outtype = FBM_MAPPED; break;
	    case 'f':   GETNAME(filter); break;
	    case 'v':   verbose_flag = 1; break;
	    case 'h':   print_usage(); print_help(); exit(1);
	    default:
	      fprintf(stderr,"Illegal option '%c' in argument %d\n",
		      *ppa,i);
	      print_hint();
	      exit(1);
	    }
	}
      else  if (infile == NULL)
	{
	  infile=argv[i];
	}
      else if (outbase == NULL)
	{
	  outbase=argv[i];
	}
      else if (outext == NULL)
	{
	  outext=argv[i];
	}
      else
	{
	  fprintf(stderr,"Too many parameters specified\n");
	  print_hint();
	  exit(1);
	}
    }

  if (pp_flag == 1)
    {
      fprintf(stderr,"Missing number behind option '%c'\n",*ppb);
      print_hint();
      exit(1);
    }

  if (outbase == NULL)
    {
      print_usage();
      exit(1);
    }

  /* fprintf(stderr,"Open Input File\n"); */
  if ((fpin = fopen(infile, "rb")) == NULL)
    {
      fprintf(stderr,"Error opening input file '%s'\n",infile);
      exit(1);
    }

  r = unfli(fpin,outbase,outext,outtype,
	    begin_frame,max_frames,verbose_flag,filter);

  if (r == 0)
    fprintf(stderr,"Stop\n");
  else if (r == 1)
    fprintf(stderr,"Ready\n");
  else if (r == -1)
    fprintf(stderr,"Read error\n");
  else if (r == -2)
    fprintf(stderr,"Error allocating memory\n");
  else
    fprintf(stderr,"Unknown error\n");

  fclose(fpin);

  return(0);
}
