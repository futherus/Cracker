#include <stdio.h>
#include <stdlib.h>

#include "cracker.h"
#include "util.h"

int main(int argc, char** argv)
{
        char filename[FILENAME_MAX]     = "hackit";
        char new_filename[FILENAME_MAX] = "newhackit";

        int err = copy_file(filename, new_filename);
        if(err)
                return err;
        
        err = chmod(new_filename, "777");
        if(err)
                return err;

        err = crack(new_filename);
        if(err)
                return err;

        return 0;
}
