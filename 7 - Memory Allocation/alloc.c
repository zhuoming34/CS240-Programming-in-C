/*Zhuoming Huang	alloc.c		modified on 12/13/2019*/
/* Package for free storage allocation:
   void initalloc()    initialize package
   char *alloc(int n)  allocate n bytes, longword aligned
   freef(char *p)      free previously alloc'd bloc

   Patrick O'Neil with help from Betty O'Neil, edited 04/15/00
   This solution written by Bob Wilson 11/18/2004
   Updated by Ron Cheung on 5/13/2014 to correct blockr's size in alloc()*/

/* external spec's--just function prototypes for initalloc,
   alloc and freef--                                                      */
#include "alloc.h"
#include <stdio.h>

/* internal def's--hidden from user of package--                          */
#define ALLOCSIZE 1000          /* size of allocation array               */
/* tag+size--assumed identical in blockr and blockl-- */
#define TAGSIZE sizeof(struct blockr)
/* minimum free block size--a blockl, then a blockr--                      */
#define MINFREESIZE (sizeof(struct blockl)+sizeof(struct blockr))
#define FREETAG 0x55            /* 01010101 tag shows block free           */
#define USEDTAG 0xaa            /* 10101010 tag shows block used           */

static char allocbuf[ALLOCSIZE]; /* storage for allocation                 */

struct blockl {                 /* info on left edge of block              */
   unsigned int tag : 8;        /* left end tag: free or used              */
   unsigned int size : 24;      /* length of block in bytes                */
   struct blockl *nextp;        /* pointer to next free block              */
   struct blockl *prevp;        /* pointer to previous free block          */
   };
struct blockr {                 /* info on right edge of block             */
   unsigned int tag : 8;        /* right end tag: free or used             */
   unsigned int size : 24;      /* length of block in bytes                */
   };
static struct blockl *freep;    /* head of free chain pointer              */
static struct blockl *cursorp;  /* cursor position in free chain           */
static void enchain(struct blockl *p);
static void unchain(struct blockl *p);
static void coalesce(struct blockl *blockl1p, struct blockl *blockl2p); 
void dumpfree(void);

/* initalloc initializes all the structures for later alloc() calls        */
void initalloc()
{
  struct blockr * blockrp;      /* ptr to struct blockr at end of block    */

   cursorp = (freep = (struct blockl *) allocbuf);   /* set cursorp
      and freep to initial freeblock, which is whole buffer                */
   freep->tag = FREETAG;        /* tag it as free                          */
   freep->size = ALLOCSIZE;     /* initial size                            */
   freep->nextp = freep;        /* one block, points to self               */
   freep->prevp = freep;        /* ditto                                   */
    /* now point blockrp to last word of freeblock                         */
   blockrp = (struct blockr *)(allocbuf + ALLOCSIZE - TAGSIZE);
   blockrp->tag = FREETAG;      /* as above                                */
   blockrp->size = ALLOCSIZE;   /* as above                                */
}

static void enchain(struct blockl *p) /* place block on free chain         */
{
   struct blockl *holdp;        /* temporary holder                        */

   holdp = freep;               /* remember old block at head of chain     */
   freep = p;                   /* place new block on head of chain        */
    /* update structures to place new block into chain                     */
   if (holdp == NULL)  {        /* free chain had become empty             */
     freep->nextp = freep;      /* one block, points to self               */
     freep->prevp = freep;      /* ditto                                   */
     cursorp = freep;           /* and cursor pts to this blk              */
   }
   else  {                      /* old free chain non-empty                */
     /* insert on nextp list-- */
     freep->nextp = holdp;      /* new block points to old block           */
     holdp->prevp->nextp = freep;  /* end block points to new block        */
                                /* and insert on prevp list--              */
     freep->prevp = holdp->prevp;  /* new block points to end block        */
     holdp->prevp = freep;      /* old block points to new block           */
   }
}

static void unchain(struct blockl *p)
{
   if (p->prevp == p)           /* prevp points to self?                   */
      freep = (cursorp = NULL); /* empty list results                      */
   else  {                      /* chain around p->structl */
     (p->prevp)->nextp = p->nextp;
     (p->nextp)->prevp = p->prevp;
     if (p == cursorp)          /* cursorp was pting to this block?        */
       cursorp = p->nextp;      /* reset to next free block                */
     if (p == freep)            /* did we give away *freep ?               */
       freep = cursorp;         /* point freep to a free block             */
   }
}

/* alloc(): find a block of n bytes. Actually, find what might be somewhat 
   more, allocxize >= n bytes, guaranteed to be longword-aligned, that is,
   starting on an address which is a multiple of 4, and is at least enough
   to make up a MINFREESIZE block, long enough to enchain when free. Note
   that a starting address multiple of 2 would be workable for numeric data
   on many machines (68000/68020), but a starting address multiple of 4
   for 32-bit numeric data has faster access characteristics on the 68020  */

