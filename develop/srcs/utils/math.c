/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:10:35 by znogueir          #+#    #+#             */
/*   Updated: 2023/03/23 20:10:46 by znogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
direction vector for pixel 0,0 :
z = cam_len;
x = WIDTH / 2;
y = HEIGHT / 2;

for each pixel we only need to increment the vector by 1 in x for the lines and
1 in y for the collumns to get every direction vector;

don't forget to normalize;
*/

/*
sphere formula : (v = direction vector, p = point of origin (0,0,0 probably),
r = radius of sphere)
a = vx^2 + vy^2 + vz^2;
b = 2(px + vx) + 2(py + vy) + 2(pz + vz);
c = px^2 + py^2 + pz^2 - r^2;
*/

double	quadratic_disrciminant()
{
}

double	quadratic_solve()
{
}
