/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quaternion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:37:16 by kyoulee           #+#    #+#             */
/*   Updated: 2023/01/07 01:17:04 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ft_quaternion.h"

// https://cs.stanford.edu/~acoates/

t_quaternion	ft_quaternion_set(double x, double y, double z, double w)
{
	t_quaternion	q;

	q.x = x;
	q.y = y;
	q.z = z;
	q.w = w;
	return (q);
}

t_quaternion	ft_quaternion_identity()
{
    return (ft_quaternion_set(0, 0, 0, 1));
}

t_quaternion	ft_quaternion_conjugate(t_quaternion q)
{
	q.x = -q.x;
	q.y = -q.y;
	q.z = -q.z;
	q.w = q.w;
	return (q);
}

double	ft_quaternion_norm(t_quaternion q)
{
	return (sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
}

t_quaternion	ft_quaternion_normalize(t_quaternion q)
{
	double	len;

	len = ft_quaternion_norm(q);

	q.x = q.x / len;
	q.y = q.y / len;
	q.z = q.z / len;
	q.w = q.w / len;
	return (q);
}


/**
 * @brief 
 * 
 * @param v3
 * @ref https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 * @return t_quaternion
 */
t_quaternion	ft_quaternion_euler_from_angles(t_angles angles)
{
	t_quaternion	q;
	t_angles		c;
	t_angles		s;
	
	c.x = cos(angles.x * 0.5);
	s.x = sin(angles.x * 0.5);
	c.y = cos(angles.y * 0.5);
	s.y = sin(angles.y * 0.5);
	c.z = cos(angles.z * 0.5);
	s.z = sin(angles.z * 0.5);

	q.x = s.x * c.y * c.z - c.x * s.y * s.z;
    q.y = c.x * s.y * c.z + s.x * c.y * s.z;
	q.z = c.x * c.y * s.z - s.x * s.y * c.z;
	q.w = c.x * c.y * c.z + s.x * s.y * s.z;

	return (q);
}

/**
 * @brief 
 * 
 * @param q 
 * @ref https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
 * @return t_angles 
 */
t_angles	ft_quaternion_euler_to_angles(t_quaternion q)
{
	t_angles	axis;
	t_angles	c;
	t_angles	s;

	s.x = 2.0 * (q.w * q.x + q.y * q.z);
	c.x = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
	axis.x = atan2(s.x, c.x);
	
	s.y = 2.0 * (q.w * q.y - q.z * q.x);
	if (fabs(s.y) >= 1)
		axis.y = copysign(M_PI / 2, s.y);
	else
		axis.y = asin(s.y);
	
	s.z = 2 * (q.w * q.z + q.x * q.y);
	c.z = 1 - 2 * (q.y * q.y + q.z * q.z);
	axis.z = atan2(s.z, c.z);
	
	return (axis);
}

/**
 * @brief 
 * 
 * @param t_angles 
 * @param angle 
 * @ref http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/
 * @return t_quaternion 
 */
t_quaternion	ft_quaternion_axis_from_angle(t_angles axis, double angle)
{
	t_quaternion	q;
	double			s;

	s = sin(angle * 0.5);
	q.x = axis.x * s;
	q.y = axis.y * s;
	q.z = axis.z * s;
	q.w = cos(angle * 0.5);
	return (q);
}

/**
 * @brief 
 * 
 * @param q 
 * @ref http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/
 * @return t_angles 
 */
t_angles	ft_quaternion_axis_to_angles(t_quaternion q)
{
	t_angles	axis;
	double		angle;
	double		divider;

	if (q.w > 1.0)
		q = ft_quaternion_normalize(q);
	angle = 2.0 * acos(q.w);
	divider = sqrt(1.0 - q.w * q.w);
	if (divider < 0.001)
	{
		axis.x = q.x;
		axis.y = q.y;
		axis.z = q.z;
	}
	else
	{
		axis.x = q.x / divider;
		axis.y = q.y / divider;
		axis.z = q.z / divider;
	}
	return (axis);
}

t_quaternion	ft_quaternion_rotation_x(double angle)
{
	t_angles	axis;

	axis.x = 1;
	axis.y = 0;
	axis.z = 0;
	return (ft_quaternion_axis_from_angle(axis, angle));
}

t_quaternion	ft_quaternion_rotation_y(double angle)
{
	t_angles	axis;

	axis.x = 0;
	axis.y = 1;
	axis.z = 0;
	return (ft_quaternion_axis_from_angle(axis, angle));
}

t_quaternion	ft_quaternion_rotation_z(double angle)
{
	t_angles	axis;

	axis.x = 0;
	axis.y = 0;
	axis.z = 1;
	return (ft_quaternion_axis_from_angle(axis, angle));	
}

/**
 * @brief 4x4
 * 
 * @param q1 
 * @param q2 
 * @ref https://en.wikipedia.org/wiki/Quaternion
 * @ref https://jjycjnmath.tistory.com/245
 * @return t_quaternion 
 */
t_quaternion	ft_quaternion_multiply(t_quaternion q1, t_quaternion q2)
{
	t_quaternion result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

	return (result);
}

/**
 * @brief 
 * 
 * @param q 
 * @ref https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
 * @ref https://en.wikipedia.org/wiki/Rotation_matrix
 * @return t_mtx3
 */
t_mtx3	ft_quaternion_rotate_matrix(t_quaternion q)
{
	t_mtx3	m3;

	m3 = ft_matrix_3(
		(double [3]){
			1 - 2 * q.y * q.y - 2 * q.z * q.z, 
			2 * q.x * q.y - 2 * q.z * q.w, 
			2 * q.x * q.z + 2 * q.y * q.w},
		(double [3]){
			2 * q.x * q.y + 2 * q.z *q.w,
			1 - 2 * q.x * q.x - 2 * q.z * q.z,
			2 * q.y * q.z - 2 * q.x * q.w},
		(double [3]){
			2 * q.x * q.z - 2 * q.y * q.w,
			2 * q.y * q.z + 2 * q.x * q.w,
			1 - 2 * q.x * q.x - 2 * q.y * q.y
		}
	);
	return (m3);
}

t_vec3	ft_quaternion_rotate_vec3(t_quaternion q, t_vec3 v3)
{
	t_vec3	result;
	t_mtx3	m3;

	m3 = ft_quaternion_rotate_matrix(q);
	result = ft_mtx3_mult_vec3(m3, v3);
	return (result);
}
