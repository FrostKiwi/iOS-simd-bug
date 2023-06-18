#include "stdio.h"

#define CGLM_OMIT_NS_FROM_STRUCT_API
#include "cglm/struct.h"

void print_mat4s(const mat4s matrix)
{
	for (int i = 0; i < 4; i++)
	{
		printf("%f %f %f %f\n",
			   matrix.raw[i][0], matrix.raw[i][1], matrix.raw[i][2], matrix.raw[i][3]);
	}
}

int main(int argc, char *argv[])
{
	/* Update Camera */
	mat4s basis;
	mat4s eulerangles;
	mat4s rotation_matrix;
	mat4s view_matrix;
	mat4s projection_matrix;
	float viewrays[20] = {
		-1.0, 1.0, 0.0, 0.0, 0.0,
		1.0, 1.0, 0.0, 0.0, 0.0,
		1.0, -1.0, 0.0, 0.0, 0.0,
		-1.0, -1.0, 0.0, 0.0, 0.0};

	basis = mat4_identity();
	rotation_matrix = glms_euler_zyx((vec3s){0.1, 2.249999, 0.0});
	eulerangles = glms_euler_zyx((vec3s){0.0, 0.0, 0.0});
	basis = mat4_mul(basis, eulerangles);
	basis = mat4_mul(basis, rotation_matrix);
	rotation_matrix = mat4_copy(basis);
	view_matrix = mat4_identity();
	view_matrix =
		glms_mul_rot(view_matrix, rotation_matrix);
	view_matrix = glms_inv_tr(view_matrix);
	projection_matrix =
		glms_perspective(1.745329, (float)800 / (float)600,
						 0.01f, 100.0);

	/* Update View-Rays */
	double distance = -0.5 / tan(1.745329 / 2.0);
	for (int i = 0; i < 4 * 5; i += 5)
	{
		viewrays[i + 4] = distance;
		viewrays[i + 2] =
			viewrays[i] * 0.5 * (float)800 / (float)600;
		viewrays[i + 3] = viewrays[i + 1] * 0.5;
		glm_vec3_rotate_m4(rotation_matrix.raw,
						   &viewrays[i + 2],
						   &viewrays[i + 2]);
	}

	puts("basis");
	print_mat4s(basis);
	puts("eulerangles");
	print_mat4s(eulerangles);
	puts("rotation_matrix");
	print_mat4s(rotation_matrix);
	puts("view_matrix");
	print_mat4s(view_matrix);
	puts("projection_matrix");
	print_mat4s(projection_matrix);
	puts("4 vec3s viewrays");
	for (int i = 0; i < 4 * 5; i += 5)
	{
		printf("%f, %f, %f\n",
			   viewrays[i + 2],
			   viewrays[i + 3],
			   viewrays[i + 4]);
	}
}
