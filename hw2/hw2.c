//#include "beavalloc.h"
//#include <assert.h>

#define MEM 1024
#define debug 1
#define debug1 1 
/*


#ifndef NUM_PTRS
# define NUM_PTRS 100
#endif // NUM_PTRS

#define OPTIONS "hvt:"

extern char end, etext, edata;
uint test_number = 0;

void run_tests(void);
*/

/* Parijat*/
struct node *cur = NULL;
struct node *start = NULL;
char *baseloc = NULL;
/*Parijat*/


void coalesce(void){




    struct node *temp = start;
}

void check_and_split(void ){


    printf(" Inside check_and_split\n");
    struct node *t = start;

    while(t!=NULL){
        int sizeofnode = sizeof((*t));
        printf("sizeofnode is %d\n",sizeofnode );
        printf("node starts at %p and data starts at %p, %d ,%d , %p,%p\n",t,t->mem_block,t->size_of_block,t->currently_in_use,t->next,t->prev);

        if((t->size_of_block - t->currently_in_use) > sizeofnode && t->currently_in_use>0){

            // split nodes;
            printf("going to split\n");
            char *ptr = (char *)t;
            int c=0;
            int offset=0;
            
            printf("node starts at %p and data starts at %p, %d ,%d , %p,%p\n",t,t->mem_block,t->size_of_block,t->currently_in_use,t->next,t->prev);
            // c = brk(t);
            printf("%p %p %p %p %p\n",t,&t->size_of_block,&t->mem_block,&t->prev,&t->currently_in_use,&t->blk_no,&t->next);
            if(debug1==1){
                //printf("splitting a node here, current location would be This node starts at %p\n ",sbrk(0));
                printf("node's header is %d\n",sizeofnode);
                printf("node starts at %p and data starts at %p\n",t,t->mem_block);
                printf("Node's total capacity %d and used size is %d\n",t->size_of_block,t->currently_in_use);
            }
            offset = sizeofnode + t->currently_in_use;

            printf("newnode needs to be started at offset %d from original node at %p\n",offset,t );
            
            
            
            printf("%p\n", ptr);

            //printf("%p %p\n",ptr+offset)
            ptr = (ptr + offset);

            printf("%p %p\n", ptr,ptr-offset);

            struct node *newnode = (struct node *)ptr;

            printf("%d %d %d %d\n",sizeof(t->currently_in_use),sizeof(t->prev),sizeof(t),sizeof((*t)) );
            printf("size of newnode %d\n",sizeof(newnode));

            assert(newnode>t);
            assert((void *)newnode > t->mem_block);
            assert(t->mem_block>t);
            //assert(newnode < &t->currently_in_use);
            printf("%p %p\n", newnode, &t->currently_in_use);
            assert(newnode>&t->currently_in_use);
            assert(newnode > &t->prev);
            assert(newnode > &t->next);

            assert(newnode > &t->size_of_block);
            assert(newnode > &t->blk_no);
            if(debug1==1){
                printf("moved break point to %p after creating a header at t + data and it's size is %d \n",newnode,sizeof(newnode));
                printf("node starts at %p and data starts at %p, %d ,%d , %p,%p\n",t,t->mem_block,t->size_of_block,t->currently_in_use,t->next,t->prev);
                printf("newnode node starts at %p and data starts at %p, %d ,%d , %p,%p\n",newnode,newnode->mem_block,newnode->size_of_block,newnode->currently_in_use,newnode->next,newnode->prev);

            }

            //printf("%p\n",newnode-t);

            newnode->next = t->next;

            printf("newnode->next %p\n",newnode->next);

            //assert(t->prev==NULL);
            //assert(t->next==NULL);
            //assert(newnode->next==NULL);
            if(t->next){
                printf("t is followed by a node\n");
                t->next->prev = newnode;

            }
            //assert(t->prev==NULL);
            newnode->prev = t;
            printf("newnode->prev %p\n",newnode->prev);
            //assert(t->prev==NULL);
            t->next = newnode;
            printf("t->next %p\n",t->next);
            //assert(t->prev==NULL);
            printf("t->currently_in_use  %d\n",t->currently_in_use);
            newnode->currently_in_use = 0;
            printf("newnode->currently_in_use %d\n",newnode->currently_in_use);
            
            printf("size of node is %d\n",sizeofnode);
            printf("Original node's total capacity %d and used size is %d\n",t->size_of_block,t->currently_in_use);

            int x = t->currently_in_use;
            //assert(t->prev==NULL);
            printf(" add of t->prev%p\n", &t->prev );
            newnode->size_of_block = (t->size_of_block - x) - sizeofnode;
            printf(" add of t->prev %p\n", &t->prev );
            //assert(t->prev==NULL);
            printf("%p %p %p\n",&newnode->size_of_block, &t->currently_in_use, &t->size_of_block );
            //assert(t->prev==NULL);

            printf("%zu\n", t->currently_in_use);

            //assert(t->prev==NULL);
            assert(t->next==newnode);
            assert(newnode->prev==t);
            //assert(t->currently_in_use!=0);
            printf("Original node's total capacity %d and used size is %d \n",t->size_of_block,t->currently_in_use);

            printf("newnode->size_of_block  %d\n",newnode->size_of_block);
            printf("t->currently_in_use  %d\n",t->currently_in_use);
            
            t->size_of_block = t->currently_in_use;
            printf("t->size_of_block  %d\n",t->size_of_block);

            printf("Original node's total capacity %d and used size is %d\n",t->size_of_block,t->currently_in_use);
            printf("%p %p \n",t->prev,t->next);
            offset = sizeofnode ;
            ptr = (char *)ptr;
            ptr = ptr + offset;
            printf("offset for data of newnode is  %d\n",offset);
            
            newnode->mem_block = (void *)ptr ;

            //assert(t->prev==NULL);
            //assert(newnode->next==NULL);
            assert(t->next == newnode);
            printf("original node starts at %p and data starts at %p, %p,%p,%d,%d\n",t,t->mem_block,t->next,t->prev,t->size_of_block,t->currently_in_use);
            printf("newnode node starts at %p and data starts at %p,%p,%p,%d,%d\n",newnode,newnode->mem_block,newnode->next,newnode->prev,newnode->size_of_block,newnode->currently_in_use);
            
            if(cur==t)
                cur = t->next;
            t = t->next;

        }

        t = t->next;


    }

    // while(start!=NULL){
    //     printf("%p %p %d %d\n",start,start->mem_block,start->currently_in_use,start->size_of_block );
    //     start = start->next;
    // }

    printf("Returning from check_and_split\n");

    return;

}

