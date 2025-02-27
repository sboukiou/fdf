#include "./fdf.h"


/**
	* distance - Calculates distance between two circles
	* Return: float point of distance (positive value always)
	*/
float	distance(t_pt a, t_pt b)
{
	return (pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

