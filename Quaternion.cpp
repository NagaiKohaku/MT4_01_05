#include "Quaternion.h"

#include "cmath"

Quaternion Quaternion::operator+(const Quaternion& q) {

	return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion& Quaternion::operator+=(const Quaternion& q) {

	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;

	return *this;
}

Quaternion Quaternion::operator-(const Quaternion& q) {

	return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}

Quaternion Quaternion::operator-() const {
	return Quaternion(-x, -y, -z, -w);
}

Quaternion& Quaternion::operator-=(const Quaternion& q) {

	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;

	return *this;
}

Quaternion Quaternion::operator*(const float& n) {

	return Quaternion(x * n, y * n, z * n, w * n);
}

//積法
Quaternion Multiply(Quaternion lhs, Quaternion rhs) {

	Quaternion result;

	Vector3 lhsVector = { lhs.x,lhs.y,lhs.z };
	Vector3 rhsVector = { rhs.x,rhs.y,rhs.z };

	Vector3 resultVector = Cross(lhsVector, rhsVector) + lhsVector * rhs.w + rhsVector * lhs.w;

	result.w = lhs.w * rhs.w - Dot(lhsVector, rhsVector);
	result.x = resultVector.x;
	result.y = resultVector.y;
	result.z = resultVector.z;

	return result;
}

//乗法単位元
Quaternion IdentityQuaternion() {
	Quaternion result;

	result.x = 0.0f;
	result.y = 0.0f;
	result.z = 0.0f;
	result.w = 1.0f;

	return result;
}

//共役
Quaternion Conjugate(Quaternion quaternion) {
	Quaternion result;

	result.x = -quaternion.x;
	result.y = -quaternion.y;
	result.z = -quaternion.z;
	result.w = quaternion.w;

	return result;
}

//ノルム
float Norm(Quaternion quaternion) {

	float sqW = quaternion.w * quaternion.w;
	float sqX = quaternion.x * quaternion.x;
	float sqY = quaternion.y * quaternion.y;
	float sqZ = quaternion.z * quaternion.z;

	return std::sqrtf(sqW + sqX + sqY + sqZ);
}

//正規化
Quaternion Normalize(Quaternion quaternion) {
	float mag = Norm(quaternion);

	if (mag != 0.0f) {
		return Quaternion(quaternion.x / mag, quaternion.y / mag, quaternion.z / mag, quaternion.w / mag);
	}

	return quaternion;
}

//逆Quaternion
Quaternion Inverse(Quaternion quaternion) {
	Quaternion result;

	Quaternion conjugate = Conjugate(quaternion);

	result.x = conjugate.x / (Norm(quaternion) * Norm(quaternion));
	result.y = conjugate.y / (Norm(quaternion) * Norm(quaternion));
	result.z = conjugate.z / (Norm(quaternion) * Norm(quaternion));
	result.w = conjugate.w / (Norm(quaternion) * Norm(quaternion));

	return result;
}

//内積
float Dot(Quaternion q1, Quaternion q2) {

	return { q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w };
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle) {

	Quaternion result;

	result.w = cosf(angle / 2.0f);
	result.x = axis.x * sinf(angle / 2.0f);
	result.y = axis.y * sinf(angle / 2.0f);
	result.z = axis.z * sinf(angle / 2.0f);

	return result;
}
