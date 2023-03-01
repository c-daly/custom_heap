pm_heap: driver.c
		gcc -o pm_heap driver.c linkedlist/linkedlist.c heap/pm_heap.c -lpthread
debug:
		gcc -o pm_heap -g driver.c linkedlist/linkedlist.c heap/pm_heap.c -lpthread
	
clean: 
	rm -f pm_heap
