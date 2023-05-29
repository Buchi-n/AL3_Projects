 #pragma once
 #include "Vector3.h"
#include <cmath>
 #include "Matrix4x4.h"

 Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
 //正規化
 Vector3 Normalize(const Vector3& v);
