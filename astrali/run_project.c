#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <project_name>\n", argv[0]);
        return 1;
    }

    char *project_name = argv[1];
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "qemu-system-i386 -drive format=raw,file=%s/operating_system.img", project_name);
    system(cmd);

    printf("Running project %s with QEMU!\n", project_name);
    return 0;
}

