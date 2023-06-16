#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
// 正規化
Vector3 Normalize(const Vector3& v);

Matrix4x4 Inverse(Matrix4x4 matrix);