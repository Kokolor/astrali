#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <project_name>\n", argv[0]);
        return 1;
    }

    char *project_name = argv[1];

    char cmd[512];

    snprintf(cmd, sizeof(cmd), "mkdir %s/bin", project_name);
    system(cmd);

    snprintf(cmd, sizeof(cmd), "nasm %s/loader.asm -f bin -o %s/bin/loader.bin", project_name, project_name);
    system(cmd);

    snprintf(cmd, sizeof(cmd), "nasm %s/extension_entry.asm -f elf32 -o %s/bin/extension_entry.o", project_name, project_name);
    system(cmd);

    snprintf(cmd, sizeof(cmd), "gcc -ffreestanding -m32 -g -c %s/extension.c -o %s/bin/extension.o -fno-stack-protector -fno-pic", project_name, project_name);
    system(cmd);

    // snprintf(cmd, sizeof(cmd), "ld -o %s/bin/full_kernel.bin -Ttext 0x1000 %s/bin/extension_entry.o %s/bin/extension.o" -m elf_i386 --oformat binary -shared -fno-stack-protector", project_name, project_name, project_name, project_name)
	    snprintf(cmd, sizeof(cmd), "ld -o %s/bin/full_kernel.bin -Ttext 0x1000 %s/bin/extension_entry.o %s/bin/extension.o -m elf_i386 --oformat binary -shared -fno-stack-protector", project_name, project_name, project_name);
    system(cmd);

    snprintf(cmd, sizeof(cmd), "cat %s/bin/loader.bin %s/bin/full_kernel.bin > %s/operating_system.img", project_name, project_name, project_name);
    system(cmd);

    snprintf(cmd, sizeof(cmd), "rm -rf %s/bin/", project_name);
    system(cmd);

    printf("Operating system image generated successfully: %s/operating_system.img\n", project_name);
    return 0;
}

