#include "include/matrix44.h"
#include "include/vector2.h"
#include "include/rasterizer.h"
#include <math.h>
#include <ncurses.h>
#include <stdio.h>

#define PI 3.141592653f

int main() {
	initscr();
	noecho();
	raw();
	start_color();
	cbreak();

	int width = 1920, height = 1080;

	Rasterizer* rasterizer = rasterizer_create(width, height);
	if (!rasterizer) {
		fprintf(stderr, "Failed to create rasterizer\n");
		return 1;
	}
	Framebuffer* fb = rasterizer_get_framebuffer(rasterizer);
	if (!fb) {
		fprintf(stderr, "Failed to create framebuffer");
	}

	float angle = 0;

	while(true) {
		angle += .002f;
		Vector4 v1 = {0, 1, 0, 1};
		Vector4 v2 = {-1, -1, 0, 1};
		Vector4 v3 = {1, -1, 0, 1};
		Vector3 rv = {0, 0, 1};

		Matrix44 transformation = matrix44_create_default();
		rotate(&transformation, &rv, angle);
		v1 = matrix44_multiply_vector4(&transformation, &v1);
		v2 = matrix44_multiply_vector4(&transformation, &v2);
		v3 = matrix44_multiply_vector4(&transformation, &v3);

		Vector2 tv1 = vector2_create(v1.x, v1.y);
		Vector2 tv2 = vector2_create(v2.x, v2.y);
		Vector2 tv3 = vector2_create(v3.x, v3.y);

		clearFrame(fb);
		rasterizeTriangle(rasterizer, fb, &tv1, &tv2, &tv3);
		presentFrame(fb, 0, 0);
	
		refresh();
		erase();
	}

	/* float angle = 0;
	while (angle < 180) {
		Matrix44 transformation = matrix44_create_default(); 
		Vector3 v4 = {0, 0, 1};
		
		rotate(&transformation, &v4, (angle * M_PI / 180.0));

		Vector4 v1 = {-1, 1, 0, 1};
		Vector4 v2 = {1, 1, 0, 1};
		Vector4 v3 = {0, -1, 1, 1};

		v1 = matrix44_multiply_vector4(&transformation, &v1);
		v2 = matrix44_multiply_vector4(&transformation, &v2);
		v3 = matrix44_multiply_vector4(&transformation, &v3);
		
		Vector2 tv1 = vector2_create(v1.x, v1.y);
		Vector2 tv2 = vector2_create(v2.x, v2.y);
		Vector2 tv3 = vector2_create(v3.x, v3.y);

		clearFrame(fb);
		rasterizeTriangle(rasterizer, fb, &tv1, &tv2, &tv3);
		presentFrame(fb, 0, 0);
		getch();
		clear();
		angle += 20;
		
	} */

	refresh();

	getch();

	// rasterizer_destroy(rasterizer);
	endwin();

	return 0;
}
