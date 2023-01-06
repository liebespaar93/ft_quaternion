#include "ft_quaternion.h"

#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
	t_quaternion	q;
	t_angles 		angles;
	t_quaternion x;
	t_quaternion y;
	t_quaternion z;
	
	angles.x = 0.6;
	angles.y = 0.1;
	angles.z = 0.8;

	x = ft_quaternion_rotation_x(angles.x);
	y = ft_quaternion_rotation_y(angles.y);
	z = ft_quaternion_rotation_z(angles.z);

	q = ft_quaternion_multiply(x, y);
	q = ft_quaternion_multiply(q, z);


	printf("\n==== quaternion_axis ====\n");


	printf("quaternion :\t%f %f %f %f \n", q.x, q.y , q.z, q.w);

	
	t_angles a = ft_quaternion_axis_to_angles(q);

	printf("axis angles :\t%f %f %f %f \n", a.x, a.y, a.z, 2.0 * acos(q.w));


	t_angles b = ft_quaternion_euler_to_angles(q);

	printf("euler angles :\t%f %f %f \n", b.x, b.y, b.z);

	printf("\n==== euler ====\n");

	t_quaternion p;

	p = ft_quaternion_euler_from_angles(angles);

	printf("quaternion :\t%f %f %f %f\n", p.x, p.y , p.z, p.w);
	
	t_angles c = ft_quaternion_axis_to_angles(p);

	printf("axis angles :\t%f %f %f %f \n", c.x, c.y, c.z, 2.0 * acos(p.w));

	t_angles d = ft_quaternion_euler_to_angles(p);

	printf("euler angles :\t%f %f %f \n", d.x, d.y, d.z);


	printf("\n==== test ====\n");


	t_quaternion test;

	test = ft_quaternion_set(1,0,0,0);

	t_quaternion test_q;
	t_quaternion test_p;

	test_q = ft_quaternion_multiply(q, test);
	test_q = ft_quaternion_multiply(test_q, ft_quaternion_conjugate(q));

	test_p = ft_quaternion_multiply(p, test);
	test_p = ft_quaternion_multiply(test_p, ft_quaternion_conjugate(p));

	printf("test_q %f %f %f %f\n", test_q.x, test_q.y, test_q.z, test_q.w);
	printf("test_p %f %f %f %f\n", test_p.x, test_p.y, test_p.z, test_p.w);

	t_angles test_angle = ft_quaternion_euler_to_angles(test);
	t_angles test_q_angle = ft_quaternion_euler_to_angles(test_q);
	t_angles test_p_angle = ft_quaternion_euler_to_angles(test_p);

	printf("test euler angles :\t%f %f %f \n", test_angle.x / M_PI * 100, test_angle.y / M_PI * 100, test_angle.z / M_PI * 100);
	printf("test_q euler angles :\t%f %f %f \n", test_q_angle.x / M_PI * 100, test_q_angle.y / M_PI * 100, test_q_angle.z / M_PI * 100);
	printf("test_p euler angles :\t%f %f %f \n", test_p_angle.x / M_PI * 100, test_p_angle.y / M_PI * 100, test_p_angle.z / M_PI * 100);


	t_vec3 v_test;

	v_test = ft_vector_3(1,0,0);

	t_vec3 v_q = ft_quaternion_rotate_vec3(q,v_test);
	t_vec3 v_p = ft_quaternion_rotate_vec3(p,v_test);

	printf("v_q %f %f %f \n", v_q.x, v_q.y, v_q.z);
	printf("v_p %f %f %f \n", v_p.x, v_p.y, v_p.z);



	printf("\n==== origin ====\n");

	t_mtx4	m_x = ft_mtx4_rot_x(0.6);
	t_mtx4	m_y = ft_mtx4_rot_y(0.1);
	t_mtx4	m_z = ft_mtx4_rot_z(0.8);

	t_mtx4 m4_test;
	
	m4_test = ft_mtx4_identity();
	m4_test = ft_mtx4_mult_mtx4(m4_test, m_x);
	m4_test = ft_mtx4_mult_mtx4(m4_test, m_y);
	m4_test = ft_mtx4_mult_mtx4(m4_test, m_z);
	
	t_vec3 orgin_v3 = ft_mtx4_mult_vec3(m4_test, v_test);

	printf("orgin_v3 %f %f %f \n", orgin_v3.x, orgin_v3.y, orgin_v3.z);
	return 0;
}
