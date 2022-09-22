#pragma once
#include <vector>
#include <typeinfo>
//#include <Windows.h>

// These should really be in the Vector class itself.
typedef __m128 VectorRegister; // SIMD XMM[0-7] structure. We use it for vector registers.
#define SHUFFLEMASK(A0,A1,B2,B3) ( (A0) | ((A1)<<2) | ((B2)<<4) | ((B3)<<6) )
#define VectorLoadAligned(Ptr) _mm_load_ps((const float*) (Ptr))
#define VectorStoreAligned(Vec, Ptr) _mm_store_ps((float*) (Ptr), Vec)
#define VectorReplicate( Vec, ElementIndex )	_mm_shuffle_ps( Vec, Vec, SHUFFLEMASK(ElementIndex,ElementIndex,ElementIndex,ElementIndex) )

struct Transform
{

private:
	Vector3f myPosition = Vector3f::Zero;
	Rotator myRotation = Vector3f::Zero;
	Vector3f myScale = Vector3f::One;
	Transform* myParent = nullptr;
	std::vector<Transform*> myChildren;

	void* myOwner = nullptr;
	const std::type_info* myOwnerType;

public:

	FORCEINLINE Vector3f GetPosition() const { return myPosition; }
	FORCEINLINE Rotator GetRotation() const { return myRotation; }
	FORCEINLINE Vector3f GetScale() const { return myScale; }

	void SetPosition(Vector3f somePosition);
	void SetRotation(Rotator someRotation);
	void SetScale(Vector3f someScale);

	inline void SetParent(Transform& aParent) {
		myParent = &aParent;
	}


	inline const int HasParent(int count = 0) {
		if (myParent)
			return myParent->HasParent(count + 1);

		return count;
	}

	Vector3f GetPosition() { return myPosition; }
	Rotator GetRotation() { return myRotation; }
	Vector3f GetScale() { return myScale; }

	void AddRotation(Rotator someRotation);

	FORCEINLINE Matrix4x4f GetMatrix(bool bNoScale = false) const
	{
		Matrix4x4f Result = Matrix4x4f::CreateIdentityMatrix();

		if (bNoScale)
			Result *= Matrix4x4f::CreateScaleMatrix({ 1, 1, 1 });
		else
			Result *= Matrix4x4f::CreateScaleMatrix(myScale);

		Result *= Matrix4x4f::CreateRollPitchYawMatrix(myRotation);
		Result *= Matrix4x4f::CreateTranslationMatrix(myPosition);


		if (myParent)
		{
			Result *= myParent->GetMatrix(bNoScale);
		}

		return Result;
	}

	inline Transform* GetParent() noexcept {
		return myParent;
	}

	inline std::vector<Transform*>& GetChildren() noexcept {
		return myChildren;
	}

	inline void AddChild(Transform* aTransform)
	{
		if (aTransform->GetParent())
		{
			auto& children = aTransform->GetParent()->GetChildren();
			children.erase(std::remove(children.begin(), children.end(), aTransform), children.end());
		}


		aTransform->SetParent(*this);
		myChildren.push_back(aTransform);
	}


	FORCEINLINE VectorRegister VectorTransformVector(const VectorRegister& VecP, const void* MatrixM) const
	{
		const VectorRegister* M = (const VectorRegister*)MatrixM;
		VectorRegister VTempX, VTempY, VTempZ, VTempW;

		VTempX = VectorReplicate(VecP, 0);
		VTempY = VectorReplicate(VecP, 1);
		VTempZ = VectorReplicate(VecP, 2);
		VTempW = VectorReplicate(VecP, 3);

		VTempX = _mm_mul_ps(VTempX, M[0]);
		VTempY = _mm_mul_ps(VTempY, M[1]);
		VTempZ = _mm_mul_ps(VTempZ, M[2]);
		VTempW = _mm_mul_ps(VTempW, M[3]);

		VTempX = _mm_add_ps(VTempX, VTempY);
		VTempZ = _mm_add_ps(VTempZ, VTempW);
		VTempX = _mm_add_ps(VTempX, VTempZ);

		return VTempX;
	}

	FORCEINLINE Vector4f TransformVector4(const Vector4f& someVector, Matrix4x4f& Matrix) const
	{
		Vector4f Result;
		VectorRegister VecP = VectorLoadAligned(&someVector);
		VectorRegister VecR = VectorTransformVector(VecP, &Matrix);
		VectorStoreAligned(VecR, &Result);
		return Result;
	}

	FORCEINLINE Vector3f TransformPosition(Vector3f& someVector) const
	{
		Matrix4x4f Matrix = GetMatrix();
		return TransformVector4(Vector4f(someVector, 1.0f), Matrix).ToVector3();
	}

	FORCEINLINE Vector3f InverseTransformPosition(Vector3f& someVector) const
	{
		Matrix4x4f Matrix = GetMatrix(true).GetInverse();
		return TransformVector4(Vector4f(someVector, 1.0f), Matrix).ToVector3();
	}



	template<typename Owner>
	void AssignOwner(Owner* anInstance)
	{
		if (!anInstance) return;

		myOwnerType = &typeid(Owner);
		myOwner = (void*)anInstance;
	}



	template<typename Owner>
	Owner* GetOwner() {

		if (!myOwner || !myOwnerType || typeid(Owner) != *myOwnerType) return nullptr;
		return (Owner*)myOwner;
	}
};

#undef SHUFFLEMASK
#undef VectorLoadAligned
#undef VectorStoreAligned
#undef VectorReplicate