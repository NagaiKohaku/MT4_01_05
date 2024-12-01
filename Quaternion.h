#pragma once
#include "Vector3.h"

struct Quaternion final {
	float x;
	float y;
	float z;
	float w;

	/// ===加法=== ///

	Quaternion operator+(const Quaternion& q);
	Quaternion& operator+=(const Quaternion& q);

	/// === 減法 === ///

	Quaternion operator-(const Quaternion& q);
	Quaternion operator-() const;
	Quaternion& operator-=(const Quaternion& q);

	Quaternion operator*(const float& n);
};

//積法
Quaternion Multiply(Quaternion lhs, Quaternion rhs);

//乗法単位元
Quaternion IdentityQuaternion();

//共役
Quaternion Conjugate(Quaternion quaternion);

//ノルム
float Norm(Quaternion quaternion);

//正規化
Quaternion Normalize(Quaternion quaternion);

//逆Quaternion
Quaternion Inverse(Quaternion quaternion);

//内積
float Dot(Quaternion q1, Quaternion q2);

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);