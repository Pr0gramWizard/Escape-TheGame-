#include "matrix4D.hpp"

// Normal constructor
Matrix4D::Matrix4D()
{
	// Looping throu the whole Matrix and filling it with zeroes
	for (int i = 0; i < 4 * 4; i++)
	{
		Elements[i] = 0.0f;
	}
}


// Constructor with given diagonal
Matrix4D::Matrix4D(float pDiagonal)
{
	
	for (int i = 0; i < 4 * 4; i++)
		Elements[i] = 0.0f;

		Elements[0 + 0 * 4] = pDiagonal;
		Elements[1 + 1 * 4] = pDiagonal;
		Elements[2 + 2 * 4] = pDiagonal;
		Elements[3 + 3 * 4] = pDiagonal;
}

Matrix4D Matrix4D::Identity()
{
	return Matrix4D(1.0f);
}

/*
	Operator
*/

Matrix4D& operator*(Matrix4D pFirstMatrix, const Matrix4D &pSecondMatrix)
{
	return pFirstMatrix.multiply(pSecondMatrix);
}

Matrix4D & Matrix4D::multiply(const Matrix4D & pOtherMatrix)
{
	Matrix4D Result(0.0f);


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0.0f;

			for (int h = 0; h < 4; h++)
			{
				sum += this->Elements[i + h * 4] * pOtherMatrix.Elements[h + j * 4];
			}

			Result.Elements[i + j * 4] = sum;
		}

	}


	return Result;
}

Matrix4D& Matrix4D::operator*=(const Matrix4D &pOtherMatrix)
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0.0f;

			for (int h = 0; h < 4; h++)
			{
				sum += this->Elements[i + h * 4] * pOtherMatrix.Elements[h + j * 4];
			}

			this->Elements[i + j * 4] = sum;
		}

	}


	return *this;
}

Matrix4D & Matrix4D::lookAt(const Vector3D & Eye, const Vector3D & Center, const Vector3D & Up)
{
	Matrix4D Matrix(1.0f);

	Vector3D F, U, S;

	Vector3D tempEye = Eye;
	Vector3D tempCenter = Center;
	Vector3D tempUp = Up;

	F = tempCenter - Eye;
	F = F.normalize();

	U = tempUp.normalize();

	S = F.crossproduct(U);
	S = S.normalize();

	U = S.crossproduct(F);


	Matrix.Elements[0] = S.x;
	Matrix.Elements[4] = S.y;
	Matrix.Elements[8] = S.z;
	Matrix.Elements[1] = U.x;
	Matrix.Elements[5] = U.y;
	Matrix.Elements[9] = U.z;
	Matrix.Elements[2] = -F.x;
	Matrix.Elements[6] = -F.y;
	Matrix.Elements[10] = -F.z;
	Matrix.Elements[12] = -S.dotproduct(tempEye);
	Matrix.Elements[13] = -U.dotproduct(tempEye);
	Matrix.Elements[14] = -F.dotproduct(tempEye);

	return Matrix;

}

void Matrix4D::Print()
{
	std::clog << Elements[0] << " " << Elements[4] << " " << Elements[8] << " " << Elements[12] << std::endl;
	std::clog << Elements[1] << " " << Elements[5] << " " << Elements[9] << " " << Elements[13] << std::endl;
	std::clog << Elements[2] << " " << Elements[6] << " " << Elements[10] << " " << Elements[14] << std::endl;
	std::clog << Elements[3] << " " << Elements[7] << " " << Elements[11] << " " << Elements[15] << std::endl;
	std::clog << " " << std::endl;
}




Matrix4D Matrix4D::Orthographic(float pLeft, float pRight, float pTop, float pBottom, float pNear, float pFar)
{
	Matrix4D Result(1.0f);

	Result.Elements[0] = 2.0f / (pRight - pLeft);
	Result.Elements[5] = 2.0f / (pTop - pBottom);
	Result.Elements[10] = 2.0f / (pNear - pFar);

	Result.Elements[12] = (pLeft + pRight) / (pLeft - pRight);
	Result.Elements[13] = (pBottom + pTop) / (pBottom - pTop);
	Result.Elements[14] = (pFar + pNear) / (pFar - pNear);

	return Result;


}

Matrix4D Matrix4D::Perspective(float pFieldOfView, float pAspectRatio, float pNear, float pFar)
{
	Matrix4D Result(1.0f);

	Result.Elements[0] = 1.0f / (pAspectRatio * tan((pFieldOfView / 2.0f)));
	Result.Elements[5] = 1.0f / tan((toRadians(0.5f * pFieldOfView)));
	Result.Elements[10] = -((pFar + pNear) / (pFar - pNear));
	Result.Elements[11] = -1.0f;
	Result.Elements[14] = -2.0f * ((pFar + pNear) / (pFar - pNear));

	return Result;
}

Matrix4D Matrix4D::Translation(const Vector3D & pTranslation)
{
	Matrix4D Result(1.0f);

	Result.Elements[4] = pTranslation.x;
	Result.Elements[8] = pTranslation.y;
	Result.Elements[12] = pTranslation.z;
	
	return Result;
}

Matrix4D Matrix4D::Rotation(const Vector3D & pAxis, float pAngle)
{
	Matrix4D Result(1.0f);

	float AngleInRadian = toRadians(pAngle);
	float cosine = cos(AngleInRadian);
	float sine = sin(AngleInRadian);

	float x = pAxis.x;
	float y = pAxis.y;
	float z = pAxis.z;

	Result.Elements[0] = x * (1.0f - cosine) + cosine;
	Result.Elements[1] = x * y * (1.0f - cosine) + z * sine;
	Result.Elements[2] = x * z * (1.0f - cosine) - y * sine;

	Result.Elements[4] = y * x * (1.0f - cosine) - z * sine;
	Result.Elements[5] = y * (1.0f - cosine) + cosine;
	Result.Elements[6] = y * z * (1.0f - cosine) + x * sine;

	Result.Elements[8] = z * x * (1.0f - cosine) + y * sine;
	Result.Elements[9] = z * y * (1.0f - cosine) - x * sine;
	Result.Elements[10] = z * (1.0f - cosine) + cosine;

	return Result;




}

Matrix4D Matrix4D::Scale(const Vector3D & pScale)
{
	Matrix4D Result(1.0f);

	Result.Elements[0] = pScale.x;
	Result.Elements[5] = pScale.y;
	Result.Elements[10] = pScale.z;

	return Result;

}

// Converts degree to radian
float Matrix4D::toRadians(float pAngle)
{
	float PI = 3.14159265358979323846f;
	return pAngle * (PI / 180.0f);
}





