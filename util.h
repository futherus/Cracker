#ifndef UTIL_H
#define UTIL_H

// ----------------------------------------------------------------------
// copies file to new_file using 'cp' OS built-in
int copy_file(const char* filename, const char* new_filename);

// ----------------------------------------------------------------------
// changes permissions for file using 'chmod' OS built-in
int chmod(const char* filename, const char* mode);

#endif // UTIL_H
