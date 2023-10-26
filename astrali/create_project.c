#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOADER_TEMPLATE "template/loader.asm"
#define EXTENSION_TEMPLATE "template/extension.c"
#define ENTRY_TEMPLATE "template/extension_entry.asm"

void copy_file(const char *source, const char *destination)
{
    char ch;
    FILE *src, *dest;

    src = fopen(source, "r");
    if (src == NULL) {
        printf("Error opening source file: %s\n", source);
        exit(1);
    }

    dest = fopen(destination, "w");
    if (dest == NULL) {
        printf("Error opening destination file: %s\n", destination);
        fclose(src);
        exit(1);
    }

    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <project_name>\n", argv[0]);
        return 1;
    }

    char *project_name = argv[1];
    char dest_loader[256], dest_extension[256], dest_entry[256];

    char mkdir_cmd[256];
    snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir %s", project_name);
    system(mkdir_cmd);

    snprintf(dest_loader, sizeof(dest_loader), "%s/loader.asm", project_name);
    snprintf(dest_extension, sizeof(dest_extension), "%s/extension.c", project_name);
    snprintf(dest_entry, sizeof(dest_entry), "%s/extension_entry.asm", project_name);

    copy_file(LOADER_TEMPLATE, dest_loader);
    copy_file(EXTENSION_TEMPLATE, dest_extension);
    copy_file(ENTRY_TEMPLATE, dest_entry);

    printf("Project %s created successfully!\n", project_name);
    return 0;
}

