#ifndef _DUAL_QUAT_H__
#define _DUAL_QUAT_H__

#include "quater.h"

// =============================================================================
namespace graphics {
// =============================================================================

class dual_quat {
    public:

    // -------------------------------------------------------------------------
    /// @name Constructors
    // -------------------------------------------------------------------------

    /// Default constructor generates a dual quaternion with no translation
    /// and no rotation either
	dual_quat()
    {
		dual_quat res = dual_quat_from(quater(1, 0, 0, 0), vec3(0.f, 0.f, 0.f));
        *this = res;
    }


    /// Fill directly the dual quaternion with two quaternion for the non-dual
    /// and dual part
	dual_quat(const quater& q0, const quater& qe)
    {
        _quat_0 = q0;
        _quat_e = qe;
    }

    /// Construct a dual quaternion with a quaternion 'q' which express the
    /// rotation and a translation vector
    dual_quat(const quater& q, const vec3& t)
    {
		dual_quat res = dual_quat_from(q, t);
        *this = res;
    }

    /// Construct from rigid transformation 't'
    /*Dual_quat_cu(const Transfo& t)
    {
        Quat_cu q(t);
        Vec3 translation(t.m[3], t.m[7], t.m[11]);
        Dual_quat_cu res = dual_quat_from(q, translation);
        *this = res;
    }
*/

    // -------------------------------------------------------------------------
    /// @name Methods
    // -------------------------------------------------------------------------

    void normalize()
    {
        float n = (float)norm(_quat_0);
        _quat_0 = _quat_0 / n;
        _quat_e = _quat_e / n;
    }

    /// Transformation of point p with the dual quaternion
    vec3 transform(const vec3& p ) const
    {
        // As the dual quaternions may be the results from a
        // linear blending we have to normalize it :
        float n = norm(_quat_0);
        quater qblend_0 = _quat_0 / n;
		quater qblend_e = _quat_e / n;

        // Translation from the normalized dual quaternion equals :
        // 2.f * qblend_e * conjugate(qblend_0)
        vec3 v0(qblend_0[1], qblend_0[2], qblend_0[3]);
		vec3 ve(qblend_e[1], qblend_e[2], qblend_e[3]);
		vec3 trans = (ve*qblend_0[0] - v0*qblend_e[0] + cross(v0,ve)) * 2.f;

        // Rotate
        return rot(qblend_0,p) + trans;
    }

    /// Rotate a vector with the dual quaternion
    vec3 rotate(const vec3& v) const
    {
        quater tmp = _quat_0;
		tmp = unit(tmp);
        return rot(tmp, v);
    }

	dual_quat dual_quat_from(const quater& q, const vec3& t) const
    {
        float w = -0.5f*( t[0] * q[1] + t[1] * q[2] + t[2] * q[3]);
        float i =  0.5f*(t[0] * q[0] + t[1] * q[3] - t[2] * q[2]);
        float j =  0.5f*(-t[0] * q[3] + t[1] * q[0] + t[2] * q[1]);
        float k =  0.5f*(t[0] * q[2] - t[1] * q[1] + t[2] * q[0]);

        return dual_quat(q, quater(w, i, j, k));
    }

    /// Convert the dual quaternion to a homogenous matrix
    /// N.B: Dual quaternion is normalized before conversion
    //Transfo to_transformation()
    //{
    //    Vec3 t;
    //    float norm = _quat_0.norm();

    //    // Rotation matrix from non-dual quaternion part
    //    Mat3 m = (_quat_0 / norm).to_matrix3();

    //    // translation vector from dual quaternion part:
    //    t.x = 2.f*(-_quat_e.w()*_quat_0.i() + _quat_e.i()*_quat_0.w() - _quat_e.j()*_quat_0.k() + _quat_e.k()*_quat_0.j()) / norm;
    //    t.y = 2.f*(-_quat_e.w()*_quat_0.j() + _quat_e.i()*_quat_0.k() + _quat_e.j()*_quat_0.w() - _quat_e.k()*_quat_0.i()) / norm;
    //    t.z = 2.f*(-_quat_e.w()*_quat_0.k() - _quat_e.i()*_quat_0.j() + _quat_e.j()*_quat_0.i() + _quat_e.k()*_quat_0.w()) / norm;

    //    return Transfo(m, t);
    //}

    // -------------------------------------------------------------------------
    /// @name Operators
    // -------------------------------------------------------------------------

	dual_quat operator+(const dual_quat& dq) const
    {
        return dual_quat(_quat_0 + dq._quat_0, _quat_e + dq._quat_e);
    }

	dual_quat operator*(float scalar) const
    {
        return dual_quat(_quat_0 * scalar, _quat_e * scalar);
    }

    /// Return a dual quaternion with no translation and no rotation
    static dual_quat identity()
    {
        return dual_quat(quater(1.f, 0.f, 0.f, 0.f),
                            vec3(0.f, 0.f, 0.f) );
    }

    // -------------------------------------------------------------------------
    /// @name Getters
    // -------------------------------------------------------------------------

	quater get_dual_part() const { return _quat_e; }

	quater get_non_dual_part() const { return _quat_0; }

	quater translation() const { return _quat_e; }

	quater rotation() const { return _quat_0; }

    void set_rotation( const quater& q ){ _quat_0 = q; }

    // -------------------------------------------------------------------------
    /// @name Attributes
    // -------------------------------------------------------------------------

private:
    /// Non-dual part of the dual quaternion. It also represent the rotation.
    /// @warning If you want to compute the rotation with this don't forget
    /// to normalize the quaternion as it might be the result of a
    /// dual quaternion linear blending
    /// (when overloaded operators like '+' or '*' are used)
    quater _quat_0;

    /// Dual part of the dual quaternion which represent the translation.
    /// translation can be extracted by computing
    /// 2.f * _quat_e * conjugate(_quat_0)
    /// @warning don't forget to normalize quat_0 and quat_e :
    /// quat_0 = quat_0 / || quat_0 || and quat_e = quat_e / || quat_0 ||
	quater _quat_e;
};

}// END Tbx NAMESPACE ==========================================================

#endif // TOOL_BOX_DUAL_QUAT_CU_HPP__