struct node *add(void *newmem,struct node * temp,size_t size){

    if(debug==0)
	   printf("add function called\n");

	if(start==NULL){

		start = temp;

		cur = start;

		cur->prev = NULL;
		cur->next = NULL;

		cur->mem_block = newmem;
		cur->size_of_block = max(MEM,size);
        //cur->currently_in_use = 0;
        cur->blk_no = 0;
        
	}else{
        if(debug==0)
            printf("start is not null, adding another node to list\n");
		//struct node *temp = (struct node *)sbrk(sizeof(struct node *));

		temp->next = NULL;

		temp->prev = cur;

		temp->size_of_block = max(MEM,size);

		temp->mem_block = newmem;
        //temp->currently_in_use = 1;

        cur->next = temp;
		cur = temp;
        cur->blk_no = cur->prev->blk_no + 1;
        if(debug==0)
            printf("Block numbers : start = %d, cur = %d\n",start->blk_no, cur->blk_no);
	}


	return cur;
}
void update_counter(struct node *head){


    if(head)
        head = head->next;
    while(head!=NULL){

        head->blk_no = head->prev->blk_no + 1;
    }

    return;

}
struct node *get_first_fit(struct node *start, size_t size){

	struct node *first_fit = NULL;
    struct node *t = start;
    if(debug==1)
        printf("Inside get_first_fit \n");
	while(t!=NULL){
        if(debug==1)
            printf("In while loop current node capacity is %d\n",t->size_of_block);
		if((t->size_of_block)>=size && t->currently_in_use==0){
			first_fit = t;
			break;
		}

		t = t->next;
	}

	
    if(debug==1){
        printf("value of start is %d\n",(start==NULL?-1:start->blk_no));
        printf("Inside get_first_fit %s\n",first_fit==NULL?"first_fit is null":"first_fit is not null");
    }
	return first_fit;

}
void *beavalloc(size_t size){

	if(size == 0)
		return (void *)NULL;

    if(baseloc==NULL){
        baseloc = sbrk(0);

        if(debug==1)
            printf("base initialized to %p \n",baseloc);

    }
    if(debug==1){
        printf("\n\n\n\n\n\n\nInside beavalloc\n");
        printf("\nvalue of start before get_fist_fit is %d\n",(start==NULL?-1:start->blk_no));
    }



	struct node *first_fit = get_first_fit(start,size);
    
    if(debug==1)
        printf("\nvalue of start after get_first_fit is %d\n",(start==NULL?-1:start->blk_no));

	if(first_fit == NULL){
        if(debug==1)
            printf("first_fit was NULL and current location of heap  is %p\n",sbrk(0));
		size_t to_get = MEM;

        struct node *temp = sbrk(sizeof(struct node *));
		void   *newmem = sbrk(max(MEM,size));

        //printf("current location of heap after creating node is %p\n",sbrk(0));
		first_fit = add(newmem,temp,size);
        if(debug==1)
            printf("current location of heap after adding memory and creating header is %p\n",sbrk(0));
		
	}

    first_fit->currently_in_use = size;
    
    if(debug==1)
        printf("value of start after memory allocation  is %d\n",start->blk_no);
    	printf("value of cur after memory allocation  is %d\n",cur->blk_no);
    assert(first_fit!=NULL);
    assert(first_fit->mem_block!=NULL);
    if(debug==1)
        printf("%p\n", first_fit->mem_block);

    check_and_split();
    update_counter();


	return first_fit->mem_block;
}
void print(struct node * start){

    struct node *temp = start;

    if(debug==1)
        printf("inside print here %p\n",temp);
	while(temp!=NULL){
        if(debug==1){
            printf("node is at %p and data is at %p \n",temp,temp->mem_block);
		  printf("cap of current block %d  and already used memory %d\n", temp->size_of_block,temp->currently_in_use);
        }
		temp = temp -> next;
	}
    if(debug==1)
	   printf("\n");
}

