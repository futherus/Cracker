#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "util.h"

// ----------------------------------------------------------------------
int copy_file(const char* filename, const char* new_filename)
{
        assert(filename && new_filename);
        
        size_t len = strlen(filename) + strlen(new_filename);

        char* tmp_buf = (char*) calloc(len + sizeof("cp "), 1);
        if(!tmp_buf)
        {
                fprintf(stderr, "ERROR: bad allocation\n");
                return 1;
        }
        
        sprintf(tmp_buf, "cp %s %s", filename, new_filename);

        int err = system(tmp_buf);

        free(tmp_buf);

        return err;
}

// ----------------------------------------------------------------------
int chmod(const char* filename, const char* mode)
{
        assert(filename &&  mode);
        
        size_t len = strlen(filename);
        
        if(strlen(mode) != 3 || !isdigit(mode[0]) || !isdigit(mode[1]) || !isdigit(mode[2]))
        {
                fprintf(stderr, "ERROR: wrong chmod mode\n");
                return 1;
        }

        char* tmp_buf = (char*) calloc(len + sizeof("chmod ___ "), 1);
        if(!tmp_buf)
        {
                fprintf(stderr, "ERROR: bad allocation\n");
                return 1;
        }
        
        sprintf(tmp_buf, "chmod %s %s", mode, filename);

        int err = system(tmp_buf);

        free(tmp_buf);

        return err;
}
