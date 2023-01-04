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


	return 0;
}