void beavalloc_reset(void){


    
   if(baseloc==NULL){
        baseloc = sbrk((char)0);
         if(debug==1)
            printf("base initialized to %p \n",baseloc);

    }
    int c = brk(baseloc);
    start = NULL;
    cur = NULL;
    if(debug==1)
        printf("base location aftre resetting is %p\n",baseloc);
	
	

	return;
} 

void beavalloc_set_verbose(u_int8_t flag){


}
void *beavcalloc(size_t nmemb, size_t size){

	if(nmemb==0 || size ==0){
		return (void *)NULL;
	}


}
void beavalloc_dump(uint leaks_only){



	return;
}

void *beavrealloc(void *ptr, size_t size){

    return;
}
void beavfree(void *ptr){

    
    if(debug==1){

        printf("Inside beavfree %p\n", ptr);
    }

    char *temp = (char *)ptr;
    printf("char temp %p\n", temp);
    temp = temp - 8;

    printf("head of this node is at %p\n", temp);

    struct node *t = (struct  node *)temp;


    printf("head of this node is at %p in typecasted form\n", t);

    t->currently_in_use = 0;

    coalesce();
    return;
}
/*
int main(void){

	printf("hello\n");

	void *p = beavalloc(11);

    printf("Succesfully completed first allocation %p\n",p);

    p = beavalloc(200);
    printf("Succesfully completed second allocation %p\n",p);

	print(start);



	//printf("%d\n",beavalloc(200));
	//print(start);

	//beavalloc(0);
	//print(start);


	//beavalloc((size_t)NULL);

	//print(start);

    beavalloc_reset();
	return 0;
}

*/

