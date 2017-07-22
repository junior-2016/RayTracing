#include"Mesh.h"
Mesh::Mesh() {}
Mesh::~Mesh()
{
	delete[] tex;
	delete[] vertUVNs;
}
Mesh::Mesh(Texture*_tex, VertexUVN*_vertUVNs) :
	tex(_tex), vertUVNs(_vertUVNs) {}
Texture* Mesh::getTexture()const
{
	return tex;
}
VertexUVN* Mesh::getVertUVNs()const
{
	return vertUVNs;
}