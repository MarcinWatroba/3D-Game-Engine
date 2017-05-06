#include <Engine/Component/BoxCollider_3D.h>

BoxCollider_3D::BoxCollider_3D()
{

}
BoxCollider_3D::BoxCollider_3D(const BoxCollider_3D &obj)
{

}
BoxCollider_3D::~BoxCollider_3D()
{

}
std::string BoxCollider_3D::get_Type()
{
	return "BoxCollider_3D";
}

void BoxCollider_3D::setUpBox(glm::vec3* minValues, glm::vec3* maxValues)
{
	centre = glm::vec3(((minValues->x + maxValues->x) / 2), ((minValues->y + maxValues->y) / 2), ((minValues->z + maxValues->z) / 2));
	heightExtent = maxValues->y;
	widthExtent = maxValues->x;
	depthExtent = maxValues->z;
	newMaxExtents = glm::vec3(widthExtent, heightExtent, depthExtent);
	newMinExtents = glm::vec3(-widthExtent, -heightExtent, -depthExtent);
	oldPos = glm::vec3(0, 0, 0);
	oldRot = glm::quat(0, 0, 0, 0);
	oldScale = glm::vec3(0, 0, 0);

	oneTime = true;

	float v[24 * 3] = {
		// Front
		minValues->x, minValues->y, maxValues->z,
		maxValues->x, minValues->y, maxValues->z,
		maxValues->x, maxValues->y, maxValues->z,
		minValues->x, maxValues->y, maxValues->z,
		// Right 			   			 
		maxValues->x, minValues->y, minValues->z,
		maxValues->x, maxValues->y, minValues->z,
		maxValues->x, maxValues->y, maxValues->z,
		maxValues->x, minValues->y, maxValues->z,
		// Back	 			   			 
		maxValues->x, minValues->y, minValues->z,
		maxValues->x, maxValues->y, minValues->z,
		minValues->x, maxValues->y, minValues->z,
		minValues->x, minValues->y, minValues->z,
		// Left	 		   		
		minValues->x, minValues->y, maxValues->z,
		minValues->x, maxValues->y, maxValues->z,
		minValues->x, maxValues->y, minValues->z,
		minValues->x, minValues->y, minValues->z,
		// Bottom	   		 
		minValues->x, minValues->y, maxValues->z,
		maxValues->x, minValues->y, maxValues->z,
		maxValues->x, minValues->y, minValues->z,
		minValues->x, minValues->y, minValues->z,
		// Top	 		   		 
		minValues->x, maxValues->y, maxValues->z,
		maxValues->x, maxValues->y, maxValues->z,
		maxValues->x, maxValues->y, minValues->z,
		minValues->x, maxValues->y, minValues->z,
	};

	for (int i = 0; i < 72; i++)
	{
		V[i] = v[i];
	}

	float n[24 * 3] = {
		// Front
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		// Right
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		// Back
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		// Left
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		// Bottom
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		// Top
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	for (int i = 0; i < 72; i++)
	{
		N[i] = n[i];
	}

	GLuint el[] = {
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23
	};

	for (int i = 0; i < 36; i++)
	{
		EL[i] = el[i];
	}
}

void BoxCollider_3D::renderBox()
{
	//glGenVertexArrays(1, &vaoHandle);
	//glBindVertexArray(vaoHandle);
	//
	//unsigned int handle[3];
	//glGenBuffers(3, handle);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	//glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), V, GL_STATIC_DRAW);
	//glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, false, 0, ((GLubyte *)NULL + (0)));
	//glEnableVertexAttribArray(0);  // Vertex position
	//
	//glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	//glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), N, GL_STATIC_DRAW);
	//glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, false, 0, ((GLubyte *)NULL + (0)));
	//glEnableVertexAttribArray(1);  // Vertex normal
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[2]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), EL, GL_STATIC_DRAW);
	//
	//glBindVertexArray(0);
}