/*

int
main(int argc, char **argv)
{
    uint8_t isVerbose = FALSE;
    {
        int opt = -1;

        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
            switch (opt) {
            case 'h':
                fprintf(stderr, "%s %s\n", argv[0], OPTIONS);
                exit(0);
                break;
            case 'v':
                isVerbose = isVerbose;
                beavalloc_set_verbose(TRUE);
                fprintf(stderr, "Verbose enabled\n");
                break;
            case 't':
                test_number = atoi(optarg);
                break;
            default: // '?' 
                fprintf(stderr, "%s\n", argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }

    run_tests();

    return 0;
}




void
run_tests(void)
{
    char *base = NULL;

    fprintf(stderr, "beavalloc tests starting\n");
    if (test_number == 0) {
        fprintf(stderr, "  running all tests\n");
    }
    else {
        fprintf(stderr, "  running only test %d\n", test_number);
    }

    // Get the beginning address of the start of the stack.
    base = sbrk(0);
    fprintf(stderr, "base: %p\n", base);
    if (test_number == 0 || test_number == 1) {
        char *ptr1 = NULL;

        // Does the heap reset function worK?
        fprintf(stderr, "*** Begin %d\n", 1);
        fprintf(stderr, "      Basic reset\n");

        beavalloc_reset();
        ptr1 = sbrk(0);
        fprintf(stderr, "  ptr : %p\n", base);
        assert(ptr1 == base);

        beavalloc_reset();
        ptr1 = sbrk(0);
        fprintf(stderr, "  ptr : %p\n", base);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 1);
    }
    if (test_number == 0 || test_number == 2) {
        char *ptr1 = NULL;

        // Allocate zero bytes and see if that works.
        fprintf(stderr, "*** Begin %d\n", 2);
        fprintf(stderr, "      zero bytes\n");

        ptr1 = beavalloc(0);
        assert(ptr1 == NULL);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 2);
    }
    if (test_number == 0 || test_number == 3) {
        char *ptr1 = NULL;

        // Just allocate 10 bytes.
        fprintf(stderr, "*** Begin %d\n", 3);
        fprintf(stderr, "      10 bytes\n");

        ptr1 = beavalloc(10);
        assert(ptr1 != NULL);
        assert(base < ptr1);

        fprintf(stderr, "  ptr1 : %p\n"
                , ptr1);

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 3);
    }
    if (test_number == 0 || test_number == 4) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr, "*** Begin %d\n", 4);
        fprintf(stderr, "      5 allocs\n");

        ptr1 = beavalloc(500);
        ptr2 = beavalloc(530);
        ptr3 = beavalloc(550);
        ptr4 = beavalloc(570);
        ptr5 = beavalloc(590);

        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
                , ptr1, ptr2, ptr3, ptr4, ptr5);

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 4);
    }

    if (test_number == 0 || test_number == 5) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr, "*** Begin %d\n", 5);
        fprintf(stderr, "      5 allocs 3 frees\n");
        ptr1 = beavalloc(510);
        ptr2 = beavalloc(530);
        ptr3 = beavalloc(550);
        ptr4 = beavalloc(570);
        ptr5 = beavalloc(590);

        fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
                , ptr1, ptr2, ptr3, ptr4, ptr5);
        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        beavalloc_dump(FALSE);

        beavfree(ptr1);
        beavfree(ptr3);
        beavfree(ptr5);

        beavalloc_dump(FALSE);
        //beavalloc_dump(TRUE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 5);
    }
    if (test_number == 0 || test_number == 6) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr, "*** Begin %d\n", 6);
        fprintf(stderr, "      5 allocs 2 frees\n");

        ptr1 = beavalloc(510);
        ptr2 = beavalloc(530);
        ptr3 = beavalloc(550);
        ptr4 = beavalloc(570);
        ptr5 = beavalloc(590);

        fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
                , ptr1, ptr2, ptr3, ptr4, ptr5);
        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        beavalloc_dump(FALSE);

        beavfree(ptr2);
        beavfree(ptr4);

        beavalloc_dump(FALSE);
        //beavalloc_dump(TRUE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 6);
    }
    if (test_number == 0 || test_number == 7) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr,"*** Begin %d\n", 7);
        fprintf(stderr,"      begin coalesce\n");

        ptr1 = beavalloc(510);
        ptr2 = beavalloc(530);
        ptr3 = beavalloc(550);
        ptr4 = beavalloc(570);
        ptr5 = beavalloc(590);

        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        beavalloc_dump(FALSE);

        beavfree(ptr2);
        beavfree(ptr4);

        beavalloc_dump(FALSE);

        fprintf(stderr,"-- coalesce right\n");
        beavfree(ptr1);

        beavalloc_dump(FALSE);

        fprintf(stderr,"-- coalesce left\n");
        beavfree(ptr5);

        beavalloc_dump(FALSE);

        fprintf(stderr,"-- coalesce right and left\n");
        beavfree(ptr3);

        beavalloc_dump(FALSE);
        //beavalloc_dump(TRUE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr,"*** End %d\n", 7);
    }
    if (test_number == 0 || test_number == 8) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;
        char *ptr4 = NULL;
        char *ptr5 = NULL;

        fprintf(stderr, "*** Begin %d\n", 8);
        fprintf(stderr, "      memset\n");

        ptr1 = beavalloc(1000);
        ptr2 = beavalloc(3000);
        ptr3 = beavalloc(5000);
        ptr4 = beavalloc(7000);
        ptr5 = beavalloc(10000);

        assert(base < ptr1);
        assert(ptr1 < ptr2);
        assert(ptr2 < ptr3);
        assert(ptr3 < ptr4);
        assert(ptr4 < ptr5);

        //fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
        //       , ptr1, ptr2, ptr3, ptr4, ptr5);

        beavalloc_dump(FALSE);

        memset(ptr1, 0x1, 1000);
        memset(ptr2, 0x2, 3000);
        memset(ptr3, 0x3, 5000);
        memset(ptr4, 0x4, 7000);
        memset(ptr5, 0x5, 10000);

        beavalloc_dump(FALSE);

        {
            char ch[10000] = {0};

            memset(ch, 0x1, 1000);
            assert(memcmp(ptr1, ch, 1000) == 0);

            memset(ch, 0x2, 3000);
            assert(memcmp(ptr2, ch, 3000) == 0);

            memset(ch, 0x3, 5000);
            assert(memcmp(ptr3, ch, 5000) == 0);

            memset(ch, 0x4, 7000);
            assert(memcmp(ptr4, ch, 7000) == 0);

            memset(ch, 0x5, 10000);
            assert(memcmp(ptr5, ch, 10000) == 0);
        }

        beavfree(ptr1);
        beavfree(ptr2);
        beavfree(ptr3);
        beavfree(ptr4);
        beavfree(ptr5);

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 8);
    }
    if (test_number == 0 || test_number == 9) {
        char *ptr1 = NULL;
        char *ptr2 = NULL;

        fprintf(stderr, "*** Begin %d\n", 9);
        fprintf(stderr, "      split and coalesce\n");

        ptr1 = beavalloc(10000);
        beavalloc_dump(FALSE);
        beavfree(ptr1);
        beavalloc_dump(FALSE);

        ptr1 = beavalloc(100);
        // should force a split
        ptr2 = beavalloc(200);

        fprintf(stderr, "  ptr1 : %p\n  ptr2 : %p\n"
                , ptr1, ptr2);

        beavalloc_dump(FALSE);

        beavfree(ptr2);
        beavalloc_dump(FALSE);

        // coalesce right
        beavfree(ptr1);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 9);
    }
    if (test_number == 0 || test_number == 10) {
        const ushort num_ptrs = NUM_PTRS;
        void *ptrs[num_ptrs];
        int i = 0;
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 10);
        fprintf(stderr, "      stress 1\n");

        for (i = 0; i < num_ptrs; i++) {
            ptrs[i] = beavalloc(i + 100);
        }

        for (i = 2; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        for (i = 3; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        for (i = 1; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }
        for (i = 0; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 10);
    }
    if (test_number == 0 || test_number == 11) {
        const ushort num_ptrs = NUM_PTRS;
        void *ptrs[num_ptrs];
        int i = 0;
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 11);
        fprintf(stderr, "      stress 2\n");

        for (i = 0; i < num_ptrs; i++) {
            ptrs[i] = beavalloc(i + 1000);
        }

        for (i = 3; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        for (i = 2; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        for (i = 1; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }
        for (i = 0; i < num_ptrs; i += 4) {
            beavfree(ptrs[i]);
        }

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 11);
    }
    if (test_number == 0 || test_number == 12) {
        const ushort num_ptrs = NUM_PTRS;
        void *ptrs[num_ptrs];
        int i = 0;
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 12);
        fprintf(stderr, "      stress 3\n");

        for (i = 0; i < num_ptrs; i++) {
            ptrs[i] = beavalloc(i + 10);
        }
        for (i = 0; i < num_ptrs; i ++) {
            beavfree(ptrs[i]);
        }

        for (i = 0; i < num_ptrs; i ++) {
            ptrs[i] = beavalloc(i + 1000);
        }
        for (i = 0; i < num_ptrs; i ++) {
            beavfree(ptrs[i]);
        }

        for (i = 0; i < num_ptrs; i ++) {
            ptrs[i] = beavalloc(i + 107);
        }
        for (i = 0; i < num_ptrs; i ++) {
            beavfree(ptrs[i]);
        }

        for (i = 0; i < num_ptrs; i ++) {
            ptrs[i] = beavalloc(i + 97);
        }
        for (i = 0; i < num_ptrs; i ++) {
            beavfree(ptrs[i]);
        }

        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        fprintf(stderr, "*** End %d\n", 12);
    }
    if (test_number == 0 || test_number == 13) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 13);
        fprintf(stderr, "      Free the free\n");

        ptr1 = beavalloc(10);
        beavfree(ptr1);
        beavalloc_set_verbose(TRUE);
        beavfree(ptr1);
        beavalloc_set_verbose(FALSE);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 13);
    }
    if (test_number == 0 || test_number == 14) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 14);
        fprintf(stderr, "      beavcalloc 1\n");

        ptr1 = beavcalloc(1000, 17);
        assert(ptr1 != NULL);
        {
            char ch[1000 * 17] = {0};

            //memset(ch, 0x1, 1000);
            assert(memcmp(ptr1, ch, 2000) == 0);
        }
        beavalloc_dump(FALSE);

        beavfree(ptr1);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 14);
    }
    if (test_number == 0 || test_number == 15) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 15);
        fprintf(stderr, "      beavcalloc 2\n");

        ptr1 = beavcalloc(0, 17);
        assert(ptr1 == NULL);
        beavalloc_dump(FALSE);

        beavfree(ptr1);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 15);
    }
    if (test_number == 0 || test_number == 16) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 16);
        fprintf(stderr, "      beavcalloc 3\n");

        ptr1 = beavcalloc(1000, 0);
        assert(ptr1 == NULL);
        beavalloc_dump(FALSE);

        beavfree(ptr1);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 16);
    }
    if (test_number == 0 || test_number == 17) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 17);
        fprintf(stderr, "      beavrealloc 1\n");

        ptr1 = beavrealloc(ptr1, 100);
        assert(ptr1 != NULL);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 17);
    }
    if (test_number == 0 || test_number == 18) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 18);
        fprintf(stderr, "      beavrealloc 2\n");

        ptr1 = beavrealloc(ptr1, 1000);
        assert(ptr1 != NULL);
        memset(ptr1, 0x1, 1000);

        ptr1 = beavrealloc(ptr1, 5000);
        assert(ptr1 != NULL);
        memset(ptr1, 0x1, 5000);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 18);
    }
    if (test_number == 0 || test_number == 19) {
        char *ptr1 = NULL;

        fprintf(stderr, "*** Begin %d\n", 19);
        fprintf(stderr, "      beavrealloc 3\n");

        ptr1 = beavrealloc(ptr1, 5000);
        assert(ptr1 != NULL);

        ptr1 = beavrealloc(ptr1, 1000);
        assert(ptr1 != NULL);
        memset(ptr1, 0x1, 1000);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "*** End %d\n", 19);
    }
    if (test_number == 0 || test_number == 20) {
        char **ptr1 = NULL;
        char *ptrs[10] = {0};
        int i = 0;

        fprintf(stderr, "*** Begin %d\n", 20);
        fprintf(stderr, "      beavrealloc 4\n");

        for (i = 0; i < 10; i++) {
            ptrs[i] = beavalloc((i + 5) * 10);
        }

        ptr1 = beavrealloc(ptr1, 5 * (sizeof(char *)));
        assert(ptr1 != NULL);

        for (i = 0; i < 5; i++) {
            ptr1[i] = ptrs[i];
        }

        assert(memcmp(ptrs, ptr1, 5 * sizeof(char *)) == 0);
        beavalloc_dump(FALSE);

        ptr1 = beavrealloc(ptr1, 2000 * (sizeof(char *)));
        assert(memcmp(ptrs, ptr1, 5 * sizeof(char *)) == 0);

        for (i = 5; i < 10; i++) {
            ptr1[i] = ptrs[i];
        }
        assert(memcmp(ptrs, ptr1, 10 * sizeof(char *)) == 0);
        beavalloc_dump(FALSE);

        ptr1 = beavrealloc(ptr1, 2 * (sizeof(char *)));
        assert(memcmp(ptrs, ptr1, 2 * sizeof(char *)) == 0);

        beavalloc_dump(FALSE);

        for (i = 0; i < 10; i++) {
            beavfree(ptrs[i]);
        }
        beavfree(ptr1);
        beavalloc_dump(FALSE);


        beavalloc_reset();
        {
            char *ptr0 = sbrk(0);
            assert(ptr0 == base);
        }
        fprintf(stderr, "*** End %d\n", 20);
    }
    if (test_number == 0 || test_number == 21) {
        char **ptr1 = NULL;
        char *ptrs[10] = {0};
        int i = 0;

        fprintf(stderr, "*** Begin %d\n", 21);
        fprintf(stderr, "      beavrealloc 5\n");

        ptr1 = beavrealloc(ptr1, 5 * (sizeof(char *)));
        assert(ptr1 != NULL);

        for (i = 0; i < 10; i++) {
            ptrs[i] = beavalloc((i + 2) * 1000);
        }

        ptr1 = beavrealloc(ptr1, 5 * (sizeof(char *)));
        assert(ptr1 != NULL);

        for (i = 0; i < 5; i++) {
            ptr1[i] = ptrs[i];
        }

        assert(memcmp(ptrs, ptr1, 5 * sizeof(char *)) == 0);
        beavalloc_dump(FALSE);

        ptr1 = beavrealloc(ptr1, 2000 * (sizeof(char *)));
        assert(memcmp(ptrs, ptr1, 5 * sizeof(char *)) == 0);

        for (i = 5; i < 10; i++) {
            ptr1[i] = ptrs[i];
        }
        assert(memcmp(ptrs, ptr1, 10 * sizeof(char *)) == 0);
        beavalloc_dump(FALSE);

        ptr1 = beavrealloc(ptr1, 2 * (sizeof(char *)));
        assert(memcmp(ptrs, ptr1, 2 * sizeof(char *)) == 0);

        beavalloc_dump(FALSE);

        for (i = 0; i < 10; i++) {
            beavfree(ptrs[i]);
        }
        beavfree(ptr1);
        beavalloc_dump(FALSE);

        beavalloc_reset();
        {
            char *ptr0 = sbrk(0);
            assert(ptr0 == base);
        }
        fprintf(stderr, "*** End %d\n", 21);
    }

    if (test_number == 0) {
        fprintf(stderr, "\n\nWoooooooHooooooo!!! All tests done and you survived.\n\n\t %c[5m Make sure they are correct. %c[0m \n\n\n", 27, 27);
    }
    else {
        fprintf(stderr, "\n\nWoooooooHooooooo!!! You survived test %d.\n\n\t %c[5m Make sure it is correct. %c[0m \n\n\n", test_number, 27, 27);
    }
}

*/
