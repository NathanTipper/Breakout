#ifndef TEXTURE2D_H
#define TEXTURE2D_H

class Texture2D
{
public:
  Texture2D();
  void Generate(unsigned int width, unsigned int height, unsigned char* data);
  void Bind() const;

  unsigned int GetId() const { return m_id; }

  unsigned int GetWidth() const { return m_width; }
  void SetWidth(unsigned int newWidth) { m_width = newWidth; }

  unsigned int GetHeight() const { return m_height; }
  void SetHeight(unsigned int newHeight) { m_height = newHeight; }

  unsigned int GetInternalFormat() const { return m_internalFormat; }
  void SetInternalFormat(unsigned int newFormat) { m_internalFormat = newFormat; }

  unsigned int GetImageFormat() const { return m_imageFormat; }
  void SetImageFormat(unsigned int newFormat) { m_imageFormat = newFormat; }

  unsigned int GetWrapS() const { return m_wrapS; }
  void SetWrapS(unsigned int newWrapS) { m_wrapS = newWrapS; }

  unsigned int GetWrapT() const { return m_wrapT; }
  void SetWrapT(unsigned int newWrapT) { m_wrapT = newWrapT; }

  unsigned int GetFilterMin() const { return m_filterMin; }
  void SetFilterMin(unsigned int newFilterMin) { m_filterMin = newFilterMin; }

  unsigned int GetFilterMax() const { return m_filterMax; }
  void SetFilterMax(unsigned int newFilterMax) { m_filterMax = newFilterMax; }

private:
  unsigned int m_id;
  unsigned int m_width, m_height;
  unsigned int m_internalFormat;
  unsigned int m_imageFormat;
  unsigned int m_wrapS;
  unsigned int m_wrapT;
  unsigned int m_filterMin;
  unsigned int m_filterMax;
};

#endif