bool BoxCollider_3D::intersects(BoxCollider_3D &other)
{
	//if (newMaxExtents.x < other.newMinExtents.x || newMinExtents.x > other.newMaxExtents.x)
	//{
	//	return false;
	//}
	//if (newMaxExtents.y < other.newMinExtents.y || newMinExtents.y > other.newMaxExtents.y)
	//{
	//	return false;
	//}
	//if (newMaxExtents.z < other.newMinExtents.z || newMinExtents.z > other.newMaxExtents.z)
	//{
	//	return false;
	//}
	//return true;

	if ((newMaxExtents.x < other.newMaxExtents.x && other.newMinExtents.x < newMaxExtents.x) || (newMaxExtents.x < other.newMinExtents.x && other.newMaxExtents.x < newMaxExtents.x)) // MaxX is between things
	{
		isCollidingX = true;
	}
	else if ((newMinExtents.x < other.newMaxExtents.x && other.newMinExtents.x < newMinExtents.x) || (newMinExtents.x < other.newMinExtents.x && other.newMaxExtents.x < newMinExtents.x)) // MinX is between things
	{
		isCollidingX = true;
	}
	else
	{
		isCollidingX = false;
	}

	if ((newMaxExtents.y < other.newMaxExtents.y && other.newMinExtents.y < newMaxExtents.y) || (newMaxExtents.y < other.newMinExtents.y && other.newMaxExtents.y < newMaxExtents.y)) // MaxY is between things
	{
		isCollidingY = true;
	}
	else if ((newMinExtents.y < other.newMaxExtents.y && other.newMinExtents.y < newMinExtents.y) || (newMinExtents.y < other.newMinExtents.y && other.newMaxExtents.y < newMinExtents.y)) // MinY is between things
	{
		isCollidingY = true;
	}
	else
	{
		isCollidingY = false;
	}

	if ((newMaxExtents.z < other.newMaxExtents.z && other.newMinExtents.z < newMaxExtents.z) || (newMaxExtents.z < other.newMinExtents.z && other.newMaxExtents.z < newMaxExtents.z)) // MaxZ is between things
	{
		isCollidingZ = true;
	}
	else if ((newMinExtents.z < other.newMaxExtents.z && other.newMinExtents.z < newMinExtents.z) || (newMinExtents.z < other.newMinExtents.z && other.newMaxExtents.z < newMinExtents.z)) // MinZ is between things
	{
		isCollidingZ = true;
	}
	else
	{
		isCollidingZ = false;
	}

	if (isCollidingX && isCollidingY && isCollidingZ)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BoxCollider_3D::setCollisionCheck(bool isColliding)
{
	collidingWithImmovable = isColliding;
}

void BoxCollider_3D::updatePos(glm::mat4 parentMatrix)
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::vec3 newRot;
	glm::decompose(parentMatrix, scale, rotation, translation, skew, perspective);
	rotation = glm::conjugate(rotation);

	if (oneTime)
	{
		oldScale = scale;
		//centre = centre * rotation;
		newMaxExtents = centre + glm::vec3(widthExtent, heightExtent, depthExtent);
		newMinExtents = centre - glm::vec3(widthExtent, heightExtent, depthExtent);
		newMaxExtents = newMaxExtents * scale;
		newMinExtents = newMinExtents * scale;
		newMaxExtents = newMaxExtents * rotation;
		newMinExtents = newMinExtents * rotation;
	}

	//if (oldRot != rotation)
	//{
	//	if (oldRot != glm::quat(0, 0, 0, 0))
	//	{
	//		tempQuat = rotation * glm::inverse(oldRot);
	//	}
	//
	//	newMaxExtents = newMaxExtents * tempQuat;
	//	newMinExtents = newMinExtents * tempQuat;
	//	////Create a rotation point
	//	
	//
	//}

	if (oldPos != translation)
	{
		centre += (translation - oldPos);
		newMaxExtents += translation - oldPos;
		newMinExtents += translation - oldPos;
	}



	oneTime = false;
	std::cout << "Plant Pot collider extents:" << std::endl;
	std::cout << "Min (" << newMinExtents.x << ", " << newMinExtents.y << ", " << newMinExtents.z << ")" << std::endl;
	std::cout << "Max (" << newMaxExtents.x << ", " << newMaxExtents.y << ", " << newMaxExtents.z << ")" << std::endl << std::endl;
	oldPos = translation;
	oldRot = rotation;

	renderBox();
}