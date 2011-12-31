#include <aes/aes.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct Line {
	char *data;
	struct Line *next, *prev;
};

typedef struct Line Line ;

int height, dummy, linenum=0;
Line *last, *first;

void
draw(void)
{
	char *buf[1024];
	Line *nline;
	Line *pline;

	if(!fgets(buf, sizeof(buf), stdin))
		quit();

	nline = malloc(sizeof(Line)) ;
	nline->next = 0;
	nline->data = strdup(buf) ;
	nline->prev = last ;

	if(!first){
		first = nline ;
	}if(last){
		last->next = nline ;
	}
	last = nline ;

	++linenum;

	/* Cleaning exceed line when reached bottom. */
	if(height <= linenum){
		free(first->data);
		first = first->next ;

		free(first->prev);

		first->prev = 0 ;
	}

	pline = last ;
	
	aes_clear_entire_screen();
	aes_move_to(1, 1);
	while(pline){
		aes_printf("%s", pline->data);
		pline = pline->prev;
	}
}

void
quit()
{
	exit(0);
}

int
main(int argc, char *argv[])
{
	aes_term_size(&dummy, &height);
	first = 0 ;

	while(1){
		usleep(500*1000);
		draw();
	}

	return 0 ;
}
