#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cracker.h"

// ----------------------------------------------------------------------
enum cracker_err
{
        CRACKER_NOERR           = 0,
        CRACKER_ALREADY_PATCHED = 1,
        CRACKER_FILE_ERR        = 2,
        CRACKER_BAD_ALLOC       = 3,
};

static int    CRACKER_OFFSET = 0x10D2;
static int8_t CRACKER_BYTE   = 0xEB;

static cracker_err replace_byte(FILE* file, size_t offset, int8_t byte);
static cracker_err read_byte(int8_t* buffer, size_t offset, FILE* file);

// ----------------------------------------------------------------------
int crack(const char* filename)
{

        FILE* file = fopen(filename, "r+b");
        if(!file)
        {
                printf("Cannot open file\n");
                return CRACKER_FILE_ERR;
        }

        int8_t probe    = 0;
        cracker_err err = CRACKER_NOERR;
        err = read_byte(&probe, CRACKER_OFFSET, file);
        if(err)
            return err;

        if(probe == CRACKER_BYTE)
            return CRACKER_ALREADY_PATCHED;

        err = replace_byte(file, CRACKER_OFFSET, CRACKER_BYTE);
        if(err)
                return err;

        fclose(file);

        return CRACKER_NOERR;
}

// ----------------------------------------------------------------------
static cracker_err replace_byte(FILE* file, size_t offset, int8_t byte)
{
        assert(file);

        if(fseek(file, offset, SEEK_SET))
        {
                fprintf(stderr, "ERROR: cannot seek position in file\n");
                return CRACKER_FILE_ERR;
        }

        if(fwrite(&byte, sizeof(int8_t), 1, file) != 1)
        {
                fprintf(stderr, "ERROR: cannot write to file");
                return CRACKER_FILE_ERR;
        }

        return CRACKER_NOERR;
}

// ----------------------------------------------------------------------
static cracker_err read_byte(int8_t* buffer, size_t offset, FILE* file)
{
        assert(file);

        if(fseek(file, offset, SEEK_SET))
        {
                fprintf(stderr, "ERROR: cannot seek position in file\n");
                return CRACKER_FILE_ERR;
        }

        if(fread(buffer, sizeof(int8_t), 1, file) != 1)
        {
                fprintf(stderr, "ERROR: cannot read from file\n");
                return CRACKER_FILE_ERR;
        }

        return CRACKER_NOERR;
}
