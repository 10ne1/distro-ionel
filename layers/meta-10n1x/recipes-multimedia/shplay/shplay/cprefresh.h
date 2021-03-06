/*
cprefresh.h                Copyright frankl 2013-2015

This file is part of frankl's stereo utilities.
See the file License.txt of the distribution and
http://www.gnu.org/licenses/gpl.txt for license details.

Here are some utility functions to clean or refresh RAM.
Optionally, they use assembler functions on ARM.
*/

inline void memcp_vfpX(void*, void*, int);
inline void memclean_vfpX(void*, int);

inline void refreshmem(char* ptr, int n)
{
  /* we make shure below that we can access ptr-off */
  int off;
  off = (unsigned int)ptr % 8;
  memcp_vfpX((void*)(ptr-off), (void*)(ptr-off), ((n+off)/8)*8);
}

inline void memclean(char* ptr, int n)
{
  int i, off, n0;
  off = (unsigned int)ptr % 8;
  if (off > 0) {
    off = 8-off;
    for (i=0; i < off; i++) ptr[i] = 0;
  }
  n0 = ((n-off)/8)*8;
  memclean_vfpX((void*)(ptr+off), n0);
  for (; n0+off < n; n0++) ptr[n0+off] = 0;
}
