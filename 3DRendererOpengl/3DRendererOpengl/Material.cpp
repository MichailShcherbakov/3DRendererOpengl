#include "StdAfx.h"
#include "Material.h"

Material::Material(const std::string& title, const Texture2D* texture) :
	m_title(title),
	m_specularExponent(0.0f),
	m_ambient(glm::vec3(1.0f)),
	m_diffuse(glm::vec3(1.0f)),
	m_specular(glm::vec3(1.0f)),
	m_dissolveExponent(1.0f),
	m_diffuseMap(texture)
{
}

std::string Material::GetTitle() const
{
	return m_title;
}

float Material::GetSpecularExponent() const
{
	return m_specularExponent;
}

glm::vec3 Material::GetAmbient() const
{
	return m_ambient;
}

glm::vec3 Material::GetDiffuse() const
{
	return m_diffuse;
}

glm::vec3 Material::GetSpecular() const
{
	return m_specular;
}

const Texture2D* Material::GetTexture() const
{
	return m_diffuseMap;
}

void Material::SetTitle(std::string& title)
{
	m_title = title;
}

void Material::SetSpecularExponent(float exponent)
{
	m_specularExponent = exponent;
}

void Material::SetAmbient(const glm::vec3& exponent)
{
	m_ambient = exponent;
}

void Material::SetDiffuse(const glm::vec3& exponent)
{
	m_diffuse = exponent;
}

void Material::SetSpecular(const glm::vec3& exponent)
{
	m_specular = exponent;
}

void Material::SetTexture(const Texture2D* texture)
{
	m_diffuseMap = texture;
}
