/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:00:29 by apriego-          #+#    #+#             */
/*   Updated: 2024/01/11 19:30:20 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_vec3	calculate_normal_cone(t_cone *cn, const t_vec3 *p)
{
	t_vec3	apex_to_p;
	//t_vec3	cn_center = cn->center;

	//calculate apex to hit point vector
	apex_to_p = substract_vec3(p, &cn->apex);
	apex_to_p = unit_vector(&apex_to_p); //NORMALIZE OR NOT
	
	//calculate apex to base 
	t_vec3 g = unit_vector(&cn->dir);

	//calculate normal -> N = AP - (AP . G) * G
	t_vec3	tmp = product_vec3_r(&g, dot(&apex_to_p, &g));
	t_vec3	normal = substract_vec3(&apex_to_p, &tmp);
	


	/* projected = product_vec3_r(&cn->dir, dot(&cn->dir, &apex_to_p));
	tmp2 = substract_vec3(&apex_to_p, &projected);
	normal = division_vec3_r(&tmp2, (cn->angle / 2.0) * dot(&cn->dir, &apex_to_p)); */
	//printf("a-p: %f, %f, %f\n", projected.x, projected.y, projected.z);
	//printf("normal: %f, %f, %f\n", normal.x, normal.y, normal.z);
	return (unit_vector(&normal));
}


/* printf("apex: %f, %f, %f\n", cn->apex.x, cn->apex.y, cn->apex.z);
	printf("center: %f, %f, %f\n", tmp_center.x, tmp_center.y, tmp_center.z);
	printf("normal: %f, %f, %f\n", normal.x, normal.y, normal.z); */
	
/* 

 

C = np.array([Cx, Cy, Cz])
A = np.array([Ax, Ay, Az])
P = np.array([Px, Py, Pz])

# Calculate vectors
V = A - C
W = P - C

# Calculate dot products
V_dot_V = np.dot(V, V)
W_dot_W = np.dot(W, W)
W_dot_V = np.dot(W, V)

# Calculate the gradient (normal to the cone)
normal = 2 * (V_dot_V * W - W_dot_V * V) */

bool	calc_hit_cone(const t_ray *ray, t_objects obj, t_hit *rec, t_evars vars)
{
	double	hit_z;
	t_vec3	tmp;

	vars.root = (-vars.half_b - vars.sqrtd) / (2 * vars.a);
	if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
	{
		vars.root = (-vars.half_b + vars.sqrtd) / (2 * vars.a);
		if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
			return (false);
	}
	tmp = product_vec3_r(&ray->dir, vars.root);
	tmp = add_vec3(&ray->orig, &tmp);
	tmp = substract_vec3(&tmp, &obj.cn->apex);
	hit_z = dot(&tmp, &obj.cn->dir);
	if (hit_z < 0 || hit_z > obj.cn->height)
		return (false);
	rec->t = vars.root;
	rec->p = ray_at(ray, vars.root);
	rec->normal = calculate_normal_cone(obj.cn, &rec->p);
	return (true);
}

bool	hit_cone(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_vec3	oc;
	t_evars	vars;
	double	half_a;

	oc = substract_vec3(&ray->orig, &obj.cn->apex);
	half_a = tan(obj.cn->angle / 2.0);
	vars.a = length_squared(&ray->dir) - (1 + half_a * half_a)
		* pow(dot(&ray->dir, &obj.cn->dir), 2);
	vars.half_b = 2 * (dot(&oc, &ray->dir) - (1 + half_a * half_a)
			* dot(&oc, &obj.cn->dir) * dot(&ray->dir, &obj.cn->dir));
	vars.c = length_squared(&oc) - (1 + half_a * half_a)
		* pow(dot(&oc, &obj.cn->dir), 2);
	vars.discriminant = vars.half_b * vars.half_b - 4 * vars.a * vars.c;
	if (vars.discriminant < 0)
		return (false);
	vars.sqrtd = sqrt(vars.discriminant);
	return (calc_hit_cone(ray, obj, rec, vars));
}

bool	hit_disk_cone(const t_ray *ray, t_objects obj, t_hit *rec)
{
	bool		r[2];
	t_ray		displace;
	t_disk		disk;

	displace.dir = obj.cn->dir;
	displace.orig = obj.cn->center;
	obj.cn->apex = ray_at(&displace, -(obj.cn->height / 2));
	disk.radius = tan(obj.cn->angle / 2) * obj.cn->height;
	disk.center = ray_at(&displace, obj.cn->height / 2);
	disk.dir = product_vec3_r(&obj.cn->dir, -1);
	r[0] = hit_cone(ray, obj, rec);
	if (r[0])
		rec->ray_tmax = rec->t;
	r[1] = hit_disk(ray, &disk, rec);
	return (r[0] || r[1]);
}
