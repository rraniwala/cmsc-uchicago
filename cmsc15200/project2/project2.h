#ifndef _PROJECT2_H_
#define _PROJECT2_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct rgb {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct image {
  uint32_t w;
  uint32_t h;
  struct rgb *pixels; // array of length w*h
};

// an image's pixels are stored in "row order",
// with the top row first from left to right,
// then the next row underneath, etc.

/* implement these two utilities in project1-utils.c */

// compare two rgb structs for logical equality
int rgb_eq(struct rgb c1, struct rgb c2);

// check if image is all gray pixels
int img_grayscale(struct image *img);

/* you may add more utilities if you like, but don't change these two */

//Skips the specified number of bytes in the specified file
void skip_bytes(int n, FILE *f);

//Converts the next number of specified bytes into an int (Max 4)
int bytes_to_int(int bytes, FILE *f);

//Converts the next number of specified bytes into an int and writes bytes
//to stdout
unsigned int bytes_to_int_putchar(int bytes);

//Prints int in JSON format
void formatted_int(char *str, int n);

//Prints str in JSON format
void formatted_str(char *str1, char *str2);

//Prints bool in JSON format
void formatted_bool(char *str, int n);

//Reads n bytes from stdin and writes them to stdout
void write_bytes(unsigned int n);

//Writes the date and time to the next 6 bytes
void write_time();

//Writes the string from stdin to stdout
void write_string();
#endif
