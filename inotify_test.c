/* Based on the demo_inotify.c program by Michael Kerrisk  */
/* original: https://github.com/bradfa/tlpi-dist/blob/master/inotify/demo_inotify.c */

#include <sys/inotify.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int inotifyFd, wd, rv, j, i;
    char *p;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
	printf("usage: %s pathname...\n", argv[0]);
    }

     /* Create inotify instance */
    inotifyFd = inotify_init();
    if (inotifyFd == -1) {
	printf("failed: inotify_init\n");
	exit(1);
    }

    for (j = 1; j < argc; j++) {
	/* For each command-line argument, add a watch for all events */
	wd = inotify_add_watch(inotifyFd, argv[j], IN_ALL_EVENTS);
	if (wd == -1)
	    printf("failed: inotify_add_watch on %s\n", argv[j]);

	if (0)
		printf("Watching %s using wd %d\n", argv[j], wd);

	/* Remove each event */
	rv = inotify_rm_watch(inotifyFd, wd);
	if (rv == -1)
	    printf("failed: inotify_rm_watch on %s\n", argv[j]);

	if (0)
		printf("inotify_rm_watch returned %d\n", rv);
    }


    exit(0);
}
