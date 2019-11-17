#include "Earth.h"

using namespace std;
using namespace glm;
using namespace basicgraphics;

Earth::Earth() {

    // Note: TEXTURE_PATH is set in config.h
    shared_ptr<Texture> tex = Texture::create2DTextureFromFile(TEXTURE_PATH);
    tex->setTexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex->setTexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    tex->setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    tex->setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    textures.push_back(tex);
    setupGeometry();
}

void Earth::setupGeometry() {
    // TODO: Write your own code here to tesselate and create texture coordinates for the Earth --> This code has been provided
    // and then save the data to a mesh (i.e. VBO). The tesselation
    // should be based on the STACKS and SLICES parameters.
    const int STACKS = 30; /// 30
    const int SLICES = 40; /// 40

    std::vector<Mesh::Vertex> verts;
    std::vector<int> indices;
    std::vector<std::shared_ptr<Texture>> textures;
    std::shared_ptr<Texture> tex = Texture::create2DTextureFromFile(TEXTURE_PATH);
    textures.push_back(tex);

    Mesh::Vertex vert;
    vec3 normal(0,0,1);
    vert.normal = normal;

    vert.position = vec3(0, 1, 0);
    vert.texCoord0 = vec2(0.5,0);
    vert.normal = vec3(0, 1, 0);
    verts.push_back(vert);

    for( int j = 0; j <= SLICES; j++){
      double theta = 2*M_PI / SLICES * j;
      for(int i = 1; i < STACKS; i++) {
        double phi = M_PI / STACKS * i;
        double y = cos(phi);
        double x = sin(phi) * cos(theta);
        double z = sin(phi) * sin(theta);
        cout << x << ", " << y << ", " << z << endl;
        vert.position = vec3(x, y, z);
        vert.texCoord0 = vec2(1 - theta/(M_PI*2), phi/(M_PI));
        vert.normal = vec3(x, y, z);
        verts.push_back(vert);
      }
    }

    vert.position = vec3(0, -1, 0);
    vert.texCoord0 = vec2(0.5,1);
    vert.normal = vec3(0, -1, 0);
    verts.push_back(vert);

    for(int j=0; j<SLICES; j++) { // j < SLICES
      // one triangle to the north pole!
      indices.push_back(0);
      indices.push_back(j*(STACKS-1) + STACKS);
      indices.push_back(j*(STACKS-1) + 1);

      for(int i=1; i<STACKS-1; i++) {
        indices.push_back(j*(STACKS-1) + i + STACKS - 1);
        indices.push_back(j*(STACKS-1) + i+1);
        indices.push_back(j*(STACKS-1) + i);

        indices.push_back(j*(STACKS-1) + i + STACKS - 1);
        indices.push_back(j*(STACKS-1) + i + STACKS);
        indices.push_back(j*(STACKS-1) + i+1);
      }

      // one triangle to the south pole!
      indices.push_back(j*(STACKS-1) + STACKS-1);
      indices.push_back(j*(STACKS-1) + STACKS - 1 + STACKS - 1);
      indices.push_back(verts.size() - 1);
    }

    const int numVertices = verts.size();
    const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
    const int cpuIndexByteSize = sizeof(int) * indices.size();
    _mesh.reset(new Mesh(textures, GL_TRIANGLES, GL_STATIC_DRAW, cpuVertexByteSize, cpuIndexByteSize, 0, verts, indices.size(), cpuIndexByteSize, &indices[0]));
}

glm::vec3 Earth::getPosition(double latitude, double longitude) {

    // TODO: Given a latitude and longitude as input, return the corresponding 3D x,y,z position
    // on your Earth geometry
    double radian_lat = (90 - latitude) * M_PI / 180;
    double radian_lng = longitude * M_PI / 180;
    double x = sin(radian_lat) * cos(radian_lng);
    double y = -1 * sin(radian_lat) * sin(radian_lng);
    double z = cos(radian_lat);

    return vec3(x, y ,z); // Dummy return so that it compiles. Replace me with the correct position.
}

void Earth::draw(GLSLProgram &shader) {
	// Former *TODO*: Draw your mesh --> provided
  _mesh->draw(shader);
}
