#include "stdio.h"

#define CGLM_OMIT_NS_FROM_STRUCT_API
#include "cglm/struct.h"

int main(int argc, char *argv[])
{
	/* Update Camera */
	mat4s basis;
	mat4s eulerangles;
	basis = mat4_identity();
	gctx.cam.cam_rotation_matrix = glms_euler_zyx((vec3s){0.100000, 2.249999, 0.000000});
	eulerangles = glms_euler_zyx(gctx.ch1.rotation);
	basis = mat4_mul(basis, eulerangles);
	basis = mat4_mul(basis, gctx.cam.cam_rotation_matrix);
	gctx.cam.cam_rotation_matrix = mat4_copy(basis);
	gctx.cam.view_matrix = mat4_identity();
	gctx.cam.view_matrix =
		glms_mul_rot(gctx.cam.view_matrix, gctx.cam.cam_rotation_matrix);
	gctx.cam.view_matrix = glms_inv_tr(gctx.cam.view_matrix);
	gctx.cam.projection_matrix =
		glms_perspective(gctx.cam.fov, (float)800 / (float)600,
						 0.01f, 100.0);

	/* Update View-Rays */
	double distance = -0.5 / tan(gctx.cam.fov / 2.0);
	for (int i = 0; i < 4 * 5; i += 5)
	{
		gctx.ch1.viewrays[i + 4] = distance;
		gctx.ch1.viewrays[i + 2] =
			gctx.ch1.viewrays[i] * 0.5 * (float)800 / (float)600;
		gctx.ch1.viewrays[i + 3] = gctx.ch1.viewrays[i + 1] * 0.5;
		glm_vec3_rotate_m4(gctx.cam.cam_rotation_matrix.raw,
						   &gctx.ch1.viewrays[i + 2],
						   &gctx.ch1.viewrays[i + 2]);
	}
}
