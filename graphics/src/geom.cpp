
#include "graphics/geom.h"
#include "graphics/_limits.h"
#include <math.h>
#include "graphics/fmatrix.h"
#include <random>
#include <mutex>

namespace graphics {

void box2::extend(const vec2& pt)
{
    if (pt[0] < minimum[0]) minimum[0] = pt[0];
    if (pt[0] > maximum[0]) maximum[0] = pt[0];
    if (pt[1] < minimum[1]) minimum[1] = pt[1];
    if (pt[1] > maximum[1]) maximum[1] = pt[1];
}

void box2::extend(const box2& r)
{
    if (r.minimum[0] < minimum[0]) minimum[0] = r.minimum[0];
    if (r.maximum[0] > maximum[0]) maximum[0] = r.maximum[0];
    if (r.minimum[1] < minimum[1]) minimum[1] = r.minimum[1];
    if (r.maximum[1] > maximum[1]) maximum[1] = r.maximum[1]; 
}

void box2::extend_epsilon(real eps)
{
	minimum -= eps;
	maximum += eps;
}

bool box2::has_intersection(const vec2& pt) const
{
    return ((pt[0] >= minimum[0]) &&    
	    (pt[1] >= minimum[1]) && 
	    (pt[0] <= maximum[0]) &&                            
	    (pt[1] <= maximum[1]));
}

bool box2::has_intersection(const box2& bb) const
{
    return 
    ((bb.maximum[0] >= minimum[0]) && (bb.minimum[0] <= maximum[0]) &&  
     (bb.maximum[1] >= minimum[1]) && (bb.minimum[1] <= maximum[1]));
}

vec2 box2::get_closest_point(const vec2& point) const
{
    vec2 result;

    if (is_empty())
	return point;
    else if (point == get_center()) {
	result[0] = maximum[0];
	result[1] = (maximum[1] + minimum[1])/2.0;
    } else if (minimum[0] == maximum[0]) {
	result[0] = minimum[0];
	result[1] = point[1];
    } else if (minimum[1] == maximum[1]) {
	result[0] = point[0];
	result[1] = minimum[1];
    } else {
	vec2 vec = point - get_center();
	real sizeX, sizeY;

	get_size(sizeX, sizeY);

	real halfX = sizeX/2.0;
	real halfY = sizeY/2.0;

	if (halfX > 0.0) vec[0] /= halfX;
	if (halfY > 0.0) vec[1] /= halfY;

	real magX = fabs(vec[0]);
	real magY = fabs(vec[1]);

	if (magX > magY) {
	    result[0] = (vec[0] > 0) ? 1.0 : -1.0;
	    if (magY > 1.0)
		magY = 1.0;
	    result[1] = (vec[1] > 0) ? magY : -magY;
	} else if (magY > magX) {
	    if (magX > 1.0)
		magX = 1.0;
	    result[0] = (vec[0] > 0) ? magX : -magX;
	    result[1] = (vec[1] > 0) ? 1.0 : -1.0;
	} else {
	    //| must be one of the corners
	    result[0] = (vec[0] > 0) ? 1.0 : -1.0;
	    result[1] = (vec[1] > 0) ? 1.0 : -1.0;
	}

	result[0] *= halfX;
	result[1] *= halfY;
	result += get_center();
    }

    return result;
    
}

void box2::make_empty()
{
    minimum = vec2(kMaxReal, kMaxReal);
    maximum = vec2(-kMaxReal, -kMaxReal);
}

void box3::extend(const vec3& pt)
{
    if (pt[0] < minimum[0]) minimum[0] = pt[0];
    if (pt[1] < minimum[1]) minimum[1] = pt[1];
    if (pt[2] < minimum[2]) minimum[2] = pt[2];
    if (pt[0] > maximum[0]) maximum[0] = pt[0];
    if (pt[1] > maximum[1]) maximum[1] = pt[1];
    if (pt[2] > maximum[2]) maximum[2] = pt[2];
}

void box3::extend(const box3& a)
{
    if (a.minimum[0] < minimum[0]) minimum[0] = a.minimum[0];
    if (a.minimum[1] < minimum[1]) minimum[1] = a.minimum[1];
    if (a.minimum[2] < minimum[2]) minimum[2] = a.minimum[2];
    if (a.maximum[0] > maximum[0]) maximum[0] = a.maximum[0];
    if (a.maximum[1] > maximum[1]) maximum[1] = a.maximum[1];
    if (a.maximum[2] > maximum[2]) maximum[2] = a.maximum[2];
}

void box3::extend_epsilon(real eps)
{
	minimum -= eps;
	maximum += eps;
}

bool box3::intersect(const line& l, vec3& ret)
{
	plane pl1(vec3(1,0,0), minimum);
	plane pl2(vec3(0,1,0), minimum);
	plane pl3(vec3(0,0,1), minimum);
	plane pl4(vec3(1,0,0), maximum);
	plane pl5(vec3(0,1,0), maximum);
	plane pl6(vec3(0,0,1), maximum);

	vec3 p1;
	box3 box = *this;
	box.extend_epsilon(0.00000001);

	real max_dist = 1000000000000.0;
	bool result = false;

	if (pl1.intersect(l, p1)) {
		if (has_intersection(p1)) {
			vec3 dir = p1-l.get_position();
			if (inner(dir, l.get_direction()) > 0) {
				real dist = norm(dir);
				if (dist < max_dist) {
					max_dist = dist;
					result = true;
					ret = p1;
				}
			}
		}
	}

	pl1 = pl2;

	if (pl1.intersect(l, p1)) {
		if (has_intersection(p1)) {
			vec3 dir = p1-l.get_position();
			if (inner(dir, l.get_direction()) > 0) {
				real dist = norm(dir);
				if (dist < max_dist) {
					max_dist = dist;
					result = true;
					ret = p1;
				}
			}
		}
	}

	pl1 = pl3;

	if (pl1.intersect(l, p1)) {
		if (has_intersection(p1)) {
			vec3 dir = p1-l.get_position();
			if (inner(dir, l.get_direction()) > 0) {
				real dist = norm(dir);
				if (dist < max_dist) {
					max_dist = dist;
					result = true;
					ret = p1;
				}
			}
		}
	}

	pl1 = pl4;

	if (pl1.intersect(l, p1)) {
		if (has_intersection(p1)) {
			vec3 dir = p1-l.get_position();
			if (inner(dir, l.get_direction()) > 0) {
				real dist = norm(dir);
				if (dist < max_dist) {
					max_dist = dist;
					result = true;
					ret = p1;
				}
			}
		}
	}
	pl1 = pl5;

	if (pl1.intersect(l, p1)) {
		if (has_intersection(p1)) {
			vec3 dir = p1-l.get_position();
			if (inner(dir, l.get_direction()) > 0) {
				real dist = norm(dir);
				if (dist < max_dist) {
					max_dist = dist;
					result = true;
					ret = p1;
				}
			}
		}
	}
	pl1 = pl6;

	if (pl1.intersect(l, p1)) {
		if (has_intersection(p1)) {
			vec3 dir = p1-l.get_position();
			if (inner(dir, l.get_direction()) > 0) {
				real dist = norm(dir);
				if (dist < max_dist) {
					max_dist = dist;
					result = true;
					ret = p1;
				}
			}
		}
	}

	return result;
}

bool box3::has_intersection(const vec3& pt) const
{
    return ((pt[0] >= minimum[0]) &&
	    (pt[1] >= minimum[1]) &&
	    (pt[2] >= minimum[2]) &&
	    (pt[0] <= maximum[0]) &&
	    (pt[1] <= maximum[1]) &&
	    (pt[2] <= maximum[2]));
}

bool box3::has_intersection(const box3& bb) const
{
    return 
     ((bb.maximum[0] >= minimum[0]) && (bb.minimum[0] <= maximum[0]) &&
      (bb.maximum[1] >= minimum[1]) && (bb.minimum[1] <= maximum[1]) &&
      (bb.maximum[2] >= minimum[2]) && (bb.minimum[2] <= maximum[2]));
}

vec3 box3::get_closest_point(const vec3& point) const
{
    vec3 result;

    if (is_empty())
	return point;
    else if (point == get_center()) {
	result[0] = (maximum[0] + minimum[0])/2.0;
	result[1] = (maximum[1] + minimum[1])/2.0;
	result[2] = maximum[2];
    } else {

	vec3 vec = point - get_center();
	real sizeX, sizeY, sizeZ;
	get_size(sizeX, sizeY, sizeZ);
	real halfX = sizeX/2.0;
	real halfY = sizeY/2.0;
	real halfZ = sizeZ/2.0;
	if (halfX > 0.0)
	    vec[0] /= halfX;
	if (halfY > 0.0)
	    vec[1] /= halfY;
	if (halfZ > 0.0)
	    vec[2] /= halfZ;

	vec3 mag;
	mag[0] = fabs(vec[0]);
	mag[1] = fabs(vec[1]);
	mag[2] = fabs(vec[2]);

	result = mag;

	if (result[0] > 1.0)
	    result[0] = 1.0;
	if (result[1] > 1.0)
	    result[1] = 1.0;
	if (result[2] > 1.0)
	    result[2] = 1.0;

	if ((mag[0] > mag[1]) && (mag[0] >  mag[2])) {
	    result[0] = 1.0;
	} else if ((mag[1] > mag[0]) && (mag[1] >  mag[2])) {
	    result[1] = 1.0;
	} else if ((mag[2] > mag[0]) && (mag[2] >  mag[1])) {
	    result[2] = 1.0;
	} else if ((mag[0] == mag[1]) && (mag[0] == mag[2])) {
	    result = vec3(1,1,1);
	} else if (mag[0] == mag[1]) {
	    result[0] = 1.0;
	    result[1] = 1.0;
	} else if (mag[0] == mag[2]) {
	    result[0] = 1.0;
	    result[2] = 1.0;
	} else if (mag[1] == mag[2]) {
	    result[1] = 1.0;
	    result[2] = 1.0;
	}

	for (int i=0; i < 3;++i)
	    if (vec[i] < 0.0) result[i] = -result[i];

	/*| scale back up and move to center    */
	result[0] *= halfX;
	result[1] *= halfY;
	result[2] *= halfZ;

	result += get_center();
    }

    return result;

}

void  box3::make_empty()
{
    minimum = vec3(kMaxReal, kMaxReal, kMaxReal);
    maximum = vec3(-kMaxReal, -kMaxReal, -kMaxReal);
}

void box3::print() const
{
	LOG("min %f %f %f, max %f %f %f\n", minimum[0], minimum[1],minimum[2], maximum[0], maximum[1], maximum[2]);
}

line& line::operator = (const line& a)
{
    pos = a.pos;
    dir = a.dir;

    return *this;
}

void line::set_value(const vec3& p0, const vec3& p1)
{
    pos = p0;
    dir = p1 - p0;
    dir = unit(dir);
}

bool  
line::get_closest_points(const line& l, vec3& ptOnThis, vec3& ptOnl) const
{
	vec3 normal = cross(dir, l.get_direction());
	if (apx_equal(normal, vec3(0))) 
		return false;

    vec3	pos2 = l.get_position();
    vec3	dir2 = l.get_direction();

    real A = inner(dir,dir2);
    real B = inner(dir,dir);
    real C = inner(dir,pos) - inner(dir,pos2);
    real D = inner(dir2,dir2);
    real E = inner(dir2,dir);
    real F = inner(dir2,pos) - inner(dir2,pos2);


    real denom = A * E - B * D;
    if (apx_equal(denom, 0.0)) {
		ptOnThis = get_closest_point(pos2);
		ptOnl = pos2;
		return false;
    }

    real s = ( C * D - A * F ) / denom;
    real t = ( C * E - B * F ) / denom;
    ptOnThis  = pos  + (dir  * s);
    ptOnl = pos2 + (dir2 * t);

    return true;
}

vec3 line::get_closest_point(const vec3& pnt) const
{
    vec3 p = pnt - pos; 
    real length = inner(p,dir);
    vec3 proj = dir;
    proj *= length; 
    vec3 result = pos + proj;
    return result;
}

bool  line::intersect(const box3& bb, vec3& enter, vec3& exit) const
{
    if (bb.is_empty())  return false;

    vec3	max = bb.get_maximum(), min = bb.get_minimum();
    vec3	points[8], inter, bary;
    int	i, v0, v1, v2;
    int	front = 0;
    bool	valid, has_isect = false;

    /*|__________________________________________________________________*/
    /*| project the (center-pos) to (pos+dir)                            */
    /*| compute the projected point and the distance from		     */
    /*| that point to the center of the box.			     */
    /*| if the distance is larger than 1/2 of diagonal of the box        */
    /*| there is nochance to intersect.				     */
    /*|__________________________________________________________________*/
    real    t = inner(bb.get_center() - pos, dir);
    vec3	diff = pos + (t * dir) - bb.get_center();
    real    dist2 = inner(diff,diff);
    real    rad_2 = inner((max - min), (max - min)) * .25;

    if (dist2 > rad_2)
	return false;

    /*| set up the eight coords of the corners of the bb	*/
    for(i = 0; i < 8;++i)
	points[i] = vec3(i & 01 ? min[0] : max[0],
			 i & 02 ? min[1] : max[1],
			 i & 04 ? min[2] : max[2]);

    /*| intersect the 12 triangles.	*/
    for(i = 0; i < 12;++i) {
	switch(i) {
	case  0: v0 = 2; v1 = 1; v2 = 0; break;//| +z
	case  1: v0 = 2; v1 = 3; v2 = 1; break;

	case  2: v0 = 4; v1 = 5; v2 = 6; break;//| -z
	case  3: v0 = 6; v1 = 5; v2 = 7; break;

	case  4: v0 = 0; v1 = 6; v2 = 2; break;//| -x
	case  5: v0 = 0; v1 = 4; v2 = 6; break;

	case  6: v0 = 1; v1 = 3; v2 = 7; break;//| +x
	case  7: v0 = 1; v1 = 7; v2 = 5; break;

	case  8: v0 = 1; v1 = 4; v2 = 0; break;//| -y
	case  9: v0 = 1; v1 = 5; v2 = 4; break;

	case 10: v0 = 2; v1 = 7; v2 = 3; break;//| +y
	case 11: v0 = 2; v1 = 6; v2 = 7; break;
	}
	if (valid = intersect(points[v0], points[v1], points[v2],
		       inter, bary, front)) {
	    if (front) {
		    enter = inter;
		    has_isect = valid;
	    } else {
		    exit = inter;
		    has_isect = valid;
	    }
	}
    }

    return has_isect;
}

bool line::intersect(real ang, const box3& box) const
{
    if (box.is_empty())
	return false;

    vec3	max = box.get_maximum(), min = box.get_minimum();
    real	fuzz = 0.0;

    if (ang < 0.0)	
	fuzz = - ang;
    else {
	real tanA = tan(ang);
	for(int i = 0; i < 8;++i) {
	    vec3 point(i & 01 ? min[0] : max[0],
		       i & 02 ? min[1] : max[1],
		       i & 04 ? min[2] : max[2]);

	    vec3	diff = point - pos;
	    real thisFuzz = sqrt(inner(diff,diff)) * tanA;

	    if (thisFuzz > fuzz)
		fuzz = thisFuzz;
	}
    }

    box3 fuzzBox = box;

    fuzzBox.extend(vec3(min[0] - fuzz, min[1] - fuzz, min[2] - fuzz));
    fuzzBox.extend(vec3(max[0] + fuzz, max[1] + fuzz, max[2] + fuzz));

    vec3 scratch1, scratch2;
    return intersect(fuzzBox, scratch1, scratch2);
}

bool line::intersect(real pickAngle,const vec3& point) const
{
    real	t, d;

    vec3	diff = point - pos;

    t = inner(diff,dir);
    if(t > 0) {
	d = sqrt(inner(diff,diff) - t*t);
	if (pickAngle < 0.0)
	    return (d < -pickAngle);
	return ((d/t) < pickAngle);
    }
    return false;
}

bool line::intersect(real ang, const vec3& v0, const vec3& v1, vec3 &intersection) const
{
    vec3	ptOnLine;
    line	inputLine(v0, v1);
    real	distance;
    bool    valid = false;

    if(get_closest_points(inputLine, ptOnLine, intersection)) {
	if(inner(intersection - v0, v1 - v0) < 0)
	    intersection = v0;
	else if(inner(intersection - v1,v0 - v1) < 0)
	    intersection = v1;

	distance = norm(ptOnLine - intersection);
	if (ang< 0.0)
	    return (distance < -ang);
	valid = (distance /norm(ptOnLine-pos)) < ang;
    }

    return valid;
}

int line::intersect(const vec3& v0, const vec3& v1, const vec3& v2,
			   vec3 &intersection,
			   vec3 &barycentric, int &front) const
{
    /*|__________________________________________________________________*/
    /*| (1) Compute the plane containing the triangle                    */
    /*|__________________________________________________________________*/

    vec3	v01 = v1 - v0;
    vec3	v12 = v2 - v1;
    vec3	normal = cross(v12,v01);

    normal = unit(normal);

    /*|__________________________________________________________________*/
    /*| Normalize normal to unit length, and make sure the length is     */
    /*| not 0 (indicating a zero-area triangle)                          */
    /*|__________________________________________________________________*/
    if (norm(normal) < epsilon)
	return false;


    /*|__________________________________________________________________*/
    /*|                                                                  */
    /*| (2) Compute the distance t to the plane along the line           */
    /*|__________________________________________________________________*/
    real d = inner(dir, normal);
    if (d < epsilon && d > -epsilon)
	return false;			//| Line is parallel to plane

    real t = inner(normal, (v0 - pos)) / d;

    //| Note: we DO NOT ignore intersections behind the eye (t < 0.0)

    /*|__________________________________________________________________*/
    /*| (3) Find the largest component of the plane normal. The other    */
    /*|     two dimensions are the axes of the aligned plane we will     */
    /*|     use to project the triangle.                                 */
    /*|__________________________________________________________________*/

    real	xAbs = normal[0] < 0.0 ? -normal[0] : normal[0];
    real	yAbs = normal[1] < 0.0 ? -normal[1] : normal[1];
    real	zAbs = normal[2] < 0.0 ? -normal[2] : normal[2];
    int	axis0, axis1;

    if (xAbs > yAbs && xAbs > zAbs) {
	axis0 = 1;
	axis1 = 2;
    } else if (yAbs > zAbs) {
	axis0 = 2;
	axis1 = 0;
    } else {
	axis0 = 0;
	axis1 = 1;
    }

    /*|__________________________________________________________________*/
    /*| (4) Determine if the projected intersection, of the line and     */
    /*|     the triangle plane, lies within the projected triangle.      */
    /*|     Since we deal with only 2 components, we can avoid the       */
    /*|     third computation.                                           */
    /*|__________________________________________________________________*/
    real intersection0 = pos[axis0] + t * dir[axis0];
    real intersection1 = pos[axis1] + t * dir[axis1];

    vec2	diff0, diff1, diff2;
    bool	isInter = false;
    real	alpha, beta;

    diff0[0] = intersection0 - v0[axis0];
    diff0[1] = intersection1 - v0[axis1];
    diff1[0] = v1[axis0]     - v0[axis0];
    diff1[1] = v1[axis1]     - v0[axis1];
    diff2[0] = v2[axis0]     - v0[axis0];
    diff2[1] = v2[axis1]     - v0[axis1];

    /*|__________________________________________________________________*/
    /*| Note: This code was rearranged somewhat from the code in         */
    /*| Graphics Gems to provide a little more numeric		     */
    /*| stability. However, it can still miss some valid intersections   */
    /*| on very tiny triangles.					     */
    /*|__________________________________________________________________*/

    isInter = false;
    beta = ((diff0[1] * diff1[0] - diff0[0] * diff1[1]) /
	    (diff2[1] * diff1[0] - diff2[0] * diff1[1]));
    if (beta >= 0.0 && beta <= 1.0) {
	alpha = -1.0;
	if (diff1[1] < -epsilon || diff1[1] > epsilon) 
	    alpha = (diff0[1] - beta * diff2[1]) / diff1[1];
	else
	    alpha = (diff0[0] - beta * diff2[0]) / diff1[0];
	isInter = (alpha >= 0.0 && alpha + beta <= 1.0);
    }

    /*|__________________________________________________________________*/
    /*| (5) If there is an intersection, set up the barycentric          */
    /*|     coordinates and figure out if the front was hit.             */
    /*|__________________________________________________________________*/

    if (isInter) {
	barycentric = vec3(1.0 - (alpha + beta), alpha, beta);
	front = (inner(dir, normal) < 0.0);
	intersection = pos + (t * dir);
    }

    return isInter;

}


bool 
line::is_on(const vec3& rhs, real eps) const
{
    vec3 on = get_closest_point(rhs);
    real dist = norm(on-rhs);

    if (dist < eps) return true;
    return false;
}


plane::plane(const vec3& p, const vec3& q, const vec3& r) 	//| plane contains p, q, r
{
    reset(p, q, r);
}

void plane::reset(const vec3& p, const vec3& q, const vec3& r)
{
    n = unit(cross(q - p, r - q));	//| orientation of tri-angle pqr
    d = inner(n, p);		//| distance from origin to the plane
}

void plane::reset(const vec3& p, const vec3& normal)
{
    n = unit(normal);
    d = inner(n, p);
}

void plane::reset(const vec3& nn, real dd)
{
    n = nn;
    d = dd;
}

plane& plane::operator = (const plane& a)
{
    n = a.n ;
    d = a.d ;
    return *this;
}

const vec3& plane::get_normal() const
{
    return n;
}

vec3& plane::get_normal()
{
    return n;
}

real plane::get_dist() const
{
    return d;
}

void plane::offset(real a)
{
    d += a;
}

bool plane::intersect(const line& l, vec3& intersection) const
{
    real	t, denom;
    denom = inner(n, l.get_direction());
    if ( apx_equal(denom,0.0) )
	    return false;
    
    t = -(inner(n, l.get_position()) - d)/denom;
    intersection = l.get_position() + (t * l.get_direction()); 
    return true;
}


bool plane::is_on(const vec3& rhs) const
{
    real val = inner(rhs, n);
    if (apx_equal(val, d)) return true;
    return false;
}


bool plane::is_same_plane(const plane &pl, real eps) const
{
	if (apx_equal(pl.get_normal(), n, eps) || apx_equal(pl.get_normal(),-n, eps)) {
		if (apx_equal(pl.get_normal() * pl.get_dist(), n * d, eps)) 
			return true;
	}
	return false;
}

bool 
plane::intersect(const plane& pl, line& is)
{
	vec3 dir = cross(n, pl.get_normal());
	vec3 pnt;

	real len = norm(dir);

	if(len < user_epsilon) 
		return false;

	/* Determine intersection point with the best suited coordinate plane. */

	real   abs;
	real   maxabs = fabs(dir[0]);
	int    index  = 0;

	if((abs = fabs(dir[1])) > maxabs) 
	{ 
		maxabs = abs;
		index  = 1; 
	}

	if((abs = fabs(dir[2])) > maxabs)
	{
		maxabs = abs; 
		index  = 2;
	}

	switch(index)
    {
         case 0: 
            pnt = vec3(
                 0.f,
                 (pl.get_normal()[2] * d     - 
                  pl.get_dist() * n[2]) / dir[0],
                 (pl.get_dist() * n[1] -
                  pl.get_normal()[1] * d) / dir[0]);
             break;
 
         case 1:
             pnt = vec3(
                 (pl.get_dist() * n[2] -
                  pl.get_normal()[2] * d) / dir[1],
                 0.f,
                 (pl.get_normal()[0] * d -
                  pl.get_dist() * n[0]) / dir[1]);
             break;
 
         case 2: 
            pnt = vec3(
                 (pl.get_normal()[1] * d -
                  pl.get_dist()* n[1]) / dir[2],
                 (pl.get_dist()* n[0] -
                  pl.get_normal()[0] * d)/ dir[2],
                 0.f);
             break;
 
        default: 
             return false;  /* Impossible */
     }
 
     /* Normalize the direction */
 
     dir *= 1.f / len;
 
     is.set_position(pnt);
	 is.set_direction(dir);
     
     return true;

}



cone::cone ()
{
    // uninitialized
}
//----------------------------------------------------------------------------
cone::cone (const vec3& rkVertex,
    const vec3& rkAxis, real fAngle)
    :
    Vertex(rkVertex),
    Axis(rkAxis)
{
    CosAngle = cos(fAngle);
    SinAngle = sin(fAngle);
}
//----------------------------------------------------------------------------

cone::cone (const vec3& rkVertex,
    const vec3& rkAxis, real fCosAngle, real fSinAngle)
    :
    Vertex(rkVertex),
    Axis(rkAxis)
{
    CosAngle = fCosAngle;
    SinAngle = fSinAngle;
}

bool cone::set_cone(const line& l, const vec3& p1, const vec3& p2)
{

	vec3 pp1 = l.get_closest_point(p1);
	vec3 pp2 = l.get_closest_point(p2);
	
	real d1 = norm(pp1-p1);
	real d2 = norm(pp2-p2);

	if (d1 < zero_epsilon) {

		if (d2 < zero_epsilon) {
			return false;
		}

		Axis = unit(p2-p1);
		Vertex = p1;
		return true;
	}
	else if (d2 < zero_epsilon) {
		if (d1 < zero_epsilon) {
			return false;
		}

		Axis = unit(p1-p2);
		Vertex = p2;
		return true;
	}

	if (apx_equal(d1, d2)) {
		// this is not cone, but cylinder
		return false;
	}


	vec3 dir1 = unit(pp1-p1);
	vec3 dir2 = unit(pp2-p2);
	
	quater q1 = u2v_quater(dir1, dir2);
	dir1 = rot(q1, dir1);

	


	vec3 new_p1 = pp1 + (dir1 * d1);

	line l2(new_p1, p2);
	vec3 on_this, on_that;
	l2.get_closest_points(l, on_this, on_that);

	Vertex = on_this;
	real ang = angle(l2.get_direction(), l.get_direction());

	if (ang >= M_PI/2.0) {
		ang = M_PI- (M_PI/2.0);
	}

	CosAngle = cos(ang);
	SinAngle = sin(ang);

	return true;
}

bool cone::intersect(const line& l, vec3& enter, vec3& exit) const
{
    // Set up the quadratic Q(t) = c2*t^2 + 2*c1*t + c0 that corresponds to
    // the cone.  Let the vertex be V, the unit-length direction vector be A,
    // and the angle measured from the cone axis to the cone wall be Theta,
    // and define g = cos(Theta).  A point X is on the cone wall whenever
    // Dot(A,(X-V)/|X-V|) = g.  Square this equation and factor to obtain
    //   (X-V)^T * (A*A^T - g^2*I) * (X-V) = 0
    // where the superscript T denotes the transpose operator.  This defines
    // a double-sided cone.  The line is L(t) = P + t*D, where P is the line
    // origin and D is a unit-length direction vector.  Substituting
    // X = L(t) into the cone equation above leads to Q(t) = 0.  Since we
    // want only intersection points on the single-sided cone that lives in
    // the half-space pointed to by A, any point L(t) generated by a root of
    // Q(t) = 0 must be tested for Dot(A,L(t)-V) >= 0.
    real fAdD = inner(Axis, l.get_direction());
    real fCosSqr = CosAngle*CosAngle;
    vec3 kE = l.get_position() - Vertex;

    real fAdE = inner(Axis, kE);
    real fDdE = inner(l.get_direction(),kE);
    real fEdE = inner(kE,kE);
    real fC2 = fAdD*fAdD - fCosSqr;
    real fC1 = fAdD*fAdE - fCosSqr*fDdE;
    real fC0 = fAdE*fAdE - fCosSqr*fEdE;
    real fDot;

	int m_iQuantity;
	vec3 intersections[2];

    // Solve the quadratic.  Keep only those X for which Dot(A,X-V) >= 0.
    if (fabs(fC2) >= zero_tolerance)
    {
        // c2 != 0
        real fDiscr = fC1*fC1 - fC0*fC2;
        if (fDiscr < (real)0.0)
        {
			return false;
        }
        else if (fDiscr > zero_tolerance)
        {
            // Q(t) = 0 has two distinct real-valued roots.  However, one or
            // both of them might intersect the portion of the double-sided
            // cone "behind" the vertex.  We are interested only in those
            // intersections "in front" of the vertex.
            real fRoot = sqrt(fDiscr);
            real fInvC2 = ((real)1.0)/fC2;
            m_iQuantity = 0;

            real fT = (-fC1 - fRoot)*fInvC2;
            intersections[m_iQuantity] = l.get_position() + fT*l.get_direction();
            kE = intersections[m_iQuantity] - Vertex;
            fDot = inner(kE, Axis);
            if (fDot > (real)0.0)
            {
                m_iQuantity++;
            }

            fT = (-fC1 + fRoot)*fInvC2;
            intersections[m_iQuantity] = l.get_position() + fT*l.get_direction();
            kE = intersections[m_iQuantity] - Vertex;
            fDot = inner(kE, Axis);
            if (fDot > (real)0.0)
            {
                m_iQuantity++;
            }

            if (m_iQuantity == 2)
            {
				enter = intersections[0];
				exit = intersections[1];
				return true;
            }
            else if (m_iQuantity == 1)
            {
				enter = intersections[0];
				exit = l.get_direction();
				return true;
            }
            else
            {
				return false;
            }
        }
        else
        {
            // one repeated real root (line is tangent to the cone)
            intersections[0] = l.get_position() - (fC1/fC2)*l.get_direction();
            kE = intersections[0] - Vertex;
            if (inner(kE,Axis) > (real)0.0)
            {
				enter = intersections[0];
				return true;
            }
            else
            {
                return false;
            }
        }
    }
    else if (fabs(fC1) >= zero_tolerance)
    {
        // c2 = 0, c1 != 0 (D is a direction vector on the cone boundary)
        intersections[0] = l.get_position() - 
            (((real)0.5)*fC0/fC1)*l.get_direction();
        kE = intersections[0] - Vertex;
        fDot = inner(kE,Axis);
        if (fDot > (real)0.0)
        {
			enter = intersections[0];
			exit = l.get_direction();
			return true;
        }
        else
        {
			return false;
        }
    }
    else if (fabs(fC0) >= zero_tolerance)
    {
		return false;
    }
    else
    {
		enter = Vertex;
		exit = l.get_direction();
		return true;
    }

    return false;
}

bool sphere::intersect(const line &l, vec3 &intersection) const
{
    real	B,C;   //| At^2 + Bt + C = 0, but A is 1 since we normalize Rd
    real	discr; //| discriminant (B^2 - 4AC)
    vec3	v;
    real	t, sqroot;
    bool	doesIntersect = true;

    //| setup B,C
    v = l.get_position() - o;
    B = 2.0 * inner(l.get_direction(),v);
    C = inner(v,v) - (r * r);

    //| compute discriminant
    //| if negative, there is no intersection
    discr = B*B - 4.0*C;
    if (discr < 0.0) {
	//| line and sphere do not intersect
	doesIntersect = false;
    }
    else {
	//| compute t0: (-B - sqrt(B^2 - 4AC)) / 2A  (A = 1)
	sqroot = sqrtf(discr);
	t = (-B - sqroot) * 0.5;
	if (t < 0.0) {
	    //| no intersection, try t1: (-B + sqrt(B^2 - 4AC)) / 2A  (A = 1)
	    t = (-B + sqroot) * 0.5;
	}

	if (t < 0.0) {
	    //| line and sphere do not intersect
	    doesIntersect = false;
	}
	else {
	    //| intersection! point is (point + (dir * t))
	    intersection = l.get_position() + (l.get_direction() * t);
	}
    }

    return doesIntersect;
}

bool sphere::intersect(const line& l, vec3& enter, vec3& exit) const
{
    real	B,C;	//| At^2 + Bt + C = 0, but A is 1 since we normalize Rd
    real	discr;	//| discriminant (B^2 - 4AC)
    vec3 	v;
    real	sqroot;
    bool	doesIntersect = true;

    //| setup B,C
    v = l.get_position() - o;
    B = 2.0 * inner(l.get_direction(),v);
    C = inner(v,v) - (r * r);

    //| compute discriminant
    //| if negative, there is no intersection
    discr = B*B - 4.0*C;

    if (discr < 0.0) {
	//| line and sphere do not intersect
	doesIntersect = false;
    }
    else {
	sqroot = sqrtf(discr);
	
	real t0 = (-B - sqroot) * 0.5;
	enter = l.get_position() + (l.get_direction() * t0);
	
	real t1 = (-B + sqroot) * 0.5;
	exit = l.get_position() + (l.get_direction() * t1);
    }

    return doesIntersect;
}



plane2::plane2(const vec2& p, const vec2& q)		//| plane contains p, q, r
{
    //| rotate vec pq by 90 deg
    vec2 pq = unit(q - p);
    n[0] = -pq[1];
    n[1] = pq[0];
    d = inner(n, p);
}



//| functions

real diameter(const vector<vec3>& poly, int& i_dia, int& j_dia)
{
    int i, j;
    real dia = -1;

    for(i = 0; i < poly.size() - 1;++i) {
	for(j = i + 1; j < poly.size(); ++j) {
	    real len = norm(poly[i] - poly[j]);
	    if(len > dia) {
		dia = len;
		i_dia = i;
		j_dia = j;
	    }
	}
    }

    return dia;
}

vec3 mean_center(const vector<vec3>& poly)
{
    vec3 sum = 0;
    for(int i = 0; i < poly.size();++i)
	sum = sum + poly[i];
    
    return sum / (real)poly.size();
}

vec3 center(const vector<vec3>& poly)
{
    int i_dia, j_dia;
    diameter(poly, i_dia, j_dia);
    return (poly[i_dia] + poly[j_dia]) * (real)0.5;
}

real diameter(const vector<vec3>& poly)
{
    int i_dia, j_dia;
    return diameter(poly, i_dia, j_dia);
}

sphere bsphere(const vector<vec3>& poly)	//| bounding sphere
{
    int i_dia, j_dia;
    real dia = diameter(poly, i_dia, j_dia);
    return sphere((poly[i_dia] + poly[j_dia]) * (real)0.5, dia *(real).5);
}

real dist(const plane& pl, const vec3& p)		//| distance
{
    return (inner(pl.n, p) - pl.d) / norm(pl.n);
}

real dist(const plane2& pl, const vec2& p)		//| distance
{
    return (inner(pl.n, p) - pl.d) / norm(pl.n);
}

real dist(const plane& pl, const vector<vec3>& poly)          //| distance
{
    real min = dist(pl, poly[0]);
    int i;
    for(i = 1; i < poly.size();++i) {
		real d = dist(pl, poly[i]);
		if(d < min)
			min = d;
    }

    return min;
}

/*|						*/
/*| distance from line (p, q) to a point, a.	*/
/*|						*/
real dist(const vec2& p, const vec2& q, const vec2& a)
{
    vec2 u = q - p;
    vec2 x = a - p;
    real t = inner(x, u) / inner(u, u);

    if(0 <= t && t < 1)
		return norm(x - u * t);
    else
		return 10000.0;	//| infinity
}

int angle_sign(const vec2& a, const vec2& b)
{
    real ang = fabs(angle(a,b));
    vec3 aa(a[0], a[1], 0.0);
    vec3 bb(b[0], b[1], 0.0);
    vec3 res = cross(aa, bb);
    if (res[2] < 0.0) ang = -ang;

    if (ang > 0.0) return 1;
    if (ang < 0.0) return -1;
    return 0;
}

int is_convex(const vector<vec2>& input)
{
    if (input.size() == 3) return 1;

    int j, _sign = 0; vec2 a, b;

    for (j = 0 ; j < input.size() ; ++j) {
	a = input[j+1] - input[j];
	b = input[j+2] - input[j+1];

	_sign = angle_sign(a, b);
	if (_sign) break;
    }

    if (!_sign) return 0;

    for (int i = j+1 ; i < input.size() ;++i) {
	a = input[i+1] - input[i];
	b = input[i+2] - input[i+1];
	int this_sign = angle_sign(a, b);
	if ( _sign * this_sign < 0 )
	    return 0;
    }

    return 1;
}

int is_pl_ccw(const std::vector<vec2>& points)
{
    real angle_sum = 0.0;
	std::vector<vec2> input;
	input.push_back(points[0]);
	for (int i = 1 ; i < points.size() ; i++) {
		if (apx_equal(input[input.size()-1], points[i])) continue;
		input.push_back(points[i]);
	}
	
	if (apx_equal(input[0], input[input.size()-1])) {
		input.resize(input.size()-1);
	}

    for (int i = 0; i < input.size() ;++i) {
		
	vec2 a = input[(i+1)%input.size()] - input[i%input.size()];
	vec2 b = input[(i+2)%input.size()] - input[(i+1)%input.size()];
	real ang = fabs(angle(a, b));
	vec3 aa(a[0], a[1], 0.0);
	vec3 bb(b[0], b[1], 0.0);
	vec3 res = cross(aa, bb);

	if (res[2] < 0.0) ang = -ang;
		
	angle_sum += degree(ang);
    }

    if (angle_sum > 0.0) return 1;
    return 0;
}

void bbox(const vector<vec3>& input, vec3& _min, vec3& _max)
{
    _min = vec3(kMaxReal, kMaxReal, kMaxReal);
    _max = vec3(-kMaxReal, -kMaxReal, -kMaxReal);

    for (int i = 0 ; i < input.size() ;++i) {
	_min[0] = min(_min[0], input[i][0]);
	_min[1] = min(_min[1], input[i][1]);
	_min[2] = min(_min[2], input[i][2]);

	_max[0] = max(_max[0], input[i][0]);
	_max[1] = max(_max[1], input[i][1]);
	_max[2] = max(_max[2], input[i][2]);
    }
}

void bbox(const vector<vec2>& input, vec2& _min, vec2& _max)
{
    _min = vec2(kMaxReal, kMaxReal);
    _max = vec2(-kMaxReal, -kMaxReal);

    for (int i = 0 ; i < input.size() ;++i) {
	_min[0] = min(_min[0], input[i][0]);
	_min[1] = min(_min[1], input[i][1]);

	_max[0] = max(_max[0], input[i][0]);
	_max[1] = max(_max[1], input[i][1]);
    }
}

real min_dist(const ivec2& p, const ivec2& q, const ivec2& a)
{
    vec2 u = q - p;
    vec2 u_u = unit(u);
    vec2 x = a - p;

    real t = inner(x, u_u);
    real d = inner(u, u);

    if (fabs(d) < epsilon)
	return (norm(a-p)+norm(a-q))*0.5;

    t /= sqrt(d);

    if (0.0 <= t && t <= 1.0)
	return norm(x - u * t);
    if (t < 0.0)
	return norm(a - p);

	return norm(a - q);
}

real min_dist(const vec2 &p, const vec2 &q, const vec2 &a)
{
    vec2 u = q - p;
    vec2 u_u = unit(u);
    vec2 x = a - p;

    real t = inner(x, u_u);
    real d = inner(u, u);

    if (fabs(d) < epsilon)
	return (norm(a-p) + norm(a-q)) * 0.5;

    t /= sqrt(d);

    if (0.0 <= t && t <= 1.0)
	return norm(x - (u * t));

    if (t < 0.0)
	return norm(a - p);

    return norm(a - q);
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| min_dist : computes distance between line(p,q) and                       */
/*|           vertex a. Besides, this computes the parameter                 */
/*|           value uu at which the shortest point is located.               */
/*|                                                                          */
/*|           0        uu     1.0                                            */
/*|           p--------.------q                                              */
/*|                                                                          */
/*|                    a                                                     */
/*| Return   : the distance between a and the point pq(uu)                   */
/*|__________________________________________________________________________*/
real min_dist(const vec2 &p, const vec2 &q, const vec2 &a, real& uu)
{
    vec2 u = q - p;
    vec2 u_u = unit(u);
    vec2 x = a - p;

    real t = inner(x, u_u);
    real d = inner(u, u);

    if (fabs(d) < epsilon) {
	uu = 0.5;
	return (norm(a-p) + norm(a-q))*0.5;
    }
	
    t /= sqrt(d);

    if (0.0 <= t && t <= 1.0) {
	uu = t;
	return norm(x - (u * t));
    } 
    
    if (t < 0.0) {
	uu = 0.0;
	return norm(a - p);
    }

    uu = 1.0;
    return norm(a - q);
}

real min_dist(const vec3 &p, const vec3 &q, const vec3 &a)
{
    vec3 u = q - p;
    vec3 u_u = unit(u);
    vec3 x = a - p;

    real t = inner(x, u_u);
    real d = inner(u, u);

    if (fabs(d) < epsilon) return (norm(a-p) + norm(a-q)) * 0.5;

    t /= sqrt(d);

    if (0.0 <= t && t <= 1.0) return norm(x - (u * t));

    if (t < 0.0) return norm(a - p);

    return norm(a - q);
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| min_dist : computes distance between line(p,q) and                       */
/*|           vertex a. Besides, this computes the parameter                 */
/*|           value uu at which the shortest point is located.               */
/*|                                                                          */
/*|           0        uu     1.0                                            */
/*|           p--------.------q                                              */
/*|                                                                          */
/*|                    a                                                     */
/*| Return   : the distance between a and the point pq(uu)                   */
/*|__________________________________________________________________________*/
real min_dist(const vec3 &p, const vec3 &q, const vec3 &a, real& uu)
{
    vec3 u = q - p;
    vec3 u_u = unit(u);
    vec3 x = a - p;

    real t = inner(x, u_u);
    real d = inner(u, u);

    if (fabs(d) < epsilon) {
		uu = 0.5;
		return (norm(a-p) + norm(a-q))*0.5;
    }
	
    t /= sqrt(d);

    if (0.0 <= t && t <= 1.0) {
		uu = t;
		return norm(x - (u * t));
    } 
    
    if (t < 0.0) {
		uu = 0.0;
		return norm(a - p);
    }

    uu = 1.0;
    return norm(a - q);
}

real min_dist(const vec4 &p, const vec4 &q, const vec4 &a)
{
    vec4 u = q - p;
    vec4 u_u = unit(u);
    vec4 x = a - p;

    real t = inner(x, u_u);
    real d = inner(u, u);

    if (fabs(d) < epsilon)
	return (norm(a-p) + norm(a-q)) * 0.5;

    t /= sqrt(d);

    if (0.0 <= t && t <= 1.0)
	return norm(x - (u * t));

    if (t < 0.0)
	return norm(a - p);

    return norm(a - q);
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| min_dist : computes distance between line(p,q) and                       */
/*|           vertex a. Besides, this computes the parameter                 */
/*|           value uu at which the shortest point is located.               */
/*|                                                                          */
/*|           0        uu     1.0                                            */
/*|           p--------.------q                                              */
/*|                                                                          */
/*|                    a                                                     */
/*| Return   : the distance between a and the point pq(uu)                   */
/*|__________________________________________________________________________*/
real min_dist(const vec4 &p, const vec4 &q, const vec4 &a, real& uu)
{
    vec4 u = q - p;
    vec4 u_u = unit(u);
    vec4 x = a - p;

    real t = inner(x, u_u);
    real d = inner(u, u);

    if (fabs(d) < epsilon) {
	uu = 0.5;
	return (norm(a-p) + norm(a-q))*0.5;
    }
	
    t /= sqrt(d);

    if (0.0 <= t && t <= 1.0) {
	uu = t;
	return norm(x - (u_u * t));
    } 
    
    if (t < 0.0) {
	uu = 0.0;
	return norm(a - p);
    }

    uu = 1.0;
    return norm(a - q);
}

bool    intersect(const vec3& l1p, const vec3& l1q, // line l1
		  const vec3& l2p, const vec3& l2q, // line l2
		  vec2& ret, vec3& pnt)
{
    line l1(l1p, l1q), l2(l2p, l2q);

    vec3 pnt1, pnt2;

    if (l1.get_closest_points(l2, pnt1, pnt2)) {
	if (norm(pnt1 - pnt2) < epsilon) {
	    real t1, t2;
	    if (min_dist(l2p, l2q, pnt1, ret[1]) < epsilon) {
		if (min_dist(l1p, l1q, pnt2, ret[0]) < epsilon) {
		    pnt = pnt2;
		    return true;
		}
	    }
	}
    }

    return false;
}

line2& line2::operator = (const line2& a)
{
    p   = a.p;
    q   = a.q;
    d   = a.d;
    dir = a.dir;

    return *this;
}

bool line2::on_half_open_edge(const vec2 &x, real& t) const
{
    real t1 = norm(x - p), t2 =  norm(x - q), t3;

    if (t1 <= user_epsilon) {
	t = 0.0;
	return true;
    }

    if (t2 <= user_epsilon) return false;

    t3 = d;

    if (t1 > t3 || t2 > t3) return false;

    vec2 prj = get_closest_point(x);
    t = norm(prj-p) / d;
    real distance = norm(prj - x);

    return	(distance <= user_epsilon);
}

bool line2::on_closed_edge(const vec2 &x) const
{
    real t1 = norm(x - p), t2 =  norm(x - q), t3;

    if (t1 <= user_epsilon) {
	return true;
    }

    t3 = d;

    if (t1 > t3 || t2 > t3) return false;

    vec2 prj = get_closest_point(x);
    real distance = norm(prj - x);

    return	(distance <= user_epsilon);
}

bool line2::on_line(const line2& ll) const
{
    vec2 prj = get_closest_point(ll.p);
    real distance1 = norm(prj - ll.p);
    prj = get_closest_point(ll.q);
    real distance2 = norm(prj - ll.q);

    return (distance1 <= user_epsilon && 
	    distance2 <= user_epsilon);
}

int line2::intersect(const line2& ll, vec2& pp, vec2& t) const
{
    t = 100000;

    if (!bbox_test(*this, ll)) return 0;

    if (on_line(ll)) { //| two line are parallel
	if (ll.on_half_open_edge(p, t[1])) {
	    return 2; 
	}

	if (on_half_open_edge(ll.p, t[0])) {
	    return 2;
	}

	return 0;
    }

    if (ll.on_half_open_edge(p, t[1])) {
	t[0] = 0.0;
	pp = p;
	return 3;
    }

    if (ll.on_closed_edge(q)) {
	return 0;
    }

    if (on_half_open_edge(ll.p, t[0])) {
	t[1] = 0.0;
	pp = ll.p;
	return 4;
    }

    if (on_closed_edge(ll.q)) {
	return 0;
    }

    vec2	a1 = q - p;
    vec2	a2 = ll.q - ll.p;
    vec2	b1 = p;
    vec2	b2 = ll.p;

    matrix A(2,2), Ainv(2,2);

    A(0,0) = a1[0];
    A(1,0) = a1[1];

    A(0,1) = -a2[0];
    A(1,1) = -a2[1];

    Ainv = A.inverse();

    if (Ainv.n == 0) return 0;

    vec2	temp = b2 - b1;

    t[0] = Ainv(0,0) * temp[0] + Ainv(0,1) * temp[1];
    t[1] = Ainv(1,0) * temp[0] + Ainv(1,1) * temp[1];

    pp = (a1 * t[0]) + b1;

    if(t[0] < 0 || t[0] > 1) return 0;
    if(t[1] < 0 || t[1] > 1) return 0;

    return 1;
}

vec2 line2::get_closest_point(const vec2& pnt, real& t) const
{
    vec2	ret  = get_closest_point(pnt);
    vec2	dir1 = ret - p;
    vec2	dir2 = q - p;
    int	s = (inner(dir1, dir2) > 0.0)? 1: 0;
    real    dist1 = norm(dir1);

    t = s ? dist1 : -dist1;

    return ret;
}

int line2::collect_coincidence(line2& ll, vec2& t) const
{
    get_closest_point(ll.p, t[0]);
    ll.get_closest_point(p, t[1]);

    real d1 = d;
    real d2 = ll.d;

    ///////////////////////////////////////|
    //| now classify the result
    ///////////////////////////////////////|
    int ret = 0;

    if (apx_equal(t[0], 0.0)) {
	t[0] = 0.0;
	t[1] = 0.0;
	ll.p  = p;

	return 1;
    }

    if (t[0] > 0 && t[0] <= (d1 - user_epsilon)) ret = 2;
    else if (t[1] > 0 && t[1] <= (d2 - user_epsilon)) ret = 3;

    t[0] = t[0]/d1;
    t[1] = t[1]/d2;

    return ret;
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| Returns 1    if the point d is inside the circle defined by the          */
/*| points a, b, c. See Guibas and Stolfi (1985) p.107.                      */
/*|__________________________________________________________________________*/
int in_circle(const vec2& a, const vec2& b, const vec2& c, const vec2& d)
{
    real az = inner(a, a);
    real bz = inner(b, b);
    real cz = inner(c, c);
    real dz = inner(d, d);

    real det = (az * tri_area(b, c, d) - bz * tri_area(a, c, d) +
		cz * tri_area(a, b, d) - dz * tri_area(a, b, c));

    return (det > 0);
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| Returns 1    if the points a, b, c are in a counterclockwise order       */
/*|__________________________________________________________________________*/
int ccw(const vec2& a, const vec2& b, const vec2& c)
{
    real det = tri_area(a, b, c);
    return (det > 0);
}

bool ccw(const vec3& a, const vec3& b, const vec3& c, const vec3& n)
{
	return inner(n, cross(b-a, c-b)) > 0.0;
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| Returns 1    if the points a, b, c are in a clockwise order              */
/*|__________________________________________________________________________*/
int cw(const vec2& a, const vec2& b, const vec2& c) 
{
    real det = tri_area(a, b, c);
    return (det < 0);
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| Returns 1    if the points a, b, c are in a counterclockwise order       */
/*|__________________________________________________________________________*/
int epsilon_ccw(const vec2& a, const vec2& b, const vec2& c)
{
    real det = tri_area(a, b, c);
    return (det > user_epsilon);
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| Returns 1    if the points a, b, c are in a clockwise order              */
/*|__________________________________________________________________________*/
int epsilon_cw(const vec2& a, const vec2& b, const vec2& c) 
{
    real det = tri_area(a, b, c);
    return (det < -user_epsilon);
}


/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| Returns the center of the circle through points a, b, c.                 */
/*| From Graphics Gems I, p.22                                               */
/*|__________________________________________________________________________*/
vec2 circumcenter(const vec2& a, const vec2& b, const vec2& c) 
{
    real d1, d2, d3, c1, c2, c3;

    d1 = inner((b - a),(c - a));
    d2 = inner((b - c),(a - c));
    d3 = inner((a - b),(c - b));
    c1 = d2 * d3;
    c2 = d3 * d1;
    c3 = d1 * d2;

    return ((c2 + c3)*a + (c3 + c1)*c + (c1 + c2)*b) / (2*(c1 + c2 + c3));
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| check if x is right of edge(org, dest)                                   */
/*|__________________________________________________________________________*/
int is_right_point(const vec2& x, const vec2& org, const vec2& dest) 
{
    return ccw(x, dest, org);
}

int is_left_point(const vec2& x, const vec2& org, const vec2& dest) 
{
    return cw(x, dest, org);
}

int on_edge(const vec2& x, const vec2& org, const vec2& dest)
{
    real t1 = norm(x - org), t2 = norm(x - dest), t3;

    if (t1 <= user_epsilon || t2 <= user_epsilon)
	return 1;

    t3 = norm(org - dest);

    if (t1 > t3 || t2 > t3)
	return 0;

    vec2 dir = (dest - org)/t3;
    vec2 prj = (inner((x - org), dir) * dir) + org;
    
    real distance = norm(prj - x);
    return (distance <= user_epsilon);
}

bool on_edge(const vec3& x, const vec3& org, const vec3& dest)
{
    real t1 = norm(x - org), t2 = norm(x - dest), t3;

    if (t1 <= user_epsilon || t2 <= user_epsilon)
	return true;

    t3 = norm(org - dest);

    if (t1 > t3 || t2 > t3)
	return false;

    vec3 dir = (dest - org)/t3;
    vec3 prj = (inner((x - org), dir) * dir) + org;
    
    real distance = norm(prj - x);
    return (distance <= user_epsilon);
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| snap x towards the line segment ab                                       */
/*|__________________________________________________________________________*/
vec2 snap(const vec2 &x, const vec2& a, const vec2& b)
{
    if (apx_equal(x, a))
		return a;
    if (apx_equal(x, b))
		return b;
    real t1 = inner((x-a), (b-a));
    real t2 = inner((x-b), (a-b));

    real t = max(t1,t2) / (t1 + t2);
    return ((t1 > t2) ? (((1-t)*a) + (t*b)) : (((1-t)*b) + (t*a)));
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| check if there is overlap of bboxes of s1 and s2.                        */
/*| But, now it does not work correctly.                                     */
/*|__________________________________________________________________________*/
int bbox_test(const line2& s1, const line2& s2)
{
    vector<vec2> data1(2);
    vector<vec2> data2(2);
    vec2 min1, max1, min2, max2;

    data1[0] = s1.p;
    data1[1] = s1.q;

    data2[0] = s2.p;
    data2[1] = s2.q;

    /*| calculate bounding boxes for each line segment */
    bbox(data1, min1, max1);
    bbox(data2, min2, max2);

    min1 = min1 - user_epsilon;
    max1 = max1 + user_epsilon;

    box2 a(min1, max1);
    box2 b(min2, max2);

    return a.has_intersection(b);
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| compute Line/line intersection :                                    */
/*| ret : 0 : intersection happened at out of domain of s1 or s2        */
/*|       1 : intersection was found                                    */
/*|       2 : intersection was found but degenertely parallel.          */
/*|           in this case further investigation is needed.             */
/*|       3 : intersection happend at the end point                     */
/*| var :                                                               */
/*|    t[0] : parameter value t, t <- [0, 1], of s1, where intersection */
/*|           was found.                                                */
/*|    t[1] : parameter value t, t <- [0, 1], of s2, where intersection */
/*|           was found.                                                */
/*|      p  : intersection point                                        */
/*|_____________________________________________________________________*/

int intersect(const line2& s1, const line2& s2, vec2& p, vec2& t)
{
    t = 100000;

    if (!bbox_test(s1, s2)) return 0;

    vec2 a1 = s1.q - s1.p;
    vec2 a2 = s2.q - s2.p;
    vec2 b1 = s1.p;
    vec2 b2 = s2.p;
    
    matrix A(2,2), Ainv(2,2);

    A(0,0) = a1[0];
    A(1,0) = a1[1];

    A(0,1) = -a2[0];
    A(1,1) = -a2[1];

    Ainv = A.inverse();
    if(Ainv.is_null()) {
	//| two line are parallel
	if (on_edge(s1.p, s2.p, s2.q))
	    return 2; 
	if (on_edge(s1.q, s2.p, s2.q))
	    return 2;
	if (on_edge(s2.p, s1.p, s1.q))
	    return 2; 
	if (on_edge(s2.q, s1.p, s1.q))
	    return 2;


	return 0;
    }


    vec2 temp = b2 - b1;
   

    t[0] = Ainv(0,0) * temp[0] + Ainv(0,1) * temp[1];
    t[1] = Ainv(1,0) * temp[0] + Ainv(1,1) * temp[1];

    if(t[0] < 0 || t[0] > 1) return 0;
    if(t[1] < 0 || t[1] > 1) return 0;

    p = a1 * t[0] + b1;

    if(t[0] < epsilon || t[0] > 1 - epsilon) return 3;
    if(t[1] < epsilon || t[1] > 1 - epsilon) return 3;

    return 1;
}

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| compute Line/line intersection :                                         */
/*| ret : 0 : intersection was not found                                     */
/*|       1 : intersection was found                                         */
/*| var : ret : intersection point                                           */
/*|__________________________________________________________________________*/
int intersect(const line2& s1, const line2& s2, vec2& ret, bool degen)
{
    if (!bbox_test(s1, s2)) return 0;

    vec2 a1 = s1.q - s1.p;
    vec2 a2 = s2.q - s2.p;
    vec2 b1 = s1.p;
    vec2 b2 = s2.p;

    matrix A(2,2), Ainv(2,2);

    A(0,0) = a1[0];
    A(1,0) = a1[1];

    A(0,1) = -a2[0];
    A(1,1) = -a2[1];

    Ainv = A.inverse();
    if(Ainv.is_null()) {
	if (degen == false) return 0;
	//| two line are parallel
	if (on_edge(s1.p, s2.p, s2.q))
	    return 1; 
	if (on_edge(s1.q, s2.p, s2.q))
	    return 1;
	return 0;
    }


    vec2 temp = b2 - b1;
    
    real t0 = Ainv(0,0) * temp[0] + Ainv(0,1) * temp[1];
    real t1 = Ainv(1,0) * temp[0] + Ainv(1,1) * temp[1];

    ret = a1 * t0 + b1;

    if ((t0 < -epsilon) || (t0 > (1.0 + epsilon))) return 0;
    if ((t1 < -epsilon) || (t1 > (1.0 + epsilon))) return 0;

    return 1;
}

int intersect(const vec2& v1, const vec2& v2,
			  const vec2& u1, const vec2& u2, 
			  vec2& ret)
{
    vec2 a1 = v2 - v1;
    vec2 a2 = u2 - u1;

    matrix A(2,2), Ainv(2,2);

    A(0,0) = a1[0];
    A(1,0) = a1[1];

    A(0,1) = -a2[0];
    A(1,1) = -a2[1];

    Ainv = A.inverse();

    if(Ainv.is_null()) {
		return 0;
    }


    vec2 temp = u1 - v1;
    
    real t0 = Ainv(0,0) * temp[0] + Ainv(0,1) * temp[1];
    real t1 = Ainv(1,0) * temp[0] + Ainv(1,1) * temp[1];

    ret = a1 * t0 + v1;

    return 1;
}


int contain(const std::vector<vec2>& pl, const vec2& p)
{
    //| choose half lay
    line2 ray;

    int i;
    for (i = 0; i < pl.size();++i) {
	if(fabs(pl[i][1] - p[1]) < epsilon) break;
    }

    if (i < pl.size()) {
	ray.p = p + vec2(0, 10 * epsilon);
    } else {
	ray.p = p;
    }

    ray.q = ray.p + vec2(1e10, 0);	//| right ray


    //| count ray intersection
    vec2 pp;
    int count = 0;
    vec2 t;

    for (i = 0; i < pl.size();++i) {
	int res = intersect(ray, line2(pl[i], pl[(i+1)%pl.size()]), pp, t);
	if(res) count++;
    }

    if (count % 2 == 0) return 0;
    else return 1;
}
/*|--------------------------------------------------------------------------*/
/*| point containment test using Hormann winding number test                 */
/*| see the paper, "The Point-in-polygon problem for arbitrary polygons",    */
/*| Journal computational geometry, 1999.                                    */
/*|--------------------------------------------------------------------------*/
int kai_contain(const std::vector<vec2>& P, const vec2& R)
{
#define __MY_DET_NEW(p,r,i, nxt) ((p[i][0]-r[0])*(p[nxt][1]-r[1]) - (p[nxt][0]-r[0])*(p[i][1]-r[1]))

    int w = 0;
    for (int i = 0 ; i < P.size() ;++i) {
		int nxt = (i + 1 == P.size()) ? 0 : i + 1;
		if (P[i][1] < R[1] == P[nxt][1] >= R[1]) { //| crossing
	    if (P[i][0] >= R[0]) {
		if (P[nxt][0] > R[0]) {
			w = w + 2 * (P[nxt][1] > P[i][1]) - 1;
		} else {
			if ((__MY_DET_NEW(P, R, i, nxt) > 0) == (P[nxt][1] > P[i][1]))
				w = w + 2 * (P[nxt][1] > P[i][1]) - 1;
		}
	    } else {
		if (P[nxt][0] > R[0])
			if ((__MY_DET_NEW(P, R, i, nxt) > 0) == (P[nxt][1] > P[i][1]))
				w = w + 2 * (P[nxt][1] > P[i][1]) - 1;
	    }
	}
    }
    return w;
}
int kai_contain(const graphics::vector<vec2>& P, const vec2& R)
{
    #define __MY_DET(p,r,i) ((p[i][0]-r[0])*(p[i+1][1]-r[1]) - (p[i+1][0]-r[0])*(p[i][1]-r[1]))

    int w = 0;
    for (int i = 0 ; i < P.size() ;++i) {
	if (P[i][1] < R[1] == P[i+1][1] >= R[1]) { //| crossing
	    if (P[i][0] >= R[0]) {
		if (P[i+1][0] > R[0]) {
		    w = w + 2 * (P[i+1][1] > P[i][1]) - 1;
		} else {
		    if ((__MY_DET(P,R,i) > 0) == (P[i+1][1] > P[i][1]))
			w = w + 2 * (P[i+1][1] > P[i][1]) - 1;
		}
	    } else {
		if (P[i+1][0] > R[0])
		    if ((__MY_DET(P,R,i) > 0) == (P[i+1][1] > P[i][1]))
			w = w + 2 * (P[i+1][1] > P[i][1]) - 1;
	    }
	}
    }
    return w;
}
real ransac_line(const std::vector<vec2>& points, line2& l)
{
    real err;

    real count = (real)points.size();

    real Sx = 0;	//| sum of x
    real Sy = 0;
    real Sxy = 0;
    real Sx2 = 0;

    for (int i = 0; i < points.size() ;++i)
    {
	Sx   += points[i][0];
	Sy   += points[i][1];
	Sxy  += points[i][0] * points[i][1];
	Sx2  += points[i][0] * points[i][0];
    }

    real a = (count * Sxy - Sx * Sy) / (count * Sx2 - Sx * Sx);
    real b = (Sx2 * Sy - Sxy * Sx) / (count * Sx2 - Sx * Sx);

    if ( fabs (a) <= 1.0 ) {                    
	/*| primarily in x-direction */
	l.p[0] = points[0][0];
	l.p[1] = l.p[0] * a + b;
	l.q[0] = points[points.size()-1][0];
	l.q[1] = l.q[0] * a + b;

	err = 0.0;
	for (int i = 0 ; i < points.size() ;++i)
	    err += fabs( points[i][1] - a * points[i][0] - b);
    } else if ( fabs(a) > 500.0 ) {
	
	l.p[0] = points[0][0];
	l.p[1] = points[0][1];
	l.q[0] = l.p[0];
	l.q[1] = points[points.size()-1][1];

	err = 0.0;
	for (int i = 0; i < points.size() ;++i)
	    err += fabs( points[i][0] - points[0][0]);
    } else {
	/*| primarily in y-direction */
	l.p[1] = points[0][1];
	l.p[0] = (l.p[1] - b) / a;
	l.q[1] = points[points.size()-1][1];
	l.q[0] = (l.q[1] - b) / a;
	err = 0.0;
	for (int i = 0; i < points.size() ;++i)
	    err += fabs( points[i][0] - (points[i][1] - b) / a );
    }

    return (err / count);

}

real line_error(const std::vector<vec3>& points, line& l)
{
	real err = 0;

	real count = (real)points.size();

	for (int i = 0; i < points.size(); ++i)
	{
		vec3 p = l.get_closest_point(points[i]);
		err += norm(p - points[i]);
	}


	return (err / count);

}


/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*| implicit_line :                                                          */
/*|                                                                          */
/*|  line equation ax + by + c = 0                                           */
/*|  where a^2 + b^2 = 1                                                     */
/*|__________________________________________________________________________*/
 implicit_line::implicit_line(const vec2& _e1, const vec2& _e2) : e1(_e1), e2(_e2)
    {
	vec3 t1(e1[0], e1[1], 1);
	vec3 t2(e2[0], e2[1], 1);
	vec3 ret = cross(t1, t2);

	real n = sqrt(ret[0]*ret[0] + ret[1]*ret[1]);

	if (n == 0.0) {
	    print(e1);
	    print(e2);
	    fatal("implicit_line::divide by zero\n");
	}

	ret /= n;

	a = ret[0];
	b = ret[1];
	c = ret[2];
    }

 


 void implicit_line::set(const vec2& aa, const vec2& bb)
    {
	e1 = aa; e2 = bb;

	vec3 t1(e1[0], e1[1], 1);
	vec3 t2(e2[0], e2[1], 1);
	vec3 ret = cross(t1, t2);

	real n = sqrt(ret[0]*ret[0] + ret[1]*ret[1]);

	if (n == 0.0) {
	    print(e1);
	    print(e2);
	    fatal("implicit_line::divide by zero\n");
	}

	ret /= n;

	a = ret[0];
	b = ret[1];
	c = ret[2];
    }

/*|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*|these operators show if the point is above or below the line input        */
/*|__________________________________________________________________________*/

int operator == (const vec2& point, const implicit_line& l)
{
    real tmp = l.dist(point);
    return (fabs(tmp) <= user_epsilon);
}

int operator < (const vec2& point, const implicit_line& l)
{
    return (l.dist(point) < -user_epsilon);
}

int operator > (const vec2& point, const implicit_line& l)
{
    return (l.dist(point) > user_epsilon);
}


#define outcode int

const int RIGHT = 8;  //1000
const int TOP = 4;    //0100
const int LEFT = 2;   //0010
const int BOTTOM = 1; //0001
 
//Compute the bit code for a point (x, y) using the clip rectangle
//bounded diagonally by (box.minimum[0], box.minimum[1]), and (box.maximum[0], box.maximum[1])
outcode ComputeOutCode (double x, double y, const box2& box)
{
	outcode code = 0;
	if (y > box.maximum[1])              //above the clip window
		code |= TOP;
	else if (y < box.minimum[1])         //below the clip window
		code |= BOTTOM;
	if (x > box.maximum[0])              //to the right of clip window
		code |= RIGHT;
	else if (x < box.minimum[0])         //to the left of clip window
		code |= LEFT;
	return code;
}
 
//Cohen?Sutherland clipping algorithm clips a line from
//P0 = (x0, y0) to P1 = (x1, y1) against a rectangle box
void LineRectClip(double& x0, double& y0,double& x1, double& y1, const box2& box)
{
	//Outcodes for P0, P1, and whatever point lies outside the clip rectangle
	outcode outcode0, outcode1, outcodeOut;
	bool accept = false, done = false;
 
	//compute outcodes
	outcode0 = ComputeOutCode (x0, y0, box);
	outcode1 = ComputeOutCode (x1, y1, box);
 
	do{
		if (!(outcode0 | outcode1))      //logical or is 0. Trivially accept and get out of loop
		{
			accept = true;
			done = true;
		}
		else if (outcode0 & outcode1)//logical and is not 0. Trivially reject and get out of loop
                {
			done = true;
                }
 
		else
		{
			//failed both tests, so calculate the line segment to clip
			//from an outside point to an intersection with clip edge
			double x, y;
			//At least one endpoint is outside the clip rectangle; pick it.
			outcodeOut = outcode0? outcode0: outcode1;
			//Now find the intersection point;
			//use formulas y = y0 + slope * (x - x0), x = x0 + (1/slope)* (y - y0)
			if (outcodeOut & TOP)          //point is above the clip rectangle
			{
				x = x0 + (x1 - x0) * (box.maximum[1] - y0)/(y1 - y0);
				y = box.maximum[1];
			}
			else if (outcodeOut & BOTTOM)  //point is below the clip rectangle
			{
				x = x0 + (x1 - x0) * (box.minimum[1] - y0)/(y1 - y0);
				y = box.minimum[1];
			}
			else if (outcodeOut & RIGHT)   //point is to the right of clip rectangle
			{
				y = y0 + (y1 - y0) * (box.maximum[0] - x0)/(x1 - x0);
				x = box.maximum[0];
			}
			else if (outcodeOut & LEFT)                         //point is to the left of clip rectangle
			{
				y = y0 + (y1 - y0) * (box.minimum[0] - x0)/(x1 - x0);
				x = box.minimum[0];
			}
			//Now we move outside point to intersection point to clip
			//and get ready for next pass.
			if (outcodeOut == outcode0)
			{
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode (x0, y0, box);
			}
			else 
			{
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode (x1, y1, box);
			}
		}
	}while (!done); 
}

static void UniformSample(int num_samples, int total_samples, std::vector<int> *samples, std::uniform_int_distribution<int>& distribution) {
    samples->resize(0);

	static std::default_random_engine generator;
	static std::mutex mtx;

	while (samples->size() < num_samples) {
		mtx.lock();
		int sample = distribution(generator);
		mtx.unlock();
		bool found = false;
		for (int j = 0; j < samples->size(); ++j) {
			found = (*samples)[j] == sample;
			if (found) {
				break;
			}
		}
		if (!found) {
			samples->push_back(sample);
		}
	}
}

static unsigned int IterationsRequired(int min_samples,
                        real outliers_probability,
                        real inlier_ratio) {
  return static_cast<unsigned int>(
      ::log(outliers_probability) / ::log(1.0 - ::pow(inlier_ratio, min_samples)));
}

static bool plane_estimate(std::vector<int>& sample, const std::vector<vec3>& samples, plane& pl)
{
	vec3 p1 = samples[sample[0]];
	vec3 p2 = samples[sample[1]];
	vec3 p3 = samples[sample[2]];
	
	line l(p1,p2);

	if (l.is_on(p3, user_epsilon)) {
		return false;
	}
	vec3 dir1 = p2-p1;
	vec3 dir2 = p3-p2;
	vec3 n = unit(cross(dir1,dir2));
	vec3 pnt = (p1 + p2 + p3)/3.0;
	pl = plane(n, pnt);
	return true;
}

static bool circle_estimate(std::vector<int>& sample, const std::vector<vec2>& samples, vec3& circle)
{
	vec2 p1 = samples[sample[0]];
	vec2 p2 = samples[sample[1]];
	vec2 p3 = samples[sample[2]];
	vec2 cen = circumcenter(p1, p2, p3);
	circle = vec3(cen[0], cen[1], norm(cen - p1));
	return true;
}

real  least_square_fit(const std::vector<vec3>& points, plane& pl)
{
	fmatrix A(points.size(), 4);

	for (int i = 0; i < points.size(); ++i) {
		A(i, 0) = points[i][0];
		A(i, 1) = points[i][1];
		A(i, 2) = points[i][2];
		A(i, 3) = 1.0;
	}

	fsvdmatrix svd(A);

	

	std::vector<real>  output(4);
	for (int i = 0; i < output.size(); i++) {

		output[i] = svd.V_(i, 3);
	}
	vec3 a = vec3(output[0], output[1], output[2]);
	real d = -output[3];
	real s = norm(a);
	d = d / s;
	a = a / s;
	pl = plane(a, d);
	real sum_d = 0;
	for (int i = 0; i < points.size(); i++) {
		sum_d += fabs(pl.signed_distance(points[i]));
	}
	sum_d = sum_d / real(points.size());
	return sum_d;
}


real eval_conic(const std::vector<double>& output, const vec2& pt)
{
	real x = pt[0];
	real y = pt[1];
	return x * x*output[0] + x * y*output[1] + y * y*output[2] + x * output[3] + y * output[4] + output[5];
}
// Ax^2 + Bxy + Cy^2 + Dx + Ey + F = 0
// return error
real  least_square_ellipse_fit(const std::vector<vec2>& points, std::vector<double>& output)
{
	fmatrix A(points.size(), 6);

	for (int i = 0; i < points.size(); ++i) {
		A(i, 0) = points[i][0] * points[i][0];
		A(i, 1) = points[i][0] * points[i][1];
		A(i, 2) = points[i][1] * points[i][1];
		A(i, 3) = points[i][0];
		A(i, 4) = points[i][1];
		A(i, 5) = 1.0;
	}

	fsvdmatrix svd(A);

	int ith = 5;

	output.resize(6);
	for (int i = 0; i < output.size(); i++) {

		output[i] = svd.V_(i, 5);
	}

	real sum_d = 0;
	for (int i = 0; i < points.size(); i++) {
		real tmp = eval_conic(output, points[i]);
		sum_d += fabs(tmp);
	}
	sum_d = sum_d / real(points.size());
	return sum_d;
}
real  least_square_fit(const std::vector<vec3>& points, line& ll)
{
	vec3 sum(0);
	for (int i = 0; i < points.size(); i++) {
		sum += points[i];
	}
	sum /= real(points.size());

	fmatrix A(points.size(), 3);

	for (int i = 0; i < points.size(); ++i) {
		vec3 sub = points[i] - sum;

		A(i, 0) = sum[0];
		A(i, 1) = sum[1];
		A(i, 2) = sum[2];
	}

	fsvdmatrix svd(A);

	vec3 dir(svd.V_(0, 0), svd.V_(1, 0), svd.V_(2, 0));
	line l(sum, sum + dir);
	ll = l;

	real sum_d = 0;
	for (int i = 0; i < points.size(); i++) {
		vec3 p = ll.get_closest_point(points[i]);
		sum_d += norm(p - points[i]);
	}
	sum_d = sum_d / real(points.size());
	return sum_d;
}


class Data
{
public:

	int n;
	double *X;		//space is allocated in the constructors
	double *Y;		//space is allocated in the constructors
	double meanX, meanY;

	// constructors
	Data();
	Data(int N);
	Data(int N, double X[], double Y[]);
	Data(const std::vector<vec2>& points);

	// routines
	void means(void);
	void center(void);
	void scale(void);
	void print(void);

	// destructors
	~Data();
};


/************************************************************************
			BODY OF THE MEMBER ROUTINES
************************************************************************/
// Default constructor
Data::Data()
{
	n = 0;
	X = new double[n];
	Y = new double[n];
	for (int i = 0; i < n; i++)
	{
		X[i] = 0.;
		Y[i] = 0.;
	}
}

// Constructor with assignment of the field N
Data::Data(int N)
{
	n = N;
	X = new double[n];
	Y = new double[n];

	for (int i = 0; i < n; i++)
	{
		X[i] = 0.;
		Y[i] = 0.;
	}
}

// Constructor with assignment of each field
Data::Data(int N, double dataX[], double dataY[])
{
	n = N;
	X = new double[n];
	Y = new double[n];

	for (int i = 0; i < n; i++)
	{
		X[i] = dataX[i];
		Y[i] = dataY[i];
	}
}
Data::Data(const std::vector<vec2>& points)
{
	n = points.size();
	X = new double[n];
	Y = new double[n];

	for (int i = 0; i < n; i++)
	{
		X[i] = points[i][0];
		Y[i] = points[i][1];
	}
}
// Routine that computes the x- and y- sample means (the coordinates of the centeroid)

void Data::means(void)
{
	meanX = 0.; meanY = 0.;

	for (int i = 0; i < n; i++)
	{
		meanX += X[i];
		meanY += Y[i];
	}
	meanX /= n;
	meanY /= n;
}

// Routine that centers the data set (shifts the coordinates to the centeroid)

void Data::center(void)
{
	double sX = 0., sY = 0.;
	int i;

	for (i = 0; i < n; i++)
	{
		sX += X[i];
		sY += Y[i];
	}
	sX /= n;
	sY /= n;

	for (i = 0; i < n; i++)
	{
		X[i] -= sX;
		Y[i] -= sY;
	}
	meanX = 0.;
	meanY = 0.;
}

// Routine that scales the coordinates (makes them of order one)

void Data::scale(void)
{
	double sXX = 0., sYY = 0., scaling;
	int i;

	for (i = 0; i < n; i++)
	{
		sXX += X[i] * X[i];
		sYY += Y[i] * Y[i];
	}
	scaling = sqrt((sXX + sYY) / n / 2.0);

	for (i = 0; i < n; i++)
	{
		X[i] /= scaling;
		Y[i] /= scaling;
	}
}

// Printing routine

void Data::print(void)
{
	/*cout << endl << "The data set has " << n << " points with coordinates :" << endl;

	for (int i = 0; i < n - 1; i++) cout << setprecision(7) << "(" << X[i] << "," << Y[i] << "), ";

	cout << "(" << X[n - 1] << "," << Y[n - 1] << ")\n";*/
}

// Destructor
Data::~Data()
{
	delete[] X;
	delete[] Y;
}
//
//						 circle.h
//
/************************************************************************
			DECLARATION OF THE CLASS CIRCLE
************************************************************************/
// Class for Circle
// A circle has 7 fields: 
//     a, b, r (of type double), the circle parameters
//     s (of type double), the estimate of sigma (standard deviation)
//     g (of type double), the norm of the gradient of the objective function
//     i and j (of type int), the iteration counters (outer and inner, respectively)

class Circle
{
public:

	// The fields of a Circle
	double a, b, r, s, g, Gx, Gy;
	int i, j;

	// constructors
	Circle();
	Circle(double aa, double bb, double rr);

	// routines
	void print(void);

	// no destructor we didn't allocate memory by hand.
};


/************************************************************************
			BODY OF THE MEMBER ROUTINES
************************************************************************/
// Default constructor

Circle::Circle()
{
	a = 0.; b = 0.; r = 1.; s = 0.; i = 0; j = 0;
}

// Constructor with assignment of the circle parameters only

Circle::Circle(double aa, double bb, double rr)
{
	a = aa; b = bb; r = rr;
}

// Printing routine

void Circle::print(void)
{
	//cout << endl;
	//cout << setprecision(10) << "center (" << a << "," << b << ")  radius "
	//	<< r << "  sigma " << s << "  gradient " << g << "  iter " << i << "  inner " << j << endl;
}
template<typename T>
inline T SQR(T t) { return t * t; };
const double One = 1.0, Two = 2.0, Three = 3.0, Four = 4.0, Five = 5.0, Six = 6.0, Ten = 10.0;
double Sigma(Data& data, Circle& circle)
{
	double sum = 0., dx, dy;

	for (int i = 0; i < data.n; i++)
	{
		dx = data.X[i] - circle.a;
		dy = data.Y[i] - circle.b;
		sum += SQR(sqrt(dx*dx + dy * dy) - circle.r);
	}
	return sqrt(sum / data.n);
}
Circle CircleFitByTaubin(Data& data)
/*
	  Circle fit to a given set of data points (in 2D)

	  This is an algebraic fit, due to Taubin, based on the journal article

	  G. Taubin, "Estimation Of Planar Curves, Surfaces And Nonplanar
				  Space Curves Defined By Implicit Equations, With
				  Applications To Edge And Range Image Segmentation",
				  IEEE Trans. PAMI, Vol. 13, pages 1115-1138, (1991)

	  Input:  data     - the class of data (contains the given points):

		  data.n   - the number of data points
		  data.X[] - the array of X-coordinates
		  data.Y[] - the array of Y-coordinates

	 Output:
			   circle - parameters of the fitting circle:

		   circle.a - the X-coordinate of the center of the fitting circle
		   circle.b - the Y-coordinate of the center of the fitting circle
		   circle.r - the radius of the fitting circle
		   circle.s - the root mean square error (the estimate of sigma)
		   circle.j - the total number of iterations

	 The method is based on the minimization of the function

				  sum [(x-a)^2 + (y-b)^2 - R^2]^2
			  F = -------------------------------
					  sum [(x-a)^2 + (y-b)^2]

	 This method is more balanced than the simple Kasa fit.

	 It works well whether data points are sampled along an entire circle or
	 along a small arc.

	 It still has a small bias and its statistical accuracy is slightly
	 lower than that of the geometric fit (minimizing geometric distances),
	 but slightly higher than that of the very similar Pratt fit.
	 Besides, the Taubin fit is slightly simpler than the Pratt fit

	 It provides a very good initial guess for a subsequent geometric fit.

	   Nikolai Chernov  (September 2012)

*/
{
	int i, iter, IterMAX = 99;

	double Xi, Yi, Zi;
	double Mz, Mxy, Mxx, Myy, Mxz, Myz, Mzz, Cov_xy, Var_z;
	double A0, A1, A2, A22, A3, A33;
	double Dy, xnew, x, ynew, y;
	double DET, Xcenter, Ycenter;

	Circle circle;

	data.means();   // Compute x- and y- sample means (via a function in the class "data")

//     computing moments 

	Mxx = Myy = Mxy = Mxz = Myz = Mzz = 0.;

	for (i = 0; i < data.n; i++)
	{
		Xi = data.X[i] - data.meanX;   //  centered x-coordinates
		Yi = data.Y[i] - data.meanY;   //  centered y-coordinates
		Zi = Xi * Xi + Yi * Yi;

		Mxy += Xi * Yi;
		Mxx += Xi * Xi;
		Myy += Yi * Yi;
		Mxz += Xi * Zi;
		Myz += Yi * Zi;
		Mzz += Zi * Zi;
	}
	Mxx /= data.n;
	Myy /= data.n;
	Mxy /= data.n;
	Mxz /= data.n;
	Myz /= data.n;
	Mzz /= data.n;

	//      computing coefficients of the characteristic polynomial

	Mz = Mxx + Myy;
	Cov_xy = Mxx * Myy - Mxy * Mxy;
	Var_z = Mzz - Mz * Mz;
	A3 = Four * Mz;
	A2 = -Three * Mz*Mz - Mzz;
	A1 = Var_z * Mz + Four * Cov_xy*Mz - Mxz * Mxz - Myz * Myz;
	A0 = Mxz * (Mxz*Myy - Myz * Mxy) + Myz * (Myz*Mxx - Mxz * Mxy) - Var_z * Cov_xy;
	A22 = A2 + A2;
	A33 = A3 + A3 + A3;

	//    finding the root of the characteristic polynomial
	//    using Newton's method starting at x=0  
	//     (it is guaranteed to converge to the right root)

	for (x = 0., y = A0, iter = 0; iter < IterMAX; iter++)  // usually, 4-6 iterations are enough
	{
		Dy = A1 + x * (A22 + A33 * x);
		xnew = x - y / Dy;
		if ((xnew == x) || (!isfinite(xnew))) break;
		ynew = A0 + xnew * (A1 + xnew * (A2 + xnew * A3));
		if (abs(ynew) >= abs(y))  break;
		x = xnew;  y = ynew;
	}

	//       computing paramters of the fitting circle

	DET = x * x - x * Mz + Cov_xy;
	Xcenter = (Mxz*(Myy - x) - Myz * Mxy) / DET / Two;
	Ycenter = (Myz*(Mxx - x) - Mxz * Mxy) / DET / Two;

	//       assembling the output

	circle.a = Xcenter + data.meanX;
	circle.b = Ycenter + data.meanY;
	circle.r = sqrt(Xcenter*Xcenter + Ycenter * Ycenter + Mz);
	circle.s = Sigma(data, circle);
	circle.i = 0;
	circle.j = iter;  //  return the number of iterations, too

	return circle;
}

Circle CircleFitByHyper(Data& data)
/*
	  Circle fit to a given set of data points (in 2D)

	  This is an algebraic fit based on the journal article

	  A. Al-Sharadqah and N. Chernov, "Error analysis for circle fitting algorithms",
	  Electronic Journal of Statistics, Vol. 3, pages 886-911, (2009)

	  It is an algebraic circle fit with "hyperaccuracy" (with zero essential bias).
	  The term "hyperaccuracy" first appeared in papers by Kenichi Kanatani around 2006

	  Input:  data     - the class of data (contains the given points):

		  data.n   - the number of data points
		  data.X[] - the array of X-coordinates
		  data.Y[] - the array of Y-coordinates

	 Output:
			   circle - parameters of the fitting circle:

		   circle.a - the X-coordinate of the center of the fitting circle
		   circle.b - the Y-coordinate of the center of the fitting circle
		   circle.r - the radius of the fitting circle
		   circle.s - the root mean square error (the estimate of sigma)
		   circle.j - the total number of iterations

	 This method combines the Pratt and Taubin fits to eliminate the essential bias.

	 It works well whether data points are sampled along an entire circle or
	 along a small arc.

	 Its statistical accuracy is theoretically higher than that of the Pratt fit
	 and Taubin fit, but practically they all return almost identical circles
	 (unlike the Kasa fit that may be grossly inaccurate).

	 It provides a very good initial guess for a subsequent geometric fit.

	   Nikolai Chernov  (September 2012)

*/
{
	int i, iter, IterMAX = 99;

	double Xi, Yi, Zi;
	double Mz, Mxy, Mxx, Myy, Mxz, Myz, Mzz, Cov_xy, Var_z;
	double A0, A1, A2, A22;
	double Dy, xnew, x, ynew, y;
	double DET, Xcenter, Ycenter;

	Circle circle;

	data.means();   // Compute x- and y- sample means (via a function in the class "data") 

//     computing moments 

	Mxx = Myy = Mxy = Mxz = Myz = Mzz = 0.;

	for (i = 0; i < data.n; i++)
	{
		Xi = data.X[i] - data.meanX;   //  centered x-coordinates
		Yi = data.Y[i] - data.meanY;   //  centered y-coordinates
		Zi = Xi * Xi + Yi * Yi;

		Mxy += Xi * Yi;
		Mxx += Xi * Xi;
		Myy += Yi * Yi;
		Mxz += Xi * Zi;
		Myz += Yi * Zi;
		Mzz += Zi * Zi;
	}
	Mxx /= data.n;
	Myy /= data.n;
	Mxy /= data.n;
	Mxz /= data.n;
	Myz /= data.n;
	Mzz /= data.n;

	//    computing the coefficients of the characteristic polynomial

	Mz = Mxx + Myy;
	Cov_xy = Mxx * Myy - Mxy * Mxy;
	Var_z = Mzz - Mz * Mz;

	A2 = Four * Cov_xy - Three * Mz*Mz - Mzz;
	A1 = Var_z * Mz + Four * Cov_xy*Mz - Mxz * Mxz - Myz * Myz;
	A0 = Mxz * (Mxz*Myy - Myz * Mxy) + Myz * (Myz*Mxx - Mxz * Mxy) - Var_z * Cov_xy;
	A22 = A2 + A2;

	//    finding the root of the characteristic polynomial
	//    using Newton's method starting at x=0  
	//     (it is guaranteed to converge to the right root)

	for (x = 0., y = A0, iter = 0; iter < IterMAX; iter++)  // usually, 4-6 iterations are enough
	{
		Dy = A1 + x * (A22 + 16.*x*x);
		xnew = x - y / Dy;
		if ((xnew == x) || (!isfinite(xnew))) break;
		ynew = A0 + xnew * (A1 + xnew * (A2 + Four * xnew*xnew));
		if (abs(ynew) >= abs(y))  break;
		x = xnew;  y = ynew;
	}

	//    computing paramters of the fitting circle

	DET = x * x - x * Mz + Cov_xy;
	Xcenter = (Mxz*(Myy - x) - Myz * Mxy) / DET / Two;
	Ycenter = (Myz*(Mxx - x) - Mxz * Mxy) / DET / Two;

	//       assembling the output

	circle.a = Xcenter + data.meanX;
	circle.b = Ycenter + data.meanY;
	circle.r = sqrt(Xcenter*Xcenter + Ycenter * Ycenter + Mz - x - x);
	circle.s = Sigma(data, circle);
	circle.i = 0;
	circle.j = iter;  //  return the number of iterations, too

	return circle;
}

real  least_square_circle_fit(const std::vector<vec2>& points, vec3& circle)
{
	
	Data dat(points);
	Circle c = CircleFitByHyper(dat);
	circle = vec3(c.a, c.b, c.r);
	vec2 cen(c.a, c.b);
	double sum = 0;
	for (int i = 0; i < points.size(); i++) {
		real d = norm(points[i] - cen);
		d = fabs(d - c.r);
		sum += d;
	}
	return sum/real(points.size());

}
static real score(plane& pl, const std::vector<vec3>& pnts, int & inlier_cnt, std::vector<vec3>& inliers, real max_error)
{
	inlier_cnt = 0;
	real sum_err = 0;
	for (int i = 0 ; i < pnts.size() ; i++) {
		real d = fabs(pl.signed_distance(pnts[i]));
		
		if (d < max_error) {
			inliers.push_back(pnts[i]);
			inlier_cnt++;
			sum_err += d;
		}
	}
	if (inlier_cnt == 0) return HUGE_VAL;
	return sum_err/(real)inlier_cnt;
}

static real score(vec3 circle, const std::vector<vec2>& pnts, int & inlier_cnt, std::vector<vec2>& inliers, real max_error)
{
	inlier_cnt = 0;
	real sum_err = 0;
	vec2 cen(circle[0], circle[1]);
	real radi = circle[2];
	for (int i = 0; i < pnts.size(); i++) {
		real d = norm(pnts[i] - cen);
		d = fabs(d - radi);

		if (d < max_error) {
			inliers.push_back(pnts[i]);
			inlier_cnt++;
			sum_err += d;
		}
	}
	if (inlier_cnt == 0) return HUGE_VAL;
	return sum_err / (real)inlier_cnt;
}

static plane RobustPlaneEstimate(const std::vector<vec3>& samples, real max_error, real outlier_pro = 0.001) {

	size_t iteration = 0;
	const size_t min_samples = 3;
	const size_t total_samples = samples.size();

	size_t max_iterations = 1000;
	const size_t really_max_iterations = 1000;

	plane best_model(vec3(1,0,0));
	real best_cost = HUGE_VAL;
	real best_inlier_ratio = 0.0;

	// In this robust estimator, the scorer always works on all the data points
	// at once. So precompute the list ahead of time.
	std::vector<int> all_samples;
	for (int i = 0; i < total_samples; ++i) {
		all_samples.push_back(i);
	}
	std::uniform_int_distribution<int> distribution(0,total_samples-1);
	std::vector<int> sample;
	std::vector<vec3> final_inliers;
	for (iteration = 0;
		iteration < max_iterations &&
		iteration < really_max_iterations; ++iteration) 
	{
		sample.clear();
		UniformSample(min_samples, total_samples, &sample, distribution);

		plane pl;
		std::vector<vec3> inliers;
		bool suc = plane_estimate(sample, samples, pl);
		if (!suc) continue;
		
		int inlier_cnt = 0;
		real cost = score(pl, samples, inlier_cnt, inliers, max_error);
		if (inlier_cnt < 4) continue;
		//cost = least_square_fit(inliers, pl);
		if (cost <best_cost) {
			best_cost = cost;
			best_inlier_ratio = inlier_cnt / float(total_samples);
			best_model = pl;
			final_inliers = inliers;
			if (best_inlier_ratio)
				max_iterations = IterationsRequired(min_samples, 
					outlier_pro,
												best_inlier_ratio);
		}
	}

	return best_model;
}

static plane RobustPlaneEstimateAsNumber(const std::vector<vec3>& samples, real max_error, real outlier_pro = 0.001) {

	size_t iteration = 0;
	const size_t min_samples = 3;
	const size_t total_samples = samples.size();
	int    best_inlier_count = 0;
	size_t max_iterations = 1000;
	const size_t really_max_iterations = 1000;

	plane best_model;
	real best_cost = HUGE_VAL;
	real best_inlier_ratio = 0.0;

	// In this robust estimator, the scorer always works on all the data points
	// at once. So precompute the list ahead of time.
	std::vector<int> all_samples;
	for (int i = 0; i < total_samples; ++i) {
		all_samples.push_back(i);
	}
	std::uniform_int_distribution<int> distribution(0, total_samples - 1);
	std::vector<int> sample;
	std::vector<vec3> final_inliers;
	for (iteration = 0;
		iteration < max_iterations &&
		iteration < really_max_iterations; ++iteration)
	{
		sample.clear();
		UniformSample(min_samples, total_samples, &sample, distribution);

		plane pl;
		std::vector<vec3> inliers;
		bool suc = plane_estimate(sample, samples, pl);
		if (!suc) continue;

		int inlier_cnt = 0;
		real cost = score(pl, samples, inlier_cnt, inliers, max_error);
		if (inlier_cnt < 4) continue;
		cost = least_square_fit(inliers, pl);
		if (best_inlier_count < inliers.size()) {
			best_cost = cost;
			best_inlier_count = inliers.size();
			best_inlier_ratio = inlier_cnt / float(total_samples);
			best_model = pl;
			final_inliers = inliers;
			if (best_inlier_ratio)
				max_iterations = IterationsRequired(min_samples,
					outlier_pro,
					best_inlier_ratio);
		}
	}

	return best_model;
}


static vec3 RobustCircleEstimateAsNumber(const std::vector<vec2>& samples, real max_error, real outlier_pro = 0.001) {

	size_t iteration = 0;
	const size_t min_samples = 3;
	const size_t total_samples = samples.size();
	int    best_inlier_count = 0;
	size_t max_iterations = 1000;
	const size_t really_max_iterations = 1000;

	vec3 best_model;
	real best_cost = HUGE_VAL;
	real best_inlier_ratio = 0.0;

	// In this robust estimator, the scorer always works on all the data points
	// at once. So precompute the list ahead of time.
	std::vector<int> all_samples;
	for (int i = 0; i < total_samples; ++i) {
		all_samples.push_back(i);
	}
	std::uniform_int_distribution<int> distribution(0, total_samples - 1);
	std::vector<int> sample;
	std::vector<vec2> final_inliers;
	for (iteration = 0;
		iteration < max_iterations &&
		iteration < really_max_iterations; ++iteration)
	{
		sample.clear();
		UniformSample(min_samples, total_samples, &sample, distribution);

		vec3 circle;
		std::vector<vec2> inliers;
		bool suc = circle_estimate(sample, samples, circle);
		if (!suc) continue;

		int inlier_cnt = 0;
		real cost = score(circle, samples, inlier_cnt, inliers, max_error);
		if (inlier_cnt < 4) continue;
		cost = least_square_circle_fit(inliers, circle);
		if (best_inlier_count < inliers.size()) {
			best_cost = cost;
			best_inlier_count = inliers.size();
			best_inlier_ratio = inlier_cnt / float(total_samples);
			best_model = circle;
			final_inliers = inliers;
			if (best_inlier_ratio)
				max_iterations = IterationsRequired(min_samples,
					outlier_pro,
					best_inlier_ratio);
		}
	}

	return best_model;
}
plane ransac_plane(const std::vector<vec3>& points, real max_error, real outlier_pro)
{
	return RobustPlaneEstimate(points, max_error, outlier_pro);
}

plane ransac_plane_as_number(const std::vector<vec3>& points, real max_error, real outlier_pro)
{
	return RobustPlaneEstimateAsNumber(points, max_error, outlier_pro);
}
vec3  ransac_circle(const std::vector<vec2>& points, real max_error, real outlier_pro)
{
	return RobustCircleEstimateAsNumber(points, max_error, outlier_pro);
}

static bool line_estimate(std::vector<int>& sample, const std::vector<vec2>& samples, line2& l)
{
	vec2 p1 = samples[sample[0]];
	vec2 p2 = samples[sample[1]];

	if (norm(p1 - p2) < user_epsilon) return false;

	l = line2(p1, p2);
	return true;
}

static bool line_estimate(std::vector<int>& sample, const std::vector<vec3>& samples, line& l)
{
	vec3 p1 = samples[sample[0]];
	vec3 p2 = samples[sample[1]];

	if (norm(p1 - p2) < user_epsilon) return false;

	l = line(p1, p2);
	return true;
}

static real linescore(line2& pl, const std::vector<vec2>& pnts, int & inlier_cnt, std::vector<vec2>& inliers, real max_error)
{
	inlier_cnt = 0;
	real sum_err = 0;
	for (int i = 0; i < pnts.size(); i++) {
		real d = norm(pl.get_closest_point(pnts[i]) - pnts[i]);

		if (d < max_error) {
			inliers.push_back(pnts[i]);
			inlier_cnt++;
			sum_err += d;
		}
	}
	if (inlier_cnt == 0) return HUGE_VAL;
	return sum_err / (real)inlier_cnt;
}


static real linescore(line& pl, const std::vector<vec3>& pnts, int & inlier_cnt, std::vector<vec3>& inliers, real max_error)
{
	inlier_cnt = 0;
	real sum_err = 0;
	for (int i = 0; i < pnts.size(); i++) {
		real d = norm(pl.get_closest_point(pnts[i]) - pnts[i]);

		if (d < max_error) {
			inliers.push_back(pnts[i]);
			inlier_cnt++;
			sum_err += d;
		}
	}
	if (inlier_cnt == 0) return HUGE_VAL;
	return sum_err / (real)inlier_cnt;
}

static real least_square_fit(const std::vector<vec2>& points, line2& l)
{
	real err;

	real count = (real)points.size();

	real Sx = 0;	//| sum of x
	real Sy = 0;
	real Sxy = 0;
	real Sx2 = 0;

	for (int i = 0; i < points.size(); ++i)
	{
		Sx += points[i][0];
		Sy += points[i][1];
		Sxy += points[i][0] * points[i][1];
		Sx2 += points[i][0] * points[i][0];
	}

	real a = (count * Sxy - Sx * Sy) / (count * Sx2 - Sx * Sx);
	real b = (Sx2 * Sy - Sxy * Sx) / (count * Sx2 - Sx * Sx);

	if (fabs(a) <= 1.0) {
		/*| primarily in x-direction */
		l.p[0] = points[0][0];
		l.p[1] = l.p[0] * a + b;
		l.q[0] = points[points.size() - 1][0];
		l.q[1] = l.q[0] * a + b;

		err = 0.0;
		for (int i = 0; i < points.size(); ++i)
			err += fabs(points[i][1] - a * points[i][0] - b);
	}
	else if (fabs(a) > 500.0) {

		l.p[0] = points[0][0];
		l.p[1] = points[0][1];
		l.q[0] = l.p[0];
		l.q[1] = points[points.size() - 1][1];

		err = 0.0;
		for (int i = 0; i < points.size(); ++i)
			err += fabs(points[i][0] - points[0][0]);
	}
	else {
		/*| primarily in y-direction */
		l.p[1] = points[0][1];
		l.p[0] = (l.p[1] - b) / a;
		l.q[1] = points[points.size() - 1][1];
		l.q[0] = (l.q[1] - b) / a;
		err = 0.0;
		for (int i = 0; i < points.size(); ++i)
			err += fabs(points[i][0] - (points[i][1] - b) / a);
	}

	return (err / count);

}
static line2 RobustLineEstimate(const std::vector<vec2>& samples, real max_error, real outlier_pro = 0.001) {

	size_t iteration = 0;
	const size_t min_samples = 2;
	const size_t total_samples = samples.size();

	size_t max_iterations = 1000;
	const size_t really_max_iterations = 1000;

	line2 best_model;
	real best_cost = HUGE_VAL;
	real best_inlier_ratio = 0.0;

	// In this robust estimator, the scorer always works on all the data points
	// at once. So precompute the list ahead of time.
	std::vector<int> all_samples;
	for (int i = 0; i < total_samples; ++i) {
		all_samples.push_back(i);
	}
	std::uniform_int_distribution<int> distribution(0, total_samples - 1);
	std::vector<int> sample;
	std::vector<vec2> final_inliers;
	for (iteration = 0;
		iteration < max_iterations &&
		iteration < really_max_iterations; ++iteration)
	{
		sample.clear();
		UniformSample(min_samples, total_samples, &sample, distribution);

		line2 pl;
		std::vector<vec2> inliers;
		bool suc = line_estimate(sample, samples, pl);
		if (!suc) continue;
		int inlier_cnt = 0;
		real cost = linescore(pl, samples, inlier_cnt, inliers, max_error);
		line2 ln;
		
		cost = least_square_fit(inliers, pl);

		if (cost <best_cost) {

			best_cost = cost;
			best_inlier_ratio = inlier_cnt / float(total_samples);
			best_model = pl;
			final_inliers = inliers;
			if (best_inlier_ratio)
				max_iterations = IterationsRequired(min_samples,
					outlier_pro,
				best_inlier_ratio);
		}
	}

	return best_model;
}



static line RobustLineEstimate(const std::vector<vec3>& samples, real max_error, real outlier_pro = 0.001) {

	size_t iteration = 0;
	const size_t min_samples = 2;
	const size_t total_samples = samples.size();
	int    best_inlier_count = 0;
	size_t max_iterations = 1000;
	const size_t really_max_iterations = 1000;

	line best_model;
	real best_cost = HUGE_VAL;
	real best_inlier_ratio = 0.0;

	// In this robust estimator, the scorer always works on all the data points
	// at once. So precompute the list ahead of time.
	std::vector<int> all_samples;
	for (int i = 0; i < total_samples; ++i) {
		all_samples.push_back(i);
	}
	std::uniform_int_distribution<int> distribution(0, total_samples - 1);
	std::vector<int> sample;
	std::vector<vec3> final_inliers;
	for (iteration = 0;
		iteration < max_iterations &&
		iteration < really_max_iterations; ++iteration)
	{
		sample.clear();
		UniformSample(min_samples, total_samples, &sample, distribution);

		line pl;
		std::vector<vec3> inliers;
		bool suc = line_estimate(sample, samples, pl);
		if (!suc) continue;
		int inlier_cnt = 0;
		real cost = linescore(pl, samples, inlier_cnt, inliers, max_error);
		line ln;
		if (inlier_cnt < 2) continue;
		cost = least_square_fit(inliers, pl);
		if (best_inlier_count < inliers.size()) {
			best_cost = cost;
			best_inlier_count = inliers.size();
		//if (cost <best_cost) {

			best_cost = cost;
			best_inlier_ratio = inlier_cnt / float(total_samples);
			best_model = pl;
			final_inliers = inliers;
			if (best_inlier_ratio)
				max_iterations = IterationsRequired(min_samples,
					outlier_pro,
					best_inlier_ratio);
		}
	}

	return best_model;
}
line2 ransac_line(const std::vector<vec2>& points, real max_error, real outlier_pro)
{
	return RobustLineEstimate(points, max_error, outlier_pro);
}

line ransac_line(const std::vector<vec3>& points, real max_error, real outlier_pro)
{
	return RobustLineEstimate(points, max_error, outlier_pro);
}

};// namespace