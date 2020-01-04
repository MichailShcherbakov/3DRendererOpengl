#ifndef _CUBE_TEXTURE_H_
#define _CUBE_TEXTURE_H_

#include <string>

class CubeTexture
{
public:
	CubeTexture();
	CubeTexture(const std::vector<std::string>& texturesPaths, bool mirrored = false);
	~CubeTexture();

public:
	void Load(const std::vector<std::string>& texturesPaths, bool mirrored = false);
	bool IsLoaded() const;
	bool IsLoaded();
	GLuint GetHandle() const;
	GLuint GetHandle();

private:
	GLuint m_handle;
	bool m_isLoaded = false;
};

#endif // _CUBE_TEXTURE_H_
