#ifndef _TEXTURE_2D_H_
#define _TEXTURE_2D_H_

#include <string>
#include "stb/stb_image.h"

class Texture2D
{
public:
	Texture2D();
	Texture2D(const std::string& path, bool mirrored = false);
	~Texture2D();

public:
	void Load(const std::string& path, bool mirrored = false);
	bool IsLoaded() const;
	bool IsLoaded();
	GLuint GetHandle() const;
	GLuint GetHandle();

private:
	GLuint m_handle;
	bool m_isLoaded = false;
};

#endif // _TEXTURE_2D_H_
