#include "../include/matrix22.h" 
#include <stdio.h>

Matrix22 matrix22_create(float m00, float m01, float m10, float m11) {
	Matrix22 mat = {m00, m01, m10, m11};
	return mat;
}

Matrix22 matrix22_create_default(void) {
	Matrix22 mat = {1.0f, 0.0f, 0.0f, 1.0f};
	return mat;
}

Matrix22 matrix22_create_copy(const Matrix22* other) {
	Matrix22 mat = {other->m00, other->m01, other->m10, other->m11};
	return mat;
}

void matrix22_print(const Matrix22* mat) {
	if (!mat) return;
	printf("%f %f\n", mat->m00, mat->m01);
	printf("%f %f\n", mat->m10, mat->m11);
}

void matrix22_add(const Matrix22* left, const Matrix22* right, Matrix22* dest) {
	if (!left || !right || !dest) return;

	dest->m00 = left->m00 + right->m00;
	dest->m01 = left->m01 + right->m01;
	dest->m10 = left->m10 + right->m10;
	dest->m11 = left->m11 + right->m11;
}

void matrix22_sub(const Matrix22 *left, const Matrix22 *right, Matrix22 *dest) {
	if (!left || !right || !dest) return;

	dest->m00 = left->m00 - right->m00;
	dest->m01 = left->m01 - right->m01;
	dest->m10 = left->m10 - right->m10;
	dest->m11 = left->m11 - right->m11;
}

void matrix22_mul(const Matrix22 *left, const Matrix22 *right, Matrix22 *dest) {
	if (!left || !right || !dest) return;

	dest->m00 = left->m00 * right->m00 + left->m01 * right->m01;
	dest->m01 = left->m01 * right->m00 + left->m11 * right->m01;
	dest->m10 = left->m00 * right->m10 + left->m10 * right->m11;
	dest->m11 = left->m01 * right->m10 + left->m11 * right->m11;
}

void matrix22_trans(const Matrix22 *left, const Vector2 *right, Vector2 *dest) {
	if (!left || !right || !dest) return;
	
	float x = left->m00 * right->x + left->m01 * right->y;
	float y = left->m10 * right->x + left->m11 * right->y;

	dest->x = x;
	dest->y = y;
}

void matrix22_identity(Matrix22* mat) {
	if (!mat) return;

	mat->m00 = 1.0f; mat->m01 = 0.0f;
	mat->m10 = 0.0f; mat->m11 = 1.0f;
}

void matrix22_set_zero(Matrix22* mat) {
	if (!mat) return;

	mat->m00 = 0.0f; mat->m01 = 0.0f;
	mat->m10 = 0.0f; mat->m11 = 0.0f;
}

void matrix22_transpose(Matrix22* mat) {
	if (!mat) return;

	float temp = mat->m01;
	mat->m01 = mat->m10;
	mat->m10 = temp;
}

void matrix22_invert(Matrix22* mat) {
	if (!mat) return;

	float determinant = det(mat);

	if (determinant != 0) {
		float determinant_inv = 1/(float)determinant;
		float t00 = mat->m11 * determinant_inv;
		float t01 = -mat->m01 * determinant_inv;
		float t11 = mat->m00 * determinant_inv;
		float t10 = -mat->m10 * determinant_inv;

		mat->m00 = t00;
		mat->m01 = t01;
		mat->m10 = t10;
		mat->m11 = t11;
	}
}

void matrix22_negate(Matrix22* mat) {
	if (!mat) return;

	mat->m00 *= -1;
	mat->m01 *= -1;
	mat->m10 *= -1;
	mat->m11 *= -1;
}

float det(const Matrix22* mat) {
	return mat->m00 * mat->m11 - mat->m01 * mat->m10;
}