char *alloc(int n)              /* return ptr to block of n characters     */
{
   struct blockr * blockrp;     /* ptr to struct blockr at end of block    */
   struct blockl *startp = cursorp,     /* search start in free chain      */
                 *holdp;        /* another ptr for general use             */
   int allocsize = 4*((n-1)/4+1)+2*TAGSIZE; /* size of block mult of 4     */
     /* note - always a multiple of 4, overhead of 2 tag/size blocks       */
   int newfreesize;             /* may leave a smaller free block behind   */
   char *p;                     /* for counting off chars in allocbuf      */

   /* look for a first fit for needed allocsize in free chain              */

   if (cursorp == NULL)         /* empty free chain?                       */
      return NULL;              /* failure to allocate                     */

   /* first make sure allocsize is large enough to enchain when freed      */

   allocsize = (allocsize > MINFREESIZE)? allocsize: MINFREESIZE;
   /* search for first fit                                                 */

   while (cursorp->size < allocsize   /* not large enough                  */
     && (cursorp = cursorp->nextp) != startp)   /* more to check?          */
         ;                            /* try again                         */  
   if (cursorp->size < allocsize)     /* nothing large enough              
*/
      return(NULL);             /* failure to allocate                     */

   /* found block large enough; can we carve off what we need and
      leave a freeblock?                                                   */
   if (cursorp->size >= allocsize + MINFREESIZE)  {  /* yes                */
      newfreesize = cursorp->size - allocsize;  /* size we will leave      */
      cursorp->size = newfreesize;  /* correct length of free block        */

     /* we will carve off the area to return from right end of free
        block we're on, so correct chaining for free block we're leaving
        already exists -- now fix up new left and right end structures     */

      p = (char *) cursorp;     /* need char pointer to count off bytes   */
      holdp = (struct blockl *) (p+=newfreesize); /* block to return       */

      blockrp = (struct blockr *) (p-TAGSIZE);  /* right end of free block */
      blockrp->size = newfreesize;   /* set up righthand free blocksize    */
      blockrp->tag = FREETAG;   /* set up righthand free tag               */

      holdp->tag = USEDTAG;     /* set up lefthand used tag                */
      holdp->size = allocsize;  /* allocated block size                    */
      blockrp = (struct blockr *) (p+allocsize-TAGSIZE); /* pt to right end */
      blockrp->tag = USEDTAG;   /* set tag                                 */
      blockrp->size = allocsize; /* set allocated block size                */ 
      return (((char *) holdp) + TAGSIZE); /* return char ptr AFTER tag/size*/
   }
   else   {                     /* won't leave a free block behind         */
      p = (char *) (holdp = cursorp); /* char pointer to current block     */
      holdp->tag = USEDTAG;     /* setr lefthand tag is used               */
      unchain(holdp);           /* take it out of the free chain           */
      blockrp = (struct blockr *) (p+(holdp->size)-TAGSIZE); /* right end  */
      blockrp->tag = USEDTAG;   /* set tag only for used block             */
      return(p+TAGSIZE);        /* char ptr AFTER tag/size                 */
   }
}

/* free block with user-pointer p (block actually starts at p - TAGSIZE)   */
void freef(char *p)
{
    printf("freef called with p=%p\n", (void *) p);

   /* you write the  code for the freef function here */
	if((p<allocbuf)||(p>allocbuf+ALLOCSIZE)){
		printf("freef: bad pointer to block to be freed, %p\n",(void *)p);
		return;
	}
	struct blockl *l = (struct blockl *)(p - TAGSIZE);//beginnig of current block
	struct blockr *r = (struct blockr *)(p + l->size - 2*TAGSIZE);//blockr of current block
	if(l->tag == FREETAG && r->tag == FREETAG){
		printf("freef: block being freed is not in use, %p\n",(void *)p-sizeof(p));
		return;
	}
	struct blockl *s, *o;
	struct blockr *q;
	//beginning of left block right tag
	q = (struct blockr *)(p - 2*TAGSIZE);
	//beginning of left block
	s = (struct blockl *)((char*)l - q->size);
	//beginning of right block
	o = (struct blockl *)((char*)r + TAGSIZE);
	
	r->tag = (l->tag = FREETAG);//mark current block free

	if(q->tag == FREETAG){
		coalesce(s,l);
		l = s;	
	}else{
		enchain(l);
	}
	if(o->tag == FREETAG){
		unchain(o);
		coalesce(l,o);
	}

 }

 /* coalesce two free blocks, left on free list at call, right one not     */
static void coalesce(struct blockl *blockl1p, struct blockl *blockl2p)
{
   struct blockr * blockrp;     /* ptr to struct blockr at end of block    */

   blockl1p->size += blockl2p->size;  /* new size is sum of old two        */
    /* now point to right end of enlarged new block                        */
   blockrp = (struct blockr *) (((char *) blockl1p)+blockl1p->size-TAGSIZE);
   blockrp->size = blockl1p->size;    /* set right end size                */
}

void dumpfree(void)
{
   struct blockl *p = freep;

   if (freep==NULL) printf("empty\n");
   else
     do
       {
         if (p==cursorp)
           printf("cursor-> ");
         else
           printf("         ");
         printf("freeblk of size %d at %p (%d from start)\n",p->size, p, (int) ((char *)p - allocbuf));
       } while ((p=p->nextp)!=freep);
 } 
