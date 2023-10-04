#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h> // Include getopt.h for command-line option parsing
#include <elf.h>

void print_elf_header(const Elf64_Ehdr *header, int printAll);

int main(int argc, char *argv[]) {
    int printAll = 0; // Flag to print all fields by default

    // Parse command-line options
    int option;
    while ((option = getopt(argc, argv, "a")) != -1) {
        switch (option) {
            case 'a':
                printAll = 1; // Set flag to print all fields
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] elf_filename\n", argv[0]);
                return 98;
        }
    }

    // Ensure there is one remaining argument (the ELF filename)
    if (optind != argc - 1) {
        fprintf(stderr, "Usage: %s [-a] elf_filename\n", argv[0]);
        return 98;
    }

    // Open the ELF file
    int fd = open(argv[optind], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 98;
    }

    // Read the ELF header
    Elf64_Ehdr header;
    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
        perror("Error reading ELF header");
        close(fd);
        return 98;
    }

    // Check if it's a valid ELF file
    if (header.e_ident[EI_MAG0] != ELFMAG0 || header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 || header.e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "Error: Not an ELF file\n");
        close(fd);
        return 98;
    }

    // Print the ELF header information, specifying whether to print all fields
    print_elf_header(&header, printAll);

    close(fd);
    return 0;
}

void print_elf_header(const Elf64_Ehdr *header, int printAll) {
    printf("ELF Header:\n");
    printf("  Magic: ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");

    if (printAll) {
        printf("  Class:                              ");
        switch (header->e_ident[EI_CLASS]) {
            case ELFCLASS32:
                printf("ELF32\n");
                break;
            case ELFCLASS64:
                printf("ELF64\n");
                break;
            default:
                printf("<unknown>\n");
                break;
        }

        printf("  Data:                               ");
        switch (header->e_ident[EI_DATA]) {
            case ELFDATA2LSB:
                printf("2's complement, little endian\n");
                break;
            case ELFDATA2MSB:
                printf("2's complement, big endian\n");
                break;
            default:
                printf("<unknown>\n");
                break;
        }

        printf("  Version:                            %d (current)\n", header->e_ident[EI_VERSION]);

        printf("  OS/ABI:                             ");
        switch (header->e_ident[EI_OSABI]) {
            case ELFOSABI_NONE:
                printf("UNIX - System V\n");
                break;
            case ELFOSABI_LINUX:
                printf("UNIX - Linux\n");
                break;
            default:
                printf("<unknown>\n");
                break;
        }

        printf("  ABI Version:                        %d\n", header->e_ident[EI_ABIVERSION]);
    }

    printf("  Type:                               ");
    switch (header->e_type) {
        case ET_NONE:
            printf("NONE (None)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown>\n");
            break;
    }

    if (printAll) {
        printf("  Entry point address:                %#lx\n", (unsigned long)header->e_entry);
    }
}
