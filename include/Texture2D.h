#ifndef TEXTURE_H
#define TEXTURE_H

struct Texture2D
{
  unsigned int id;
  unsigned int width, height;
  unsigned int internal_format;
  unsigned int image_format;
  unsigned int wrap_s;
  unsigned int wrap_t;
  unsigned int filter_min;
  unsigned int filter_max;
};

void generate_Texture2D(Texture2D* texture, unsigned char* data);
Texture2D texture2D_load_from_file(const char *filename);
void bind_Texture2D(Texture2D* texture);

#endif
