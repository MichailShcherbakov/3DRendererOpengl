#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Texture2D.h"

#include <string>
#include "glm/glm.hpp"

class Material
{
public:
	std::string GetTitle() const;
	float GetSpecularExponent() const;
	glm::vec3 GetAmbient() const;
	glm::vec3 GetDiffuse() const;
	glm::vec3 GetSpecular() const;
	const Texture2D* GetTexture() const;

public:
	void SetTitle(std::string& title);
	void SetSpecularExponent(float exponent);
	void SetAmbient(glm::vec3& exponent);
	void SetDiffuse(glm::vec3& exponent);
	void SetSpecular(glm::vec3& exponent);
	void SetTexture(const Texture2D* texture);

private:
	std::string m_title;			// newmtl
	float m_specularExponent;		// Ns
	glm::vec3 m_ambient;			// Ka
	glm::vec3 m_diffuse;			// Kd
	glm::vec3 m_specular;			// Ks
	float m_dissolveExponent;		// d
	const Texture2D* m_diffuseMap;
};

#endif // _MATERIAL_H_

