#include "./Foxes-C/foxes.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define USAGE "Usage: %s [OPTION...] [TAG]\n\nOptions:\n  -w <width>\t\tset the width of the image\n  -h <height>\t\tset the height of the image\n  -r <width:height>\tset the aspect ratio ex. \"1:2\"\n\nTAG:\n  fox\n  curious\n  happy\n  scarry\n  sleeping\n"

int main(int argc, char *argv[]) {
    int width = 0;
    int height = 0;
    char* aspectRatio = "";
    char* tag = "";

    int opt;
    extern char *optarg;
    extern int optind, optopt;

    while ((opt = getopt(argc, argv, "w:h:r:")) != -1) {
        switch (opt) {
        case 'w': width = atoi(optarg); break;
        case 'h': height = atoi(optarg); break;
        case 'r': aspectRatio = optarg; break;
        default:
            fprintf(stderr, USAGE, argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    for ( ; optind < argc; optind++) {
        if (access(argv[optind], R_OK)) {
            if (strcmp(tag, "") == 0 && (
                        strcmp(argv[optind], "fox") == 0 ||
                        strcmp(argv[optind], "curious") == 0 ||
                        strcmp(argv[optind], "happy") == 0 ||
                        strcmp(argv[optind], "scary") == 0 ||
                        strcmp(argv[optind], "sleeping") == 0)) {
                tag = argv[optind];
            }
            else {
                if (tag) {
                    fprintf(stderr, "%s: tag is already set, no need for %s\n", argv[0], argv[optind]);
                }
                else {
                    fprintf(stderr, "%s: invalid tag %s\n", argv[0], argv[optind]);
                }
                fprintf(stderr, USAGE, argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (strcmp(tag, "") == 0) {
        fprintf(stderr, "%s: no tag set\n", argv[0]);
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }

    foxes_options options = {};
    if (width) options.width = width;
    if (height) options.height = height;
    if (strcmp(aspectRatio, "") != 0) options.aspectRatio = aspectRatio;

    if (strcmp(tag, "fox") == 0) {
        printf("%s\n", foxes_fox(options));
    }
    else if (strcmp(tag, "curious") == 0) {
        printf("%s\n", foxes_curious(options));
    }
    else if (strcmp(tag, "happy") == 0) {
        printf("%s\n", foxes_happy(options));
    }
    else if (strcmp(tag, "scary") == 0) {
        printf("%s\n", foxes_scary(options));
    }
    else {
        printf("%s\n", foxes_sleeping(options));
    }

    return 0;
}
