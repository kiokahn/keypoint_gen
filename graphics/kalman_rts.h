#pragma once

#include <vector>
#include <graphics/vec.h>
#include <graphics/matrix3x3.h>
#include <graphics/quater.h>
namespace graphics
{
std::vector<vec3> kalman_rts(const std::vector<vec3>& pos, const std::vector<real>& t);
std::vector<real> diff(const std::vector<real>& in);
std::vector<vec4> diff(const std::vector<vec4>& in);
std::vector<vec3> smooth(const std::vector<vec3>& in, int filter_size);
real mean(const std::vector<real>& in);
vec3 mean(const std::vector<vec3>& in);
std::vector<vec4> linear_interp(const std::vector<real>&t, const std::vector<vec4>& g, const std::vector<real>&new_t);
std::vector<vec4> linear_quater_interp(const std::vector<real>&t, const std::vector<vec4>& g, const std::vector<real>&new_t);

std::vector<vec3> linear_interp(const std::vector<real>&t, const std::vector<vec3>& g, const std::vector<real>&new_t);
// return residual after registration
real register_directions(const std::vector<vec3>& pangVis,
	const std::vector<vec3>& angImu,
	const std::vector<real>& t,
	real td,
	matrix3x3& Rs,
	vec3& bias);

void alignCameraIMU(std::vector<vec3>& accVis, 
	std::vector<vec4>&qtVis, 
	std::vector<real>& tVis, 
	std::vector<vec3>& accImu, 
	std::vector<real>&  tImu, 
	matrix3x3& Rs, real td);

void estimateAlignment(const std::vector<quater>&qtVis,
	const std::vector<real>&tVis,
	const std::vector<vec3>&angImu,
	const std::vector<real>& tImu,
	matrix3x3& Rs,
	real& td,
	vec3& bg);

real estimateScale(const std::vector<vec3>& accVis,
	const std::vector<vec4>&qtVis,
	const std::vector<vec3>& accImu,
	const std::vector<real>&  t,
	real& scale,
	vec3& bias);
};