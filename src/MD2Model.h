#ifndef MD2_MODEL_H_INCLUDED
#define MD2_MODEL_H_INCLUDED
#include "Vec3f.h"
#include <Windows.h>
#include <gl\GL.h>
#include "Image.h"

struct MD2Vertex {
	Vec3f pos;
	Vec3f normal;
};

struct MD2Frame {
	char name[16];
	MD2Vertex* vertices;
};

struct MD2TexCoord {
	float texCoordX;
	float texCoordY;
};

struct MD2Triangle {
	int vertices[3];  //The indices of the vertices in this triangle
	int texCoords[3]; //The indices of the texture coordinates of the triangle
};

class MD2Model {
	private:
		MD2Frame* frames;
		int numFrames;
		MD2TexCoord* texCoords;
		MD2Triangle* triangles;
		int numTriangles;
		TImagePtr modelTextureImage;
		
		int startFrame; //The first frame of the current animation
		int endFrame;   //The last frame of the current animation
		
		/* The position in the current animation.  0 indicates the beginning of
		 * the animation, which is at the starting frame, and 1 indicates the
		 * end of the animation, which is right when the starting frame is
		 * reached again.  It always lies between 0 and 1.
		 */
		float time;
		
		MD2Model();
	public:
		~MD2Model();
		
		//Switches to the given animation
		void setAnimation(const char* name);
		//Advances the position in the current animation.  The entire animation
		//lasts one unit of time.
		void advance(float dt, float x, float z);
		//Draws the current state of the animated model.
		void draw();
		
		//Loads an MD2Model from the specified file.  Returns NULL if there was
		//an error loading it.
		static MD2Model* load(const char* filename);
};
#endif
