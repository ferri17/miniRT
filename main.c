
#include <stdio.h>
#include <stdlib.h>

typedef struct Cubo
{
	int x;
} Cubo;

typedef struct Sphere
{
	int y;
} Sphere;

typedef union
{
	Cubo *cubo;
	Sphere *sphere;
} objectType;

typedef struct Obects
{
	objectType object;
	void (*hit)(objectType);
} Objects;

void hitCubo(objectType obj)
{
	Cubo cubo = *obj.cubo;
	printf("CUBO %i\n", cubo.x);
}

void hitSphere(objectType obj)
{
	Sphere sphere = *obj.sphere;
	printf("SPHERE %i\n", sphere.y);
}

int main()
{
	Sphere	sphere;
	Cubo	cubo;
	Objects	objects[2];

	sphere.y = 10;
	objects[0].object.sphere = &sphere;
	sphere.y = 124;
	objects[0].hit = hitSphere;

	cubo.x = 142;
	objects[1].object.cubo = &cubo;
	objects[1].hit = hitCubo;

	for (int i = 0; i < 2; i++)
		objects[i].hit(objects[i].object);

	
}